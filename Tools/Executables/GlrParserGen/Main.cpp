#include <VlppGlrParserCompiler.h>

using namespace vl;
using namespace vl::console;
using namespace vl::collections;
using namespace vl::stream;
using namespace vl::filesystem;
using namespace vl::regex;
using namespace vl::glr;
using namespace vl::glr::automaton;
using namespace vl::glr::parsergen;
using namespace vl::glr::xml;

#define EXIT_ERROR(MESSAGE)\
	do\
	{\
		Console::SetColor(true, false, false, true);\
		Console::WriteLine(MESSAGE);\
		Console::SetColor(true, true, true, false);\
		return 1;\
	} while(false)

#define EXIT_IF_PARSER_FAIL(ERRORS, TITLE)\
	do\
	{\
		if (ERRORS.Count() > 0)\
		{\
			Console::SetColor(true, false, false, true);\
			Console::WriteLine(TITLE);\
			PrintParsingErrors(ERRORS);\
			Console::SetColor(true, true, true, false);\
			return 1;\
		}\
	} while(false)

#define EXIT_IF_COMPILE_FAIL(GLOBAL)\
	do\
	{\
		if (GLOBAL.Errors().Count() > 0)\
		{\
			Console::SetColor(true, false, false, true);\
			Console::WriteLine(L"Failed to compile the syntax:");\
			PrintCompileErrors(GLOBAL);\
			Console::SetColor(true, true, true, false);\
			return 1;\
		}\
	} while(false)

#define READ_ATTRIBUTE(STORAGE, ELEMENT, NAME, PATH)\
	do\
	{\
		if (auto attributeToRead = XmlGetAttribute(ELEMENT, NAME))\
		{\
			STORAGE = attributeToRead->value.value;\
		}\
		else\
		{\
			EXIT_ERROR(L"Missing " PATH L".");\
		}\
	} while(false)\

#define READ_ELEMENT(STORAGE, ELEMENT, NAME, PATH)\
	do\
	{\
		if (auto elementToRead = XmlGetElement(ELEMENT, NAME))\
		{\
			STORAGE = XmlGetValue(elementToRead);\
		}\
		else\
		{\
			EXIT_ERROR(L"Missing " PATH L".");\
		}\
	} while(false)\

#define READ_ELEMENT_ITEMS(STORAGE, REGEX, ELEMENT, NAME, PATH)\
	do\
	{\
		if (auto elementToRead = XmlGetElement(ELEMENT, NAME))\
		{\
			auto value = XmlGetValue(elementToRead);\
			if (auto match = REGEX.MatchHead(value))\
			{\
				for (auto item : match->Groups()[REGEX.CaptureNames().IndexOf(L"item")])\
				{\
					STORAGE.Add(item.Value());\
				}\
			}\
			else\
			{\
				EXIT_ERROR(L"Incorrect namespace format in: " PATH L".");\
			}\
		}\
		else\
		{\
			EXIT_ERROR(L"Missing " PATH L".");\
		}\
	} while(false)\

void PrintParsingErrors(List<ParsingError>& errors)
{
	for (auto error : errors)
	{
		Console::WriteLine(
			L"[row:" + itow(error.codeRange.start.row + 1) + L"]"
			L"[column:" + itow(error.codeRange.start.column + 1) + L"]"
			L": " + error.message); 
	}
}

