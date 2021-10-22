#pragma once

#include "ObjectParent.hpp"


namespace ke
{

	/// <summary>
	/// KEngine Rectangle is a rectangle based on SFML RectangleShape that can carry a texture or text
	/// </summary>
	class Rectangle : public GuiObject
	{
	public:

		/// <summary>
		/// Default Rectangle counstructor
		/// </summary>
		/// <remarks> 
		/// Note that shape is not initialized here
		/// </remarks>
		/// <sealso cref="Rectangle::create"/>
		Rectangle();


		////////////////////////////////


		/// <summary>
		/// Rectangle counstructor for color and text
		/// </summary>
		/// <param name="size">rectangle size</param>
		/// <param name="position">rectangle position, based on origin</param>
		/// <param name="origin">shape origin</param>
		/// <param name="text">text displayed with rectangle</param>
		/// <param name="character_size">text size</param>
		/// <param name="text_position">text position relative to the recangle</param>
		/// <param name="object_color">shape color</param>
		/// <param name="text_color">text color</param>
		/// <param name="outline_thickness">outline thickness</param>
		/// <param name="outline_color">outline color</param>
		/// <param name="rotation">rotation in degrees</param>
		/// <param name="text_style">SFML text style</param>
		/// <param name="text_shift">Vector2f correcting tex position</param>
		/// <param name="font">KEngie Font inherited form GuiObject</param>
		/// <param name="active">is object is processed and rendered</param>
		Rectangle(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin = MIDDLE_MIDDLE,
			const std::wstring& text = L"",
			unsigned int character_size = 20,
			int text_position = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& text_color = sf::Color::White,
			float outline_thickness = 0,
			const sf::Color& outline_color = sf::Color::Transparent,
			float rotation = 0.f,
			unsigned int text_style = sf::Text::Regular,
			const sf::Vector2f& text_shift = sf::Vector2f(0, 0),
			int font = Arial,
			bool active = true);


		/// <summary>
		/// Rectangle constructor for textures
		/// </summary>
		/// <param name="size">shape size</param>
		/// <param name="position">shape position, based on origin</param>
		/// <param name="origin">shape origin</param>
		/// <param name="texture">SFML texture</param>
		/// <param name="rotation">rotation in degrees</param>
		/// <param name="active">is object is processed and rendered</param>
		Rectangle(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin = MIDDLE_MIDDLE,
			const sf::Texture* texture = nullptr,
			float rotation = 0.f,
			bool active = true);


		/// <summary>
		/// Rectangle constructor for textures
		/// </summary>
		/// <param name="size">shape size</param>
		/// <param name="position">shape position, based on origin</param>
		/// <param name="origin">shape origin</param>
		/// <param name="filename">path to texture</param>
		/// <param name="rotation">rotation in degrees</param>
		/// <param name="active">is object is processed and rendered</param>
		Rectangle(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin = MIDDLE_MIDDLE,
			const std::string& filename = "",
			float rotation = 0.f,
			bool active = true);



		////////////////////////////////



		/// <summary>
		/// Rectangle destructor
		/// </summary>
		/// <remarks>
		/// nothing is inside
		/// </remarks>
		virtual ~Rectangle();



		////////////////////////////////



		/// <summary>
		/// Rectangle copy cosntructor
		/// </summary>
		/// <param name="other">copied Rectangle</param>
		/// <remarks>
		/// Not constant because of this stupid texture
		/// </remarks>
		Rectangle(Rectangle& other);


		/// <summary>
		/// Rectangle "=" operator
		/// </summary>
		/// <param name="other">copied Rectangle</param>
		/// <returns>*this</returns>
		/// <remarks>
		/// Not constant because of this stupid texture
		/// </remarks>
		Rectangle& operator= (Rectangle& other);



		////////////////////////////////



		/// <summary>
		/// Creates colored Rectangle with Text
		/// </summary>
		/// <param name="size">rectangle size</param>
		/// <param name="position">rectangle position, based on origin</param>
		/// <param name="origin">shape origin</param>
		/// <param name="text">text displayed with rectangle</param>
		/// <param name="character_size">text size</param>
		/// <param name="text_position">text position relative to the recangle</param>
		/// <param name="object_color">shape color</param>
		/// <param name="text_color">text color</param>
		/// <param name="outline_thickness">outline thickness</param>
		/// <param name="outline_color">outline color</param>
		/// <param name="rotation">rotation in degrees</param>
		/// <param name="text_style">SFML text style</param>
		/// <param name="text_shift">Vector2f correcting tex position</param>
		/// <param name="font">KEngie Font inherited form GuiObject</param>
		/// <param name="active">is object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin = MIDDLE_MIDDLE,
			const std::wstring& text = L"",
			unsigned int character_size = 20,
			int text_position = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& text_color = sf::Color::White,
			float outline_thickness = 0,
			const sf::Color& outline_color = sf::Color::Transparent,
			float rotation = 0.f,
			unsigned int text_style = sf::Text::Regular,
			const sf::Vector2f& text_shift = sf::Vector2f(0, 0),
			int font = Arial,
			bool active = true);


