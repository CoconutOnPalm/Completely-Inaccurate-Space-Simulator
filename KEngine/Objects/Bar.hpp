#pragma once

#include "ObjectParent.hpp"
#include "CurvedButton.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Button.hpp"



namespace ke
{


	/// <summary>
	/// KEngine PercentageBar is an object that can be used to set percent of some parameter (e.g. volume, brightness etc.)
	/// </summary>
	class PercentageBar : public GuiObject
	{
	public:


		/// <summary>
		/// PercentageBar default constructor
		/// </summary>
		PercentageBar();


		////////////////////////////////


		/// <summary>
		/// PercentageBar constructor
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="button_radius">shifting button radius</param>
		/// <param name="position">object position</param>
		/// <param name="origin">object origin</param>
		/// <param name="button_texture">shifting button texture</param>
		/// <param name="object_texture">button texture</param>
		/// <param name="button_color">shifting button color</param>
		/// <param name="object_color">object color</param>
		/// <param name="button_outline_thickness">shifting button outline thickness</param>
		/// <param name="button_outline_color">shifting button outline color</param>
		/// <param name="object_outline_thickness">object outline thickness</param>
		/// <param name="object_outline_color">object outline color</param>
		/// <param name="active">if object is processed and rendered</param>
		PercentageBar(
			const sf::Vector2f& size,
			float button_radius,
			const sf::Vector2f& position,
			int origin,
			const sf::Texture* button_texture,
			const sf::Texture* object_texture,
			const sf::Color& button_color = sf::Color::Transparent,
			const sf::Color& object_color = sf::Color::Transparent,
			float button_outline_thickness = 0,
			const sf::Color& button_outline_color = sf::Color::Transparent,
			float object_outline_thickness = 0,
			const sf::Color& object_outline_color = sf::Color::Transparent,
			bool active = true);



		/// <summary>
		/// PercentageBar constructor
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="button_radius">shifting button radius</param>
		/// <param name="position">object position</param>
		/// <param name="origin">object origin</param>
		/// <param name="button_texture_path">path shifting button texture</param>
		/// <param name="object_texture_path">path button texture</param>
		/// <param name="button_color">shifting button color</param>
		/// <param name="object_color">object color</param>
		/// <param name="button_outline_thickness">shifting button outline thickness</param>
		/// <param name="button_outline_color">shifting button outline color</param>
		/// <param name="object_outline_thickness">object outline thickness</param>
		/// <param name="object_outline_color">object outline color</param>
		/// <param name="active">if object is processed and rendered</param>
		PercentageBar(
			const sf::Vector2f& size,
			float button_radius,
			const sf::Vector2f& position,
			int origin,
			const std::string& button_texture_path,
			const std::string& object_texture_path,
			const sf::Color& button_color = sf::Color::Transparent,
			const sf::Color& object_color = sf::Color::Transparent,
			float button_outline_thickness = 0,
			const sf::Color& button_outline_color = sf::Color::Transparent,
			float object_outline_thickness = 0,
			const sf::Color& object_outline_color = sf::Color::Transparent,
			bool active = true);


		////////////////////////////////


		/// <summary>
		/// PercentageBar destructor
		/// </summary>
		virtual ~PercentageBar();



		////////////////////////////////



		/// <summary>
		/// PercentageBar copy constuctor
		/// </summary>
		/// <param name="other">othrt PercentageBar</param>
		PercentageBar(PercentageBar& other);



		/// <summary>
		/// PercentageBar '=' operator
		/// </summary>
		/// <param name="other">other PercentageBar</param>
		/// <returns>*this</returns>
		PercentageBar& operator= (PercentageBar& other);



		////////////////////////////////



		/// <summary>
		/// PercentageBar creator
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="button_radius">shifting button radius</param>
		/// <param name="position">object position</param>
		/// <param name="origin">object origin</param>
		/// <param name="button_texture">shifting button texture</param>
		/// <param name="object_texture">button texture</param>
		/// <param name="button_color">shifting button color</param>
		/// <param name="object_color">object color</param>
		/// <param name="button_outline_thickness">shifting button outline thickness</param>
		/// <param name="button_outline_color">shifting button outline color</param>
		/// <param name="object_outline_thickness">object outline thickness</param>
		/// <param name="object_outline_color">object outline color</param>
		/// <param name="active">if object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			float button_radius,
			const sf::Vector2f& position,
			int origin,
			const sf::Texture* button_texture,
			const sf::Texture* object_texture,
			const sf::Color& button_color = sf::Color::Transparent,
			const sf::Color& object_color = sf::Color::Transparent,
			float button_outline_thickness = 0,
			const sf::Color& button_outline_color = sf::Color::Transparent,
			float object_outline_thickness = 0,
			const sf::Color& object_outline_color = sf::Color::Transparent,
			bool active = true);



