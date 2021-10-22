#pragma once


#include "States/State.hpp"
#include "Space Objects/ObjectBuffer.hpp"
#include "States/Global/FileStorage.hpp"
#include "States/Global/TypeMap.hpp"



enum OBJECT_LIBRARY_OverlayQuitStatus
{
	OL_NOT_QUITTING,
	QUITTING_WITH_OBJECT,
	QUITTING_WITHOUT_OBJECT,
};


class ObjectLibraryOverlay
{
public:

	ObjectLibraryOverlay();
	~ObjectLibraryOverlay();

	void assign(sf::RenderWindow* window);

	void initUI();

	void loadObjects();

	void updateEvents(const MousePosition& mousePosition, float dt);
	void updatePollEvents(const MousePosition& mousePosition, float dt, sf::Event& event);

	void updateColors(const sf::Vector2f& mousePosition, const float dt);

	int quitStatus() const;

	void render();

	bool active() const;
	void activate();
	void deactivate();

	ObjectBuffer* output();

private:


	void updateObjectInfo();

	std::wstring findSystemName(std::vector<std::unique_ptr<ObjectIcon>>::iterator selected);


	////////////////////////////////

	sf::RenderWindow* m_window;

	int m_quitStatus;
	bool m_active;

	ObjectBuffer m_output;

	std::vector<std::unique_ptr<ObjectIcon>>::iterator m_selected;


	// backgrounds
	ke::Rectangle m_background;
	ke::Rectangle m_top_section;
	ke::Rectangle m_right_section;

	// top section
	ke::InputButton m_search_box;
	std::array<ke::Button, 4> m_filtering_options;

	// right section
	ke::Button m_add_button;
	ke::Button m_close_button;


	std::array<ke::Button, 6> m_object_info; // | name | mass | radius | class | subtype | system name |

	ke::Button m_hints;

	// other

	ke::Slider m_slider;
	ke::HoldView m_view_barrier;


	// objects

	std::vector<std::unique_ptr<ke::Button>> m_system_names;
	std::vector<std::vector<std::unique_ptr<ObjectIcon>>::iterator> m_system_begining;
	std::vector<std::pair<unsigned int, unsigned int>> m_system_bounds;
	std::vector<std::unique_ptr<ObjectIcon>> m_objects;
	

	std::list<ObjectIcon*> m_on_screen;

	std::vector<ke::Colorf> m_obj_colors;
	std::array<ke::Colorf, 12> m_GUI_colors;

	float m_next_position;


	sf::View m_obj_view;
	sf::Vector2f mPosView; // mouse position by obj_view;
};

