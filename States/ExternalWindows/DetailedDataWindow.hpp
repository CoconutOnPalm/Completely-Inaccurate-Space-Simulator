#pragma once

#include <KEngine/Algorithms.hpp>
#include <KEngine/Graphics.hpp>

#include "Space Objects/SpaceObject.hpp"
#include "Settings/AppSettings.hpp"
#include "Space Objects/ObjectBuffer.hpp"

#include <future>


class ObjectBuffer;

enum class ExternalWindowStatus
{
	OPENED,
	CLOSED
};


enum class WindowSizingMode
{
	NONE,
	HORIZONTALLY,
	VERTICALLY,
	ALLATONCE
};



class DetailedDataWindow
{
public:

	DetailedDataWindow();
	~DetailedDataWindow();


	void Run(SpaceObject* selected_object);

	void End();

	void Init(SpaceObject* selected_object);
	void UpdateDynamicData(ObjectBuffer buffer);
	void UpdateStaticData(ObjectBuffer buffer);

	void lock();
	void unlock();
	bool locked();

	ExternalWindowStatus status() const;


private:


	void UpdateMouse();
	void UpdateEvents();

	void Render();

	void UpdateDeltaTime();

	void Close();

	void loadData();

	void initGUI();
	void updateGUI();


	ExternalWindowStatus m_status;
	bool m_running;
	bool m_locked;

	sf::Clock _dtClock;
	float dt; // delta time;

	sf::RenderWindow window;
	sf::View view;
	sf::View topView;

	const sf::Vector2f m_default_windowSize;
	const sf::Vector2f m_maximum_windowSize;
	const sf::Vector2f m_minimum_windowSize;


	sf::Event event;

	bool m_windowHolded;
	sf::Vector2f m_windowCatchDiff;

	// mouse position

	sf::Vector2f mPosView;	 // relative to view
	sf::Vector2f mPosWindow; // relative to window
	sf::Vector2f mPosScreen; // relative to screen


	sf::Cursor m_cursor_default;
	sf::Cursor m_cursor_size_horizontal;
	sf::Cursor m_cursor_size_vertical;
	sf::Cursor m_cursor_all_at_once;

	WindowSizingMode m_sizing_mode;

	bool m_window_size_clicked;
	bool m_fullscreen_on;


	// refered object

	SpaceObject* m_selected_object;

	
	////////   G U I   ///////

	ke::Button m_titlebar;
	ke::Button m_exitButton;
	ke::Button m_maximizeButton;
	ke::Button m_minimizeButton;


	ke::Button m_icon;
	ke::Button m_name;

	ke::Rectangle m_compartmentBar;


	// mass | radius | density | density | surface_g | fss | sss

	std::vector<std::unique_ptr<ke::Button>> m_signs;
	std::vector<std::unique_ptr<ke::Button>> m_values;

	//ke::Button m_mass;
	//ke::Button m_mass_sign;
	//ke::Button m_radius;
	//ke::Button m_radius_sign;
	//ke::Button m_density;
	//ke::Button m_density_sign;
	//ke::Button m_surface_g;
	//ke::Button m_surface_g_sign;
	//ke::Button m_firts_space_speed;
	//ke::Button m_firts_space_speed_sign;
	//ke::Button m_second_space_speed;
	//ke::Button m_second_space_speed_sign;
};