		/// <summary>
		/// PercentageBar creator
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="button_radius">shifting button radius</param>
		/// <param name="position">object position</param>
		/// <param name="origin">object origin</param>
		/// <param name="button_texture_path">path shifting button texture</param>
		/// <param name="object_texture_path">path button texture</param>
		/// <param name="button_color">shifting button color</param>
		/// <param name="object_color">object color</param>
		/// <param name="button_outline_thickness">shifting button outline thickness</param>
		/// <param name="button_outline_color">shifting button outline color</param>
		/// <param name="object_outline_thickness">object outline thickness</param>
		/// <param name="object_outline_color">object outline color</param>
		/// <param name="active">if object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			float button_radius,
			const sf::Vector2f& position,
			int origin,
			const std::string& button_texture_path,
			const std::string& object_texture_path,
			const sf::Color& button_color = sf::Color::Transparent,
			const sf::Color& object_color = sf::Color::Transparent,
			float button_outline_thickness = 0,
			const sf::Color& button_outline_color = sf::Color::Transparent,
			float object_outline_thickness = 0,
			const sf::Color& object_outline_color = sf::Color::Transparent,
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
		/// sets object size
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
		/// Sets shifting button radius
		/// </summary>
		/// <param name="radius">shufting button radius</param>
		void setButtonRadius(float radius);


		/// <summary>
		/// returns shiftong button radius
		/// </summary>
		/// <returns>shiftong button radius</returns>
		float getButtonRadius() const;



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
		/// Does nothing - not available in this object
		/// </summary>
		/// <param name="text"></param>
		void setText(const std::wstring& text);


		/// <summary>
		/// Does nothing - not available in this object
		/// </summary>
		/// <returns>std::wstring()</returns>
		std::wstring getText() const;



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
		/// Does nothing - not available in this object
		/// </summary>
		/// <param name="angle"></param>
		void setRotation(float angle);


		/// <summary>
		/// Does nothing - not available in this object
		/// </summary>
		/// <param name="angle"></param>
		void rotate(float angle);


		/// <summary>
		/// Does nothing - not available in this object
		/// </summary>
		/// <returns>0.f</returns>
		float getRotation() const;



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
		/// sets shifting button scale 
		/// </summary>
		/// <param name="factors">scale in SFML Vector2f</param>
		void setButtonScale(const sf::Vector2f& factors);


		/// <summary>
		/// sets shifting button scale
		/// </summary>
		/// <param name="factor_x">x scale factor</param>
		/// <param name="factor_y">y scale factor</param>
		void setButtonScale(float factor_x, float factor_y);



		/// <summary>
		/// scales object by given factors
		/// </summary>
		/// <param name="factors">scale factors in SFML Vector2f</param>
		void scale(const sf::Vector2f& factors);


		/// <summary>
		/// scales shifting button by given factors
		/// </summary>
		/// <param name="factors">scale factors in SFML Vector2f</param>
		void scaleButton(const sf::Vector2f& factors);



		/// returns object scale
		/// </summary>
		/// <returns>object scale in SFML Vector2f</returns>
		sf::Vector2f getScale() const;


		/// returns shifting button scale
		/// </summary>
		/// <returns>object scale in SFML Vector2f</returns>
		sf::Vector2f getButtonScale() const;



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


		/// <summary>
		/// returns shifting button center
		/// </summary>
		/// <returns>position of object center</returns>
		sf::Vector2f getButtonCenter() const;



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
		/// sets shifting button texture
		/// </summary>
		/// <param name="texture">pointer to oryginal texutre</param>
		/// <remarks>
		/// when texture is nullptr, sets texture to empty texture
		/// </remarks>
		void setButtonTexture(const sf::Texture* texture);



		/// <summary>
		/// sets object texture
		/// </summary>
		/// <param name="filename">path to the texture</param>
		void setTexture(const std::string& filename);


		/// <summary>
		/// sets shifting button texture
		/// </summary>
		/// <param name="filename">path to the texture</param>
		void setButtonTexture(const std::string& filename);



