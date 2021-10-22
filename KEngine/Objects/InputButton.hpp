#pragma once

#include "ObjectParent.hpp"
#include "Button.hpp"
#include "Rectangle.hpp"

#include <string>


namespace ke
{

	/// <summary>
	/// KEngine InputBUtton is an object based on Kengine Button where you can type text to it
	/// </summary>
	class InputButton : public GuiObject
	{
	public:


		/// <summary>
		/// Default InputBUtton constructor 
		/// </summary>
		InputButton();


		////////////////////////////////


		/// <summary>
		/// InputBUtton constructor
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="position">object position</param>
		/// <param name="origin">object origin</param>
		/// <param name="texture">SFML texture</param>
		/// <param name="default_text">text displated when object is not selectec</param>
		/// <param name="text_scope">defines which characters can be typed in</param>
		/// <param name="max_number_of_characters">maxinum number of characters</param>
		/// <param name="max_number_of_lines">maximum number of lines</param>
		/// <param name="character_size">text size</param>
		/// <param name="text_position">text position relative to the object</param>
		/// <param name="object_color">object color</param>
		/// <param name="text_color">text color</param>
		/// <param name="default_text_color">default text color</param>
		/// <param name="outline_thickness">object outline thickness</param>
		/// <param name="outline_color">object outline color</param>
		/// <param name="text_style">SFML text style</param>
		/// <param name="text_shift">Vector2f correcting tex position</param>
		/// <param name="font">KEngie Font inherited form GuiObject</param>
		/// <param name="active">is object is processed and rendered</param>
		InputButton(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin,
			const sf::Texture* texture,
			const std::wstring& default_text = L"",
			int text_scope = Everything,
			unsigned int max_number_of_characters = 20,
			unsigned int max_number_of_lines = 1,
			unsigned int character_size = 20,
			int text_position = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& text_color = sf::Color::White,
			const sf::Color& default_text_color = sf::Color::White,
			float outline_thickness = 0,
			const sf::Color& outline_color = sf::Color::Transparent,
			unsigned int text_style = sf::Text::Regular,
			const sf::Vector2f& text_shift = sf::Vector2f(0, 0),
			int font = Arial,
			bool active = true);


		////////////////////////////////


		/// <summary>
		/// InputBUtton constructor
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="position">object position</param>
		/// <param name="origin">object origin</param>
		/// <param name="filename">path to texture</param>
		/// <param name="default_text">text displated when object is not selectec</param>
		/// <param name="text_scope">defines which characters can be typed in</param>
		/// <param name="max_number_of_characters">maxinum number of characters</param>
		/// <param name="max_number_of_lines">maximum number of lines</param>
		/// <param name="character_size">text size</param>
		/// <param name="text_position">text position relative to the object</param>
		/// <param name="object_color">object color</param>
		/// <param name="text_color">text color</param>
		/// <param name="default_text_color">default text color</param>
		/// <param name="outline_thickness">object outline thickness</param>
		/// <param name="outline_color">object outline color</param>
		/// <param name="text_style">SFML text style</param>
		/// <param name="text_shift">Vector2f correcting tex position</param>
		/// <param name="font">KEngie Font inherited form GuiObject</param>
		/// <param name="active">is object is processed and rendered</param>
		InputButton(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin,
			const std::string& filename,
			const std::wstring& default_text = L"",
			int text_scope = Everything,
			unsigned int max_number_of_characters = 20,
			unsigned int max_number_of_lines = 1,
			unsigned int character_size = 20,
			int text_position = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& text_color = sf::Color::White,
			const sf::Color& default_text_color = sf::Color::White,
			float outline_thickness = 0,
			const sf::Color& outline_color = sf::Color::Transparent,
			unsigned int text_style = sf::Text::Regular,
			const sf::Vector2f& text_shift = sf::Vector2f(0, 0),
			int font = Arial,
			bool active = true);


		////////////////////////////////


		/// <summary>
		/// InputButton destructor
		/// </summary>
		/// <remarks>
		/// nothing is inside
		/// </remarks>
		virtual ~InputButton();


