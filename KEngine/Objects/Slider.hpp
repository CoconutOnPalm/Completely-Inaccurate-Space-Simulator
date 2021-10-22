#pragma once

#include "ObjectParent.hpp"
#include "Button.hpp"


namespace ke
{

	/// <summary>
	/// KEngine Slider is and object based on 2x KEngine Button that can move view by 'sliding' through the track (works like this right bar on chrome) 
	/// </summary>
	class Slider : public GuiObject
	{
	public:


		/// <summary>
		/// Default Slider constructor
		/// </summary>
		Slider();


		////////////////////////////////


		/// <summary>
		/// Slider constructor
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="position">object position</param>
		/// <param name="field_height">height of scrolled view</param>
		/// <param name="origin">object origin, only RIGHT_... available</param>
		/// <param name="slider_texture">'sliding rectangle' texture</param>
		/// <param name="slider_track_texture">'slider track' texture</param>
		/// <param name="slider_color">color of 'sliding rectangle'</param>
		/// <param name="slider_track_color">color of 'slider track'</param>
		/// <param name="slider_outline_thickness">'sliding rectangle' outline thickness</param>
		/// <param name="slider_outline_color">'sliding rectangle' outline color</param>
		/// <param name="slider_track_outline_thickness">'slider track' outline thickness</param>
		/// <param name="slider_track_outline_color">'slider track' outline color</param>
		/// <param name="active"></param>
		Slider(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			float field_height,
			int origin,
			const sf::Texture* slider_texture,
			const sf::Texture* slider_track_texture,
			const sf::Color& slider_color = sf::Color::Black,
			const sf::Color& slider_track_color = sf::Color::Transparent,
			float slider_outline_thickness = 0,
			const sf::Color& slider_outline_color = sf::Color::Transparent,
			float slider_track_outline_thickness = 0,
			const sf::Color& slider_track_outline_color = sf::Color::Transparent,
			bool active = true);


		////////////////////////////////


		/// <summary>
		/// Slider constructor
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="position">object position</param>
		/// <param name="field_height">height of scrolled view</param>
		/// <param name="origin">object origin, only RIGHT_... available</param>
		/// <param name="slider_texture_path">path to 'sliding rectangle' texture</param>
		/// <param name="slider_track_texture_path">path to 'slider track' texture</param>
		/// <param name="slider_color">color of 'sliding rectangle'</param>
		/// <param name="slider_track_color">color of 'slider track'</param>
		/// <param name="slider_outline_thickness">'sliding rectangle' outline thickness</param>
		/// <param name="slider_outline_color">'sliding rectangle' outline color</param>
		/// <param name="slider_track_outline_thickness">'slider track' outline thickness</param>
		/// <param name="slider_track_outline_color">'slider track' outline color</param>
		/// <param name="active"></param>
		Slider(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			float field_height,
			int origin,
			const std::string& slider_texture_path,
			const std::string& slider_track_texture_path,
			const sf::Color& slider_color = sf::Color::Black,
			const sf::Color& slider_track_color = sf::Color::Transparent,
			float slider_outline_thickness = 0,
			const sf::Color& slider_outline_color = sf::Color::Transparent,
			float slider_track_outline_thickness = 0,
			const sf::Color& slider_track_outline_color = sf::Color::Transparent,
			bool active = true);


		////////////////////////////////


		/// <summary>
		/// Slider destructor
		/// </summary>
		/// <remarks>
		/// nothing is inside
		/// </remarks>
		virtual ~Slider();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Slider copy constructor
		/// </summary>
		/// <param name="other">other Slider</param>
		Slider(Slider& other);


		////////////////////////////////


