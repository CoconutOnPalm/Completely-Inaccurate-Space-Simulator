#pragma once


#include "States/State.hpp"
#include "Space Objects/ObjectBuffer.hpp"
#include "States/Global/FileStorage.hpp"
#include "States/Global/TypeMap.hpp"




enum class OBJECT_LIRARY_SORTING_BY
{
	SYSTEMS,
	A_Z,
	Z_A
};



class Tile;
class SystemNameTile;


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

	OverlayQuitCode quitStatus() const;
	void resetQuitStatus();

	void render();

	bool active() const;
	void activate();
	void deactivate();

	ObjectBuffer* output();
	void resetOutput();

private:


	void updateObjectInfo();
	void updateObjectPosition();

	void updateSystemSorting();
	void updateAZSorting();
	void updateZASorting();

	//std::wstring findSystemName(std::vector<std::unique_ptr<ObjectIcon>>::iterator selected);


	////////////////////////////////

	sf::RenderWindow* m_window;

	OverlayQuitCode m_quitCode;
	bool m_active;

	ObjectBuffer m_output;

	std::vector<std::unique_ptr<Tile>>::iterator m_selected;
	std::vector<std::unique_ptr<Tile>>::iterator m_invaded_icon;


	// backgrounds
	ke::Rectangle m_background;
	ke::Rectangle m_top_section;
	ke::Rectangle m_right_section;

	// top section
	ke::InputButton m_search_box;
	std::array<ke::Button, 3> m_filtering_options;

	OBJECT_LIRARY_SORTING_BY m_sorting_type;
	std::string m_filter;

	// right section
	ke::Button m_add_button;
	ke::Button m_close_button;


	std::array<ke::Button, 6> m_object_info; // | name | mass | radius | class | subtype | system name |

	ke::Button m_quick_info; // name and class for icons inv by mouse

	// other

	ke::Slider m_slider;
	ke::HoldView m_view_barrier;


	// objects

	//std::vector<std::vector<std::unique_ptr<Tile>>::iterator> m_system_begining;
	//std::vector<std::pair<unsigned int, unsigned int>> m_system_bounds;
	//std::vector<std::unique_ptr<Tile>> m_default_ptr_layout;
	std::vector<std::unique_ptr<SystemNameTile>> m_system_names;
	std::vector<std::unique_ptr<Tile>> m_objects;
	std::vector<std::pair<int , std::string>> m_sorted_object_order;
	

	std::list<std::vector<std::unique_ptr<Tile>>::iterator> m_on_screen;

	std::vector<ke::Colorf> m_obj_colors;
	std::array<ke::Colorf, 16> m_GUI_colors;

	float m_next_position;


	sf::View m_obj_view;
	sf::Vector2f mPosView; // mouse position by obj_view;

	const int m_icons_per_row;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class Tile
{
public:

	Tile(
		const std::string& icon_filename,		// <-- ObjectIcon parameter
		const std::string& object_filename,		// <-- ObjectIcon parameter
		const sf::Vector2f& size,				// <-- ObjectIcon parameter
		const sf::Vector2f& position,			// <-- ObjectIcon parameter
		const std::string& obj_name,			// <-- ObjectIcon parameter
		int type,								// <-- ObjectIcon parameter
		int _class,								// <-- ObjectIcon parameter
		int subtype,							// <-- ObjectIcon parameter
		long double obj_mass,					// <-- ObjectIcon parameter
		long double obj_radius,					// <-- ObjectIcon parameter
		float brightness,						// <-- ObjectIcon parameter
		const sf::Vector3f& color, 				// <-- ObjectIcon parameter
		std::string system_name);				// <-- system name

	~Tile();

	sf::Vector2f defaultPosition() const;
	std::string systemName() const;
	std::string name() const;
	ObjectIcon& Icon();
	

private:

	ObjectIcon m_icon;
	std::string m_system_name;
	sf::Vector2f m_default_position;
};


class SystemNameTile
{
public:

	SystemNameTile(
		const sf::Vector2f& size,			// <-- ke::Button params that have to be used
		const sf::Vector2f& position,		// <-- ke::Button params that have to be used
		int origin,							// <-- ke::Button params that have to be used
		const sf::Texture* texture,			// <-- ke::Button params that have to be used
		const std::wstring& text,			// <-- ke::Button params that have to be used
		unsigned int character_size,		// <-- ke::Button params that have to be used
		int text_position,					// <-- ke::Button params that have to be used
		const sf::Color& object_color,		// <-- ke::Button params that have to be used
		const sf::Color& text_color,		// <-- ke::Button params that have to be used
		float outline_thickness,			// <-- ke::Button params that have to be used
		const sf::Color& outline_color,		// <-- ke::Button params that have to be used
		float rotation,						// <-- ke::Button params that have to be used
		unsigned int text_style,			// <-- ke::Button params that have to be used
		const sf::Vector2f& text_shift);	// <-- ke::Button params that have to be used

	~SystemNameTile();

	ke::Button& Button();
	std::string& name();
	sf::Vector2f defaultPosition() const;

private:

	ke::Button m_tile;
	std::string m_str_name;
	sf::Vector2f m_default_position;
};