#include "State.hpp"

State::State(sf::RenderWindow* sf_window, sf::View* sf_view, int current_state)
	: p_quitCode(StateQuitCode::NOT_QUITTING)
{
	window = sf_window;
	view = sf_view;

	winSize = sf::Vector2f(window->getSize());
	viewSize = view->getSize();

	p_current_state = current_state;

	if (p_current_state != SIMULATION)
		window->setFramerateLimit(AppSettings::MaxMenuFPS());
	else
		window->setFramerateLimit(AppSettings::MaxSimulationFPS());
}



sf::RenderWindow* State::window;
sf::View* State::view;

sf::Vector2f State::winSize;
sf::Vector2f State::viewSize;

std::vector<std::unique_ptr<State>>* State::states;

int State::p_current_state;


State::~State()
{
	
}

void State::LoadStaticData(static std::vector<std::unique_ptr<State>>* states_vec)
{
	states = states_vec;
}

int State::Quit()
{
	return p_quitCode;
}