void PrintCompileErrors(ParserSymbolManager& global)
{
	for (auto error : global.Errors())
	{
		switch (error.location.type)
		{
		case ParserDefFileType::Ast:
			Console::Write(L"[Ast:" + error.location.name + L"]");
			break;
		case ParserDefFileType::Lexer:
			Console::Write(L"[Lexer]");
			break;
		case ParserDefFileType::Syntax:
			Console::Write(L"[Syntax:" + error.location.name + L"]");
			break;
		}

		Console::Write(
			L"[row:" + itow(error.location.codeRange.start.row + 1) + L"]"
			L"[column:" + itow(error.location.codeRange.start.column + 1) + L"]");

#define CASE_1(LABEL, P1, ...)\
		Console::WriteLine(\
			L"[" L ## #LABEL L"]"\
			L"[" L ## #P1 L":" + error.arg1 + L"]"\
			);\

#define CASE_2(LABEL, P1, P2, ...)\
		Console::WriteLine(\
			L"[" L ## #LABEL L"]"\
			L"[" L ## #P1 L":" + error.arg1 + L"]"\
			L"[" L ## #P2 L":" + error.arg2 + L"]"\
			);\

#define CASE_3(LABEL, P1, P2, P3, ...)\
		Console::WriteLine(\
			L"[" L ## #LABEL L"]"\
			L"[" L ## #P1 L":" + error.arg1 + L"]"\
			L"[" L ## #P2 L":" + error.arg2 + L"]"\
			L"[" L ## #P3 L":" + error.arg3 + L"]"\
			);\

#define CASE_4(LABEL, P1, P2, P3, P4, ...)\
		Console::WriteLine(\
			L"[" L ## #LABEL L"]"\
			L"[" L ## #P1 L":" + error.arg1 + L"]"\
			L"[" L ## #P2 L":" + error.arg2 + L"]"\
			L"[" L ## #P3 L":" + error.arg3 + L"]"\
			L"[" L ## #P4 L":" + error.arg4 + L"]"\
			);\

#define CASE_CALL2(ARG1, ARG2, ARG3, ARG4, ARG5, FUNC, ...)\
		FUNC(ARG1, ARG2, ARG3, ARG4, ARG5)

#define CASE_CALL(ARGS)\
		CASE_CALL2 ARGS

#define CASE(LABEL, ...)\
		case ParserErrorType::LABEL:\
			CASE_CALL((LABEL, __VA_ARGS__, CASE_4, CASE_3, CASE_2, CASE_1))\
			break;\
		

		switch (error.type)
		{
		GLR_PARSER_ERROR_LIST(CASE)
		default:
			Console::WriteLine(L"<UNKNOWN-ERROR>");
		}

#undef CASE
#undef CASE_CALL
#undef CASE_CALL2
#undef CASE_4
#undef CASE_3
#undef CASE_2
#undef CASE_1
	}
}

