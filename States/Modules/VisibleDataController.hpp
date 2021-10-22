#pragma once

#include "States/State.hpp"

#include "Space Objects/Planet.hpp"
#include "Space Objects/Star.hpp"
#include "Space Objects/CenterOfMass.hpp"
#include "Space Objects/ObjectIcon.hpp"
#include "Equasions/Equasions.hpp"
#include "Equasions/Constants.hpp"

#define objvector std::vector<std::unique_ptr<SpaceObject>>


class VisibleDataController
{
public:

	VisibleDataController();

	virtual ~VisibleDataController();

	void assign(
		std::vector<std::unique_ptr<ke::Button>>* symbols,
		std::unordered_map<std::string, std::unique_ptr<ke::InputButton>>* values,
		std::vector<std::unique_ptr<ke::Button>>* units,
		std::vector<std::unique_ptr<ke::Button>>* modifiers,
		ke::InputButton* object_name,
		objvector* objects);


	void assignScale(long double space_scale, long double planet_scale, long double star_scale);


	void loadData(objvector::iterator selected_object, const sf::Vector2f& winSize);
	void setEmpty();

	void updateStaticData(objvector::iterator selected_object, ke::InputButton* object_name);
	void updateDynamicData(objvector::iterator selected_object);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	void checkInputString();


private:


	void updateDistanceBlocks(objvector::iterator selected_object);


	std::vector<std::unique_ptr<SpaceObject>>* m_objects;

	std::vector<std::unique_ptr<ke::Button>>* m_symbols;
	std::unordered_map<std::string, std::unique_ptr<ke::InputButton>>* m_values;
	std::vector<std::unique_ptr<ke::Button>>* m_units;

	std::vector<std::unique_ptr<ke::Button>>* m_modifiers;
	ke::InputButton* m_object_name;

	std::vector<ke::Colorf> m_colors;

	long double m_space_scale;
	long double m_planet_scale;
	long double m_star_scale;
};