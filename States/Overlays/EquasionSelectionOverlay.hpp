#pragma once


#include "States/State.hpp"



class EquasionSelectionOverlay
{
public:

	EquasionSelectionOverlay(const sf::Vector2f& winSize);
	~EquasionSelectionOverlay();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	OverlayQuitCode quitStatus() const;

	void render(sf::RenderWindow* window);

private:

	OverlayQuitCode m_quitCode;

	int m_selected;

	ke::Button m_background;
	ke::Button m_ok;
	ke::Button m_cancel;

	ke::Button m_r;
	ke::Button m_r2;
	ke::Button m_r3;

	std::array<ke::Colorf, 5> m_colors;
};