		////////////////////////////////


		/// <summary>
		/// InputButton copy constructor
		/// </summary>
		/// <param name="other">other InputButton</param>
		InputButton(InputButton& other);


		/// <summary>
		/// InputButton '=' operator 
		/// </summary>
		/// <param name="other">other InputButton</param>
		/// <returns>this</returns>
		InputButton& operator= (InputButton& other);


		////////////////////////////////


		/// <summary>
		/// InputBUtton creator, works like construcor
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="position">object position</param>
		/// <param name="origin">object origin</param>
		/// <param name="texture">SFML texture</param>
		/// <param name="default_text">text displated when object is not selectec</param>
		/// <param name="text_scope">defines which characters can be typed in</param>
		/// <param name="max_number_of_characters">maxinum number of characters</param>
		/// <param name="max_number_of_lines">maximum number of lines</param>
		/// <param name="character_size">text size</param>
		/// <param name="text_position">text position relative to the object</param>
		/// <param name="object_color">object color</param>
		/// <param name="text_color">text color</param>
		/// <param name="default_text_color">default text color</param>
		/// <param name="outline_thickness">object outline thickness</param>
		/// <param name="outline_color">object outline color</param>
		/// <param name="text_style">SFML text style</param>
		/// <param name="text_shift">Vector2f correcting tex position</param>
		/// <param name="font">KEngie Font inherited form GuiObject</param>
		/// <param name="active">is object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin,
			const sf::Texture* texture,
			const std::wstring& default_text = L"",
			int text_scope = Everything,
			unsigned int max_number_of_characters = 20,
			unsigned int max_number_of_lines = 1,
			unsigned int character_size = 20,
			int text_position = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& text_color = sf::Color::White,
			const sf::Color& default_text_color = sf::Color::White,
			float outline_thickness = 0,
			const sf::Color& outline_color = sf::Color::Transparent,
			unsigned int text_style = sf::Text::Regular,
			const sf::Vector2f& text_shift = sf::Vector2f(0, 0),
			int font = Arial,
			bool active = true);


		////////////////////////////////


