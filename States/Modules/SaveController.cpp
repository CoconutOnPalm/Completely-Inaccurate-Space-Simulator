#include "SaveController.hpp"

SaveController::SaveController()
	: m_objectController(nullptr)
{
	std::ifstream loader("Data/saved_simulations_list.txt");

	if (!loader.is_open())
	{
		ke::throw_error("SaveCotroller::SaveController()", "simulations list not found", "CRITICAL_FILE_ERROR");
		return;
	}

	size_t map_size;
	loader >> map_size;

	std::string name, path;

	for (int i = 0; i < map_size; i++)
	{
		loader >> name >> path;
		m_savedSimulations[name] = path;
	}
}

SaveController::~SaveController()
{
	this->SaveAll();
}

void SaveController::assign(ObjectController* object_controller)
{
	m_objectController = object_controller;
}

#define obj (*itr->get())

SimulationSaveErrorCode SaveController::Load(const std::string& name, std::vector<std::unique_ptr<SpaceObject>>* objects, const sf::Vector2f& viewsize, const sf::Vector2f& winsize)
{
	ke::FileStream loader(this->getFilePath(name), std::ios::in | std::ios::binary);

	std::cout << this->getFilePath(name) << '\n';

	if (!loader.loaded())
		return SimulationSaveErrorCode::FILE_NOT_FOUND;


	size_t objcount;
	loader.binRead(objcount);

	m_objectController->clearObjects(viewsize);

	for (int i = 0; i < objcount; i++)
	{
		ObjectBuffer buffer;
		int type, _class, subtype;
		long double mass, radius;
		std::string name, filename, icon_filename;
		float brightness;
		sf::Vector3f color;

		sf::Vector2f position;
		sf::Vector2<double> velocity;

		loader.binRead(name);
		loader.binRead(filename);
		loader.binRead(icon_filename);
		loader.binRead(type);
		loader.binRead(_class);
		loader.binRead(subtype);
		loader.binRead(mass);
		loader.binRead(radius);
		loader.binRead(brightness);
		loader.binRead(color.x);
		loader.binRead(color.y);
		loader.binRead(color.z);

		loader.binRead(position.x);
		loader.binRead(position.y);
		loader.binRead(velocity.x);
		loader.binRead(velocity.y);

		buffer.load(type, _class, subtype, mass, radius, name, filename, icon_filename, brightness, color);

		m_objectController->addObject(&buffer, position, viewsize, winsize, name, velocity);
	}


	return SimulationSaveErrorCode::NO_FILE_ERROR;
}

SimulationSaveErrorCode SaveController::Save(const std::string& name, std::vector<std::unique_ptr<SpaceObject>>* objects)
{
	if (this->file_exists(name))
		return SimulationSaveErrorCode::FILE_ALREADY_EXISTS;

	m_savedSimulations[name] = "Data/Simulations/" + name + ".sim";

	ke::FileStream saver("Data/Simulations/" + name + ".sim", std::ios::out | std::ios::binary);

	if (!saver.loaded())
		return SimulationSaveErrorCode::FILE_NOT_FOUND;

	saver.binWrite(objects->size() - 1);

	for (auto itr = objects->begin() + 1; itr != objects->end(); ++itr)
	{
		saver.binWrite(obj.name());
		saver.binWrite(obj.filename());
		saver.binWrite(obj.iconFilename());
		saver.binWrite(obj.type());
		saver.binWrite(obj.objectClass());
		saver.binWrite(obj.subtype());
		saver.binWrite(obj.data.mass);
		saver.binWrite(obj.data.radius);
		saver.binWrite(obj.data.brightness);
		saver.binWrite(obj.data.color.x);
		saver.binWrite(obj.data.color.y);
		saver.binWrite(obj.data.color.z);

		saver.binWrite(obj.object.getPosition().x);
		saver.binWrite(obj.object.getPosition().y);
		saver.binWrite(obj.object.physics()->getSpeed().x);
		saver.binWrite(obj.object.physics()->getSpeed().y);
	}

	return SimulationSaveErrorCode::NO_FILE_ERROR;
}

