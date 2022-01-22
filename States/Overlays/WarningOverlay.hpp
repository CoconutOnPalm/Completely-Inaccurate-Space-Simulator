#pragma once


#include "States/State.hpp"


class WarningOverlay
{
public:

	WarningOverlay(const std::wstring& message, const sf::Vector2f & winSize);
	~WarningOverlay();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	OverlayQuitCode quitStatus() const;

	void render(sf::RenderWindow* window);

private:

	OverlayQuitCode m_quitCode;

	ke::Button m_background;
	ke::Button m_ok;
	ke::Button m_cancel;
	
	ke::Colorf ok_color;
	ke::Colorf cancel_color;
};

