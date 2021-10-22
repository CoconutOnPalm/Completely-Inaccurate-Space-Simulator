#pragma once

#include <SFML/Graphics.hpp>

#include <windows.h>


#include "States/State.hpp"
#include "States/MainMenu.hpp"
#include "States/WindowGui.hpp"
#include "Animations/Intro.hpp"

#include "Settings/AppSettings.hpp"

#include "States/Global/FileStorage.hpp"



class Application
{
public:

	Application();
	~Application();


	void Run();
	void End();


private:

	void InitWindow();
	void InitVariables();
	void InitObjects();
	void InitStates();


	void Update();

	void UpdateMouse();
	void UpdateEvents();

	void Render();

	void UpdateDeltaTime();



	sf::Clock _dtClock;
	float dt; // delta time;

	sf::RenderWindow window;
	sf::View view;

	sf::Event event;


	// mouse position

	sf::Vector2f mPosView;	 // relative to view
	sf::Vector2f mPosWindow; // relative to window
	sf::Vector2f mPosScreen; // relative to screen


	std::vector<std::unique_ptr<State>> states;


	// titlebar
	
};

