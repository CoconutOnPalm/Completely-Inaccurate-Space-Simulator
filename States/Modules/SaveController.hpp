#pragma once

#include "States/State.hpp"
#include "ObjectController.hpp"


enum class SimulationSaveErrorCode
{
	NO_FILE_ERROR,
	FILE_NOT_FOUND,
	FILE_ALREADY_EXISTS,
	FILE_DOES_NOT_EXIST
};


class SaveController
{
public:

	SaveController();
	~SaveController();

	void assign(ObjectController* object_controller);

	SimulationSaveErrorCode Load(const std::string& name, std::vector<std::unique_ptr<SpaceObject>>* objects, const sf::Vector2f& viewsize, const sf::Vector2f& winsize);
	SimulationSaveErrorCode Save(const std::string& name, std::vector<std::unique_ptr<SpaceObject>>* objects);
	SimulationSaveErrorCode AutoSave(const std::string& name, std::vector<std::unique_ptr<SpaceObject>>* objects);

	SimulationSaveErrorCode LoadLatest(std::vector<std::unique_ptr<SpaceObject>>* objects, const sf::Vector2f& viewsize, const sf::Vector2f& winsize);
	SimulationSaveErrorCode QuickSave(std::vector<std::unique_ptr<SpaceObject>>* objects);

	std::string getFilePath(std::string name);

	bool file_exists(std::string name) const;


private:

	SimulationSaveErrorCode SaveAll();

	ObjectController* m_objectController;

	std::string m_latest;
	std::map<std::string, std::string> m_savedSimulations;
};

