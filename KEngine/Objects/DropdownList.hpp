#pragma once

#include "ObjectParent.hpp"
#include "Button.hpp"

#include <memory>
#include <vector>
#include <algorithm>


namespace ke
{

	/// <summary>
	/// KEngine Dropdownlist is a list of KEngine Buttons that you can choose (Works like window settings in a typical game)
	/// </summary>
	class DropdownList 
	{
	public:

		/// <summary>
		/// Default DropdownList constructor
		/// </summary>
		DropdownList();


		////////////////////////////////


		/// <summary>
		/// DropdownList constructor
		/// </summary>
		/// <param name="size">selected option size</param>
		/// <param name="position">object position</param>
		/// <param name="default_texture">selected option texture</param>
		/// <param name="default_text">selected option text</param>
		/// <param name="default_character_size">selected option character size</param>
		/// <param name="default_text_position">selected option text position</param>
		/// <param name="default_object_color">selected option object color</param>
		/// <param name="default_text_color">selected option text color</param>
		/// <param name="default_outline_thickness">selected option outline thickness</param>
		/// <param name="default_outline_color">selected option outline color</param>
		/// <param name="default_text_style">selected option text style</param>
		/// <param name="default_text_shift">selected option text shift</param>
		/// <param name="default_font">selected option text font</param>
		/// <param name="expanded">is list expanded as it gets greated?</param>
		/// <param name="acitve">is object is processed and rendered</param>
		DropdownList(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			const sf::Texture* default_texture,
			const std::wstring& default_text = L"",
			unsigned int default_character_size = 20,
			int default_text_position = MIDDLE_MIDDLE,
			const sf::Color& default_object_color = sf::Color::Transparent,
			const sf::Color& default_text_color = sf::Color::White,
			float default_outline_thickness = 0,
			const sf::Color& default_outline_color = sf::Color::Transparent,
			unsigned int default_text_style = sf::Text::Regular,
			const sf::Vector2f& default_text_shift = sf::Vector2f(0, 0),
			int default_font = Arial,
			bool expanded = false,
			bool acitve = true);



		/// <summary>
		/// DropdownList constructor
		/// </summary>
		/// <param name="size">selected option size</param>
		/// <param name="position">object position</param>
		/// <param name="default_texture_filename">path to selected option texture</param>
		/// <param name="default_text">selected option text</param>
		/// <param name="default_character_size">selected option character size</param>
		/// <param name="default_text_position">selected option text position</param>
		/// <param name="default_object_color">selected option object color</param>
		/// <param name="default_text_color">selected option text color</param>
		/// <param name="default_outline_thickness">selected option outline thickness</param>
		/// <param name="default_outline_color">selected option outline color</param>
		/// <param name="default_text_style">selected option text style</param>
		/// <param name="default_text_shift">selected option text shift</param>
		/// <param name="default_font">selected option text font</param>
		/// <param name="expanded">is list expanded as it gets greated?</param>
		/// <param name="acitve">is object is processed and rendered</param>
		DropdownList(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			const std::string& default_texture_filename,
			const std::wstring& default_text = L"",
			unsigned int default_character_size = 20,
			int default_text_position = MIDDLE_MIDDLE,
			const sf::Color& default_object_color = sf::Color::Transparent,
			const sf::Color& default_text_color = sf::Color::White,
			float default_outline_thickness = 0,
			const sf::Color& default_outline_color = sf::Color::Transparent,
			unsigned int default_text_style = sf::Text::Regular,
			const sf::Vector2f& default_text_shift = sf::Vector2f(0, 0),
			int default_font = Arial,
			bool expanded = false,
			bool acitve = true);


		////////////////////////////////


		/// <summary>
		/// DropdownList destructor
		/// </summary>
		/// <remarks>
		/// nothing is inside
		/// </remarks>
		virtual ~DropdownList();


		////////////////////////////////