SimulationSaveErrorCode SaveController::AutoSave(const std::string& name, std::vector<std::unique_ptr<SpaceObject>>* objects)
{
	if (!this->file_exists(name))
		return SimulationSaveErrorCode::FILE_DOES_NOT_EXIST;;

	ke::FileStream saver(this->getFilePath(name), std::ios::out | std::ios::binary);

	if (!saver.loaded())
		return SimulationSaveErrorCode::FILE_NOT_FOUND;

	saver.binWrite(objects->size() - 1);

	for (auto itr = objects->begin() + 1; itr != objects->end(); ++itr)
	{
		saver.binWrite(obj.name());
		saver.binWrite(obj.filename());
		saver.binWrite(obj.iconFilename());
		saver.binWrite(obj.type());
		saver.binWrite(obj.objectClass());
		saver.binWrite(obj.subtype());
		saver.binWrite(obj.data.mass);
		saver.binWrite(obj.data.radius);
		saver.binWrite(obj.data.brightness);
		saver.binWrite(obj.data.color.x);
		saver.binWrite(obj.data.color.y);
		saver.binWrite(obj.data.color.z);

		saver.binWrite(obj.object.getPosition().x);
		saver.binWrite(obj.object.getPosition().y);
		saver.binWrite(obj.object.physics()->getSpeed().x);
		saver.binWrite(obj.object.physics()->getSpeed().y);
	}

	return SimulationSaveErrorCode::NO_FILE_ERROR;
}




SimulationSaveErrorCode SaveController::LoadLatest(std::vector<std::unique_ptr<SpaceObject>>* objects, const sf::Vector2f& viewsize, const sf::Vector2f& winsize)
{
	ke::FileStream loader("Data/Simulations/latest_save.sim", std::ios::in | std::ios::binary);

	if (!loader.loaded())
		return SimulationSaveErrorCode::FILE_NOT_FOUND;


	size_t objcount;
	loader.binRead(objcount);


	for (int i = 0; i < objcount; i++)
	{
		ObjectBuffer buffer;
		int type, _class, subtype;
		long double mass, radius;
		std::string name, filename, icon_filename;
		float brightness;
		sf::Vector3f color;

		sf::Vector2f position;
		sf::Vector2<double> velocity;

		loader.binRead(name);
		loader.binRead(filename);
		loader.binRead(icon_filename);
		loader.binRead(type);
		loader.binRead(_class);
		loader.binRead(subtype);
		loader.binRead(mass);
		loader.binRead(radius);
		loader.binRead(brightness);
		loader.binRead(color.x);
		loader.binRead(color.y);
		loader.binRead(color.y);

		loader.binRead(position.x);
		loader.binRead(position.y);
		loader.binRead(velocity.x);
		loader.binRead(velocity.y);

		buffer.load(type, _class, subtype, mass, radius, name, filename, icon_filename, brightness, color);

		m_objectController->addObject(&buffer, position, viewsize, winsize, name, velocity);
	}


	return SimulationSaveErrorCode::NO_FILE_ERROR;
}



SimulationSaveErrorCode SaveController::QuickSave(std::vector<std::unique_ptr<SpaceObject>>* objects)
{
	ke::FileStream saver("Data/Simulations/latest_save.sim", std::ios::out | std::ios::binary);

	if (!saver.loaded())
		return SimulationSaveErrorCode::FILE_NOT_FOUND;

	saver.binWrite(objects->size() - 1);

	for (auto itr = objects->begin() + 1; itr != objects->end(); ++itr)
	{
		saver.binWrite(obj.name());
		saver.binWrite(obj.filename());
		saver.binWrite(obj.iconFilename());
		saver.binWrite(obj.type());
		saver.binWrite(obj.objectClass());
		saver.binWrite(obj.subtype());
		saver.binWrite(obj.data.mass);
		saver.binWrite(obj.data.radius);
		saver.binWrite(obj.data.brightness);
		saver.binWrite(obj.data.color.x);
		saver.binWrite(obj.data.color.y);
		saver.binWrite(obj.data.color.z);

		saver.binWrite(obj.object.getPosition().x);
		saver.binWrite(obj.object.getPosition().y);
		saver.binWrite(obj.object.physics()->getSpeed().x);
		saver.binWrite(obj.object.physics()->getSpeed().y);
	}

	return SimulationSaveErrorCode::NO_FILE_ERROR;
}

#undef obj


std::string SaveController::getFilePath(std::string name)
{
	if (this->file_exists(name))
		return m_savedSimulations[name];
	else
		return "Data/Simulations/latest_save.sim";
}

bool SaveController::file_exists(std::string name) const
{
	return m_savedSimulations.find(name) != m_savedSimulations.end();
}

SimulationSaveErrorCode SaveController::SaveAll()
{
	std::ofstream saver("Data/saved_simulations_list.txt", std::ios::trunc);

	if (!saver.good())
		return SimulationSaveErrorCode::FILE_NOT_FOUND;


	saver << m_savedSimulations.size() << '\n';
	//std::cout << m_savedSimulations.size() << '\n';

	for (auto itr : m_savedSimulations)
		saver << itr.first << ' ' << itr.second << '\n';

	return SimulationSaveErrorCode::NO_FILE_ERROR;
}