		/// <summary>
		/// Slider '=' operator
		/// </summary>
		/// <param name="other">other Slider</param>
		/// <returns>*this</returns>
		Slider& operator= (Slider& other);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Slider creator
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="position">object position</param>
		/// <param name="field_height">height of scrolled view</param>
		/// <param name="origin">object origin, only RIGHT_... available</param>
		/// <param name="slider_texture">'sliding rectangle' texture</param>
		/// <param name="slider_track_texture">'slider track' texture</param>
		/// <param name="slider_color">color of 'sliding rectangle'</param>
		/// <param name="slider_track_color">color of 'slider track'</param>
		/// <param name="slider_outline_thickness">'sliding rectangle' outline thickness</param>
		/// <param name="slider_outline_color">'sliding rectangle' outline color</param>
		/// <param name="slider_track_outline_thickness">'slider track' outline thickness</param>
		/// <param name="slider_track_outline_color">'slider track' outline color</param>
		/// <param name="active"></param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			float field_height,
			int origin,
			const sf::Texture* slider_texture,
			const sf::Texture* slider_track_texture,
			const sf::Color& slider_color = sf::Color::Black,
			const sf::Color& slider_track_color = sf::Color::Transparent,
			float slider_outline_thickness = 0,
			const sf::Color& slider_outline_color = sf::Color::Transparent,
			float slider_track_outline_thickness = 0,
			const sf::Color& slider_track_outline_color = sf::Color::Transparent,
			bool active = true);


		////////////////////////////////