int main(int argc, char* argv[])
{
	Console::SetTitle(L"Vczh GLR ParserGen for C++");
	if (argc != 2)
	{
		Console::SetColor(true, false, false, true);
		Console::WriteLine(L"GlrParserGen.exe <config-xml>");
		Console::SetColor(true, true, true, false);
		return 0;
	}

	auto workingDir = FilePath(atow(argv[1])).GetFolder();
	Ptr<XmlDocument> config;
	{
		Parser parser;
		List<ParsingError> errors;
		InstallDefaultErrorMessageGenerator(parser, errors);
		auto text = File(atow(argv[1])).ReadAllTextByBom();
		config = XmlParseDocument(text, parser);
		EXIT_IF_PARSER_FAIL(errors, L"Failed to read the input XML file.");
	}

	if (config->rootElement->name.value != L"Parser") EXIT_ERROR(L"Missing /Parser.");

	ParserSymbolManager global;
	AstSymbolManager astManager(global);
	LexerSymbolManager	lexerManager(global);
	SyntaxSymbolManager syntaxManager(global);
	Executable executable;
	Metadata metadata;

	FilePath generatedDir;
	Dictionary<WString, WString> files;

	Regex regexNamespace(L"^(<item>[^:]+)(::(<item>[^:]+))*$");
	Regex regexIncludes(L"^(<item>[^;]+)(;(<item>[^;]+))*$");
	auto indexItem = regexNamespace.CaptureNames().IndexOf(L"item");

	READ_ATTRIBUTE(global.name, config->rootElement, L"name", L"/Parser@name");
	READ_ELEMENT_ITEMS(global.includes, regexIncludes, config->rootElement, L"Includes", L"/Parser/Includes");
	READ_ELEMENT_ITEMS(global.cppNss, regexNamespace, config->rootElement, L"CppNamespace", L"/Parser/CppNamespace");
	READ_ELEMENT(global.headerGuard, config->rootElement, L"HeaderGuard", L"/Parser/HeaderGuard");
	{
		WString outputDir;
		READ_ELEMENT(outputDir, config->rootElement, L"OutputDir", L"/Parser/OutputDir");
		generatedDir = workingDir / outputDir;
	}

	auto output = GenerateParserFileNames(global);

	TypeParser typeParser;
	RuleParser ruleParser;
	List<ParsingError> errors;
	InstallDefaultErrorMessageGenerator(typeParser, errors);
	InstallDefaultErrorMessageGenerator(ruleParser, errors);

	if (auto elementAsts = XmlGetElement(config->rootElement, L"Asts"))
	{
		List<Ptr<XmlElement>> asts;
		CopyFrom(asts, XmlGetElements(elementAsts, L"Ast"));
		if (asts.Count() == 0) EXIT_ERROR(L"Missing /Parser/Asts/Ast");

		for (auto elementAst : asts)
		{
			WString name, file;
			READ_ATTRIBUTE(name, elementAst, L"name", L"/Parser/Asts/Ast@name");
			READ_ATTRIBUTE(file, elementAst, L"file", L"/Parser/Asts/Ast@file[@name=\"" + name + L"\"]");
			Console::WriteLine(L"Processing " + file + L" ...");

			File astFile = workingDir / file;
			if (!astFile.Exists()) EXIT_ERROR(L"Missing ast definition file: " + astFile.GetFilePath().GetFullPath());
			auto astInput = astFile.ReadAllTextByBom();
			auto ast = typeParser.ParseFile(astInput);
			EXIT_IF_PARSER_FAIL(errors, L"Syntax errors found in file: " + astFile.GetFilePath().GetFullPath());

			auto astDefFile = astManager.CreateFile(name);
			READ_ELEMENT_ITEMS(astDefFile->cppNss, regexNamespace, elementAst, L"CppNamespace", L"/Parser/Asts/Ast@file[@name=\"" + name + L"\"]/CppNamespace");
			READ_ELEMENT_ITEMS(astDefFile->refNss, regexNamespace, elementAst, L"ReflectionNamespace", L"/Parser/Asts/Ast@file[@name=\"" + name + L"\"]/ReflectionNamespace");
			READ_ELEMENT(astDefFile->classPrefix, elementAst, L"ClassPrefix", L"/Parser/Asts/Ast@file[@name=\"" + name + L"\"]/ClassPrefix");
			CompileAst(astManager, astDefFile, ast);
		}

		EXIT_IF_COMPILE_FAIL(global);
		GenerateAstFileNames(astManager, output);
		WriteAstFiles(astManager, output, files);
	}
	else
	{
		EXIT_ERROR(L"Missing /Parser/Asts");
	}

	if (auto elementLexer = XmlGetElement(config->rootElement, L"Lexer"))
	{
		WString file;
		READ_ATTRIBUTE(file, elementLexer, L"file", L"/Parser/Lexer@file");
		Console::WriteLine(L"Processing " + file + L" ...");

		File lexerFile = workingDir / file;
		auto lexerInput = lexerFile.ReadAllTextByBom();
		CompileLexer(lexerManager, lexerInput);

		EXIT_IF_COMPILE_FAIL(global);
		WriteLexerFiles(lexerManager, output, files);
	}
	else
	{
		EXIT_ERROR(L"Missing /Parser/Asts");
	}

	if (auto elementSyntax = XmlGetElement(config->rootElement, L"Syntax"))
	{
		WString name, file;
		READ_ATTRIBUTE(name, elementSyntax, L"name", L"/Parser/Syntax@name");
		READ_ATTRIBUTE(file, elementSyntax, L"file", L"/Parser/Syntax@file[@name=\"" + name + L"\"]");
		Console::WriteLine(L"Processing " + file + L" ...");

		File syntaxFile = workingDir / file;
		auto syntaxInput = syntaxFile.ReadAllTextByBom();
		auto syntax = ruleParser.ParseFile(syntaxInput);
		EXIT_IF_PARSER_FAIL(errors, L"Syntax errors found in file: " + syntaxFile.GetFilePath().GetFullPath());

		List<Ptr<GlrSyntaxFile>> syntaxFiles;
		syntaxFiles.Add(syntax);
		syntaxManager.name = name;
		CompileSyntax(astManager, lexerManager, syntaxManager, output, syntaxFiles);
		EXIT_IF_COMPILE_FAIL(global);

		syntaxManager.BuildCompactNFA();
		EXIT_IF_COMPILE_FAIL(global);
		syntaxManager.BuildCrossReferencedNFA();
		EXIT_IF_COMPILE_FAIL(global);
		syntaxManager.BuildAutomaton(lexerManager.Tokens().Count(), executable, metadata);
		EXIT_IF_COMPILE_FAIL(global);

		for (auto elementExport : XmlGetElements(elementSyntax, L"Export"))
		{
			WString rule;
			READ_ATTRIBUTE(rule, elementExport, L"rule", L"/Parser/Syntax@file[@name=\"" + name + L"\"]/Export@rule");

			vint index = syntaxManager.Rules().Keys().IndexOf(rule);
			if (index == -1)
			{
				EXIT_ERROR(L"Rule \"" + rule + L"\" is not defined in the syntax.");
			}

			auto ruleSymbol = syntaxManager.Rules().Values()[index];
			syntaxManager.parsableRules.Add(ruleSymbol);

			if (auto attType = XmlGetAttribute(elementExport, L"type"))
			{
				syntaxManager.ruleTypes.Add(ruleSymbol, attType->value.value);
			}
			else
			{
				auto classSymbol = ruleSymbol->ruleType;
				auto classFile = classSymbol->Owner();
				auto type =
					From(classFile->cppNss)
						.Reverse()
						.Aggregate(
							classFile->classPrefix + classSymbol->Name(),
							[](auto&& a, auto&& b) { return b + L"::" + a; }
					);
				syntaxManager.ruleTypes.Add(ruleSymbol, type);
			}
		}

		GenerateSyntaxFileNames(syntaxManager, output);
		WriteSyntaxFiles(syntaxManager, executable, metadata, output, files);
	}
	else
	{
		EXIT_ERROR(L"Missing /Parser/Asts");
	}

	{
		auto elementAsts = XmlGetElement(config->rootElement, L"Asts");
		for (auto elementAst : XmlGetElements(elementAsts, L"Ast"))
		{
			auto name = XmlGetAttribute(elementAst, L"name")->value.value;
			auto astOutput = output->astOutputs[astManager.Files()[name]];

			if (auto elementBlocked = XmlGetElement(elementAst, L"BlockedUtilities"))
			{
				for (auto elementUtility : XmlGetElements(elementBlocked))
				{
					auto utility = elementUtility->name.value;
					if (utility == L"Empty")
					{
						files.Remove(astOutput->emptyH);
						files.Remove(astOutput->emptyCpp);
					}
					else if (utility == L"Copy")
					{
						files.Remove(astOutput->copyH);
						files.Remove(astOutput->copyCpp);
					}
					else if (utility == L"Traverse")
					{
						files.Remove(astOutput->traverseH);
						files.Remove(astOutput->traverseCpp);
					}
					else if (utility == L"Json")
					{
						files.Remove(astOutput->jsonH);
						files.Remove(astOutput->jsonCpp);
					}
					else if (utility == L"Builder")
					{
						files.Remove(astOutput->builderH);
						files.Remove(astOutput->builderCpp);
					}
					else
					{
						EXIT_ERROR(L"Unknown utility \"" + utility + L"\" in /Parser/Asts/Ast[@name=\"" + name + L"\"]/BlockedUtilities/*");
					}
				}
			}
		}
	}

	{
		if (!Folder(generatedDir).Exists())
		{
			Folder(generatedDir).Create(true);
		}

		for (auto [key, index] : indexed(files.Keys()))
		{
			File outputFile = generatedDir / key;
			auto content = files.Values()[index];
			if (outputFile.Exists())
			{
				auto existing = outputFile.ReadAllTextByBom();
				if (content == existing)
				{
					Console::SetColor(true, true, false, true);
					Console::WriteLine(outputFile.GetFilePath().GetFullPath());
					Console::SetColor(true, true, true, false);
					continue;
				}
			}

			Console::SetColor(false, true, false, true);
			Console::WriteLine(outputFile.GetFilePath().GetFullPath());
			Console::SetColor(true, true, true, false);
			outputFile.WriteAllText(content, false, BomEncoder::Utf8);
		}
	}
	return 0;
}