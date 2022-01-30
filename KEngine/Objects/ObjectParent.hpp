#pragma once

#include <SFML/Graphics.hpp>

#include "../Structures/Data.hpp"
#include "../Structures/Color.hpp"
#include "../Structures/Vector4.hpp"
#include "../Structures/Settings.hpp"
#include "../Structures/Time.hpp"

#include "../Physics/Physics.hpp"

#include "../Algorithms/Algor.hpp"
#include "../Algorithms/FileStream.hpp"

#include <iostream>
#include <cstdlib>
#include <thread>


/// <summary>
/// Namespace containing Kengine initialization
/// </summary>
namespace KEngine
{

	/// <summary>
	/// Default Initialization
	/// </summary>
	/// <returns>if eveerything succeed - true</returns>
	bool Init();


	/// <summary>
	/// Initialization where you can specify settings options and which fonts can be initialized
	/// </summary>
	/// <param name="forceDefaultSettings"></param>
	/// <param name="loadArial"></param>
	/// <param name="loadArialUnicode"></param>
	/// <param name="loadCalibri"></param>
	/// <param name="loadComicSans"></param>
	/// <param name="loadCourierNew"></param>
	/// <param name="loadTimesNewRoman"></param>
	/// <param name="loadTrebuchetMS"></param>
	/// <param name="loadVerdana"></param>
	/// <returns>if eveerything succeed - true</returns>
	bool CustomInit(
		bool forceDefaultSettings = false,
		bool loadArial =			true,
		bool loadArialUnicode =		true,
		bool loadCalibri =			true,
		bool loadComicSans =		true,
		bool loadCourierNew =		true,
		bool loadTimesNewRoman =	true,
		bool loadTrebuchetMS =		true,
		bool loadVerdana =			true  );

} // namespace KEngine



namespace ke
{

	// Forwand Physics class declaration
	class Physics;


	/// <summary>
	/// Parent class for most of KEngine objects
	/// </summary>
	class GuiObject
	{
	public:

		/// <summary>
		/// Initializes Things fonts
		/// </summary>
		/// <returns>if loading from fonst went correctly, true</returns>
		static bool Init();


		/// <summary>
		/// Initializes specific fonts
		/// </summary>
		/// <param name="loadArial"></param>
		/// <param name="loadArialUnicode"></param>
		/// <param name="loadCalibri"></param>
		/// <param name="loadComicSans"></param>
		/// <param name="loadCourierNew"></param>
		/// <param name="loadTimesNewRoman"></param>
		/// <param name="loadTrebuchetMS"></param>
		/// <param name="loadVerdana"></param>
		/// <returns>if loading from fonst went correctly, true</returns>
		static bool CustomInit(
			bool loadArial =			true,
			bool loadArialUnicode =		true, 
			bool loadCalibri =			true, 
			bool loadComicSans =		true, 
			bool loadCourierNew =		true, 
			bool loadTimesNewRoman =	true,
			bool loadTrebuchetMS =		true, 
			bool loadVerdana =			true );

		GuiObject();
		virtual ~GuiObject();


		///////////////////////

		// pure virtual functions

		virtual void setPosition(const sf::Vector2f& position) = 0;
		virtual void setPosition(float x, float y) = 0;
		virtual sf::Vector2f getPosition() const = 0;

		virtual void setSize(const sf::Vector2f& size) = 0;
		virtual void setSize(float size_x, float size_y) = 0;
		virtual sf::Vector2f getSize() const = 0;

		virtual void move(const sf::Vector2f& offset) = 0;
		virtual void move(float offset_x, float offset_y) = 0;

		virtual void setText(const std::wstring& text) = 0;
		virtual std::wstring getText() const = 0;

		virtual void setOrigin(int origin) = 0;
		virtual int getOrigin() const = 0;

		virtual void setRotation(float angle) = 0;
		virtual void rotate(float angle) = 0;
		virtual float getRotation() const = 0;

		virtual void setPositionByCenter(const sf::Vector2f& position) = 0;
		virtual sf::Vector2f getShapeCenter() const = 0;

