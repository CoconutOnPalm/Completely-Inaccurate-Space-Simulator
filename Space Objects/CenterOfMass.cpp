#include "CenterOfMass.hpp"

CenterOfMass::CenterOfMass(long double radius, float outline_thickness)
{
	p_name = "Center of Mass";
	p_type = CENTER_OF_MASS;

	object.physics()->setMass(ke::Settings::MinimumAbsoluteMass());

	object.create(radius, sf::Vector2f(0, 0), ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::MIDDLE_MIDDLE, sf::Color::Transparent, sf::Color::Transparent, outline_thickness, sf::Color(128, 128, 128, 192));

	p_click_radius.create(1, { 0, 0 }, ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::MIDDLE_MIDDLE,
		sf::Color::Transparent, sf::Color::Transparent);
	p_click_radius.setActiveStatus(false);
}

CenterOfMass::~CenterOfMass()
{

}

bool CenterOfMass::update(float dt)
{
	return false;
}

void CenterOfMass::updatePhysicalData()
{

}

void CenterOfMass::render(sf::RenderWindow* window)
{
	object.render(window);
}