		/// <summary>
		/// Creates textured Rectangle
		/// </summary>
		/// <param name="size">shape size</param>
		/// <param name="position">shape position, based on origin</param>
		/// <param name="origin">shape origin</param>
		/// <param name="texture">SFML texture</param>
		/// <param name="rotation">rotation in degrees</param>
		/// <param name="active">is object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin = MIDDLE_MIDDLE,
			const sf::Texture* texture = nullptr,
			float rotation = 0.f,
			bool active = true);


		/// <summary>
		/// Creates textured Rectangle
		/// </summary>
		/// <param name="size">shape size</param>
		/// <param name="position">shape position, based on origin</param>
		/// <param name="origin">shape origin</param>
		/// <param name="filename">path to texture</param>
		/// <param name="rotation">rotation in degrees</param>
		/// <param name="active">is object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			int origin = MIDDLE_MIDDLE,
			const std::string& filename = "",
			float rotation = 0.f,
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
		/// retuns pointer to the shape
		/// </summary>
		/// <returns>SFML RectangleShape</returns>
		sf::RectangleShape* getShape();	


		/// <summary>
		/// returns pointer to the text
		/// </summary>
		/// <returns>SFML Text</returns>
		sf::Text* getSfText();



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
		/// sets object rotation
		/// </summary>
		/// <remarks>
		/// works fine only when origin == text position 
		/// </remarks>
		/// <param name="angle">rotation in degrees</param>
		void setRotation(float angle);


		/// <summary>
		/// rotates object
		/// </summary>
		/// <remarks>
		/// works fine only when origin == text position 
		/// </remarks>
		/// <param name="angle">rotation in degrees</param>
		void rotate(float angle);


		/// <summary>
		/// returns object rotation
		/// </summary>
		/// <returns>rotation in degrees</returns>
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
		void setTexture(const std::string& filename);


		/// <summary>
		/// returns poiter to object texture
		/// </summary>
		/// <returns>SFML Texutre</returns>
		const sf::Texture* getTexture() const;


		/// <summary>
		/// adds path to unknown texture
		/// </summary>
		/// <param name="path"></param>
		/// <remarks>
		/// use only with good reason and when texture oryginal path is unknown
		/// </remarks>
		void addPathToTexture(const std::string& path);


		/// <summary>
		/// returns path to texture
		/// </summary>
		/// <returns>path to texture</returns>
		std::string getTexturePath() const;


		/// <summary>
		/// checks if correct texture is on
		/// </summary>
		/// <returns>if textture is set, true</returns>
		bool isTextureSet() const;



		////////////////////////////////



		/// <summary>
		/// sets object color
		/// </summary>
		/// <param name="color">new SFML color</param>
		void setFillColor(const sf::Color& color = sf::Color::Transparent);


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
		void setTextColor(const sf::Color& text_color = sf::Color::White);


		/// <summary>
		/// returns text color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getTextColor() const;



		////////////////////////////////



		/// <summary>
		/// sets object outline color
		/// </summary>
		/// <param name="outline_color">new SFML Color</param>
		void setOutlineColor(const sf::Color& outline_color = sf::Color::Transparent);


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
		void setOutlineThickness(float outline_thickness = 0);


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
		/// <param name="button">SFML button or key</param>
		/// <param name="mousePosition">position of the mouse</param>
		/// <param name="event">SFML event</param>
		/// <returns>if cliked, true </returns>
		bool isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const;



		////////////////////////////////



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



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// rounds text position to int
		/// </summary>
		/// <param name="mousePosition">mouse position</param>
		/// <param name="event">SFML event</param>
		/// <param name="button">SFML Button or key</param>
		/// <param name="view">SFML view</param>
		/// <returns></returns>
		float update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view);



		////////////////////////////////



		/// <summary>
		/// renders object
		/// </summary>
		/// <param name="window">SFML window where object is rendered</param>
		void render(sf::RenderWindow* window);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// inits physics
		/// </summary>
		/// <remarks>
		/// raw init, you have to set mass and friction independently
		/// </remarks>
		void initPhysics();


		/// <summary>
		/// inits physics
		/// </summary>
		/// <param name="mass">objec mass</param>
		/// <param name="friction">object friction (friction over time)</param>
		void initPhysics(long double mass, float friction);


		/// <summary>
		/// removes physics from the object
		/// </summary>
		void deletePhysics();


		////////////////////////////////


		/// <summary>
		/// updates physics
		/// </summary>
		/// <param name="dt">delta time</param>
		void updatePhysics(const float dt);


		/// <summary>
		/// gate to physics
		/// </summary>
		/// <returns>KEngie Physics assigned to the object</returns>
		Physics* physics();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// checks if object has been created
		/// </summary>
		/// <returns>if object is created, true</returns>
		bool created() const;




	private:


		// PRIVATE FUNCTIONS


		/// <summary>
		/// updates shapeCenter
		/// </summary>
		void shapeUpdate();

		/// <summary>
		/// updates shapeCenter and shape origin
		/// </summary>
		void fullShapeUpdate();


		/// <summary>
		/// updates text position
		/// </summary>
		void textUpdate();

		/// <summary>
		/// updates text position and text origin
		/// </summary>
		void fullTextUpdate();


		/// <summary>
		/// updates font
		/// </summary>
		/// <param name="font">Specific font inherited form GuiObject</param>
		void fontUpdate(int font);



		// MEMBERS



		sf::RectangleShape	m_shape;		// SFML Rectangle 
		sf::Vector2f		m_shapeCenter;	// center of the shape
		int					m_origin;		// origin of the shape


		sf::Text		m_text;				// SFML Text
		int				m_text_font;		// KEngie text font
		sf::Vector2f	m_text_shift;		// Vector2f correcting text position
		int				m_text_position;	// position of the shape's text


		sf::Texture		m_texture;			// shape's texture (if empty, it uses KEngine Empty Texture)
		std::string		m_texture_path;		// path to file where texture is located
		bool			m_texture_set;		// is texture not empty?


		std::unique_ptr<Physics> m_physics; // upointer to KEngie physics component

		bool m_active;	// is object active?
		bool m_created;	// has object been created?
	};


} // namespace ke