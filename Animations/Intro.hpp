#pragma once

#include "States/State.hpp"
#include "States/MainMenu.hpp"

class IntroState;


void IS_start_intro_closing(State& iState);


class IntroState : public State
{
public:

	IntroState(sf::RenderWindow* sf_window, sf::View* sf_view);
	virtual ~IntroState();

	void InitState();

	void reloadState();


	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);


	void renderBackground();
	void renderByView();
	void renderByWindow();


	StateQuitCode Quit();

private:

	friend void IS_start_intro_closing(State& iState);

	bool m_intro_on;

	sf::Clock m_clock;
	float m_time;

	sf::Clock m_pause_clock;
	float m_pause_time;

	ke::Rectangle m_shader_mask;
	ke::Rectangle m_state_mask;
	ke::Rectangle m_KEngine_LOGO;

	ke::Colorf m_sm_color;

	sf::Shader m_shader;
};