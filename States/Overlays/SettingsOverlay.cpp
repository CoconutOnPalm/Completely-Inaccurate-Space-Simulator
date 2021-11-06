#include "SettingsOverlay.hpp"

SettingsOverlay::SettingsOverlay()
{

}

SettingsOverlay::~SettingsOverlay()
{

}

void SettingsOverlay::assign(sf::RenderWindow* window)
{
	m_window = window;
}

void SettingsOverlay::initUI()
{

}

void SettingsOverlay::loadObjects()
{

}

void SettingsOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{

}

void SettingsOverlay::updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event)
{

}

void SettingsOverlay::updateColors(const sf::Vector2f& mousePosition, const float dt)
{

}

QuickSettings& SettingsOverlay::output()
{
	return m_output;
}

void SettingsOverlay::render()
{

}
