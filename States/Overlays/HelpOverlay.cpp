#include "HelpOverlay.hpp"

HelpOverlay::HelpOverlay(const sf::Vector2f& winsize)
	: m_quitCode(OverlayQuitCode::NOT_QUITTING)
{
	m_help_window.create(winsize, { 0, 0 }, ke::Origin::LEFT_TOP, "Textures/StateTextures/Simulation/Help.png");
}

HelpOverlay::~HelpOverlay()
{

}

void HelpOverlay::updateEvents(const MousePosition& mousePosition, float dt)
{
	
}

void HelpOverlay::updatePollEvents(const sf::Vector2f& mousePosition, float dt, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
		m_quitCode = OverlayQuitCode::QUITTING;
}

OverlayQuitCode HelpOverlay::quitStatus() const
{
	return m_quitCode;
}

void HelpOverlay::render(sf::RenderWindow* window)
{
	m_help_window.render(window);
}
