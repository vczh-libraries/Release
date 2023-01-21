#include "Codepack.h"

LazyList<FilePath> SearchFiles(
	const Folder& folder,
	const WString& extension,
	List<WString>& exceptions
)
{
	auto files = Ptr(new List<File>);
	auto folders = Ptr(new List<Folder>);
	folder.GetFiles(*files.Obj());
	folder.GetFolders(*folders.Obj());

	return LazyList<File>(files)
		.Select([](const File& file)
		{
			return file.GetFilePath();
		})
		.Where([&](const FilePath& filePath)
		{
			return From(exceptions)
				.All([&](const WString& except)
				{
					return INVLOC.FindFirst(filePath.GetFullPath(), except, Locale::IgnoreCase).key == -1;
				});
		})
		.Where([=](const FilePath& path)
		{
			return INVLOC.EndsWith(path.GetName(), extension, Locale::IgnoreCase);
		})
		.Concat(
			LazyList<Folder>(folders)
			.SelectMany([&](const Folder& folder)
			{
				return SearchFiles(folder, extension, exceptions);
			})
		);
}

LazyList<FilePath> GetCppFiles(
	const FilePath& folder,
	List<WString>& exceptions
)
{
	return SearchFiles(folder, L".cpp", exceptions);
}

LazyList<FilePath> GetHeaderFiles(
	const FilePath& folder,
	List<WString>& exceptions
)
{
	return SearchFiles(folder, L".h", exceptions);
}