		/// <summary>
		/// returns poiter to object texture
		/// </summary>
		/// <returns>SFML Texutre</returns>
		const sf::Texture* getTexture() const;


		/// <summary>
		/// returns poiter to shifting button texture
		/// </summary>
		/// <returns>SFML Texutre</returns>
		const sf::Texture* getButtonTexture() const;



		////////////////////////////////



		/// <summary>
		/// sets object color
		/// </summary>
		/// <param name="color">new SFML color</param>
		void setFillColor(const sf::Color& color = sf::Color::Transparent);


		/// <summary>
		/// sets shifting button color
		/// </summary>
		/// <param name="color">new SFML color</param>
		void setButtonColor(const sf::Color& color = sf::Color::Transparent);



		/// <summary>
		/// returns object color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getFillColor() const;


		/// <summary>
		/// returns shifting button color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getButtonColor() const;



		////////////////////////////////



		/// <summary>
		/// Does nothing - not available in this object
		/// </summary>
		/// <param name="text_color"></param>
		void setTextColor(const sf::Color& text_color = sf::Color::White);


		/// <summary>
		/// Does nothing - not available in this object
		/// </summary>
		/// <returns>sf::Color::Transparent</returns>
		const sf::Color& getTextColor() const;



		////////////////////////////////



		/// <summary>
		/// sets object outline color
		/// </summary>
		/// <param name="outline_color">new SFML Color</param>
		void setOutlineColor(const sf::Color& outline_color = sf::Color::Transparent);


		/// <summary>
		/// sets shifting button outline color
		/// </summary>
		/// <param name="outline_color">new SFML Color</param>
		void setOutlineButtonColor(const sf::Color& outline_color = sf::Color::Transparent);



		/// <summary>
		/// returns object outline color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getOutlineColor() const;


		/// <summary>
		/// returns shifting button outline color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getOutlineButtonColor() const;



		////////////////////////////////



		/// <summary>
		/// sets object outline thickness
		/// </summary>
		/// <param name="outline_thickness">new outline thickness</param>
		void setOutlineThickness(float outline_thickness = 0);


		/// <summary>
		/// sets shifting button outline thickness
		/// </summary>
		/// <param name="outline_thickness">new outline thickness</param>
		void setOutlineButtonThickness(float outline_thickness = 0);



		/// <summary>
		/// returns object outline thickness
		/// </summary>
		/// <returns>outline thickness</returns>
		float getOutlineThickness() const;


		/// <summary>
		/// returns shifting button outline thickness
		/// </summary>
		/// <returns>outline thickness</returns>
		float getOutlineButtonThickness() const;



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


		/// <summary>
		/// checks if point (mouse position) is on the shifting button
		/// </summary>
		/// <remarks>
		/// rotation check works fine only when origin is set to MIDDLE_MIDDLE
		/// </remarks>
		/// <param name="mousePosition">point (mouse position)</param>
		/// <returns>if collides, true</returns>
		bool isButtonInvaded(const sf::Vector2f& mousePosition) const;



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


		/// <summary>
		/// checks if shifting button is clicked by specific key
		/// </summary>
		/// <remarks>
		/// call in pollEvent(..) loop
		/// </remarks>
		/// <param name="button">SFML button or key</param>
		/// <param name="mousePosition">position of the mouse</param>
		/// <param name="event">SFML event</param>
		/// <returns>if cliked, true </returns>
		bool isButtonClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const;



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



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// returns colored shifting button
		/// </summary>
		/// <returns>KEngine Circle</returns>
		Circle* getColorButton();


		/// <summary>
		/// returns textured shifting button
		/// </summary>
		/// <returns>KEngine Circle</returns>
		Circle* getTextureButton();


		/// <summary>
		/// returns button 'track'
		/// </summary>
		/// <returns>KEngine CurvedButton</returns>
		CurvedButton* getObject();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Sets object %
		/// </summary>
		/// <param name="percent"></param>
		void setPercent(float percent);


		/// <summary>
		/// returns current %
		/// </summary>
		/// <returns>current percent</returns>
		float getPercent();



		////////////////////////////////



		/// <summary>
		/// sets if object is currently changable
		/// </summary>
		/// <param name="holded"></param>
		void setHolded(bool holded);


		/// <summary>
		/// returns if shifting button is holded
		/// </summary>
		/// <returns></returns>
		bool isHolded() const;



		////////////////////////////////



		/// <summary>
		/// returns button shift from left side
		/// </summary>
		/// <returns>current shift</returns>
		float getShift() const;



