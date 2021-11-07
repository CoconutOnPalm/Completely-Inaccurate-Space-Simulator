#pragma once

#include "States/State.hpp"

//#include "KEngine/Algorithms.hpp"


enum QUIT_OverlayQuitStatus
{
	QS_NOT_QUITTING,
	QUITTING,
	QUITTING_AND_SAVING,
	CLOSING_OVRL
};



class QuitOverlay
{
public:

	QuitOverlay(const sf::Vector2f& winSize);
	~QuitOverlay();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	OverlayQuitCode quitStatus() const;

	void render(sf::RenderWindow* window);

private:

	OverlayQuitCode m_quitCode;

	ke::Button m_button;
	//ke::Button m_quit_button;
	std::unordered_map<std::string, ke::Button> m_buttons;
	std::array<ke::Colorf, 3> m_buttonColors;

};

