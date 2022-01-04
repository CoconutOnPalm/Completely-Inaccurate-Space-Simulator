#pragma once

#include "Space Objects/SpaceObject.hpp";
#include "States/State.hpp"
#include "ObjectController.hpp"
#include "VisibleDataController.hpp"


class Collider
{
public:

	Collider();
	~Collider();

	void assing(ObjectController* object_controller, const sf::Vector2f& winsize, long double space_scale);

	bool update(std::vector<std::unique_ptr<SpaceObject>>* objects, const float dt, std::vector<std::unique_ptr<SpaceObject>>::iterator& selected_object, const sf::Vector2f& viewsize, const sf::Vector2f& winsize);

	void renderBoooms(sf::RenderWindow* window);

	std::pair<std::string, std::string> deletedObjects() const;

private:

	long double m_space_scale;

	ke::Rectangle m_boom_mask;
	ke::Colorf m_mask_color;

	std::pair<std::string, std::string> m_objects_to_delete;

	std::list<std::pair<SpaceObject*, SpaceObject*>> m_collision_canditates;
	ObjectController* m_object_controller;
};