		////////////////////////////////



		/// <summary>
		/// reverses object redner order
		/// </summary>
		void reverseRenderOrder();


		/// <summary>
		/// sets object render order
		/// </summary>
		/// <param name="order"></param>
		void setRenderOrder(bool order);


		/// <summary>
		/// returns object render order
		/// </summary>
		/// <returns></returns>
		bool getRenderOrder();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// updates object, use in pollEvent loop
		/// </summary>
		/// <param name="mousePosition"></param>
		/// <param name="event">SFML event</param>
		/// <param name="button">SFML mouse button</param>
		/// <param name="view">SFML view, can be nullptr</param>
		/// <returns></returns>
		float update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// renders object
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


		Circle			m_texture_button; // textured shifting button
		Circle			m_color_button;	  // colord shifting button
		CurvedButton	m_object;		  // button 'track'

		float	m_shift;		// button shift from left side to actual position, used to calculate %
		bool	m_holded;		// if button is shifting rn
								
		float	m_catchDiff;	// variable used to helps user with shifting
	};









	////////////////////////////////////////////////////////////////////////////////////////////
	//========================================================================================//
	////////////////////////////////////////////////////////////////////////////////////////////









	/// <summary>
	/// KEngine PointBar is a bar that ca visualize points / progress in range
	/// </summary>
	class PointBar : public GuiObject
	{
	public:


		/// <summary>
		/// PointBar default constructor
		/// </summary>
		PointBar();


		////////////////////////////////


		/// <summary>
		/// PointBar constructor
		/// </summary>
		/// <param name="size"></param>
		/// <param name="position"></param>
		/// <param name="texture">SFML texture</param>
		/// <param name="points">number of points</param>
		/// <param name="min_points">pts down range</param>
		/// <param name="max_points">pts upper range</param>
		/// <param name="origin"object origin</param>
		/// <param name="object_color">object color</param>
		/// <param name="bar_color">progress bar color</param>
		/// <param name="object_outline_thickness">object outline thickness</param>
		/// <param name="bar_outline_thickness">progress bar outline thickness</param>
		/// <param name="object_outline_color">object outline color</param>
		/// <param name="bar_outline_color">progress bar outline color</param>
		/// <param name="active">if object is processed and rendered</param>
		PointBar(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			const sf::Texture* texture,
			float points = 0,
			float min_points = 0,
			float max_points = 100,
			int origin = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& bar_color = sf::Color::Black,
			float object_outline_thickness = 0,
			float bar_outline_thickness = 0,
			const sf::Color& object_outline_color = sf::Color::Transparent,
			const sf::Color& bar_outline_color = sf::Color::Transparent,
			bool active = true);



		/// <summary>
		/// PointBar constructor
		/// </summary>
		/// <param name="size"></param>
		/// <param name="position"></param>
		/// <param name="texture_path">path to object texture</param>
		/// <param name="points">number of points</param>
		/// <param name="min_points">pts down range</param>
		/// <param name="max_points">pts upper range</param>
		/// <param name="origin"object origin</param>
		/// <param name="object_color">object color</param>
		/// <param name="bar_color">progress bar color</param>
		/// <param name="object_outline_thickness">object outline thickness</param>
		/// <param name="bar_outline_thickness">progress bar outline thickness</param>
		/// <param name="object_outline_color">object outline color</param>
		/// <param name="bar_outline_color">progress bar outline color</param>
		/// <param name="active">if object is processed and rendered</param>
		PointBar(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			const std::string& texture_path,
			float points = 0,
			float min_points = 0,
			float max_points = 100,
			int origin = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& bar_color = sf::Color::Black,
			float object_outline_thickness = 0,
			float bar_outline_thickness = 0,
			const sf::Color& object_outline_color = sf::Color::Transparent,
			const sf::Color& bar_outline_color = sf::Color::Transparent,
			bool active = true);


		////////////////////////////////


		/// <summary>
		/// PointBar destructor
		/// </summary>
		virtual ~PointBar();



		////////////////////////////////



		/// <summary>
		/// PointBar copy constructor
		/// </summary>
		/// <param name="other">other PointBar</param>
		PointBar(PointBar& other);


		/// <summary>
		/// PointBar '=' operator
		/// </summary>
		/// <param name="other">other PointBar</param>
		/// <returns>*this</returns>
		PointBar& operator= (PointBar& other);



		////////////////////////////////



		/// <summary>
		/// PointBar creator
		/// </summary>
		/// <param name="size"></param>
		/// <param name="position"></param>
		/// <param name="texture">SFML texture</param>
		/// <param name="points">number of points</param>
		/// <param name="min_points">pts down range</param>
		/// <param name="max_points">pts upper range</param>
		/// <param name="origin"object origin</param>
		/// <param name="object_color">object color</param>
		/// <param name="bar_color">progress bar color</param>
		/// <param name="object_outline_thickness">object outline thickness</param>
		/// <param name="bar_outline_thickness">progress bar outline thickness</param>
		/// <param name="object_outline_color">object outline color</param>
		/// <param name="bar_outline_color">progress bar outline color</param>
		/// <param name="active">if object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			const sf::Texture* texture,
			float points = 0,
			float min_points = 0,
			float max_points = 100,
			int origin = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& bar_color = sf::Color::Black,
			float object_outline_thickness = 0,
			float bar_outline_thickness = 0,
			const sf::Color& object_outline_color = sf::Color::Transparent,
			const sf::Color& bar_outline_color = sf::Color::Transparent,
			bool active = true);



		/// <summary>
		/// PointBar creator
		/// </summary>
		/// <param name="size"></param>
		/// <param name="position"></param>
		/// <param name="texture_path">path to object texture</param>
		/// <param name="points">number of points</param>
		/// <param name="min_points">pts down range</param>
		/// <param name="max_points">pts upper range</param>
		/// <param name="origin"object origin</param>
		/// <param name="object_color">object color</param>
		/// <param name="bar_color">progress bar color</param>
		/// <param name="object_outline_thickness">object outline thickness</param>
		/// <param name="bar_outline_thickness">progress bar outline thickness</param>
		/// <param name="object_outline_color">object outline color</param>
		/// <param name="bar_outline_color">progress bar outline color</param>
		/// <param name="active">if object is processed and rendered</param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			const std::string& texture_path,
			float points = 0,
			float min_points = 0,
			float max_points = 100,
			int origin = MIDDLE_MIDDLE,
			const sf::Color& object_color = sf::Color::Transparent,
			const sf::Color& bar_color = sf::Color::Black,
			float object_outline_thickness = 0,
			float bar_outline_thickness = 0,
			const sf::Color& object_outline_color = sf::Color::Transparent,
			const sf::Color& bar_outline_color = sf::Color::Transparent,
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



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object size
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


		/// <summary>
		/// returns bar size
		/// </summary>
		/// <returns>size in SFML Vector2f</returns>
		sf::Vector2f getBarSize() const;



		////////////////////////////////////////////////////////////////



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



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets text (wstring) of object text
		/// </summary>
		/// <param name="text">new wstring</param>
		void setText(const std::wstring& text);


		/// <summary>
		/// returns text (wide stirng)
		/// </summary>
		/// <returns>text wstring</returns>
		std::wstring getText() const;



		////////////////////////////////////////////////////////////////



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



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Doeas nothing - not available in this object
		/// </summary>
		/// <param name="angle"></param>
		void setRotation(float angle);


		/// <summary>
		/// Doeas nothing - not available in this object
		/// </summary>
		/// <param name="angle"></param>
		void rotate(float angle);


		/// <summary>
		/// Doeas nothing - not available in this object
		/// </summary>
		/// <returns>0.f</returns>
		float getRotation() const;



		////////////////////////////////////////////////////////////////



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


		/// returns object scale
		/// </summary>
		/// <returns>object scale in SFML Vector2f</returns>
		sf::Vector2f getScale() const;



		////////////////////////////////////////////////////////////////



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



		////////////////////////////////////////////////////////////////



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



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object color
		/// </summary>
		/// <param name="color">new SFML color</param>
		void setFillColor(const sf::Color& color = sf::Color::Transparent);


		/// <summary>
		/// sets bar color
		/// </summary>
		/// <param name="color">new SFML color</param>
		void setBarFillColor(const sf::Color& color = sf::Color::Transparent);



		/// <summary>
		/// returns object color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getFillColor() const;


		/// <summary>
		/// returns bar color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getBarFillColor() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Does nothing - not available in this object
		/// </summary>
		/// <param name="text_color"></param>
		void setTextColor(const sf::Color& text_color = sf::Color::White);


		/// <summary>
		/// Does nothing - not available in this object
		/// </summary>
		/// <returns>sf::Color::Transparent</returns>
		const sf::Color& getTextColor() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object outline color
		/// </summary>
		/// <param name="outline_color">new SFML Color</param>
		void setOutlineColor(const sf::Color& outline_color = sf::Color::Transparent);


		/// <summary>
		/// sets bar outline color
		/// </summary>
		/// <param name="outline_color">new SFML Color</param>
		void setBarOutlineColor(const sf::Color& outline_color = sf::Color::Transparent);



		/// <summary>
		/// returns object outline color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getOutlineColor() const;


		/// <summary>
		/// returns bar outline color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getBarOutlineColor() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object outline thickness
		/// </summary>
		/// <param name="outline_thickness">new outline thickness</param>
		void setOutlineThickness(float outline_thickness = 0);


		/// <summary>
		/// sets object bar thickness
		/// </summary>
		/// <param name="outline_thickness">new outline thickness</param>
		void setBarOutlineThickness(float outline_thickness = 0);



		/// <summary>
		/// returns object outline thickness
		/// </summary>
		/// <returns>outline thickness</returns>
		float getOutlineThickness() const;


		/// <summary>
		/// returns bar outline thickness
		/// </summary>
		/// <returns>outline thickness</returns>
		float getBarOutlineThickness() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// checks if point (mouse position) is on the object
		/// </summary>
		/// <param name="mousePosition">point (mouse position)</param>
		/// <returns>if collides, true</returns>
		bool isInvaded(const sf::Vector2f& mousePosition) const;



		/// <summary>
		/// checks if point (mouse position) is on the bar
		/// </summary>
		/// <param name="mousePosition">point (mouse position)</param>
		/// <returns>if collides, true</returns>
		bool isBarInvaded(const sf::Vector2f& mousePosition) const;



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



		/// <summary>
		/// checks if bar is clicked by specific key
		/// </summary>
		/// <remarks>
		/// call in pollEvent(..) loop
		/// </remarks>
		/// <param name="button">SFML button or key</param>
		/// <param name="mousePosition">position of the mouse</param>
		/// <param name="event">SFML event</param>
		/// <returns>if cliked, true </returns>
		bool isBarClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const;



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



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// returns Bar
		/// </summary>
		/// <returns>KEngine Rectangle</returns>
		Rectangle* getBar();


		/// <summary>
		/// returns Bar 'background'
		/// </summary>
		/// <returns>KEngine Button</returns>
		Button* getObject();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sdds 1 point to current amount
		/// </summary>
		void addPoint();


		/// <summary>
		/// subtracts 1 point from current amount
		/// </summary>
		void subtractPoint();



		////////////////////////////////



		/// <summary>
		/// adds x points to current amount
		/// </summary>
		/// <param name="count">number of added points</param>
		void addPoints(float count);


		/// <summary>
		/// substracts x points from current amount
		/// </summary>
		/// <param name="count">number of substructed points</param>
		void subtractPoints(float count);



		////////////////////////////////



		/// <summary>
		/// sets number of points
		/// </summary>
		/// <param name="count">number of points</param>
		void setPointCount(float count);


		/// <summary>
		/// returns current number of points
		/// </summary>
		/// <returns>current number of points</returns>
		float getPointCount() const;



		////////////////////////////////



		/// <summary>
		/// sets pts downrange
		/// </summary>
		/// <param name="min_count">pts downrange</param>
		void setMinPointCount(float min_count);


		/// <summary>
		/// returns pts downrange
		/// </summary>
		/// <returns>pts downrange</returns>
		float getMinPointCount() const;



		////////////////////////////////



		/// <summary>
		/// sets pts upper range
		/// </summary>
		/// <param name="max_count">pts upper range</param>
		void setMaxPointCount(float max_count);


		/// <summary>
		/// returns pts upper range
		/// </summary>
		/// <returns>pts upper range</returns>
		float getMaxPointCount() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// does nothing
		/// </summary>
		/// <param name="mousePosition"></param>
		/// <param name="event"></param>
		/// <param name="button"></param>
		/// <param name="view"></param>
		/// <returns>0</returns>
		float update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// renders obeject
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



		// PRIVATE FUNCTIONS


		/// <summary>
		/// updates point bar size
		/// </summary>
		void updateBarSize();


		/// <summary>
		/// updates point bar position
		/// </summary>
		void updateBarPosition();



		// MEMBERS

		Rectangle	m_bar;	  // pts representatnion
		Button		m_object; // max pts representatnion

		float m_pts;	 // current points
		float m_min_pts; // minimum points
		float m_max_pts; // maximum points
	};

} // namespace ke