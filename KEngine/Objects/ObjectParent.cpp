#include "ObjectParent.hpp"


namespace KEngine
{
	bool Init()
	{
		bool success = true; // returns loading status (successful or not)

		if (!ke::Settings::Init())  success = false;
		if (!ke::GuiObject::Init()) success = false;

		return success;
	}


	bool CustomInit(
		bool forceDefaultSettings,
		bool loadArial,
		bool loadArialUnicode,
		bool loadCalibri,
		bool loadComicSans,
		bool loadCourierNew,
		bool loadTimesNewRoman,
		bool loadTrebuchetMS,
		bool loadVerdana)
	{
		bool success = ke::Settings::Init(); // returns loading status (successful or not)

		if (forceDefaultSettings)
			ke::Settings::restoreDefaults();

		if (!ke::GuiObject::CustomInit(loadArial, loadArialUnicode, loadCalibri, loadComicSans, loadCourierNew, loadTimesNewRoman, loadTrebuchetMS, loadVerdana))
			success = false;

		return true;
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////



namespace ke
{

	Origin GuiObject::TP;
	Origin GuiObject::OR;
	Font GuiObject::FONT;
	TextScope GuiObject::TS;


	sf::Font GuiObject::f_arial;
	sf::Font GuiObject::f_arial_unicode;
	sf::Font GuiObject::f_calibri;
	sf::Font GuiObject::f_comic_sans;
	sf::Font GuiObject::f_courier_new;
	sf::Font GuiObject::f_times_new_roman;
	sf::Font GuiObject::f_trebuchet_MS;
	sf::Font GuiObject::f_verdana;

	bool GuiObject::s_arial_status = true;
	bool GuiObject::s_arial_uni_status = true;
	bool GuiObject::s_calibri_status = true;
	bool GuiObject::s_comic_status = true;
	bool GuiObject::s_courier_status = true;
	bool GuiObject::s_times_nr_status = true;
	bool GuiObject::s_trebuchet_status = true;
	bool GuiObject::s_verdana_status = true;


	bool GuiObject::s_fonts_inited = false;


	////////////////////////////////


	bool GuiObject::Init()
	{
		bool success = true; // returns loading status (successful or not)


		FileStream filestream;
		if (!filestream.open(Settings::DefaultFontPath(), std::ios::in))
		{
			throw_error("GuiObject::Init()", "failed to load font paths - setting paths to default", "ERROR");
			success = false;
		}


		const int font_num = 8;
		std::string paths[font_num] = { 
			"KEngine/Sources/Data/arial.ttf",
			"KEngine/Sources/Data/arialUNI.ttf",
			"KEngine/Sources/Data/calibri.ttf",
			"KEngine/Sources/Data/comic.ttf",
			"KEngine/Sources/Data/cour.ttf",
			"KEngine/Sources/Data/times.ttf",
			"KEngine/Sources/Data/trebuc.ttf",
			"KEngine/Sources/Data/verdana.ttf" 
		};

		for (int i = 0; i < font_num; i++)
			filestream.textRead(paths[i]);


		if (!f_arial.loadFromFile(paths[0])) { success = false; s_arial_status = false; }
		if (!f_arial_unicode.loadFromFile(paths[1])) { success = false; s_arial_uni_status = false; }
		if (!f_calibri.loadFromFile(paths[2])) { success = false; s_calibri_status = false; }
		if (!f_comic_sans.loadFromFile(paths[3])) { success = false; s_comic_status = false; }
		if (!f_courier_new.loadFromFile(paths[4])) { success = false; s_courier_status = false; }
		if (!f_times_new_roman.loadFromFile(paths[5])) { success = false; s_times_nr_status = false; }
		if (!f_trebuchet_MS.loadFromFile(paths[6])) { success = false; s_trebuchet_status = false; }
		if (!f_verdana.loadFromFile(paths[7])) { success = false; s_verdana_status = false; }

		s_fonts_inited = true;

		return success;
	}


	////////////////////////////////


	bool GuiObject::CustomInit(
		bool loadArial,
		bool loadArialUnicode,
		bool loadCalibri,
		bool loadComicSans,
		bool loadCourierNew,
		bool loadTimesNewRoman,
		bool loadTrebuchetMS,
		bool loadVerdana)
	{
		bool success = true; // returns loading status (successful or not)


		FileStream filestream;
		if (!filestream.open(Settings::DefaultFontPath(), std::ios::in))
		{
			throw_error("GuiObject::Init()", "failed to load font paths - setting paths to default", "ERROR");
			success = false;
		}


		const int font_num = 8;
		std::string paths[font_num] = { 
			"KEngine/Sources/Data/arial.ttf",
			"KEngine/Sources/Data/arialUNI.ttf",
			"KEngine/Sources/Data/calibri.ttf",
			"KEngine/Sources/Data/comic.ttf",
			"KEngine/Sources/Data/cour.ttf",
			"KEngine/Sources/Data/times.ttf",
			"KEngine/Sources/Data/trebuc.ttf",
			"KEngine/Sources/Data/verdana.ttf" 
		};

		for (int i = 0; i < font_num; i++)
			filestream.textRead(paths[i]);

		if (loadArial && !f_arial.loadFromFile(paths[0])) { success = false; s_arial_status = false; }
		if (loadArialUnicode && !f_arial_unicode.loadFromFile(paths[1])) { success = false; s_arial_uni_status = false; }
		if (loadCalibri && !f_calibri.loadFromFile(paths[2])) { success = false; s_calibri_status = false; }
		if (loadComicSans && !f_comic_sans.loadFromFile(paths[3])) { success = false; s_comic_status = false; }
		if (loadCourierNew && !f_courier_new.loadFromFile(paths[4])) { success = false; s_courier_status = false; }
		if (loadTimesNewRoman && !f_times_new_roman.loadFromFile(paths[5])) { success = false; s_times_nr_status = false; }
		if (loadTrebuchetMS && !f_trebuchet_MS.loadFromFile(paths[6])) { success = false; s_trebuchet_status = false; }
		if (loadVerdana && !f_verdana.loadFromFile(paths[7])) { success = false; s_verdana_status = false; }

		s_fonts_inited = true;

		return success;
	}


	////////////////////////////////////////////////////////////////



	GuiObject::GuiObject()
	{

// check for debug mode for more optimization
#if NODEBUG
#else

		if (!s_fonts_inited)
			throw_error("GuiObject constructor", "failed to initialize fonts - call ke::GuiObject::Init() first", "ERROR");

#endif // NODEBUG

	}


	////////////////////////////////


	GuiObject::~GuiObject()
	{

	}


	////////////////////////////////


	Physics* GuiObject::physics()
	{
		return nullptr;
	}





	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	HoldObjectWithMouse::HoldObjectWithMouse()
		:m_catchDiff(0, 0)
	{
		m_object = nullptr;
		m_holding = false;
	}


	HoldObjectWithMouse::HoldObjectWithMouse(GuiObject* object)
		:m_catchDiff(0, 0)
	{
		m_object = object;
		m_holding = false;
	}


	////////////////////////////////


	void HoldObjectWithMouse::connectToObject(GuiObject* object)
	{
		m_object = object;
		m_holding = false;
	}



	////////////////////////////////////////////////////////////////



	bool HoldObjectWithMouse::update(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event)
	{
		if (!m_object->isActive())
			return false;

		if (event.type == sf::Event::MouseButtonPressed && event.key.code == button && m_object->isInvaded(mousePosition))
		{
			m_holding = true;
			m_catchDiff = sf::Vector2f(m_object->getShapeCenter() - mousePosition);
		}

		if (sf::Mouse::isButtonPressed(button) && m_holding)
			m_object->setPosition(mousePosition + m_catchDiff);
		else
			m_holding = false;

		return m_holding;
	}


	////////////////////////////////


	bool HoldObjectWithMouse::HoldObject(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event)
	{
		return this->update(button, mousePosition, event);
	}



	////////////////////////////////////////////////////////////////



	void HoldObjectWithMouse::setHoldStatus(bool status)
	{
		m_holding = status;
	}





	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	HoldView::HoldView()
		: m_view(nullptr)
		, m_deltaP(0, 0)
		, m_border(0, 0, 0, 0)
	{

	}


	HoldView::HoldView(sf::View* view)
		: m_view(view)
		, m_deltaP(0, 0)
		, m_border(0, 0, 0, 0)
	{

	}


	////////////////////////////////


	HoldView::~HoldView()
	{

	}


	////////////////////////////////////////////////////////////////


	void HoldView::setView(sf::View* view)
	{
		m_view = view;
	}


	////////////////////////////////////////////////////////////////


	void HoldView::setBorders(const sf::Vector2f& left_top, const sf::Vector2f& right_bottom)
	{
		if (m_view->getCenter().x - m_view->getSize().x * 0.5 < left_top.x) m_view->setCenter(left_top.x + m_view->getSize().x * 0.5, m_view->getCenter().y);
		if (m_view->getCenter().y - m_view->getSize().y * 0.5 < left_top.y) m_view->setCenter(m_view->getCenter().x, left_top.y + m_view->getSize().y * 0.5);

		if (m_view->getCenter().x + m_view->getSize().x * 0.5 > right_bottom.x) m_view->setCenter(right_bottom.x - m_view->getSize().x * 0.5, m_view->getCenter().y);
		if (m_view->getCenter().y + m_view->getSize().y * 0.5 > right_bottom.y) m_view->setCenter(m_view->getCenter().x, right_bottom.y - m_view->getSize().y * 0.5);

		m_border = Vector4f(left_top, right_bottom);
	}


	void HoldView::setBorders(const Vector4f& border)
	{
		if (m_view->getCenter().x - m_view->getSize().x * 0.5 < border.x) m_view->setCenter(border.x + m_view->getSize().x * 0.5, m_view->getCenter().y);
		if (m_view->getCenter().y - m_view->getSize().y * 0.5 < border.y) m_view->setCenter(m_view->getCenter().x, border.y + m_view->getSize().y * 0.5);

		if (m_view->getCenter().x + m_view->getSize().x * 0.5 > border.z) m_view->setCenter(border.z - m_view->getSize().x * 0.5, m_view->getCenter().y);
		if (m_view->getCenter().y + m_view->getSize().y * 0.5 > border.v) m_view->setCenter(m_view->getCenter().x, border.y - m_view->getSize().y * 0.5);

		m_border = border;
	}



	////////////////////////////////////////////////////////////////



	bool HoldView::updateClick(const sf::Vector2f& mousePosition, sf::Mouse::Button button, sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == button)
		{
			m_deltaP = m_view->getCenter() - mousePosition;
			m_view->setCenter(-mousePosition - m_deltaP);
			m_deltaP = m_view->getCenter() - mousePosition;

			return true;
		}
		return false;
	}


	bool HoldView::update(const sf::Vector2f& mousePosition, sf::Mouse::Button button)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			m_view->setCenter(-mousePosition - m_deltaP);

			if (m_border != Vector4f(0, 0, 0, 0))
			{
				if (m_view->getCenter().x - m_view->getSize().x * 0.5 < m_border.x) m_view->setCenter(m_border.x + m_view->getSize().x * 0.5, m_view->getCenter().y);
				if (m_view->getCenter().y - m_view->getSize().y * 0.5 < m_border.y) m_view->setCenter(m_view->getCenter().x, m_border.y + m_view->getSize().y * 0.5);

				if (m_view->getCenter().x + m_view->getSize().x * 0.5 > m_border.z) m_view->setCenter(m_border.z - m_view->getSize().x * 0.5, m_view->getCenter().y);
				if (m_view->getCenter().y + m_view->getSize().y * 0.5 > m_border.v) m_view->setCenter(m_view->getCenter().x, m_border.v - m_view->getSize().y * 0.5);
			}

			return true;
		}


