#pragma once

#include <KEngine/Algorithms.hpp>
#include <KEngine/Graphics.hpp>

#include "Space Objects/SpaceObject.hpp"
#include "Settings/AppSettings.hpp"



enum class ExternalWindowStatus
{
	OPENED,
	CLOSED
};



class DetailedDataWindow
{
public:

	DetailedDataWindow();
	~DetailedDataWindow();


	void Init(SpaceObject* selected_object);

	void Load(SpaceObject* selected_object);

	void Update();

	void UpdateMouse();
	void UpdateEvents();

	void Render();

	void UpdateDeltaTime();

	void End();


	ExternalWindowStatus status() const;


private:

	void initGUI();
	void loadData();


	ExternalWindowStatus m_status;

	sf::Clock _dtClock;
	float dt; // delta time;

	sf::RenderWindow window;
	sf::View view;

	sf::Event event;

	bool m_windowHolded;
	sf::Vector2f m_windowCatchDiff;

	// mouse position

	sf::Vector2f mPosView;	 // relative to view
	sf::Vector2f mPosWindow; // relative to window
	sf::Vector2f mPosScreen; // relative to screen


	// refered object

	SpaceObject* m_selected_object;

	
	////////   G U I   ///////

	ke::Button m_titlebar;
	ke::Button m_exitButton;


	ke::Button m_icon;
	ke::Button m_name;

	ke::Button m_mass;
	ke::Button m_radius;
	ke::Button m_density;
	ke::Button m_surface_g;
	ke::Button m_firts_space_speed;
	ke::Button m_second_space_speed;
};
