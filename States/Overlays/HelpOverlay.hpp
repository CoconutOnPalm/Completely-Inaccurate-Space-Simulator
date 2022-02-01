#pragma once

#include "States/State.hpp"


class HelpOverlay
{
public:

	HelpOverlay(const sf::Vector2f& winsize);
	~HelpOverlay();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const sf::Vector2f& mousePosition, float dt, sf::Event& event);

	OverlayQuitCode quitStatus() const;

	void render(sf::RenderWindow* window);

private:

	OverlayQuitCode m_quitCode;

	ke::Button m_help_window;
};

