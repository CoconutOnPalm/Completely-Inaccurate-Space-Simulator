#include "Application.hpp"

Application::Application()
	: dt(0.f)
{
	AppSettings::Init();

	this->InitWindow();
	this->InitStates();
	this->InitVariables();
	this->InitObjects();

	FileStorage::LinkFiles();

	//IS_start_intro_closing(*(states.back().get()));
}

Application::~Application()
{

}


void Application::InitWindow()
{
	window.create(sf::VideoMode(AppSettings::DefaultWindowSize().x, AppSettings::DefaultWindowSize().y), "Completely Inaccurate Space Simulator", (AppSettings::WindowStyle() != sf::Style::Fullscreen) ? (sf::Style::None) : (sf::Style::Fullscreen));
	window.setFramerateLimit(AppSettings::MaxMenuFPS());


	view.setSize(sf::Vector2f(window.getSize()));
	view.setCenter(view.getSize() / 2.f);
}

void Application::InitVariables()
{
	
}

void Application::InitObjects()
{
	for (auto& itr : states)
		itr->InitState();
}

void Application::InitStates()
{
	states.reserve(2);

	states.emplace_back(std::make_unique<WindowGui>(&window, &view));
	states.emplace_back(std::make_unique<IntroState>(&window, &view));

	State::LoadStaticData(&states);
}



////////////////////////////////////////////////////////////////



void Application::Run()
{
	while (window.isOpen())
	{
		this->Update();
		this->Render();
		this->UpdateDeltaTime();
	}
}



////////////////////////////////////////////////////////////////



void Application::Update()
{
	this->UpdateMouse();
	this->UpdateEvents();
}

void Application::UpdateMouse()
{
	mPosScreen = sf::Vector2f(sf::Mouse::getPosition());
	mPosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
	mPosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void Application::UpdateEvents()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->End();

		
		for (auto& itr : states)
			itr->updatePollEvents({mPosView, mPosWindow, mPosScreen}, dt, event);
	}


	for (auto& itr : states)
	{
		itr->updateEvents({ mPosView, mPosWindow, mPosScreen }, dt);

		if (itr->Quit() == APP_END)
			this->End();
	}
}



////////////////////////////////////////////////////////////////



void Application::Render()
{
	window.clear(sf::Color::Black);


	window.setView(window.getDefaultView());

	for (auto itr = states.rbegin(), eoi = states.rend(); itr != eoi; itr++)
		(*itr)->renderBackground();

	window.setView(view);

	for (auto itr = states.rbegin(), eoi = states.rend(); itr != eoi; itr++)
		(*itr)->renderByView();

	window.setView(window.getDefaultView());

	for (auto itr = states.rbegin(), eoi = states.rend(); itr != eoi; itr++)
		(*itr)->renderByWindow();


	window.setView(view);


	window.display();
}



////////////////////////////////////////////////////////////////



void Application::UpdateDeltaTime()
{
	dt = _dtClock.restart().asSeconds();
}



////////////////////////////////////////////////////////////////



void Application::End()
{
	window.close();

	/*sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	texture.copyToImage().saveToFile("Textures/screenshot.jpg");*/
}