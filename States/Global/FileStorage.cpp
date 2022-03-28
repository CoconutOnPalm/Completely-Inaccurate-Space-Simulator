#include "FileStorage.hpp"

FileStorage::FileStorage() {}

FileStorage::~FileStorage() { this->saveLinkedFilesData(); }

FileStorage& FileStorage::Get()
{
	static FileStorage instance;
	return instance;
}


void FileStorage::LinkFiles()
{
	Get().linkMajorFiles();
	Get().linkIconLayoutsFiles();
	Get().linkObjectDatabase();
}

void FileStorage::saveLinkedFilesData()
{
	Get().saveMajorFiles();
	Get().saveIconLayoutsFiles();
	Get().saveObjectDatabase();
}


void FileStorage::linkMajorFiles()
{
	ke::FileStream linker("Data/filelinker.bin", std::ios::binary | std::ios::in);

	if (!linker.loaded())
	{
		ke::throw_error("FileStorage::linkMajorFiles()", "COULD NOT LINK FILES", "CRITICAL FILE ERROR");
		return;
	}

	size_t no_files = 2; // number of files


	linker.binRead(no_files);

	std::string name;
	std::string path;

	for (size_t i = 0; i < no_files; i++)
	{
		linker.binRead(name);
		linker.binRead(path);

		std::ifstream filecheck(path);

		if (filecheck.good())
			Get().linked_files[name] = path;
		else
			ke::throw_error("FileStorage::linkMajorFiles()", "could not load " + name + "file", "FILE ERROR");
	}

	// test
	std::cout << "linkMajorFiles()\n";
	for (auto& itr : Get().linked_files)
		std::cout << "Linked \'" << itr.first << "\' with path: " << itr.second << '\n';
}

void FileStorage::linkIconLayoutsFiles()
{
	ke::FileStream linker("Data/iconLinker.bin", std::ios::binary | std::ios::in);

	if (!linker.loaded())
	{
		ke::throw_error("FileStorage::linkIconLayoutsFiles()", "COULD NOT LINK FILES", "CRITICAL FILE ERROR");
		return;
	}

	size_t no_files = 2; // number of files


	linker.binRead(no_files);

	std::string name;
	std::string path;

	for (size_t i = 0; i < no_files; i++)
	{
		linker.binRead(name);
		linker.binRead(path);

		std::ifstream filecheck(path);
		
		if (filecheck.good())
			Get().linked_icon_layouts_files[name] = path;
	}

	// test
	std::cout << "linkIconLayoutsFiles()\n";
	for (auto& itr : Get().linked_icon_layouts_files)
		std::cout << "Linked \'" << itr.first << "\' with path: " << itr.second << '\n';
}

void FileStorage::linkObjectDatabase()
{
	ke::FileStream linker("Data/objectDatabaseLinker.bin", std::ios::binary | std::ios::in);

	if (!linker.loaded())
	{
		ke::throw_error("FileStorage::linkObjectDatabase()", "COULD NOT LINK FILES", "CRITICAL FILE ERROR");
		return;
	}

	size_t no_files = 2; // number of files

	linker.binRead(no_files);

	std::string name;
	std::string path;

	for (size_t i = 0; i < no_files; i++)
	{
		linker.binRead(name);
		linker.binRead(path);

		std::ifstream filecheck(path);

		if (filecheck.good())
			Get().linked_space_objects_database[name] = path;
	}

	//Get().linked_space_objects_database["Colors"] = "Data/ObjectDatabase/Colors.sodb";
	
	// test
	std::cout << "linkObjectDatabase()\n";
	for (auto& itr : Get().linked_space_objects_database)
		std::cout << "Linked \'" << itr.first << "\' with path: " << itr.second << '\n';
}



void FileStorage::saveMajorFiles()
{
	ke::FileStream savestr("Data/filelinker.bin", std::ios::binary | std::ios::out | std::ios::trunc);

	if (!savestr.loaded())
	{
		ke::throw_error("FileStorage::saveMajorFiles()", "COULD NOT SAVE FILES TO LINKER", "CRITICAL FILE ERROR");
		return;
	}

	savestr.binWrite(Get().linked_files.size());

	for (auto& itr : Get().linked_files)
	{
		savestr.binWrite(itr.first);
		savestr.binWrite(itr.second);
	}
}

void FileStorage::saveIconLayoutsFiles()
{
	ke::FileStream savestr("Data/iconLinker.bin", std::ios::binary | std::ios::out | std::ios::trunc);

	if (!savestr.loaded())
	{
		ke::throw_error("FileStorage::saveIconLayoutsFiles()", "COULD NOT SAVE FILES TO LINKER", "CRITICAL FILE ERROR");
		return;
	}

	savestr.binWrite(Get().linked_icon_layouts_files.size());

	for (auto& itr : Get().linked_icon_layouts_files)
	{
		savestr.binWrite(itr.first);
		savestr.binWrite(itr.second);
	}
}

void FileStorage::saveObjectDatabase()
{
	ke::FileStream savestr("Data/objectDatabaseLinker.bin", std::ios::binary | std::ios::out | std::ios::trunc);

	if (!savestr.loaded())
	{
		ke::throw_error("FileStorage::saveObjectDatabase()", "COULD NOT SAVE FILES TO LINKER", "CRITICAL FILE ERROR");
		return;
	}


	savestr.binWrite(Get().linked_space_objects_database.size());

	for (auto& itr : Get().linked_space_objects_database)
	{
		savestr.binWrite(itr.first);
		savestr.binWrite(itr.second);
	}
}