		virtual void setScale(const sf::Vector2f& factors) = 0;
		virtual void setScale(float factor_x, float factor_y) = 0;
		virtual void scale(const sf::Vector2f& factors) = 0;
		virtual sf::Vector2f getScale() const = 0;

		virtual void setTexture(const sf::Texture* texture) = 0;
		virtual void setTexture(const std::string& texture_path) = 0;
		virtual const sf::Texture* getTexture() const = 0;

		virtual void setFillColor(const sf::Color& color = sf::Color::Transparent) = 0;
		virtual const sf::Color& getFillColor() const = 0;

		virtual void setTextColor(const sf::Color& text_color = sf::Color::White) = 0;
		virtual const sf::Color& getTextColor() const = 0;

		virtual void setOutlineColor(const sf::Color& outline_color = sf::Color::Transparent) = 0;
		virtual const sf::Color& getOutlineColor() const = 0;

		virtual void setOutlineThickness(float outline_thickness = 0) = 0;
		virtual float getOutlineThickness() const = 0;

		virtual bool isInvaded(const sf::Vector2f& mousePosition) const = 0;
		virtual bool isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const = 0;

		virtual bool isActive() const = 0;
		virtual void setActiveStatus(bool status = true) = 0;


		virtual float update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view) = 0;

		virtual void render(sf::RenderWindow* window) = 0;



		/// <summary>
		/// default physics poiter. If object does not support physics, returns nullptr
		/// </summary>
		/// <returns>nullptr</returns>
		virtual Physics* physics();


		virtual bool created() const = 0;


		/// enum declarations

		static Origin TP;  // text position
		static Origin OR;  // origin
		static Font FONT; // origin
		static TextScope TS; // text scope

	protected:

		static sf::Font f_arial;			// arial					SFML font representation
		static sf::Font f_arial_unicode;	// arial unicode extended	SFML font representation
		static sf::Font f_calibri;			// calibri					SFML font representation
		static sf::Font f_comic_sans;		// comic sans				SFML font representation
		static sf::Font f_courier_new;		// courier new				SFML font representation
		static sf::Font f_times_new_roman;	// times new roman			SFML font representation
		static sf::Font f_trebuchet_MS;		// trebuchetMS				SFML font representation
		static sf::Font f_verdana;			// verdana					SFML font representation
											
		static bool s_arial_status;			// arial					load status
		static bool s_arial_uni_status;		// arial unicode extended	load status
		static bool s_calibri_status;		// calibri					load status
		static bool s_comic_status;			// comic sans				load status
		static bool s_courier_status;		// courier new				load status
		static bool s_times_nr_status;		// times new roman			load status
		static bool s_trebuchet_status;		// trebuchetMS				load status
		static bool s_verdana_status;		// verdana					load status


	private:

