#pragma once

#include <KEngine/Algorithms.hpp>
#include <KEngine/Graphics.hpp>
#include <KEngine/Audio.hpp>

#include <SFML/Graphics.hpp>

#include "Settings/AppSettings.hpp"
#include "Equasions/Constants.hpp"

#include <sstream>
#include <iomanip>
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <future>
#include <thread>
#include <functional>


enum class StateQuitCode
{
	NOT_QUITTING,
	STATE_QUIT,
	APP_END,
	ANIMATION_OUTRO
};


enum class OverlayQuitCode
{
	NOT_QUITTING,
	QUITTING,

	QUITTING_WITH_OBJECT,
	QUITTING_WITHOUT_OBJECT,

	QUITTING_AND_SAVING,
	CLOSING_OVRL,

	CHANGING_SETTINGS
};


enum class STATE
{
	NONE,
	INTRO,
	MAIN_MENU,
	SETTINGS,
	SIM_OPENING,
	SIMULATION
};



struct MousePosition
{
	MousePosition(const sf::Vector2f& _view, const sf::Vector2f& _window, const sf::Vector2f& _screen)
		: byView(_view)
		, byWindow(_window)
		, byScreen(_screen)
	{};

	sf::Vector2f byView;
	sf::Vector2f byWindow;
	sf::Vector2f byScreen;
};



class State
{
public:

	State(sf::RenderWindow* sf_window, sf::View* sf_view, STATE current_state);
	virtual ~State();

	static void LoadStaticData(static std::vector<std::unique_ptr<State>>* states_vec);

	virtual void InitState() = 0;

	virtual void reloadState() = 0;

	virtual void updateEvents(const MousePosition& mousePosition, float dt) = 0;
	virtual void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event) = 0;


	virtual void renderBackground() = 0;
	virtual void renderByView() = 0;
	virtual void renderByWindow() = 0;

	virtual StateQuitCode Quit();


	StateQuitCode p_quitCode;


protected:

	static sf::RenderWindow* window;
	static sf::View* view;

	static sf::Vector2f winSize;  // window size
	static sf::Vector2f viewSize; // view size

	static std::vector<std::unique_ptr<State>>* states;

	static STATE p_current_state;


private:

};