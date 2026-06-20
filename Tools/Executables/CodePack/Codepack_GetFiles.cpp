#include "Codepack.h"

LazyList<FilePath> SearchFiles(
	const FilePath& folderPath,
	const WString& extension,
	List<WString>& exceptions
)
{
	auto files = Ptr(new List<File>);
	auto folders = Ptr(new List<Folder>);
	auto folder = Folder(NormalizePathForFileSystem(folderPath));
	folder.GetFiles(*files.Obj());
	folder.GetFolders(*folders.Obj());
	CopyFrom(
		*files.Obj(),
		From(*files.Obj()).OrderBy([](const File& a, const File& b)
		{
			return GetCodePackPath(a.GetFilePath().GetFullPath()) <=> GetCodePackPath(b.GetFilePath().GetFullPath());
		})
		);
	CopyFrom(
		*folders.Obj(),
		From(*folders.Obj()).OrderBy([](const Folder& a, const Folder& b)
		{
			return GetCodePackPath(a.GetFilePath().GetFullPath()) <=> GetCodePackPath(b.GetFilePath().GetFullPath());
		})
		);

	return LazyList<File>(files)
		.Select([](const File& file)
		{
			return file.GetFilePath();
		})
		.Where([&](const FilePath& filePath)
		{
			auto fullPath = GetCodePackPath(filePath.GetFullPath());
			return From(exceptions)
				.All([&](const WString& except)
				{
					return INVLOC.FindFirst(fullPath, except, Locale::IgnoreCase).key == -1;
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
				return SearchFiles(folder.GetFilePath(), extension, exceptions);
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
