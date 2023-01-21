#include "Codepack.h"

void CategorizeCodeFiles(
	Ptr<XmlDocument> config,
	LazyList<FilePath> files,
	Group<WString, FilePath>& categorizedFiles,
	Dictionary<FilePath, WString>& inputFileToCategories
)
{
	for (auto e : XmlGetElements(XmlGetElement(config->rootElement, L"categories"), L"category"))
	{
		auto name = XmlGetAttribute(e, L"name")->value.value;
		auto pattern = wupper(XmlGetAttribute(e, L"pattern")->value.value);

		List<WString> exceptions;
		CopyFrom(
			exceptions,
			XmlGetElements(e,L"except")
				.Select([](const Ptr<XmlElement> x)
				{
					return XmlGetAttribute(x, L"pattern")->value.value;
				})
			);

		List<FilePath> filterFiles;
		CopyFrom(
			filterFiles,
			From(files).Where([&](const FilePath& f)
				{
					auto path = f.GetFullPath();
					return INVLOC.FindFirst(path, pattern, Locale::IgnoreCase).key != -1
						&& From(exceptions).All([&](const WString& ex)
						{
							return INVLOC.FindFirst(path, ex, Locale::IgnoreCase).key == -1;
						});
				})
			);

		for (auto file : filterFiles)
		{
			if (!categorizedFiles.Contains(name, file))
			{
				categorizedFiles.Add(name, file);
				inputFileToCategories.Add(file, name);
			}
		}
	}

	for (auto a : categorizedFiles.Keys())
	{
		for (auto b : categorizedFiles.Keys())
		{
			if (a != b)
			{
				const auto& as = categorizedFiles.Get(a);
				const auto& bs = categorizedFiles.Get(b);
				List<FilePath> cs;
				CopyFrom(cs, From(as).Intersect(bs));
				CHECK_ERROR(From(cs).IsEmpty(), L"A file should not appear in multiple categories.");
			}
		}
	}
}