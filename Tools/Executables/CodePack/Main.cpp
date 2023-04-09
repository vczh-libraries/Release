#include "Codepack.h"

int main(int argc, char* argv[])
{
	Console::SetTitle(L"Vczh CodePack for C++");
	if (argc != 2)
	{
		Console::SetColor(true, false, false, true);
		Console::WriteLine(L"CodePack.exe <config-xml>");
		Console::SetColor(true, true, true, false);
		return 0;
	}

	// load configuration
	auto workingDir = FilePath(atow(argv[1])).GetFolder();
	Ptr<XmlDocument> config;
	{
		Parser parser;
		List<ParsingError> errors;
		InstallDefaultErrorMessageGenerator(parser, errors);
		auto text = ReadFile(atow(argv[1]));
		config = XmlParseDocument(text, parser);

		if (errors.Count() > 0)
		{
			Console::SetColor(true, false, false, true);
			Console::WriteLine(L"Failed to read the input XML file.");
			for (auto error : errors)
			{
				Console::WriteLine(L"[row:" + itow(error.codeRange.start.row + 1) + L"][column:" + itow(error.codeRange.start.column + 1) + L"]: " + error.message);
			}
			Console::SetColor(true, true, true, false);
			return 1;
		}
	}

	Dictionary<WString, Tuple<WString, bool>> categorizedOutput;	// category -> {output file, generate?}
	{
		// get configuration for all categories
		CopyFrom(
			categorizedOutput,
			XmlGetElements(XmlGetElement(config->rootElement, L"output"), L"codepair")
				.Select([&](Ptr<XmlElement> e)
				{
					return Pair(
						XmlGetAttribute(e, L"category")->value.value,
						Tuple(
							XmlGetAttribute(e, L"filename")->value.value,
							XmlGetAttribute(e, L"generate")->value.value == L"true"
						)
					);
				})
		);
	}

	// collect code files
	List<FilePath> unprocessedCppFiles;								// all cpp files need to combine
	List<FilePath> unprocessedHeaderFiles;							// all header files need to combine
	Dictionary<FilePath, LazyList<FilePath>> cachedFileToIncludes;	// file -> directly/indirectly included files
	Group<FilePath, Tuple<WString, FilePath>> conditionOns;			// #ifdef -> files to include
	Group<FilePath, Tuple<WString, FilePath>> conditionOffs;		// #ifndef -> files to include
	{
		// get included folders
		List<FilePath> folders;
		CopyFrom(
			folders,
			XmlGetElements(XmlGetElement(config->rootElement,L"folders"), L"folder")
				.Select([&](Ptr<XmlElement> e)
				{
					return workingDir / XmlGetAttribute(e, L"path")->value.value;
				})
			);

		// get excluded folders
		List<WString> exceptions;
		CopyFrom(
			exceptions,
			XmlGetElements(XmlGetElement(config->rootElement,L"folders"), L"except")
				.Select([&](Ptr<XmlElement> e)
				{
					return XmlGetAttribute(e, L"pattern")->value.value;
				})
			);

		// enumerate all *.cpp files in specified folders
		CopyFrom(
			unprocessedCppFiles,
			From(folders)
				.SelectMany([&](const FilePath& folder) { return GetCppFiles(folder, exceptions); })
				.Distinct()
			);

		// enumerate all *.h files in specified folders
		CopyFrom(
			unprocessedHeaderFiles,
			From(folders)
				.SelectMany([&](const FilePath& folder) { return GetHeaderFiles(folder, exceptions); })
				.Distinct()
			);
	}

	// categorize code files
	Group<WString, FilePath> categorizedCppFiles;					// category -> cpp files
	Group<WString, FilePath> categorizedHeaderFiles;				// category -> header files
	Dictionary<FilePath, WString> inputFileToCategories;			// input file -> category
	{
		// categorize all *.cpp and *.h files
		CategorizeCodeFiles(config, unprocessedCppFiles, categorizedCppFiles, inputFileToCategories);
		CategorizeCodeFiles(config, unprocessedHeaderFiles, categorizedHeaderFiles, inputFileToCategories);
	}

	// collect import files as system include
	Dictionary<WString, FilePath> skippedImportFiles;				// file name -> file path
	for (vint i = 0; i < categorizedOutput.Count(); i++)
	{
		if (!categorizedOutput.Values()[i].get<1>())
		{
			auto category = categorizedOutput.Keys()[i];
			for (auto skippedImportFile : categorizedHeaderFiles[category])
			{
				skippedImportFiles.Add(skippedImportFile.GetName(), skippedImportFile);
			}
		}
	}

	// check if there any *.h file is included without assigning a category
	{
		List<FilePath> headerFiles;
		CopyFrom(
			headerFiles,
			From(unprocessedHeaderFiles)
				.Concat(unprocessedCppFiles)
				.SelectMany([&](const FilePath& includedFile)
				{
					return GetIncludedFiles(includedFile, skippedImportFiles, cachedFileToIncludes, conditionOns, conditionOffs);
				})
				.Concat(unprocessedHeaderFiles)
				.Distinct()
				.Except(unprocessedHeaderFiles)
			);

		if (headerFiles.Count() > 0)
		{
			Console::SetColor(true, false, false, true);
			Console::WriteLine(L"Error: The following files are not categorized.");
			for (auto headerFile : headerFiles)
			{
				Console::WriteLine(headerFile.GetFullPath());
			}
			Console::SetColor(true, true, true, false);
			CHECK_ERROR(true, L"All included files should be categorized");
		}
	}

	// calculate category dependencies
	PartialOrderingProcessor popCategories;							// POP for category ordering
	Group<vint, WString> componentToCategoryNames;					// component index to category names
	{
		SortedList<FilePath> items;
		Group<FilePath, FilePath> depGroup;

		CopyFrom(items, From(unprocessedCppFiles).Concat(unprocessedHeaderFiles));
		for (auto filePath : items)
		{
			for (auto includedFile : GetIncludedFiles(filePath, skippedImportFiles, cachedFileToIncludes, conditionOns, conditionOffs))
			{
				depGroup.Add(filePath, includedFile);
			}
		}

		popCategories.InitWithSubClass(items, depGroup, inputFileToCategories);
		popCategories.Sort();

		for (vint i = 0; i < popCategories.components.Count(); i++)
		{
			auto& component = popCategories.components[i];
			for (vint j = 0; j < component.nodeCount; j++)
			{
				auto& firstNode = popCategories.nodes[component.firstNode[j]];
				auto firstFile = items[firstNode.firstSubClassItem[0]];
				componentToCategoryNames.Add(i, inputFileToCategories[firstFile]);
			}
		}

		bool needExit = false;
		for (vint i = 0; i < componentToCategoryNames.Count(); i++)
		{
			const auto& cycleCategories = componentToCategoryNames.GetByIndex(i);
			if (cycleCategories.Count() > 1)
			{
				Console::SetColor(true, false, false, true);
				Console::WriteLine(
					L"Error: Cycle dependency found in categories: "
					+ From(cycleCategories).Aggregate([](const WString& a, const WString& b) {return a + L", " + b; })
					+ L".");
				Console::SetColor(true, true, true, false);
				needExit = true;
			}
		}
		CHECK_ERROR(!needExit, L"Cycle dependency is not allowed");
	}

	Dictionary<FilePath, WString> inputFileToOutputFiles;			// input file -> output file
	{
		for (vint i = 0; i < inputFileToCategories.Count(); i++)
		{
			auto key = inputFileToCategories.Keys()[i];
			auto value = inputFileToCategories.Values()[i];
			inputFileToOutputFiles.Add(key, categorizedOutput[value].get<0>());
		}
	}

	// prepare output folder
	auto outputFolder = workingDir / (XmlGetAttribute(XmlGetElement(config->rootElement, L"output"), L"path")->value.value);
	auto outputIncludeOnlyFolder = outputFolder / L"IncludeOnly";
	if (!Folder(outputIncludeOnlyFolder).Exists())
	{
		Folder(outputIncludeOnlyFolder).Create(true);
	}

	// generate categorized header dependencies
	Dictionary<WString, LazyList<WString>> categorizedHeaderIncludes;
	for (vint i = 0; i < popCategories.components.Count(); i++)
	{
		auto& component = popCategories.components[i];
		auto categoryName = componentToCategoryNames[i][0];
		categorizedHeaderIncludes.Add(
			categoryName,
			From(*popCategories.nodes[component.firstNode[0]].ins)
				.Where([&](vint nodeIndex)
				{
					return nodeIndex != component.firstNode[0];
				})
				.Select([&](vint nodeIndex)
				{
					return categorizedOutput[componentToCategoryNames[popCategories.nodes[nodeIndex].component][0]].get<0>() + L".h";
				})
			);
	}

	// generate code pair header files
	Dictionary<WString, Ptr<SortedList<WString>>> categorizedSystemIncludes;
	for (vint i = 0; i < popCategories.components.Count(); i++)
	{
		auto categoryName = componentToCategoryNames[i][0];
		auto outputPath = outputFolder / (categorizedOutput[categoryName].get<0>() + L".h");
		auto outputIncludeOnlyPath = outputIncludeOnlyFolder / (categorizedOutput[categoryName].get<0>() + L".h");

		auto systemIncludes = Ptr(new SortedList<WString>);
		categorizedSystemIncludes.Add(categoryName, systemIncludes);

		if (categorizedOutput[categoryName].get<1>())
		{
			vint headerIndex = categorizedHeaderFiles.Keys().IndexOf(categoryName);
			if (headerIndex == -1) continue;
			Combine(
				inputFileToOutputFiles,
				skippedImportFiles,
				cachedFileToIncludes,
				conditionOns,
				conditionOffs,
				categorizedHeaderFiles.GetByIndex(headerIndex),
				outputPath,
				outputIncludeOnlyPath,
				*systemIncludes.Obj(),
				categorizedHeaderIncludes[categoryName]
				);
		}
	}

	// generate code pair cpp files
	for (vint i = 0; i < popCategories.components.Count(); i++)
	{
		auto categoryName = componentToCategoryNames[i][0];
		if (categorizedOutput[categoryName].get<1>())
		{
			WString outputHeader[] = { categorizedOutput[categoryName].get<0>() + L".h"};
			vint headerIndex = categorizedHeaderFiles.Keys().IndexOf(categoryName);

			auto outputPath = outputFolder / (categorizedOutput[categoryName].get<0>() + L".cpp");
			auto outputIncludeOnlyPath = outputIncludeOnlyFolder / (categorizedOutput[categoryName].get<0>() + L".cpp");
			Combine(
				inputFileToOutputFiles,
				skippedImportFiles,
				cachedFileToIncludes,
				conditionOns,
				conditionOffs,
				categorizedCppFiles[categoryName],
				outputPath,
				outputIncludeOnlyPath,
				*categorizedSystemIncludes[categoryName].Obj(),
				(headerIndex == -1 ? categorizedHeaderIncludes[categoryName] : From(outputHeader))
				);
		}
	}

	return 0;
}