		/// <summary>
		/// Slider creator
		/// </summary>
		/// <param name="size">object size</param>
		/// <param name="position">object position</param>
		/// <param name="field_height">height of scrolled view</param>
		/// <param name="origin">object origin, only RIGHT_... available</param>
		/// <param name="slider_texture_path">path to 'sliding rectangle' texture</param>
		/// <param name="slider_track_texture_path">path to 'slider track' texture</param>
		/// <param name="slider_color">color of 'sliding rectangle'</param>
		/// <param name="slider_track_color">color of 'slider track'</param>
		/// <param name="slider_outline_thickness">'sliding rectangle' outline thickness</param>
		/// <param name="slider_outline_color">'sliding rectangle' outline color</param>
		/// <param name="slider_track_outline_thickness">'slider track' outline thickness</param>
		/// <param name="slider_track_outline_color">'slider track' outline color</param>
		/// <param name="active"></param>
		void create(
			const sf::Vector2f& size,
			const sf::Vector2f& position,
			float field_height,
			int origin,
			const std::string& slider_texture_path,
			const std::string& slider_track_texture_path,
			const sf::Color& slider_color = sf::Color::Black,
			const sf::Color& slider_track_color = sf::Color::Transparent,
			float slider_outline_thickness = 0,
			const sf::Color& slider_outline_color = sf::Color::Transparent,
			float slider_track_outline_thickness = 0,
			const sf::Color& slider_track_outline_color = sf::Color::Transparent,
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


		////////////////


		/// <summary>
		/// Returns slider position
		/// </summary>
		/// <returns></returns>
		sf::Vector2f getPosition() const;


		/// <summary>
		/// Returns track position
		/// </summary>
		/// <returns></returns>
		sf::Vector2f getSliderTrackPosition() const;



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


		////////////////


		/// <summary>
		/// returns object size
		/// </summary>
		/// <returns>size in SFML Vector2f</returns>
		sf::Vector2f getSize() const;


		/// <summary>
		/// returns slider size
		/// </summary>
		/// <returns></returns>
		sf::Vector2f getSliderSize() const;



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


		////////////////


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
		/// not available in Slider
		/// </summary>
		/// <param name="text"></param>
		void setText(const std::wstring& text);


		/// <summary>
		/// not available in Slider
		/// </summary>
		/// <returns>empty std::wstring</returns>
		std::wstring getText() const;



		////////////////////////////////



		/// <summary>
		/// sets object origin, only RIGHT_... available
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
		/// not available in Slider
		/// </summary>
		/// <param name="angle"></param>
		void setRotation(float angle);


		/// <summary>
		/// not available in Slider
		/// </summary>
		/// <param name="angle"></param>
		void rotate(float angle);


		/// <summary>
		/// not available in Slider
		/// </summary>
		/// <returns>0.0f</returns>
		float getRotation() const;



		////////////////////////////////



		/// <summary>
		/// sets position by object's center
		/// </summary>
		/// <param name="position">new position</param>
		void setPositionByCenter(const sf::Vector2f& position);


		/// <summary>
		/// returns slider center
		/// </summary>
		/// <returns>slider center</returns>
		sf::Vector2f getShapeCenter() const;


		/// <summary>
		/// slider track center
		/// </summary>
		/// <returns>slider track center</returns>
		sf::Vector2f getTrackCenter() const;



		////////////////////////////////



		/// <summary>
		/// sets slider texture
		/// </summary>
		/// <param name="texture">SFML texture</param>
		void setTexture(const sf::Texture* texture);


		/// <summary>
		/// sets slider track texture
		/// </summary>
		/// <param name="texture">SFML texture</param>
		void setTrackTexture(const sf::Texture* texture);


		////////////////


		/// <summary>
		/// sets slider texture from given filename
		/// </summary>
		/// <param name="filename">texture path</param>
		void setTexture(const std::string& filename);


		/// <summary>
		/// sets slider track texture from given filename
		/// </summary>
		/// <param name="filename">texture path</param>
		void setTrackTexture(const std::string& filename);


		////////////////


		/// <summary>
		/// returns slider's texture 
		/// </summary>
		/// <returns>SFML texture</returns>
		const sf::Texture* getTexture() const;


		/// <summary>
		/// returns slider track's texture 
		/// </summary>
		/// <returns>SFML texture</returns>
		const sf::Texture* getTrackTexture() const;



		////////////////////////////////



		/// <summary>
		/// sets slider fill color
		/// </summary>
		/// <param name="color">SFML color</param>
		void setFillColor(const sf::Color& color);


		/// <summary>
		/// sets slider track fill color
		/// </summary>
		/// <param name="color">SFML color</param>
		void setTrackColor(const sf::Color& color);


		////////////////


		/// <summary>
		/// returns slider fill color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getFillColor() const;


		/// <summary>
		/// returns slider track fill color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getTrackColor() const;



		////////////////////////////////



		/// <summary>
		/// not available in slider
		/// </summary>
		/// <param name="text_color"></param>
		void setTextColor(const sf::Color& text_color = sf::Color::White);


		/// <summary>
		/// not available in slider
		/// </summary>
		/// <returns>sf::Color::Transparent</returns>
		const sf::Color& getTextColor() const;



		////////////////////////////////



		/// <summary>
		/// sets slider outline fill color
		/// </summary>
		/// <param name="outline_color">SFML color</param>
		void setOutlineColor(const sf::Color& outline_color);


		/// <summary>
		/// sets slider track outline fill color
		/// </summary>
		/// <param name="outline_color">SFML color</param>
		void setTrackOutlineColor(const sf::Color& outline_color);


		////////////////


		/// <summary>
		/// returns slider outline fill color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getOutlineColor() const;


		/// <summary>
		/// returns slider track outline fill color
		/// </summary>
		/// <returns>SFML color</returns>
		const sf::Color& getTrackOutlineColor() const;



		////////////////////////////////


		
		/// <summary>
		/// sets slider outline thickness
		/// </summary>
		/// <param name="outline_thickness">slider outline thickness</param>
		void setOutlineThickness(float outline_thickness = 0);


		/// <summary>
		/// sets slider track outline thickness
		/// </summary>
		/// <param name="outline_thickness">slider track outline thickness</param>
		void setTrackOutlineThickness(float outline_thickness = 0);


		////////////////


		/// <summary>
		/// returns slider outline thickness
		/// </summary>
		/// <returns>slider outline thickness</returns>
		float getOutlineThickness() const;


		/// <summary>
		/// returns slider track outline thickness
		/// </summary>
		/// <returns>slider track outline thickness</returns>
		float getTrackOutlineThickness() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// checks if point (mouse position) is on the slider
		/// </summary>
		/// <param name="mousePosition">point (mouse position)</param>
		/// <returns>if collides - true</returns>
		bool isInvaded(const sf::Vector2f& mousePosition) const;


		////////////////


		/// <summary>
		/// checks if point (mouse position) is on the slider track 
		/// </summary>
		/// <param name="mousePosition">point (mouse position)</param>
		/// <returns>if collides - true</returns>
		bool isTrackInvaded(const sf::Vector2f& mousePosition) const;



		////////////////////////////////



		/// <summary>
		/// checks if sldier is clicked by specific key
		/// </summary>
		/// <param name="button">SFML button</param>
		/// <param name="mousePosition">position of the mouse</param>
		/// <param name="event">SFML event</param>
		/// <returns>if clicked</returns>
		bool isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const;


		////////////////


		/// <summary>
		/// checks if sldier is clicked by specific key
		/// </summary>
		/// <param name="button">SFML button</param>
		/// <param name="mousePosition">position of the mouse</param>
		/// <param name="event">SFML event</param>
		/// <returns>if clicked</returns>
		bool isTrackClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const;



		////////////////////////////////////////////////////////////////



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
		/// sets hold status - is slider holded by mouse (is sliding)
		/// </summary>
		/// <param name="status">hold status</param>
		void setHoldStatus(bool status);


		/// <summary>
		/// checks if slider is holde bu mouse
		/// </summary>
		/// <returns></returns>
		bool isHolded() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// returns Slider
		/// </summary>
		/// <returns>KEngine Button</returns>
		Button* getSlider();


		/// <summary>
		/// returns Slider track
		/// </summary>
		/// <returns>KEngine Button</returns>
		Button* getSliderTrack();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// sets heigth of slided view
		/// </summary>
		/// <param name="field_height">'page' height</param>
		void setFieldHeight(float field_height);


		/// <summary>
		/// returns heigth of slided view
		/// </summary>
		/// <returns>'page' height</returns>
		float getFieldHeight() const;



		////////////////////////////////



		/// <summary>
		/// returns how much slider shifted from top
		/// </summary>
		/// <returns>slider center (y) - slider track top (y)</returns>
		float getShift() const;



		////////////////////////////////



		/// <summary>
		/// sets view start position
		/// </summary>
		/// <param name="top_position">shift from 0 (y) coordinate</param>
		/// <param name="view">SFML view</param>
		void setViewPositionShift(float top_position, sf::View* view);


		/// <summary>
		/// returns view start position
		/// </summary>
		/// <returns>view shift for 0 (y) coordinate</returns>
		float getViewPositionShift() const;



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// Slider heart, responsible for all operatons, use in pollEvent loop
		/// </summary>
		/// <param name="mousePosition">mouse position</param>
		/// <param name="event">SFML event</param>
		/// <param name="button">SFML button</param>
		/// <param name="view">SMFL view, can be nullptr</param>
		/// <returns>shift (y) for object not affected by the view</returns>
		float update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view);



		////////////////////////////////



		/// <summary>
		/// updates size, used automatically (ignore it)
		/// </summary>
		void updateSize();



		////////////////////////////////



		void updateSliderPosition(sf::View* view);
		void updateSliderPosition(float offset);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// renders object
		/// </summary>
		/// <param name="window">SMFL window</param>
		void render(sf::RenderWindow* window);



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// checks if object has been created
		/// </summary>
		/// <returns>if object is created, true</returns>
		bool created() const;





	private:



		// MEMBERS 


		Button m_slider;		// This bar used for scrolling
		Button m_slider_track;	// 'Track' for scrolling bar


		bool	m_holded;		// is slider holded?
		float	m_catchDiff;	// difference between mouse position and slider center
								
		float	m_field_height;	// scrolled view size
		float	m_shift;		// slider shift from pos 0
		float	m_top_pos;		// view shift from 0y coordinate


		bool m_created; // has object been initialized?
	};

} // namespace ke