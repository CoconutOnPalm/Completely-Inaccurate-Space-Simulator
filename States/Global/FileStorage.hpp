#pragma once

#include <KEngine/Algorithms.hpp>
#include <map>
#include <unordered_map>
#include <vector>


class FileStorage
{
public:

	FileStorage();
	~FileStorage();

	FileStorage(const FileStorage& copy) = delete;
	void operator= (const FileStorage& copy) = delete;

	static FileStorage& Get();


	static void LinkFiles();

	static void saveLinkedFilesData();

	std::map<std::string, std::string> linked_files;
	std::map<std::string, std::string> linked_icon_layouts_files;
	std::unordered_map<std::string, std::string> linked_space_objects_database;

private:

	static void linkMajorFiles();
	static void linkIconLayoutsFiles();
	static void linkObjectDatabase();

	static void saveMajorFiles();
	static void saveIconLayoutsFiles();
	static void saveObjectDatabase();
};