		return false;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============               F U N C T I O N S    W I T H    G U I O B J E C T               ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool SmoothColorChange(GuiObject* object, bool tf_argumet, const sf::Color& target_color, const sf::Color& basic_color, Color<float>& float_color, const float intensity, const float dt)
	{ 
		if (tf_argumet)
		{
			if (float_color == Colorf(target_color))
				return false;

			int rs = sgn(target_color.r - basic_color.r);
			int gs = sgn(target_color.g - basic_color.g);
			int bs = sgn(target_color.b - basic_color.b);
			int as = sgn(target_color.a - basic_color.a);

			float_color.r += intensity * dt * rs;
			float_color.g += intensity * dt * gs;
			float_color.b += intensity * dt * bs;
			float_color.a += intensity * dt * as;

			if (rs > 0)
			{
				if (float_color.r > static_cast<float>(target_color.r) || float_color.r < static_cast<float>(basic_color.r))
					float_color.r = static_cast<float>(target_color.r);
			}
			else
			{
				if (float_color.r < static_cast<float>(target_color.r) || float_color.a > static_cast<float>(basic_color.a))
					float_color.r = static_cast<float>(target_color.r);
			}

			if (gs > 0)
			{
				if (float_color.g > static_cast<float>(target_color.g) || float_color.g < static_cast<float>(basic_color.g))
					float_color.g = static_cast<float>(target_color.g);
			}
			else
			{
				if (float_color.g < static_cast<float>(target_color.g) || float_color.a > static_cast<float>(basic_color.a))
					float_color.g = static_cast<float>(target_color.g);
			}

			if (bs > 0)
			{
				if (float_color.b > static_cast<float>(target_color.b) || float_color.b < static_cast<float>(basic_color.b))
					float_color.b = static_cast<float>(target_color.b);
			}
			else
			{
				if (float_color.b < static_cast<float>(target_color.b) || float_color.a > static_cast<float>(basic_color.a))
					float_color.b = static_cast<float>(target_color.b);
			}

			if (as > 0)
			{
				if (float_color.a > static_cast<float>(target_color.a) || float_color.a < static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(target_color.a);
			}
			else
			{
				if (float_color.a < static_cast<float>(target_color.a) || float_color.a > static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(target_color.a);
			}


			if (float_color.r < 0) float_color.r = 0;
			else if (float_color.r > 255) float_color.r = 255;
			if (float_color.g < 0) float_color.g = 0;
			else if (float_color.g > 255) float_color.g = 255;
			if (float_color.b < 0) float_color.b = 0;
			else if (float_color.b > 255) float_color.b = 255;
			if (float_color.a < 0) float_color.a = 0;
			else if (float_color.a > 255) float_color.a = 255;


			object->setFillColor(sf::Color(
				static_cast<sf::Uint8>(float_color.r),
				static_cast<sf::Uint8>(float_color.g),
				static_cast<sf::Uint8>(float_color.b),
				static_cast<sf::Uint8>(float_color.a)));
		}
		else
		{
			if (float_color == Colorf(basic_color))
				return false;

			int rs = sgn(target_color.r - basic_color.r);
			int gs = sgn(target_color.g - basic_color.g);
			int bs = sgn(target_color.b - basic_color.b);
			int as = sgn(target_color.a - basic_color.a);

			float_color.r -= intensity * dt * rs;
			float_color.g -= intensity * dt * gs;
			float_color.b -= intensity * dt * bs;
			float_color.a -= intensity * dt * as;


			if (rs > 0)
			{
				if (float_color.r > static_cast<float>(target_color.r) || float_color.r < static_cast<float>(basic_color.r))
					float_color.r = static_cast<float>(basic_color.r);
			}
			else
			{
				if (float_color.r < static_cast<float>(target_color.r) || float_color.a > static_cast<float>(basic_color.a))
					float_color.r = static_cast<float>(basic_color.r);
			}

			if (gs > 0)
			{
				if (float_color.g > static_cast<float>(target_color.g) || float_color.g < static_cast<float>(basic_color.g))
					float_color.g = static_cast<float>(basic_color.g);
			}
			else
			{
				if (float_color.g < static_cast<float>(target_color.g) || float_color.a > static_cast<float>(basic_color.a))
					float_color.g = static_cast<float>(basic_color.g);
			}

			if (bs > 0)
			{
				if (float_color.b > static_cast<float>(target_color.b) || float_color.b < static_cast<float>(basic_color.b))
					float_color.b = static_cast<float>(basic_color.b);
			}
			else
			{
				if (float_color.b < static_cast<float>(target_color.b) || float_color.a > static_cast<float>(basic_color.a))
					float_color.b = static_cast<float>(basic_color.b);
			}

			if (as > 0)
			{
				if (float_color.a > static_cast<float>(target_color.a) || float_color.a < static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(basic_color.a);
			}
			else
			{
				if (float_color.a < static_cast<float>(target_color.a) || float_color.a > static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(basic_color.a);
			}


			if (float_color.r < 0) float_color.r = 0;
			else if (float_color.r > 255) float_color.r = 255;
			if (float_color.g < 0) float_color.g = 0;
			else if (float_color.g > 255) float_color.g = 255;
			if (float_color.b < 0) float_color.b = 0;
			else if (float_color.b > 255) float_color.b = 255;
			if (float_color.a < 0) float_color.a = 0;
			else if (float_color.a > 255) float_color.a = 255;


			object->setFillColor(sf::Color(
				static_cast<sf::Uint8>(float_color.r),
				static_cast<sf::Uint8>(float_color.g),
				static_cast<sf::Uint8>(float_color.b),
				static_cast<sf::Uint8>(float_color.a)));
		}

		return tf_argumet;
	}



	////////////////////////////////////////////////////////////////



	bool SmoothOutlineColorChange(GuiObject* object, bool tf_argumet, const sf::Color& target_color, const sf::Color& basic_color, Color<float>& float_color, const float intensity, const float dt)
	{
		if (tf_argumet)
		{
			if (float_color == Colorf(target_color))
				return false;

			int rs = sgn(target_color.r - basic_color.r);
			int gs = sgn(target_color.g - basic_color.g);
			int bs = sgn(target_color.b - basic_color.b);
			int as = sgn(target_color.a - basic_color.a);


			float_color.r += intensity * dt * rs;
			float_color.g += intensity * dt * gs;
			float_color.b += intensity * dt * bs;
			float_color.a += intensity * dt * as;

			if (rs > 0)
			{
				if (float_color.r > static_cast<float>(target_color.r) || float_color.r < static_cast<float>(basic_color.r))
					float_color.r = static_cast<float>(target_color.r);
			}
			else
			{
				if (float_color.r < static_cast<float>(target_color.r) || float_color.a > static_cast<float>(basic_color.a))
					float_color.r = static_cast<float>(target_color.r);
			}

			if (gs > 0)
			{
				if (float_color.g > static_cast<float>(target_color.g) || float_color.g < static_cast<float>(basic_color.g))
					float_color.g = static_cast<float>(target_color.g);
			}
			else
			{
				if (float_color.g < static_cast<float>(target_color.g) || float_color.a > static_cast<float>(basic_color.a))
					float_color.g = static_cast<float>(target_color.g);
			}

			if (bs > 0)
			{
				if (float_color.b > static_cast<float>(target_color.b) || float_color.b < static_cast<float>(basic_color.b))
					float_color.b = static_cast<float>(target_color.b);
			}
			else
			{
				if (float_color.b < static_cast<float>(target_color.b) || float_color.a > static_cast<float>(basic_color.a))
					float_color.b = static_cast<float>(target_color.b);
			}

			if (as > 0)
			{
				if (float_color.a > static_cast<float>(target_color.a) || float_color.a < static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(target_color.a);
			}
			else
			{
				if (float_color.a < static_cast<float>(target_color.a) || float_color.a > static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(target_color.a);
			}


			if (float_color.r < 0) float_color.r = 0;
			else if (float_color.r > 255) float_color.r = 255;
			if (float_color.g < 0) float_color.g = 0;
			else if (float_color.g > 255) float_color.g = 255;
			if (float_color.b < 0) float_color.b = 0;
			else if (float_color.b > 255) float_color.b = 255;
			if (float_color.a < 0) float_color.a = 0;
			else if (float_color.a > 255) float_color.a = 255;


			object->setOutlineColor(sf::Color(static_cast<sf::Uint8>(float_color.r),
				static_cast<sf::Uint8>(float_color.g),
				static_cast<sf::Uint8>(float_color.b),
				static_cast<sf::Uint8>(float_color.a)));
		}
		else
		{
			if (float_color == Colorf(basic_color))
				return false;

			int rs = sgn(target_color.r - basic_color.r);
			int gs = sgn(target_color.g - basic_color.g);
			int bs = sgn(target_color.b - basic_color.b);
			int as = sgn(target_color.a - basic_color.a);


			float_color.r -= intensity * dt * rs;
			float_color.g -= intensity * dt * gs;
			float_color.b -= intensity * dt * bs;
			float_color.a -= intensity * dt * as;


			if (rs > 0)
			{
				if (float_color.r > static_cast<float>(target_color.r) || float_color.r < static_cast<float>(basic_color.r))
					float_color.r = static_cast<float>(basic_color.r);
			}
			else
			{
				if (float_color.r < static_cast<float>(target_color.r) || float_color.a > static_cast<float>(basic_color.a))
					float_color.r = static_cast<float>(basic_color.r);
			}

			if (gs > 0)
			{
				if (float_color.g > static_cast<float>(target_color.g) || float_color.g < static_cast<float>(basic_color.g))
					float_color.g = static_cast<float>(basic_color.g);
			}
			else
			{
				if (float_color.g < static_cast<float>(target_color.g) || float_color.a > static_cast<float>(basic_color.a))
					float_color.g = static_cast<float>(basic_color.g);
			}

			if (bs > 0)
			{
				if (float_color.b > static_cast<float>(target_color.b) || float_color.b < static_cast<float>(basic_color.b))
					float_color.b = static_cast<float>(basic_color.b);
			}
			else
			{
				if (float_color.b < static_cast<float>(target_color.b) || float_color.a > static_cast<float>(basic_color.a))
					float_color.b = static_cast<float>(basic_color.b);
			}

			if (as > 0)
			{
				if (float_color.a > static_cast<float>(target_color.a) || float_color.a < static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(basic_color.a);
			}
			else
			{
				if (float_color.a < static_cast<float>(target_color.a) || float_color.a > static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(basic_color.a);
			}


			if (float_color.r < 0) float_color.r = 0;
			else if (float_color.r > 255) float_color.r = 255;
			if (float_color.g < 0) float_color.g = 0;
			else if (float_color.g > 255) float_color.g = 255;
			if (float_color.b < 0) float_color.b = 0;
			else if (float_color.b > 255) float_color.b = 255;
			if (float_color.a < 0) float_color.a = 0;
			else if (float_color.a > 255) float_color.a = 255;


			object->setOutlineColor(sf::Color(static_cast<sf::Uint8>(float_color.r),
				static_cast<sf::Uint8>(float_color.g),
				static_cast<sf::Uint8>(float_color.b),
				static_cast<sf::Uint8>(float_color.a)));
		}

		return tf_argumet;
	}



	////////////////////////////////////////////////////////////////



	bool SmoothTextColorChange(GuiObject* object, bool tf_argumet, const sf::Color& target_color, const sf::Color& basic_color, Color<float>& float_color, const float intensity, const float dt)
	{
		if (tf_argumet)
		{
			if (float_color == Colorf(target_color))
				return false;

			int rs = sgn(target_color.r - basic_color.r);
			int gs = sgn(target_color.g - basic_color.g);
			int bs = sgn(target_color.b - basic_color.b);
			int as = sgn(target_color.a - basic_color.a);


			float_color.r += intensity * dt * rs;
			float_color.g += intensity * dt * gs;
			float_color.b += intensity * dt * bs;
			float_color.a += intensity * dt * as;

			if (rs > 0)
			{
				if (float_color.r > static_cast<float>(target_color.r) || float_color.r < static_cast<float>(basic_color.r))
					float_color.r = static_cast<float>(target_color.r);
			}
			else
			{
				if (float_color.r < static_cast<float>(target_color.r) || float_color.a > static_cast<float>(basic_color.a))
					float_color.r = static_cast<float>(target_color.r);
			}

			if (gs > 0)
			{
				if (float_color.g > static_cast<float>(target_color.g) || float_color.g < static_cast<float>(basic_color.g))
					float_color.g = static_cast<float>(target_color.g);
			}
			else
			{
				if (float_color.g < static_cast<float>(target_color.g) || float_color.a > static_cast<float>(basic_color.a))
					float_color.g = static_cast<float>(target_color.g);
			}

			if (bs > 0)
			{
				if (float_color.b > static_cast<float>(target_color.b) || float_color.b < static_cast<float>(basic_color.b))
					float_color.b = static_cast<float>(target_color.b);
			}
			else
			{
				if (float_color.b < static_cast<float>(target_color.b) || float_color.a > static_cast<float>(basic_color.a))
					float_color.b = static_cast<float>(target_color.b);
			}

			if (as > 0)
			{
				if (float_color.a > static_cast<float>(target_color.a) || float_color.a < static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(target_color.a);
			}
			else
			{
				if (float_color.a < static_cast<float>(target_color.a) || float_color.a > static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(target_color.a);
			}


			if (float_color.r < 0) float_color.r = 0;
			else if (float_color.r > 255) float_color.r = 255;
			if (float_color.g < 0) float_color.g = 0;
			else if (float_color.g > 255) float_color.g = 255;
			if (float_color.b < 0) float_color.b = 0;
			else if (float_color.b > 255) float_color.b = 255;
			if (float_color.a < 0) float_color.a = 0;
			else if (float_color.a > 255) float_color.a = 255;


			object->setTextColor(sf::Color(static_cast<sf::Uint8>(float_color.r),
				static_cast<sf::Uint8>(float_color.g),
				static_cast<sf::Uint8>(float_color.b),
				static_cast<sf::Uint8>(float_color.a)));
		}
		else
		{
			if (float_color == Colorf(basic_color))
				return false;

			int rs = sgn(target_color.r - basic_color.r);
			int gs = sgn(target_color.g - basic_color.g);
			int bs = sgn(target_color.b - basic_color.b);
			int as = sgn(target_color.a - basic_color.a);


			float_color.r -= intensity * dt * rs;
			float_color.g -= intensity * dt * gs;
			float_color.b -= intensity * dt * bs;
			float_color.a -= intensity * dt * as;


			if (rs > 0)
			{
				if (float_color.r > static_cast<float>(target_color.r) || float_color.r < static_cast<float>(basic_color.r))
					float_color.r = static_cast<float>(basic_color.r);
			}
			else
			{
				if (float_color.r < static_cast<float>(target_color.r) || float_color.a > static_cast<float>(basic_color.a))
					float_color.r = static_cast<float>(basic_color.r);
			}

			if (gs > 0)
			{
				if (float_color.g > static_cast<float>(target_color.g) || float_color.g < static_cast<float>(basic_color.g))
					float_color.g = static_cast<float>(basic_color.g);
			}
			else
			{
				if (float_color.g < static_cast<float>(target_color.g) || float_color.a > static_cast<float>(basic_color.a))
					float_color.g = static_cast<float>(basic_color.g);
			}

			if (bs > 0)
			{
				if (float_color.b > static_cast<float>(target_color.b) || float_color.b < static_cast<float>(basic_color.b))
					float_color.b = static_cast<float>(basic_color.b);
			}
			else
			{
				if (float_color.b < static_cast<float>(target_color.b) || float_color.a > static_cast<float>(basic_color.a))
					float_color.b = static_cast<float>(basic_color.b);
			}

			if (as > 0)
			{
				if (float_color.a > static_cast<float>(target_color.a) || float_color.a < static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(basic_color.a);
			}
			else
			{
				if (float_color.a < static_cast<float>(target_color.a) || float_color.a > static_cast<float>(basic_color.a))
					float_color.a = static_cast<float>(basic_color.a);
			}


			if (float_color.r < 0) float_color.r = 0;
			else if (float_color.r > 255) float_color.r = 255;
			if (float_color.g < 0) float_color.g = 0;
			else if (float_color.g > 255) float_color.g = 255;
			if (float_color.b < 0) float_color.b = 0;
			else if (float_color.b > 255) float_color.b = 255;
			if (float_color.a < 0) float_color.a = 0;
			else if (float_color.a > 255) float_color.a = 255;


			object->setTextColor(sf::Color(static_cast<sf::Uint8>(float_color.r),
				static_cast<sf::Uint8>(float_color.g),
				static_cast<sf::Uint8>(float_color.b),
				static_cast<sf::Uint8>(float_color.a)));
		}

		return tf_argumet;
	}



	////////////////////////////////////////////////////////////////////////////////////////////////



	bool SmoothMove(GuiObject* object, const sf::Vector2f& destination, const sf::Vector2f& start_position, const float speed, const float dt)
	{
		if (destination != start_position)
		{
			sf::Vector2f temp;


			const float
				X = destination.x - start_position.x,
				Y = destination.y - start_position.y;

			float angle = (atan(X / Y));

			if (Y > 0) // idk why, but only with Y it works
			{
				temp.x = sin(angle) * speed * dt;
				temp.y = cos(angle) * speed * dt;

				if (Y == 0)
					temp.x = sin(angle) * speed * -dt;
			}
			else
			{
				temp.x = sin(angle) * speed * -dt;
				temp.y = cos(angle) * speed * -dt;

				if (Y == 0)
					temp.x = sin(angle) * speed * dt;
			}

			object->move(temp);


			if (destination.x - start_position.x > 0 && object->getPosition().x > destination.x)
				object->setPosition(destination.x, object->getPosition().y);
			else if (destination.x - start_position.x < 0 && object->getPosition().x < destination.x)
				object->setPosition(destination.x, object->getPosition().y);

			if (destination.y - start_position.y > 0 && object->getPosition().y > destination.y)
				object->setPosition(object->getPosition().x, destination.y);
			else if (destination.y - start_position.y < 0 && object->getPosition().y < destination.y)
				object->setPosition(object->getPosition().x, destination.y);

			return true;

		}
		else return false;
	}



	////////////////////////////////////////////////////////////////////////////////////////////////



	bool SmoothViewMove(sf::View* view, const sf::Vector2f& destination, const sf::Vector2f& start_position, const float speed, const float dt)
	{
		if (view->getCenter() == destination)
			return false;


		sf::Vector2f offsetBuffer;


		//float angle = atan((destination.x - view->getCenter().x) / (destination.y - view->getCenter().y));


		//if ((destination.y - view->getCenter().y) > 0) // idk why, but only with Y it works
		//{
		//	offsetBuffer.x = sin(angle) * speed * dt;
		//	offsetBuffer.y = cos(angle) * speed * dt;

		//	if ((destination.y - view->getCenter().y) == 0)
		//		offsetBuffer.x = sin(angle) * speed * -dt;
		//}
		//else
		//{
		//	offsetBuffer.x = sin(angle) * speed * -dt;
		//	offsetBuffer.y = cos(angle) * speed * -dt;

		//	if ((destination.y - view->getCenter().y) == 0)
		//		offsetBuffer.x = sin(angle) * speed * dt;
		//}


		const float
			X = destination.x - start_position.x,
			Y = destination.y - start_position.y;

		float angle = (atan(-(start_position.y - destination.y) / (start_position.x - destination.x)));
		if ((start_position.x < destination.x)) angle += PI;

		//if (Y > 0) // idk why, but only with Y it works
		//{
		//	offsetBuffer.x = sin(angle) * speed * dt;
		//	offsetBuffer.y = cos(angle) * speed * dt;

		//	if (Y == 0)
		//		offsetBuffer.x = sin(angle) * speed * -dt;
		//}
		//else
		{
			offsetBuffer.x = cos(angle) * speed * -dt;
			offsetBuffer.y = sin(angle) * speed * dt;

			//if (Y == 0)
				//offsetBuffer.x *= -1;
				//offsetBuffer.x = sin(angle) * speed * dt;
		}


		view->move(offsetBuffer);


		if (destination.x - start_position.x > 0 && view->getCenter().x > destination.x)
		{
			view->setCenter(destination.x, view->getCenter().y);
			//return false;
		}
		else if (destination.x - start_position.x < 0 && view->getCenter().x < destination.x)
		{
			view->setCenter(destination.x, view->getCenter().y);
			//return false;
		}

		if (destination.y - start_position.y > 0 && view->getCenter().y > destination.y)
		{
			view->setCenter(view->getCenter().x, destination.y);
			//return false;
		}
		else if (destination.y - start_position.y < 0 && view->getCenter().y < destination.y)
		{
			view->setCenter(view->getCenter().x, destination.y);
			//return false;
		}


		//if (Y != 0 && destination.x == view->getCenter().x)
			//view->setCenter(destination);
		//if (X != 0 && destination.y == view->getCenter().y)
			//view->setCenter(destination);

		return true;
	}



	////////////////////////////////////////////////////////////////////////////////////////////////



	bool SmoothRotation(GuiObject* object, float target_rotation, const float speed, const float dt)
	{
		if (object->getRotation() == target_rotation)
			return false;

		varGuard(target_rotation, 0.f, 360.f);

		object->rotate(speed * dt * sgn(target_rotation - object->getRotation()));

		if (target_rotation - object->getRotation() > 1)
		{
			if (object->getRotation() > target_rotation)
				object->setRotation(target_rotation);
			return false;
		}
		else
		{
			if (object->getRotation() < target_rotation)
				object->setRotation(target_rotation);
			return false;
		}

		return true;
	}



	////////////////////////////////////////////////////////////////////////////////////////////////



	bool SmoothScale(GuiObject* object, const sf::Vector2f& target_scale, const float speed, const float dt)
	{
		if (target_scale == object->getScale())
			return false;

		sf::Vector2f delta(target_scale - object->getScale());

		float angle = atan((delta.x) / (delta.y));

		sf::Vector2f scale_buff(sin(angle) * speed * dt, cos(angle) * speed * dt);

		if (delta.y < 0) // idk why, but only with y it works
		{
			scale_buff.x *= -1;
			scale_buff.y *= -1;
		}

		if (delta.x > 0) // scaling up
			if (object->getScale().x + scale_buff.x > target_scale.x)
				scale_buff.x = target_scale.x - object->getScale().x; else;
		else if (delta.x < 0) // scaling down
			if (object->getScale().x - scale_buff.x < target_scale.x)
				scale_buff.x = -target_scale.x + object->getScale().x; else;

		if (delta.y > 0) // scaling up
			if (object->getScale().y + scale_buff.y > target_scale.y)
				scale_buff.y = target_scale.y - object->getScale().y; else;
		else if (delta.y < 0) // scaling down
			if (object->getScale().y - scale_buff.y < target_scale.y)
				scale_buff.y = -target_scale.y + object->getScale().y; else;

		object->setScale(object->getScale() + scale_buff);

		return true;
	}



	////////////////////////////////////////////////////////////////////////////////////////////////



	bool ViewHolding(sf::View* view, sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event, const sf::Vector2f& top_left_barrier_cord, const sf::Vector2f& bottom_right_barrier_cord)
	{
		static bool holded;
		static sf::Vector2f viev_speed;
		static sf::Vector2f startPos;

		if (sf::Event::MouseButtonPressed && event.key.code == button)
		{
			holded = true;
			startPos = sf::Vector2f(mousePosition);
		}

		if (sf::Mouse::isButtonPressed(button) && holded)
		{
			viev_speed.x = mousePosition.x - startPos.x;
			viev_speed.y = mousePosition.y - startPos.y;
			view->move(-viev_speed.x, -viev_speed.y);
		}
		else holded = false;


		if (view->getCenter().x - view->getSize().x * 0.5 < top_left_barrier_cord.x) view->setCenter(top_left_barrier_cord.x + view->getSize().x * 0.5, view->getCenter().y);
		if (view->getCenter().y - view->getSize().y * 0.5 < top_left_barrier_cord.y) view->setCenter(view->getCenter().x, top_left_barrier_cord.y + view->getSize().y * 0.5);

		if (view->getCenter().x + view->getSize().x * 0.5 > bottom_right_barrier_cord.x) view->setCenter(bottom_right_barrier_cord.x - view->getSize().x * 0.5, view->getCenter().y);
		if (view->getCenter().y + view->getSize().y * 0.5 > bottom_right_barrier_cord.y) view->setCenter(view->getCenter().x, bottom_right_barrier_cord.y - view->getSize().y * 0.5);

		return holded;
	}



	////////////////////////////////////////////////////////////////////////////////////////////////



	bool isOutsideTheView(GuiObject* object, sf::View* view, const sf::Vector2f& shift)
	{
		if (object->getShapeCenter().x + object->getSize().x * object->getScale().x / 2 + shift.x < view->getCenter().x - view->getSize().x * 0.5)
			return true;
		if (object->getShapeCenter().x - object->getSize().x * object->getScale().x / 2 - shift.x > view->getCenter().x + view->getSize().x * 0.5)
			return true;
		if (object->getShapeCenter().y + object->getSize().y * object->getScale().y / 2 + shift.y < view->getCenter().y - view->getSize().y * 0.5)
			return true;
		if (object->getShapeCenter().y - object->getSize().y * object->getScale().y / 2 - shift.y > view->getCenter().y + view->getSize().y * 0.5)
			return true;
		return false;
	}



	////////////////////////////////////////////////////////////////



	bool isQuittingTheView(GuiObject* object, sf::View* view)
	{
		if (object->getShapeCenter().x - object->getSize().x / 2 < view->getCenter().x * object->getScale().x - view->getSize().x * 0.5)
			return true;
		if (object->getShapeCenter().x + object->getSize().x / 2 > view->getCenter().x * object->getScale().x + view->getSize().x * 0.5)
			return true;
		if (object->getShapeCenter().y - object->getSize().y / 2 < view->getCenter().y * object->getScale().y - view->getSize().y * 0.5)
			return true;
		if (object->getShapeCenter().y + object->getSize().y / 2 > view->getCenter().y * object->getScale().y + view->getSize().y * 0.5)
			return true;
		return false;
	}

} // namespace ke