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
	//ke::FileStream fstr;
	//fstr.createFile("Data/filelinker.bin");
	//fstr.createFile("Data/IconLayouts/iconLinker.bin");

	//if (fstr.open("Data/filelinker.bin", std::ios::binary | std::ios::out | std::ios::trunc))
	//fstr.binWrite((size_t)2);
	//fstr.binWrite((std::string)"SETTINGS");
	//fstr.binWrite((std::string)"Data/settings.bin");
	//fstr.binWrite((std::string)"OBJECT_ICON_LAYOUTS");
	//fstr.binWrite((std::string)"Data/recentlyUsedIcons.glo");

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



	//Get().linked_files["SETTINGS"] = "Data/settings.bin";
	//Get().linked_files["OBJECT_ICON_LAYOUT"] = "Data/recentlyUsedIcons.glo";
	//return;

	size_t no_files = 2; // number of files

	linker.binRead(no_files);
	std::cout << no_files << '\n';

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

	//Get().linked_files["ICON_HISTORY"] = "Data/recentlyUsedIcons.glo";
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

	//Get().linked_icon_layouts_files["Default"] = "Data/IconLayouts/Default.slo";
	//Get().linked_icon_layouts_files["test1"] = "Data/IconLayouts/test1.slo";

	linker.binRead(no_files);
	//return;

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

	//Get().linked_icon_layouts_files["Default"] = "Data/IconLayouts/Default.slo";
	//Get().linked_icon_layouts_files["test1"] = "Data/IconLayouts/test1.slo";

	linker.binRead(no_files);
	//return;

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

	Get().linked_space_objects_database["Default"] = "Data/ObjectDatabase/Default.sodb";

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



	//Get().linked_files["SETTINGS"] = "Data/settings.bin";
	//Get().linked_files["OBJECT_ICON_LAYOUT"] = "Data/recentlyUsedIcons.glo";

	savestr.binWrite(Get().linked_files.size());
	//savestr.binWrite(2);

	for (auto& itr : Get().linked_files)
	{
		savestr.binWrite(itr.first);
		savestr.binWrite(itr.second);
	}

	//savestr.binWrite(std::string("OBJECT_DATABASE_LINKER"));
	//savestr.binWrite(std::string("Data/objectDatabaseLinker.bin"));
	//savestr.createFile("Data/objectDatabaseLinker.bin");
}

void FileStorage::saveIconLayoutsFiles()
{
	ke::FileStream savestr("Data/iconLinker.bin", std::ios::binary | std::ios::out | std::ios::trunc);

	if (!savestr.loaded())
	{
		ke::throw_error("FileStorage::saveIconLayoutsFiles()", "COULD NOT SAVE FILES TO LINKER", "CRITICAL FILE ERROR");
		return;
	}

	//Get().linked_icon_layouts_files["Default"] = "Data/IconLayouts/Default.slo";
	//Get().linked_icon_layouts_files["test1"] = "Data/IconLayouts/test1.slo";
	//savestr.binWrite(2);

	savestr.binWrite(Get().linked_icon_layouts_files.size());

	for (auto& itr : Get().linked_icon_layouts_files)
	{
		savestr.binWrite(itr.first);
		savestr.binWrite(itr.second);
	}
	//savestr.binWrite(2);
	//savestr.binWrite(std::string("Default"));
	//savestr.binWrite(std::string("Data/IconLayouts/Default.slo"));
	//savestr.binWrite(std::string("test1"));
	//savestr.binWrite(std::string("Data/IconLayouts/test1.slo"));
}

void FileStorage::saveObjectDatabase()
{
	ke::FileStream savestr("Data/objectDatabaseLinker.bin", std::ios::binary | std::ios::out | std::ios::trunc);

	if (!savestr.loaded())
	{
		ke::throw_error("FileStorage::saveObjectDatabase()", "COULD NOT SAVE FILES TO LINKER", "CRITICAL FILE ERROR");
		return;
	}

	FileStorage::Get().linked_space_objects_database["SODB_TEST1"] = "Data/ObjectDatabase/test1.sodb";
	FileStorage::Get().linked_space_objects_database["SODB_TEST2"] = "Data/ObjectDatabase/test1.sodb";

	//Get().linked_space_objects_database["Solar System"] = "Data/ObjectDatabase/SolarSystem.sodb";
	//Get().linked_icon_layouts_files["test1"] = "Data/IconLayouts/test1.slo";

	//savestr.binWrite(Get().linked_space_objects_database.size());
	savestr.binWrite(Get().linked_space_objects_database.size());

	for (auto& itr : Get().linked_space_objects_database)
	{
		savestr.binWrite(itr.first);
		savestr.binWrite(itr.second);
	}
}