		static bool s_fonts_inited; // has fonts been initialized?

	};





	////////////////////////////////////////////////////////////////




	/// <summary>
	/// Object holding component, use if you want to move object with mouse
	/// </summary>
	class HoldObjectWithMouse
	{
	public:

		/// <summary>
		/// Default HoldObjectWithMouse constructor
		/// </summary>
		HoldObjectWithMouse();


		/// <summary>
		/// HoldObjectWithMouse constructor
		/// </summary>
		/// <param name="object">GuiObject you want to move</param>
		HoldObjectWithMouse(GuiObject* object);


		////////////////////////////////


		/// <summary>
		/// connets object to this class
		/// </summary>
		/// <param name="object"></param>
		void connectToObject(GuiObject* object);


		////////////////////////////////


		/// <summary>
		/// Updates object position position
		/// </summary>
		/// <param name="button">SFML mouse button</param>
		/// <param name="mousePosition">mosue position</param>
		/// <param name="event">SFML event</param>
		/// <returns>if moved - true</returns>
		bool update(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event);


		/// <summary>
		/// Updates object position position
		/// </summary>
		/// <param name="button">SFML mouse button</param>
		/// <param name="mousePosition">mosue position</param>
		/// <param name="event">SFML event</param>
		/// <returns>if moved - true</returns>
		bool HoldObject(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event);


		////////////////////////////////


		/// <summary>
		/// Sets manually object holding
		/// </summary>
		/// <param name="status">hold status</param>
		void setHoldStatus(bool status);



	private:


		GuiObject*		m_object;	 // GuiObject you want to move
		bool			m_holding;	 // holding status
		sf::Vector2f	m_catchDiff; // object center - mouse position

	};





	////////////////////////////////////////////////////////////////



	

	/// <summary>
	/// View Holding component, use if you want to move view with mouse
	/// </summary>
	class HoldView
	{
	public:

		/// <summary>
		/// HoldView default constructor
		/// </summary>
		HoldView();


		/// <summary>
		/// HoldView constructor
		/// </summary>
		/// <param name="view">SFML view</param>
		HoldView(sf::View* view);


		/// <summary>
		/// HoldView destructor
		/// </summary>
		~HoldView();


		////////////////////////////////


		/// <summary>
		/// adds connects view to the object
		/// </summary>
		/// <param name="view">SFML view</param>
		void setView(sf::View* view);


		////////////////////////////////


		/// <summary>
		/// sets borders where view can be moved
		/// </summary>
		/// <param name="left_top">left top corner coordinate</param>
		/// <param name="right_bottom">right bottom corner coordinate</param>
		void setBorders(const sf::Vector2f& left_top, const sf::Vector2f& right_bottom);


		/// <summary>
		/// sets borders where view can be moved
		/// </summary>
		/// <param name="border">left top and right bottom corners coordinates</param>
		void setBorders(const Vector4f& border);


		////////////////////////////////


		/// <summary>
		/// updates view position, use outside pollEvent loop
		/// </summary>
		/// <param name="mousePosition">mouse position</param>
		/// <param name="button">SFML mouse button</param>
		/// <returns>if view was moved - true</returns>
		bool update(const sf::Vector2f& mousePosition, sf::Mouse::Button button);


		/// <summary>
		/// updates view holding, use inside pollEvent loop
		/// </summary>
		/// <param name="mousePosition">mouse position</param>
		/// <param name="button">SFML mouse button</param>
		/// <param name="event">SFML event</param>
		/// <returns>if clicked, true</returns>
		bool updateClick(const sf::Vector2f& mousePosition, sf::Mouse::Button button, sf::Event& event);



	private:


		sf::View*		m_view;	  // SFML view
		sf::Vector2f	m_deltaP; // view center - mouse position
		Vector4f		m_border; // border coordinates

	};





	//======----------                 ----------======//
	// F U N C T I O N S   W I T H   G U I O B J E C T //
	//======----------                 ----------======//





	//////////////////////////////////////////////////////////////////////////



	/// <summary>
	/// Smoothly changes color
	/// </summary>
	/// <param name="object">affected object</param>
	/// <param name="tf_argumet">true - changing to target color, false - changing to basic color</param>
	/// <param name="target_color">color after change</param>
	/// <param name="basic_color">basic color</param>
	/// <param name="float_color">KEngie Color<float> which is used to correctly calculate current color, must outlive whole operation</param>
	/// <param name="intensity">speed</param>
	/// <param name="dt">delta time</param>
	/// <returns>same as tf_argument</returns>
	bool SmoothColorChange(GuiObject* object, bool tf_argumet, const sf::Color& target_color, const sf::Color& basic_color, Color<float>& float_color, const float intensity, const float dt);


	////////////////////////////////


	/// <summary>
	/// Smoothly changes object's outline color
	/// </summary>
	/// <param name="object">affected object</param>
	/// <param name="tf_argumet">true - changing to target color, false - changing to basic color</param>
	/// <param name="target_color">color after change</param>
	/// <param name="basic_color">basic color</param>
	/// <param name="float_color">KEngie Color<float> which is used to correctly calculate current color, must outlive whole operation</param>
	/// <param name="intensity">speed</param>
	/// <param name="dt">delta time</param>
	/// <returns>same as tf_argument</returns>
	bool SmoothOutlineColorChange(GuiObject* object, bool tf_argumet, const sf::Color& target_color, const sf::Color& basic_color, Color<float>& float_color, const float intensity, const float dt);


	////////////////////////////////


	/// <summary>
	/// Smoothly changes object's text color
	/// </summary>
	/// <param name="object">affected object</param>
	/// <param name="tf_argumet">true - changing to target color, false - changing to basic color</param>
	/// <param name="target_color">color after change</param>
	/// <param name="basic_color">basic color</param>
	/// <param name="float_color">KEngie Color<float> which is used to correctly calculate current color, must outlive whole operation</param>
	/// <param name="intensity">speed</param>
	/// <param name="dt">delta time</param>
	/// <returns>same as tf_argument</returns>
	bool SmoothTextColorChange(GuiObject* object, bool tf_argumet, const sf::Color& target_color, const sf::Color& basic_color, Color<float>& float_color, const float intensity, const float dt);



	////////////////////////////////////////////////////////////////



	/// <summary>
	/// Moves object to specific location with given speed
	/// </summary>
	/// <param name="object">affected object</param>
	/// <param name="destination">targeted position</param>
	/// <param name="start_position"></param>
	/// <param name="speed">movement speed</param>
	/// <param name="dt">delta time</param>
	/// <returns>if objest is moving - true</returns>
	bool SmoothMove(GuiObject* object, const sf::Vector2f& destination, const sf::Vector2f& start_position, const float speed, const float dt);



	////////////////////////////////////////////////////////////////




	bool SmoothViewMove(sf::View* view, const sf::Vector2f& destination, const sf::Vector2f& start_position, const float speed, const float dt);



	////////////////////////////////////////////////////////////////



	/// <summary>
	/// Rotates object with given speed to given rotation
	/// </summary>
	/// <param name="object">affected object</param>
	/// <param name="target_rotation">target rotation, set 360 or 0 to move infinitely</param>
	/// <param name="speed">rotation speed (angle per frame * dt)</param>
	/// <param name="dt">delta time</param>
	/// <returns>if rotated - true</returns>
	bool SmoothRotation(GuiObject* object, float target_rotation, const float speed, const float dt);



	////////////////////////////////////////////////////////////////



	/// <summary>
	/// Scales object smoothly
	/// </summary>
	/// <param name="object">affected object</param>
	/// <param name="target_scale">scale after this magic</param>
	/// <param name="speed">speed of scaling</param>
	/// <param name="dt">delta time</param>
	/// <returns>if somethig changed - true</returns>
	bool SmoothScale(GuiObject* object, const sf::Vector2f& target_scale, const float speed, const float dt);



	////////////////////////////////////////////////////////////////



	/// <summary>
	/// OLD FUNCTION, USE KEngine HoldView CLASS INSTEAD. Enables moving throught the given view like a map
	/// </summary>
	/// <param name="view">given view</param>
	/// <param name="button">mouse mutton used to move the view</param>
	/// <param name="mousePosition">mouse position</param>
	/// <param name="event">SFML event</param>
	/// <param name="top_left_barrier_cord">top left corner (barrier)</param>
	/// <param name="bottom_right_barrier_cord">right bottom corner (barrier)</param>
	/// <returns>if holded - true</returns>
	bool ViewHolding(sf::View* view, sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event, const sf::Vector2f& top_left_barrier_cord = sf::Vector2f(0, 0), const sf::Vector2f& bottom_right_barrier_cord = sf::Vector2f(0, 0));



	////////////////////////////////////////////////////////////////



	/// <summary>
	/// checks if object is outside the view
	/// </summary>
	/// <param name="object">checked object</param>
	/// <param name="view">the given view</param>
	/// <param name="shift">custom shifted barrier</param>
	/// <returns>outside - true</returns>
	bool isOutsideTheView(GuiObject* object, sf::View* view, const sf::Vector2f& shift = sf::Vector2f(0, 0));


	////////////////////////////////


	/// <summary>
	/// checks if object is touching of is outside the view
	/// </summary>
	/// <param name="object">checked object</param>
	/// <param name="view">the given view</param>
	/// <returns>if is quitting - true</returns>
	bool isQuittingTheView(GuiObject* object, sf::View* view);


} // namespace ke