		/// <summary>
		/// DropdownList create function
		/// </summary>
		/// <param name="size">selected option size</param>
		/// <param name="position">object position</param>
		/// <param name="default_texture">selected option texture</param>
		/// <param name="default_text">selected option text</param>
		/// <param name="default_character_size">selected option character size</param>
		/// <param name="default_text_position">selected option text position</param>
		/// <param name="default_object_color">selected option object color</param>
		/// <param name="default_text_color">selected option text color</param>
		/// <param name="default_outline_thickness">selected option outline thickness</param>
		/// <param name="default_outline_color">selected option outline color</param>
		/// <param name="default_text_style">selected option text style</param>
		/// <param name="default_text_shift">selected option text shift</param>
		/// <param name="default_font">selected option text font</param>
		/// <param name="expanded">is list expanded as it gets greated?</param>
		/// <param name="acitve">is object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			const sf::Texture* default_texture,
			const std::wstring& default_text = L"",
			unsigned int default_character_size = 20,
			int default_text_position = MIDDLE_MIDDLE,
			const sf::Color& default_object_color = sf::Color::Transparent,
			const sf::Color& default_text_color = sf::Color::White,
			float default_outline_thickness = 0,
			const sf::Color& default_outline_color = sf::Color::Transparent,
			unsigned int default_text_style = sf::Text::Regular,
			const sf::Vector2f& default_text_shift = sf::Vector2f(0, 0),
			int default_font = Arial,
			bool expanded = false,
			bool acitve = true);



