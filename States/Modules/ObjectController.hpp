#pragma once

#include "States/State.hpp"

#include "Space Objects/Planet.hpp"
#include "Space Objects/Star.hpp"
#include "Space Objects/CenterOfMass.hpp"
#include "Space Objects/ObjectIcon.hpp"
#include "Space Objects/ObjectBuffer.hpp"
#include "Space Objects/ObjectBuffer.hpp"
#include "Equasions/Equasions.hpp"
#include "Equasions/Constants.hpp"

#define objvector std::vector<std::unique_ptr<SpaceObject>>
#define iconvector std::vector<std::unique_ptr<ObjectIcon>>


class ObjectController
{
public:

	ObjectController();
	virtual ~ObjectController();

	void assign(objvector* objects, ke::Circle* orbit_preview, ke::Rectangle* distance_preview, ke::Circle* placed_object);

	void assignScale(long double space_scale, long double planet_scale, long double star_scale, float shader_scale, float brightness_scale);


	void addObject(objvector::iterator& selected_object,
		ObjectBuffer* object_data, const sf::Vector2f& position,
		const sf::Vector2f& viewSize, const sf::Vector2f& winSize, const std::string& name);

	void addObject(ObjectBuffer* object_data, const sf::Vector2f& position, // without selected_object
		const sf::Vector2f& viewSize, const sf::Vector2f& winSize, const std::string& name, const sf::Vector2<double>& velocity);

	void addObjectParallelly(ObjectBuffer object_data, const sf::Vector2f& position, // without selected_object
		const sf::Vector2f& viewSize, const sf::Vector2f& winSize, const std::string& name, const sf::Vector2<double>& velocity);

	void clearObjects(const sf::Vector2f& viewsize);

	void createObjectPreview(ObjectBuffer* object_data, objvector::iterator selected_object, iconvector::iterator selected_icon);
	void createObjectPreview(ObjectBuffer* object_data, objvector::iterator selected_object);
	void createObjectPreview(ObjectBuffer* object_data);
	void deleteObject(objvector::iterator& selected_object);

	void updateObjects(float dt, unsigned int time_scale, float sim_speed);
	void updateObjectPreview(objvector::iterator selected_object, 
		const MousePosition& mousePosition, const sf::Vector2f& viewSize, const sf::Vector2f& winSize);

	void checkName(std::string& name); // leave unstatic

private:

	std::vector<std::unique_ptr<SpaceObject>>* m_objects;

	ke::Circle* m_orbit_preview;
	ke::Rectangle* m_distance_preview;
	ke::Circle* m_placed_object;

	long double m_space_scale;
	long double m_planet_scale;
	long double m_star_scale;
	float m_shader_scale;
	float m_brightness_scale;




	// threads

	std::vector<std::future<void>> m_calculationThreads;
};