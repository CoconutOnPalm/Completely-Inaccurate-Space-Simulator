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


class DistanceBlock;



class DetailedDataWindow
{
public:

	DetailedDataWindow();
	~DetailedDataWindow();


	void Run(SpaceObject* selected_object, ObjectBuffer buffer, long double space_scale);

	void End();

	void updateObjectPointer(SpaceObject* selected_object);

	void Init(SpaceObject* selected_object);
	void UpdateStaticData(ObjectBuffer buffer);
	void UpdateDynamicData(std::vector<ForceData> data);

	void loadData(SpaceObject* selected_object);

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


	SpaceObject* m_selected_object;

	
	////////   G U I   ///////


	ke::Slider m_slider;
	ke::HoldView m_view_holder;


	ke::Button m_titlebar;
	ke::Button m_exitButton;
	ke::Button m_maximizeButton;
	ke::Button m_minimizeButton;


	ke::Button m_icon;
	ke::Button m_name;

	ke::Rectangle m_icon_background;

	ke::Rectangle m_compartmentBar;


	// mass | radius | density | density | surface_g | fss | sss

	std::vector<std::unique_ptr<ke::Button>> m_signs;
	std::vector<std::unique_ptr<ke::Button>> m_values;
	std::vector<std::unique_ptr<ke::Button>> m_units;

	std::vector<std::unique_ptr<DistanceBlock>> m_force_data_blocks;

	std::vector<ForceData> m_force_data;


	std::array<ke::Colorf, 24> m_colors;
};





class DistanceBlock
{
public:
	DistanceBlock(const sf::Vector2f& position, const sf::Vector2f& winsize);
	~DistanceBlock();

	void updatePosition(const sf::Vector2f& position, const sf::Vector2f& winsize);
	sf::Vector2f getPosition() const;
	void update(const SpaceObject* selected_object, const ForceData& refered_object);

	void setActive(bool active);
	bool active() const;

	void render(sf::RenderWindow* window);

private:

	bool m_active;

	ke::Button m_objectName;
	ke::Button m_distance_sign;
	ke::Button m_distance;
	ke::Button m_force_sign;
	ke::Button m_force;

	//std::array<ke::Colorf, 5> m_colors;
};