		/// <summary>
		/// DropdownList create function
		/// </summary>
		/// <param name="size">selected option size</param>
		/// <param name="position">object position</param>
		/// <param name="default_texture_filename">path to selected option texture</param>
		/// <param name="default_text">selected option text</param>
		/// <param name="default_character_size">selected option character size</param>
		/// <param name="default_text_position">selected option text position</param>
		/// <param name="default_object_color">selected option object color</param>
		/// <param name="default_text_color">selected option text color</param>
		/// <param name="default_outline_thickness">selected option outline thickness</param>
		/// <param name="default_outline_color">selected option outline color</param>
		/// <param name="default_text_style">selected option text style</param>
		/// <param name="default_text_shift">selected option text shift</param>
		/// <param name="default_font">selected option text font</param>
		/// <param name="expanded">is list expanded as it gets greated?</param>
		/// <param name="acitve">is object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			const std::string& default_texture_filename,
			const std::wstring& default_text = L"",
			unsigned int default_character_size = 20,
			int default_text_position = MIDDLE_MIDDLE,
			const sf::Color& default_object_color = sf::Color::Transparent,
			const sf::Color& default_text_color = sf::Color::White,
			float default_outline_thickness = 0,
			const sf::Color& default_outline_color = sf::Color::Transparent,
			unsigned int default_text_style = sf::Text::Regular,
			const sf::Vector2f& default_text_shift = sf::Vector2f(0, 0),
			int default_font = Arial,
			bool expanded = false,
			bool acitve = true);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Adds an "option" to the list
		/// </summary>
		/// <param name="texture">SMLF texture</param>
		/// <param name="text">object text</param>
		/// <param name="character_size">text size</param>
		/// <param name="text_position">text position relative to the object</param>
		/// <param name="object_color">this "option" color</param>
		/// <param name="text_color">this "option" text color</param>
		/// <param name="outline_thickness">this "option" outline thickness</param>
		/// <param name="outline_color">this "option" outline color</param>
		/// <param name="text_style">SFML text style</param>
		/// <param name="text_shift">Vector2f correcting tex position</param>
		/// <param name="font">KEngie font</param>
		void addMember(
			const sf::Texture* texture,
			const std::wstring& text = L"",
			unsigned int character_size = 20,
			int text_position = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& text_color = sf::Color::White,
			float outline_thickness = 0,
			const sf::Color& outline_color = sf::Color::Transparent,
			unsigned int text_style = sf::Text::Regular,
			const sf::Vector2f& text_shift = sf::Vector2f(0, 0),
			int font = Arial);



		/// <summary>
		/// Adds an "option" to the list
		/// </summary>
		/// <param name="filename">path to texture</param>
		/// <param name="text">object text</param>
		/// <param name="character_size">text size</param>
		/// <param name="text_position">text position relative to the object</param>
		/// <param name="object_color">this "option" color</param>
		/// <param name="text_color">this "option" text color</param>
		/// <param name="outline_thickness">this "option" outline thickness</param>
		/// <param name="outline_color">this "option" outline color</param>
		/// <param name="text_style">SFML text style</param>
		/// <param name="text_shift">Vector2f correcting tex position</param>
		/// <param name="font">KEngie font</param>
		void addMember(
			const std::string& filename,
			const std::wstring& text = L"",
			unsigned int character_size = 20,
			int text_position = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& text_color = sf::Color::White,
			float outline_thickness = 0,
			const sf::Color& outline_color = sf::Color::Transparent,
			unsigned int text_style = sf::Text::Regular,
			const sf::Vector2f& text_shift = sf::Vector2f(0, 0),
			int font = Arial);


		////////////////////////////////


		/// <summary>
		/// Deletes all options from the object
		/// </summary>
		void deleteList();


		////////////////////////////////


		/// <summary>
		/// Removes member ("option") by its position
		/// </summary>
		/// <param name="member_number">member position</param>
		void removeMember(unsigned int member_number);


		/// <summary>
		/// Removes member ("option") by its ID
		/// </summary>
		/// <param name="member_id">member ID</param>
		void removeMemberByID(int member_id);



		////////////////////////////////////////////////////////////////


		
		/// <summary>
		/// Sets given member as active
		/// </summary>
		/// <param name="member_number">member position</param>
		void setMemberAsActive(unsigned int member_number);


		////////////////////////////////


		/// <summary>
		/// Swaps to memmbers
		/// </summary>
		/// <param name="mn_1">position of 1st member</param>
		/// <param name="mn_2">position of 2nd member</param>
		void swapMembers(unsigned int mn_1, unsigned int mn_2);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// returns vector of members 
		/// </summary>
		/// <returns>pointer to members</returns>
		std::vector<std::unique_ptr<Button>>* getMembers();


		/// <summary>
		/// returns pointer to selected member
		/// </summary>
		/// <returns>pointer to selected memberr</returns>
		Button* getSelected();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// updates members position
		/// </summary>
		void updateMembersPosition();


		////////////////////////////////////////////////////////////////


		/// <summary>
		/// checks if objects is actove (is proccessed and rendered)
		/// </summary>
		/// <returns>if active, true</returns>
		bool isActive() const;


		/// <summary>
		/// sets status of the objects (active or not)
		/// </summary>
		/// <param name="status">new status</param>
		void setActiveStatus(bool status = true);


		////////////////////////////////


		/// <summary>
		/// checks if the list is expanded
		/// </summary>
		/// <returns>if expanded, true</returns>
		bool Expanded() const;


		/// <summary>
		/// expands or collapses the list
		/// </summary>
		/// <param name="status">new expand status</param>
		void setExpandStatus(bool status);


		////////////////////////////////


		/// <summary>
		/// returns ID of selected member
		/// </summary>
		/// <returns></returns>
		int getSelectedID() const;


		/// <summary>
		/// returns pointer to member ID list
		/// </summary>
		/// <returns>member ID list</returns>
		const std::vector<int>* getMembersID() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Updates the list - use it to make the whole object work. use in pollEvent loop
		/// </summary>
		/// <param name="mousePosition">mouse position</param>
		/// <param name="event">SFML event</param>
		/// <param name="button">SMFL button</param>
		/// <param name="view">SMFL viev</param>
		/// <returns>if something with selected member changed - true</returns>
		bool update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// draws object on screen
		/// </summary>
		/// <param name="window">SFML window where object is rendered</param>
		void render(sf::RenderWindow* window);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// checks if object is created
		/// </summary>
		/// <returns>if object is created, true</returns>
		bool created() const;





	private:


		std::unique_ptr<Button>					m_selected; // selected object
		std::vector<std::unique_ptr<Button>>	m_members;	// members 

		std::vector<float>	m_member_pos;	// members Y position
		std::vector<int>	m_member_id;	// members IDs


		bool m_expaned;	// status of list - expanded or not

		int m_pos_itr;	// iterator to member position (in for loops is constructor and addMember)
		int m_act_id;	// selected member ID


		sf::Vector2f	m_def_pos;			// mein object position
		sf::Color		m_def_color;		// selected object color
		sf::Color		m_def_text_color;	// selected object text color
		sf::Color		m_def_out_color;	// selected object outline color
		float			m_def_out_thick;	// selected object outline thickness
		unsigned int	m_def_text_style;	// selected object text style
		int				m_def_font;			// selected object font
			

		bool m_def_active;	// is object proccessed and rendered?
		bool m_created;		// has object been created?
	};

} // namespace ke