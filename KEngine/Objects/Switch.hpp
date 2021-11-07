#pragma once

#include "CurvedButton.hpp"
#include "Circle.hpp"



namespace ke
{


	/// <summary>
	/// KEngine Switch is and object that is holding signal which can be changed (true or false)
	/// </summary>
	class Switch : public GuiObject
	{
	public:


		/// <summary>
		/// Switch default constructor
		/// </summary>
		Switch();


		////////////////////////////////


		/// <summary>
		/// Switch constructor
		/// </summary>
		/// <param name="size"></param>
		/// <param name="button_radius"></param>
		/// <param name="position"></param>
		/// <param name="origin">object origin</param>
		/// <param name="button_texture">SFML texture</param>
		/// <param name="object_texture">SFML texture</param>
		/// <param name="button_color"></param>
		/// <param name="object_color"></param>
		/// <param name="button_outline_thickness"></param>
		/// <param name="button_outline_color"></param>
		/// <param name="object_outline_thickness"></param>
		/// <param name="object_outline_color"></param>
		/// <param name="active">if object is processed and rendered</param>
		Switch(
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
		/// Switch constructor
		/// </summary>
		/// <param name="size"></param>
		/// <param name="button_radius"></param>
		/// <param name="position"></param>
		/// <param name="origin">object origin</param>
		/// <param name="button_texture_path">path to SFML texture</param>
		/// <param name="object_texture_path">path to SFML texture</param>
		/// <param name="button_color"></param>
		/// <param name="object_color"></param>
		/// <param name="button_outline_thickness"></param>
		/// <param name="button_outline_color"></param>
		/// <param name="object_outline_thickness"></param>
		/// <param name="object_outline_color"></param>
		/// <param name="active">if object is processed and rendered</param>
		Switch(
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
		/// Switch destructor
		/// </summary>
		virtual ~Switch();


		////////////////////////////////


		/// <summary>
		/// Switch copy constructor
		/// </summary>
		/// <param name="other">other Switch</param>
		Switch(Switch& other);


		/// <summary>
		/// Switch '=' operator
		/// </summary>
		/// <param name="other">other Switch</param>
		/// <returns>*this</returns>
		Switch& operator= (Switch& other);



		////////////////////////////////



		/// <summary>
		/// Switch creator
		/// </summary>
		/// <param name="size"></param>
		/// <param name="button_radius"></param>
		/// <param name="position"></param>
		/// <param name="origin">object origin</param>
		/// <param name="button_texture">SFML texture</param>
		/// <param name="object_texture">SFML texture</param>
		/// <param name="button_color"></param>
		/// <param name="object_color"></param>
		/// <param name="button_outline_thickness"></param>
		/// <param name="button_outline_color"></param>
		/// <param name="object_outline_thickness"></param>
		/// <param name="object_outline_color"></param>
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
		/// Switch creator
		/// </summary>
		/// <param name="size"></param>
		/// <param name="button_radius"></param>
		/// <param name="position"></param>
		/// <param name="origin">object origin</param>
		/// <param name="button_texture_path">path to SFML texture</param>
		/// <param name="object_texture_path">path to SFML texture</param>
		/// <param name="button_color"></param>
		/// <param name="object_color"></param>
		/// <param name="button_outline_thickness"></param>
		/// <param name="button_outline_color"></param>
		/// <param name="object_outline_thickness"></param>
		/// <param name="object_outline_color"></param>
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



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets button radius
		/// </summary>
		/// <param name="radius">new button radius</param>
		void setButtonRadius(float radius);


		/// <summary>
		/// returns button radius
		/// </summary>
		/// <returns></returns>
		float getButtonRadius() const;



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
		/// does nothing - not available in this object
		/// </summary>
		/// <param name="text"></param>
		void setText(const std::wstring& text);


		/// <summary>
		/// does nothing - not available in this object
		/// </summary>
		/// <returns>std::wstring()</returns>
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
		/// does nothing - not available in this object
		/// </summary>
		/// <param name="angle"></param>
		void setRotation(float angle);


		/// <summary>
		/// does nothing - not available in this object
		/// </summary>
		/// <param name="angle"></param>
		void rotate(float angle);


		/// <summary>
		/// does nothing - not available in this object
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
		/// sets button scale 
		/// </summary>
		/// <param name="factors">scale in SFML Vector2f</param>
		void setButtonScale(const sf::Vector2f& factors);


		/// <summary>
		/// sets button scale
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
		/// scales button by given factors
		/// </summary>
		/// <param name="factors">scale factors in SFML Vector2f</param>
		void scaleButton(const sf::Vector2f& factors);



		/// returns object scale
		/// </summary>
		/// <returns>button scale in SFML Vector2f</returns>
		sf::Vector2f getScale() const;


		/// returns button scale
		/// </summary>
		/// <returns>button scale in SFML Vector2f</returns>
		sf::Vector2f getButtonScale() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object position independently from origin
		/// </summary>
		/// <param name="position">position in SFML Vector2f</param>
		void setPositionByCenter(const sf::Vector2f& position);


		/// <summary>
		/// returns object center
		/// </summary>
		/// <returns>position of object center</returns>
		sf::Vector2f getShapeCenter() const;


		/// <summary>
		/// returns button center
		/// </summary>
		/// <returns>position of button center</returns>
		sf::Vector2f getButtonCenter() const;



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
		/// sets button texture
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
		void setTexture(const std::string& texture_path);


		/// <summary>
		/// sets button texture
		/// </summary>
		/// <param name="filename">path to the texture</param>
		void setButtonTexture(const std::string& texture_path);



		/// <summary>
		/// returns poiter to object texture
		/// </summary>
		/// <returns>SFML Texutre</returns>
		const sf::Texture* getTexture() const;


		/// <summary>
		/// returns poiter to button texture
		/// </summary>
		/// <returns>SFML Texutre</returns>
		const sf::Texture* getButtonTexture() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object color
		/// </summary>
		/// <param name="color">new SFML color</param>
		void setFillColor(const sf::Color& color = sf::Color::Transparent);


		/// <summary>
		/// sets button color
		/// </summary>
		/// <param name="color">new SFML color</param>
		void setButtonColor(const sf::Color& color = sf::Color::Transparent);



		/// <summary>
		/// returns object color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getFillColor() const;


		/// <summary>
		/// returns button color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getButtonColor() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// does nothing - not available in this object
		/// </summary>
		/// <param name="text_color"></param>
		void setTextColor(const sf::Color& text_color = sf::Color::White);


		/// <summary>
		/// does nothing - not available in this object
		/// </summary>
		/// <returns>std::wstring()</returns>
		const sf::Color& getTextColor() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object outline color
		/// </summary>
		/// <param name="outline_color">new SFML Color</param>
		void setOutlineColor(const sf::Color& outline_color = sf::Color::Transparent);


		/// <summary>
		/// sets button outline color
		/// </summary>
		/// <param name="outline_color">new SFML Color</param>
		void setOutlineButtonColor(const sf::Color& outline_color = sf::Color::Transparent);



		/// <summary>
		/// returns object outline color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getOutlineColor() const;


		/// <summary>
		/// returns button outline color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getOutlineButtonColor() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object outline thickness
		/// </summary>
		/// <param name="outline_thickness">new outline thickness</param>
		void setOutlineThickness(float outline_thickness);


		/// <summary>
		/// sets button outline thickness
		/// </summary>
		/// <param name="outline_thickness">new outline thickness</param>
		void setOutlineButtonThickness(float outline_thickness);



		/// <summary>
		/// returns object outline thickness
		/// </summary>
		/// <returns>outline thickness</returns>
		float getOutlineThickness() const;


		/// <summary>
		/// returns button outline thickness
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
		/// checks if point (mouse position) is on the button
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
		/// checks if button is clicked by specific key
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
		/// Returns colored button
		/// </summary>
		/// <returns></returns>
		Circle* getColorButton();


		/// <summary>
		/// returon textured button
		/// </summary>
		/// <returns></returns>
		Circle* getTextureButton();


		/// <summary>
		/// returns 'track'
		/// </summary>
		/// <returns></returns>
		CurvedButton* getObject();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets object signal (true or false)
		/// </summary>
		/// <param name="signal">new signal</param>
		void setSignal(bool signal);


		/// <summary>
		/// returns signal
		/// </summary>
		/// <returns></returns>
		bool getSignal() const;


		/// <summary>
		/// sets status of the objects (active or not)
		/// </summary>
		/// <param name="status">new status</param>
		bool signal() const;


		////////////////////////////////


		/// <summary>
		/// cheks if button is moving (with SmoothSignalChange())
		/// </summary>
		/// <returns></returns>
		bool isMoving() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// updates object, use in pollEvent loop
		/// </summary>
		/// <param name="mousePosition">mouse position</param>
		/// <param name="event">SFML event</param>
		/// <param name="button">SFML mouse button</param>
		/// <param name="view"></param>
		/// <returns>if clicked - 1</returns>
		float update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view);


		////////////////////////////////


		/// <summary>
		/// checs for click for SmoothSignalChange
		/// </summary>
		/// <param name="mousePosition">mouse position</param>
		/// <param name="event">SFML event</param>
		/// <param name="button">SMFL mouse button</param>
		/// /// <returns>if clicked - true</returns>
		bool SSC_click_update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button);


		/// <summary>
		/// changes signal smoothly
		/// </summary>
		/// <param name="speed">button speed</param>
		/// <param name="dt">delta time</param>
		/// <returns>if moving - true</returns>
		bool SmoothSignalChange(float speed, float dt);



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


		// MEMBERS 


		CurvedButton	m_object;			// 'background' for button
		Circle			m_texture_button;	// button holding texture
		Circle			m_color_button;		// button holding color

		bool m_signal; // object signal
		bool m_moving; // is button moving? (for Smooth signal change)
	};

} // namespace ke