		/// <summary>
		/// InputBUtton creator, works like construcor
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="position">object position</param>
		/// <param name="origin">object origin</param>
		/// <param name="filename">path to texture</param>
		/// <param name="default_text">text displated when object is not selectec</param>
		/// <param name="text_scope">defines which characters can be typed in</param>
		/// <param name="max_number_of_characters">maxinum number of characters</param>
		/// <param name="max_number_of_lines">maximum number of lines</param>
		/// <param name="character_size">text size</param>
		/// <param name="text_position">text position relative to the object</param>
		/// <param name="object_color">object color</param>
		/// <param name="text_color">text color</param>
		/// <param name="default_text_color">default text color</param>
		/// <param name="outline_thickness">object outline thickness</param>
		/// <param name="outline_color">object outline color</param>
		/// <param name="text_style">SFML text style</param>
		/// <param name="text_shift">Vector2f correcting tex position</param>
		/// <param name="font">KEngie Font inherited form GuiObject</param>
		/// <param name="active">is object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin,
			const std::string& filename,
			const std::wstring& default_text = L"",
			int text_scope = Everything,
			unsigned int max_number_of_characters = 20,
			unsigned int max_number_of_lines = 1,
			unsigned int character_size = 20,
			int text_position = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& text_color = sf::Color::White,
			const sf::Color& default_text_color = sf::Color::White,
			float outline_thickness = 0,
			const sf::Color& outline_color = sf::Color::Transparent,
			unsigned int text_style = sf::Text::Regular,
			const sf::Vector2f& text_shift = sf::Vector2f(0, 0),
			int font = Arial,
			bool active = true);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Sets object position
		/// </summary>
		/// <param name="position">new position</param>
		void setPosition(const sf::Vector2f& position);


		/// <summary>
		/// Sets object position
		/// </summary>
		/// <param name="x">x position</param>
		/// <param name="y">y position</param>
		void setPosition(float x, float y);


		/// <summary>
		/// Returns object position
		/// </summary>
		/// <returns>position in SFML Vector2f</returns>
		sf::Vector2f getPosition() const;



		////////////////////////////////



		/// <summary>
		/// sets shape size
		/// </summary>
		/// <param name="size">new size</param>
		void setSize(const sf::Vector2f& size);


		/// <summary>
		/// sets object size
		/// </summary>
		/// <param name="size_x">x size</param>
		/// <param name="size_y">y size</param>
		void setSize(float size_x, float size_y);


		/// <summary>
		/// returns object size
		/// </summary>
		/// <returns>size in SFML Vector2f</returns>
		sf::Vector2f getSize() const;



		////////////////////////////////



		/// <summary>
		/// moves object by given offset
		/// </summary>
		/// <param name="offset">Vector2f offset in px</param>
		void move(const sf::Vector2f& offset);


		/// <summary>
		/// moves object by given offset
		/// </summary>
		/// <param name="offset_x">x offset in px</param>
		/// <param name="offset_y">y offset in px</param>
		void move(float offset_x, float offset_y);



		////////////////////////////////



		/// <summary>
		/// sets text (wstring) of object text
		/// </summary>
		/// <param name="text">new wstring</param>
		void setText(const std::wstring& text = L"");


		/// <summary>
		/// returns text (wide stirng)
		/// </summary>
		/// <returns>text wstring</returns>
		std::wstring getText() const;



		////////////////////////////////



		/// <summary>
		/// Sets default text - text displayed when object is not selected
		/// </summary>
		/// <param name="default_text">default text</param>
		void setDefautText(const std::wstring& default_text);


		/// <summary>
		/// Returns default text - text displayed when object is not selected
		/// </summary>
		/// <returns>default text</returns>
		std::wstring getDefautText() const;



		////////////////////////////////



		/// <summary>
		/// Sets which characters can be typed in, use KEngine TextScope enum
		/// </summary>
		/// <param name="text_scope">KEngine text scope enum</param>
		void setTextScope(int text_scope);


		/// <summary>
		/// returns which characters can be typed in, use KEngine TextScope enum
		/// </summary>
		/// <returns>text scope</returns>
		int getTextScope() const;



		////////////////////////////////



		/// <summary>
		/// sets object origin
		/// </summary>
		/// <param name="origin"></param>
		void setOrigin(int origin);


		/// <summary>
		/// retuns object origin
		/// </summary>
		/// <returns>origin</returns>
		int getOrigin() const;



		////////////////////////////////



		/// <summary>
		/// Does not available in InputButton
		/// </summary>
		/// <param name="angle"></param>
		void setRotation(float angle);


		/// <summary>
		/// Does not available in InputButton
		/// </summary>
		/// <param name="angle"></param>
		void rotate(float angle);


		/// <summary>
		/// Does not available in InputButton
		/// </summary>
		/// <returns></returns>
		float getRotation() const;



		////////////////////////////////



		/// <summary>
		/// sets position independently from origin
		/// </summary>
		/// <param name="position">position in SFML Vector2f</param>
		void setPositionByCenter(const sf::Vector2f& position);


		/// <summary>
		/// returns object center
		/// </summary>
		/// <returns>position of object center</returns>
		sf::Vector2f getShapeCenter() const;



		////////////////////////////////



		/// <summary>
		/// sets object scale 
		/// </summary>
		/// <param name="factors">scale in SFML Vector2f</param>
		void setScale(const sf::Vector2f& factors);


		/// <summary>
		/// sets object scale
		/// </summary>
		/// <param name="factor_x">x scale factor</param>
		/// <param name="factor_y">y scale factor</param>
		void setScale(float factor_x, float factor_y);


		/// <summary>
		/// scales object by given factors
		/// </summary>
		/// <param name="factors">scale factors in SFML Vector2f</param>
		void scale(const sf::Vector2f& factors);


		/// <summary>
		/// returns object scale
		/// </summary>
		/// <returns>object scale in SFML Vector2f</returns>
		sf::Vector2f getScale() const;



		////////////////////////////////



		/// <summary>
		/// sets object texture
		/// </summary>
		/// <param name="texture">pointer to oryginal texutre</param>
		/// <remarks>
		/// when texture is nullptr, sets texture to empty texture
		/// </remarks>
		void setTexture(const sf::Texture* texture);


		/// <summary>
		/// sets object texture
		/// </summary>
		/// <param name="filename">path to the texture</param>
		void setTexture(const std::string& texture_path);


		/// <summary>
		/// returns poiter to object texture
		/// </summary>
		/// <returns>SFML Texutre</returns>
		const sf::Texture* getTexture() const;



		////////////////////////////////



		/// <summary>
		/// sets object color
		/// </summary>
		/// <param name="color">new SFML color</param>
		void setFillColor(const sf::Color& color);


		/// <summary>
		/// returns object color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getFillColor() const;



		////////////////////////////////



		/// <summary>
		/// sets text color
		/// </summary>
		/// <param name="text_color">new SFML color</param>
		void setTextColor(const sf::Color& text_color);


		/// <summary>
		/// Sets default text color
		/// </summary>
		/// <param name="text_color">default text color</param>
		void setDefaultTextColor(const sf::Color& text_color);


		////////////////


		/// <summary>
		/// returns text color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getTextColor() const;


		/// <summary>
		/// returns default text color
		/// </summary>
		/// <returns>default text color</returns>
		const sf::Color& getDefaultTextColor() const;



		////////////////////////////////



		/// <summary>
		/// sets object outline color
		/// </summary>
		/// <param name="outline_color">new SFML Color</param>
		void setOutlineColor(const sf::Color& outline_color);


		/// <summary>
		/// returns object outline color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getOutlineColor() const;



		////////////////////////////////



		/// <summary>
		/// sets object outline thickness
		/// </summary>
		/// <param name="outline_thickness">new outline thickness</param>
		void setOutlineThickness(float outline_thickness);



		/// <summary>
		/// returns object outline thickness
		/// </summary>
		/// <returns>outline thickness</returns>
		float getOutlineThickness() const;



		////////////////////////////////



		/// <summary>
		/// sets text position
		/// </summary>
		/// <param name="position">text position</param>
		/// <param name="text_shift"></param>
		void setTextPosition(int position, const sf::Vector2f& text_shift = sf::Vector2f(0, 0));


		/// <summary>
		/// returns text position
		/// </summary>
		/// <returns>text position</returns>
		int getTextPosition() const;


		////////////////


		/// <summary>
		/// returns text shift
		/// </summary>
		/// <returns>text shift</returns>
		sf::Vector2f getTextShift() const;



		////////////////////////////////



		/// <summary>
		/// returns text style
		/// </summary>
		/// <param name="style">SFML Text style</param>
		void setTextStyle(int style);


		/// <summary>
		/// returns text style
		/// </summary>
		/// <returns>SFML text style as uint</returns>
		unsigned int getTextStyle() const;



		////////////////////////////////



		/// <summary>
		/// sets text font
		/// </summary>
		/// <param name="font">KEngine font inherited form GuiObject</param>
		void setFont(int font);


		/// <summary>
		/// returns text font
		/// </summary>
		/// <returns>KEngine font inherited from GuiObject</returns>
		int getFont() const;



		////////////////////////////////



		/// <summary>
		/// sets text size
		/// </summary>
		/// <param name="char_size">text size</param>
		void setCharacterSize(unsigned int char_size);


		/// <summary>
		/// returns text size
		/// </summary>
		/// <returns>size as uint</returns>
		unsigned int getCharacterSize() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Returns this InputButton 
		/// </summary>
		/// <returns>pointer to this InputButton</returns>
		Button* getObject();


		/// <summary>
		/// Returns Cursor
		/// </summary>
		/// <returns>pointer to Cursor</returns>
		Rectangle* getCursor();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// checks if point (mouse position) is on the object
		/// </summary>
		/// <remarks>
		/// rotation check works fine only when origin is set to MIDDLE_MIDDLE
		/// </remarks>
		/// <param name="mousePosition">point (mouse position)</param>
		/// <returns>if collides, true</returns>
		bool isInvaded(const sf::Vector2f& mousePosition) const;



		////////////////////////////////



		/// <summary>
		/// checks if object is clicked by specific key
		/// </summary>
		/// <remarks>
		/// call in pollEvent(..) loop
		/// </remarks>
		/// <param name="button">SFML button</param>
		/// <param name="mousePosition">position of the mouse</param>
		/// <param name="event">SFML event</param>
		/// <returns>if clicked, true </returns>
		bool isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const;



		////////////////////////////////



		/// <summary>
		/// checks if objects is active (is proccessed and rendered)
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
		/// Sets if text can be entered
		/// </summary>
		/// <param name="status">can you enter some text?</param>
		void setEPS(bool status); // Entering Possibility Status


		/// <summary>
		/// checks if text can be entered
		/// </summary>
		/// <returns>if text can be entered - true</returns>
		bool getEPS() const;



		////////////////////////////////



		/// <summary>
		/// retruns current number of characters
		/// </summary>
		/// <returns>current number of characters</returns>
		size_t getCharNum();


		/// <summary>
		/// returns current number of lines
		/// </summary>
		/// <returns>current number of lines</returns>
		unsigned int getLineNum();



		////////////////////////////////



		/// <summary>
		/// sets maximum number of characters
		/// </summary>
		/// <param name="max_char_num">maximum number of characters</param>
		void setMaxCharacterNum(unsigned int max_char_num);


		/// <summary>
		/// returns maximum number of chracters
		/// </summary>
		/// <returns>maximum number of characters</returns>
		unsigned int getMaxCharacterNum() const;



		////////////////////////////////



		/// <summary>
		/// sets maximum number of lines
		/// </summary>
		/// <param name="max_line_num">maximum number of lines</param>
		void setMaxLineNum(unsigned int max_line_num);


		/// <summary>
		/// returns maximum number of lines
		/// </summary>
		/// <returns>maximum number of lines</returns>
		unsigned int getMaxLineNum() const;



		////////////////////////////////



		/// <summary>
		/// Enables object update - entering, modifying text and changing parameters (use in pollEvent loop)
		/// </summary>
		/// <param name="mousePosition">mouse position</param>
		/// <param name="event">SFML event</param>
		/// <param name="button">SFML button</param>
		/// <param name="view">SMFL view, can be nullptr</param>
		/// <returns></returns>
		float update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view);


		////////////////


		/// <summary>
		/// updates cursor, use outside pollEvent loop
		/// </summary>
		void updateCursor();



		////////////////////////////////



		/// <summary>
		/// renders object
		/// </summary>
		/// <param name="window"></param>
		void render(sf::RenderWindow* window);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// checks if object has been created
		/// </summary>
		/// <returns>if object is created, true</returns>
		bool created() const;





	private:



		// MEMBERS


		Button		m_object; // InputButton based on KEngine Button

		Rectangle	m_cursor; // cursor (only available when maximum lines == 0)


		std::wstring	m_imp_text;			// text buffer of entered text
		std::wstring	m_def_text;			// text buffer that shows when object is not selected
		sf::Color		m_text_color;		// color buffer for text color
		sf::Color		m_def_text_color;	// color buffer for default text color
		int				m_text_scope;		// which character can be typed in

		bool			m_possible_to_ent;	// can text be entered?


		unsigned int m_no_lines;	// current number of lines
									
		unsigned int m_max_char;	// maximum characters
		unsigned int m_max_lines;	// maximum lines


		sf::Clock	m_cursor_flick_clock; // SFML clock responsible for cursor pulsing 
		float		m_flick_time;		  // variable that stores time given by the clock


		bool m_created; // has object been initialized?

	};

} // namespace ke