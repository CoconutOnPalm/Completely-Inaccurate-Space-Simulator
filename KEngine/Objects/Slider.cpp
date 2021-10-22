#include "Slider.hpp"

namespace ke
{


	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	Slider::Slider()
		: m_holded(false)
		, m_catchDiff(0.f)
		, m_field_height(0.f)
		, m_shift(0.f)
		, m_top_pos(0.F)
		, m_created(false)
	{

	}


	////////////////////////////////


	Slider::Slider(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		float field_height,
		int origin,
		const sf::Texture* slider_texture,
		const sf::Texture* slider_track_texture,
		const sf::Color& slider_color,
		const sf::Color& slider_track_color,
		float slider_outline_thickness,
		const sf::Color& slider_outline_color,
		float slider_track_outline_thickness,
		const sf::Color& slider_track_outline_color,
		bool active)

		: m_holded(false)
		, m_catchDiff(0.f)
		, m_field_height(field_height)
		, m_shift(0.f)
		, m_top_pos(0.F)
		, m_created(true)
	{
		if (origin != RIGHT_TOP || origin != RIGHT_MIDDLE || origin != RIGHT_BOTTOM)
			origin = RIGHT_TOP;

		m_slider.create(sf::Vector2f(size.x, size.y * size.y / field_height), sf::Vector2f(position.x, position.y + (size.y * size.y / field_height) / 2), RIGHT_MIDDLE, slider_texture, L"", 0, MIDDLE_MIDDLE, slider_color, sf::Color::Transparent, slider_outline_thickness, slider_outline_color);
		m_slider_track.create(size, position, origin, slider_track_texture, L"", 0, MIDDLE_MIDDLE, slider_track_color, sf::Color::Transparent, slider_track_outline_thickness, slider_track_outline_color);
	}


	////////////////////////////////


	Slider::Slider(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		float field_height,
		int origin,
		const std::string& slider_texture_path,
		const std::string& slider_track_texture_path,
		const sf::Color& slider_color,
		const sf::Color& slider_track_color,
		float slider_outline_thickness,
		const sf::Color& slider_outline_color,
		float slider_track_outline_thickness,
		const sf::Color& slider_track_outline_color,
		bool active)

		: m_holded(false)
		, m_catchDiff(0.f)
		, m_field_height(field_height)
		, m_shift(0.f)
		, m_top_pos(0.F)
		, m_created(true)
	{
		if (origin != RIGHT_TOP || origin != RIGHT_MIDDLE || origin != RIGHT_BOTTOM)
			origin = RIGHT_TOP;

		m_slider.create(sf::Vector2f(size.x, size.y * size.y / field_height), sf::Vector2f(position.x, position.y + (size.y * size.y / field_height) / 2), RIGHT_MIDDLE, slider_texture_path, L"", 0, MIDDLE_MIDDLE, slider_color, sf::Color::Transparent, slider_outline_thickness, slider_outline_color);
		m_slider_track.create(size, position, origin, slider_track_texture_path, L"", 0, MIDDLE_MIDDLE, slider_track_color, sf::Color::Transparent, slider_track_outline_thickness, slider_track_outline_color);
	}


	////////////////////////////////


	Slider::~Slider()
	{

	}



	////////////////////////////////////////////////////////////////



	Slider::Slider(Slider& other)
		: m_holded(false)
		, m_catchDiff(0.f)
		, m_field_height(other.getFieldHeight())
		, m_shift(other.getShift())
		, m_top_pos(0.F)
		, m_created(true)
	{
		// to achieve lvalue
		sf::Texture temp_1 = *other.getTexture();		
		sf::Texture temp_2 = *other.getTrackTexture();

		m_slider.create(sf::Vector2f(other.getSize().x, other.getSize().y * other.getSize().y / this->m_field_height), sf::Vector2f(other.getPosition().x, other.getPosition().y + other.getShift() + (other.getSize().y * other.getSize().y / this->m_field_height) / 2), RIGHT_MIDDLE, &temp_1, L"", 0, MIDDLE_MIDDLE, other.getFillColor(), sf::Color::Transparent, other.getOutlineThickness(), other.getOutlineColor());
		m_slider_track.create(other.getSize(), other.getPosition(), other.getOrigin(), &temp_2, L"", 0, MIDDLE_MIDDLE, other.getTrackColor(), sf::Color::Transparent, other.getTrackOutlineThickness(), other.getTrackColor());
	}


	////////////////////////////////


	Slider& Slider::operator= (Slider& other)
	{
		m_field_height = other.getFieldHeight();
		m_shift = other.getShift();

		// to achieve lvalue
		sf::Texture temp_1 = *other.getTexture();
		sf::Texture temp_2 = *other.getTrackTexture();

		m_slider.create(sf::Vector2f(other.getSize().x, other.getSize().y * other.getSize().y / this->m_field_height), sf::Vector2f(other.getPosition().x, other.getPosition().y + other.getShift() + (other.getSize().y * other.getSize().y / this->m_field_height) / 2), RIGHT_MIDDLE, &temp_1, L"", 0, MIDDLE_MIDDLE, other.getFillColor(), sf::Color::Transparent, other.getOutlineThickness(), other.getOutlineColor());
		m_slider_track.create(other.getSize(), other.getPosition(), other.getOrigin(), &temp_2, L"", 0, MIDDLE_MIDDLE, other.getTrackColor(), sf::Color::Transparent, other.getTrackOutlineThickness(), other.getTrackColor());

		m_created = true;

		return *this;
	}



	////////////////////////////////////////////////////////////////



	void Slider::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		float field_height,
		int origin,
		const sf::Texture* slider_texture,
		const sf::Texture* slider_track_texture,
		const sf::Color& slider_color,
		const sf::Color& slider_track_color,
		float slider_outline_thickness,
		const sf::Color& slider_outline_color,
		float slider_track_outline_thickness,
		const sf::Color& slider_track_outline_color,
		bool active)
	{
		if (origin != RIGHT_TOP && origin != RIGHT_MIDDLE && origin != RIGHT_BOTTOM)
			origin = RIGHT_TOP;


		m_slider.create(sf::Vector2f(size.x, size.y * size.y / field_height), sf::Vector2f(position.x, position.y + (size.y * size.y / field_height) / 2), RIGHT_MIDDLE, slider_texture, L"", 0, MIDDLE_MIDDLE, slider_color, sf::Color::Transparent, slider_outline_thickness, slider_outline_color);
		m_slider_track.create(size, position, origin, slider_track_texture, L"", 0, MIDDLE_MIDDLE, slider_track_color, sf::Color::Transparent, slider_track_outline_thickness, slider_track_outline_color);

		m_field_height = field_height;

		m_created = true;
	}


	////////////////////////////////


	void Slider::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		float field_height,
		int origin,
		const std::string& slider_texture_path,
		const std::string& slider_track_texture_path,
		const sf::Color& slider_color,
		const sf::Color& slider_track_color,
		float slider_outline_thickness,
		const sf::Color& slider_outline_color,
		float slider_track_outline_thickness,
		const sf::Color& slider_track_outline_color,
		bool active)
	{
		if (origin != RIGHT_TOP && origin != RIGHT_MIDDLE && origin != RIGHT_BOTTOM)
			origin = RIGHT_TOP;

		m_slider.create(sf::Vector2f(size.x, size.y * size.y / field_height), sf::Vector2f(position.x, position.y + (size.y * size.y / field_height) / 2), RIGHT_MIDDLE, slider_texture_path, L"", 0, MIDDLE_MIDDLE, slider_color, sf::Color::Transparent, slider_outline_thickness, slider_outline_color);
		m_slider_track.create(size, position, origin, slider_track_texture_path, L"", 0, MIDDLE_MIDDLE, slider_track_color, sf::Color::Transparent, slider_track_outline_thickness, slider_track_outline_color);

		m_field_height = field_height;

		m_created = true;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                           M O D    F U N C T I O N S                          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void Slider::setPosition(const sf::Vector2f& position)
	{
		m_slider_track.setPosition(position);

		switch (m_slider.getOrigin())
		{
		case RIGHT_TOP:
		{
			m_slider.setPosition(sf::Vector2f(position.x, position.y + (m_slider_track.getSize().y * m_slider_track.getScale().y * m_slider_track.getSize().y * m_slider_track.getScale().y / m_field_height) / 2 + m_shift));
		}
		break;

		case RIGHT_MIDDLE:
		{
			m_slider.setPosition(sf::Vector2f(position.x, position.y - m_slider_track.getSize().y * m_slider_track.getScale().y / 2 + (m_slider_track.getSize().y * m_slider_track.getScale().y * m_slider_track.getSize().y * m_slider_track.getScale().y / m_field_height) / 2 + m_shift));
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_slider.setPosition(sf::Vector2f(position.x, position.y + m_slider_track.getSize().y * m_slider_track.getScale().y / 2 - (m_slider_track.getSize().y * m_slider_track.getScale().y * m_slider_track.getSize().y * m_slider_track.getScale().y / m_field_height) / 2 + m_shift));
		}
		break;

		default:
		{
			m_slider.setPosition(sf::Vector2f(position.x, position.y + (m_slider_track.getSize().y * m_slider_track.getScale().y * m_slider_track.getSize().y * m_slider_track.getScale().y / m_field_height) / 2 + m_shift));
		}
		break;
		}
	}


	void Slider::setPosition(float x, float y)
	{
		this->setPosition(sf::Vector2f(x, y));
	}


	sf::Vector2f Slider::getPosition() const
	{
		return m_slider.getPosition();
	}


	sf::Vector2f Slider::getSliderTrackPosition() const
	{
		return m_slider_track.getPosition();
	}



	////////////////////////////////////////////////////////////////



	void Slider::setSize(const sf::Vector2f& size)
	{
		m_slider.setSize(sf::Vector2f(size.x, size.y * size.y / m_field_height));
		m_slider_track.setSize(size);

		this->setPosition(m_slider_track.getPosition());
		this->updateSize();
	}


	void Slider::setSize(float size_x, float size_y)
	{
		m_slider.setSize(sf::Vector2f(size_x, size_y * size_y / m_field_height));
		m_slider_track.setSize(size_x, size_y);

		this->setPosition(m_slider_track.getPosition());
		this->updateSize();
	}


	sf::Vector2f Slider::getSize() const
	{
		return m_slider_track.getSize();
	}


	sf::Vector2f Slider::getSliderSize() const
	{
		return m_slider.getSize();
	}



	////////////////////////////////////////////////////////////////



	void Slider::move(const sf::Vector2f& offset)
	{
		m_slider.move(offset);
		m_slider_track.move(offset);
	}


	void Slider::move(float offset_x, float offset_y)
	{
		m_slider.move(offset_x, offset_y);
		m_slider_track.move(offset_x, offset_y);
	}


	void Slider::setScale(const sf::Vector2f& factors)
	{
		m_slider.setScale(factors);
		m_slider_track.setScale(factors);

		this->updateSize();
	}


	void Slider::setScale(float factor_x, float factor_y)
	{
		m_slider.setScale(factor_x, factor_y);
		m_slider_track.setScale(factor_x, factor_y);

		this->updateSize();
	}


	void Slider::scale(const sf::Vector2f& factors)
	{
		m_slider.scale(factors);
		m_slider_track.scale(factors);

		this->updateSize();
	}


	sf::Vector2f Slider::getScale() const
	{
		return m_slider_track.getScale();
	}



	////////////////////////////////////////////////////////////////



	void Slider::setText(const std::wstring& text)
	{
		// not available in this object
	}


	std::wstring Slider::getText() const
	{
		// not available in this object

		return std::wstring();
	}



	////////////////////////////////////////////////////////////////



	void Slider::setOrigin(int origin)
	{
		///changes origin of the KEngine Slider's track
		/**available origins: <br>
		  * RIGHT_TOP     = top right corner <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * RIGHT_BOTTOM  = bottom right corner */

		if (origin != RIGHT_TOP && origin != RIGHT_MIDDLE && origin != RIGHT_BOTTOM)
		{
			origin = RIGHT_TOP;
			throw_error("Slider::setOrigin(..)", "Given object origin is incorrect", "WARNING");
		}

		m_slider_track.setOrigin(origin);

		this->setPosition(m_slider_track.getPosition());
	}


	int Slider::getOrigin() const
	{
		///returns origin of the KEngine Slider's track
		/**available origins: <br>
		  * RIGHT_TOP     = top right corner <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * RIGHT_BOTTOM  = bottom right corner */

		return m_slider_track.getOrigin();
	}



	////////////////////////////////////////////////////////////////



	void Slider::setRotation(float angle)
	{
		// not available in this object
	}


	void Slider::rotate(float angle)
	{
		// not available in this object
	}


	float Slider::getRotation() const
	{
		// not available in this object

		return 0.0f;
	}



	////////////////////////////////////////////////////////////////



	void Slider::setPositionByCenter(const sf::Vector2f& postion)
	{
		this->setPosition(postion.x + m_slider_track.getPosition().x - m_slider_track.getShapeCenter().x, postion.y + m_slider_track.getPosition().y - m_slider_track.getShapeCenter().y);
	}


	sf::Vector2f Slider::getShapeCenter() const
	{
		return m_slider.getShapeCenter();
	}


	sf::Vector2f Slider::getTrackCenter() const
	{
		return m_slider_track.getShapeCenter();
	}



	////////////////////////////////////////////////////////////////



	void Slider::setTexture(const sf::Texture* texture)
	{
		m_slider.setTexture(texture);
	}


	void Slider::setTrackTexture(const sf::Texture* texture)
	{
		m_slider_track.setTexture(texture);
	}


	void Slider::setTexture(const std::string& filename)
	{
		m_slider.setTexture(filename);
	}


	void Slider::setTrackTexture(const std::string& filename)
	{
		m_slider_track.setTexture(filename);
	}


	const sf::Texture* Slider::getTexture() const
	{
		return m_slider.getTexture();
	}


	const sf::Texture* Slider::getTrackTexture() const
	{
		return m_slider_track.getTexture();
	}

	

	////////////////////////////////////////////////////////////////



	void Slider::setFillColor(const sf::Color& color)
	{
		m_slider.setFillColor(color);
	}


	void Slider::setTrackColor(const sf::Color& color)
	{
		m_slider_track.setFillColor(color);
	}


	const sf::Color& Slider::getFillColor() const
	{
		return m_slider.getFillColor();
	}


	const sf::Color& Slider::getTrackColor() const
	{
		return m_slider_track.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void Slider::setTextColor(const sf::Color& text_color)
	{
		///does nothing, not text in this object
	}

	const sf::Color& Slider::getTextColor() const
	{
		///does nothing, no text in this object

		return sf::Color::Transparent;
	}



	////////////////////////////////////////////////////////////////



	void Slider::setOutlineColor(const sf::Color& outline_color)
	{
		m_slider.setOutlineColor(outline_color);
	}


	void Slider::setTrackOutlineColor(const sf::Color& outline_color)
	{
		m_slider_track.setOutlineColor(outline_color);
	}


	const sf::Color& Slider::getOutlineColor() const
	{
		return m_slider.getOutlineColor();
	}


	const sf::Color& Slider::getTrackOutlineColor() const
	{
		return m_slider_track.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void Slider::setOutlineThickness(float outline_thickness)
	{
		m_slider.setOutlineThickness(outline_thickness);
	}


	void Slider::setTrackOutlineThickness(float outline_thickness)
	{
		m_slider_track.setOutlineThickness(outline_thickness);
	}


	float Slider::getOutlineThickness() const
	{
		return m_slider.getOutlineThickness();
	}


	float Slider::getTrackOutlineThickness() const
	{
		return m_slider_track.getOutlineThickness();
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool Slider::isInvaded(const sf::Vector2f& mousePoaition) const
	{
		return m_slider.isInvaded(mousePoaition);
	}


	bool Slider::isTrackInvaded(const sf::Vector2f& mousePosition) const
	{
		return m_slider_track.isInvaded(mousePosition);
	}



	////////////////////////////////////////////////////////////////



	bool Slider::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_slider.isClicked(button, mousePosition, event);
	}


	bool Slider::isTrackClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_slider_track.isClicked(button, mousePosition, event);
	}



	////////////////////////////////////////////////////////////////



	bool Slider::isActive() const
	{
		return m_slider.isActive();
	}


	void Slider::setActiveStatus(bool status)
	{
		m_slider.setActiveStatus(status);
		m_slider_track.setActiveStatus(status);
	}



	////////////////////////////////////////////////////////////////



	void Slider::setHoldStatus(bool status)
	{
		m_holded = status;
	}


	bool Slider::isHolded() const
	{
		return m_holded;
	}



	////////////////////////////////////////////////////////////////



	Button* Slider::getSlider()
	{
		return &m_slider;
	}


	Button* Slider::getSliderTrack()
	{
		return &m_slider_track;
	}



	////////////////////////////////////////////////////////////////



	void Slider::setFieldHeight(float field_height)
	{
		m_field_height = field_height;
	}


	float Slider::getFieldHeight() const
	{
		return m_field_height;
	}



	////////////////////////////////////////////////////////////////



	float Slider::getShift() const
	{
		return m_shift;
	}



	////////////////////////////////////////////////////////////////



	void Slider::setViewPositionShift(float top_position, sf::View* view)
	{
		m_top_pos = top_position;

		if (view)
		{
			view->setCenter(view->getCenter().x, m_shift * ((m_field_height) - view->getSize().y) / ((m_slider_track.getSize().y * m_slider_track.getScale().y - m_slider.getSize().y * m_slider.getScale().y)) + view->getSize().y * 0.5);

			if (m_top_pos)
				view->setCenter(view->getCenter().x, view->getCenter().y + m_top_pos);
		}
	}


	float Slider::getViewPositionShift() const
	{
		return m_top_pos;
	}



	////////////////////////////////////////////////////////////////



	void Slider::updateSize()
	{
		m_slider.setSize(sf::Vector2f(m_slider.getSize().x, m_slider_track.getSize().y * m_slider_track.getSize().y * m_slider_track.getScale().y / m_field_height));
	}



	////////////////////////////////



	void Slider::updateSliderPosition(sf::View* view)
	{
		float s_size_buff = m_slider.getSize().y * m_slider.getScale().y;				// slider size (with scale)
		float st_size_buff = m_slider_track.getSize().y * m_slider_track.getScale().y;	// slider track size (with scale)
		float st_top_pos_buff = m_slider_track.getShapeCenter().y - st_size_buff * 0.5f; // slider track top

		if (view)
			m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5f + ((view->getCenter().y - m_top_pos) - view->getSize().y * 0.5f) * (st_size_buff - s_size_buff) / ((m_field_height - view->getSize().y))));

		if (m_slider.getPosition().y < st_top_pos_buff + s_size_buff * 0.5)
			m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5f));
		if (m_slider.getPosition().y > st_top_pos_buff + st_size_buff - s_size_buff * 0.5f)
			m_slider.setPosition(sf::Vector2f(m_slider_track.getPosition().x, st_top_pos_buff + st_size_buff - s_size_buff * 0.5));
	}

	void Slider::updateSliderPosition(float offset)
	{
		float s_size_buff = m_slider.getSize().y * m_slider.getScale().y;				// slider size (with scale)
		float st_size_buff = m_slider_track.getSize().y * m_slider_track.getScale().y;	// slider track size (with scale)
		float st_top_pos_buff = m_slider_track.getShapeCenter().y - st_size_buff * 0.5f; // slider track top

		//m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5f + ((view->getCenter().y - m_top_pos) - view->getSize().y * 0.5f) * (st_size_buff - s_size_buff) / ((m_field_height - view->getSize().y))));
		//m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5f + offset * (st_size_buff - s_size_buff) / m_field_height));
		m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, (st_size_buff - s_size_buff) * offset / (m_field_height * (-s_size_buff * 0.5) * (-st_top_pos_buff))));

		if (m_slider.getPosition().y < st_top_pos_buff + s_size_buff * 0.5)
			m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5f));
		if (m_slider.getPosition().y > st_top_pos_buff + st_size_buff - s_size_buff * 0.5f)
			m_slider.setPosition(sf::Vector2f(m_slider_track.getPosition().x, st_top_pos_buff + st_size_buff - s_size_buff * 0.5));
	}



	////////////////////////////////////////////////////////////////



	float Slider::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		if (!m_slider.isActive() || !m_slider_track.isActive())
			return 0.f;

		// updates slider size
		this->updateSize();

		// to avoid additional calculations
		float s_size_buff = m_slider.getSize().y * m_slider.getScale().y;				// slider size (with scale)
		float st_size_buff = m_slider_track.getSize().y * m_slider_track.getScale().y;	// slider track size (with scale)
		float st_top_pos_buff = m_slider_track.getShapeCenter().y - st_size_buff * 0.5f; // slider track top


		// position guard
		if (view)
			m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5f + ((view->getCenter().y - m_top_pos) - view->getSize().y * 0.5f) * (st_size_buff - s_size_buff) / ((m_field_height - view->getSize().y))));
		if (m_slider.getPosition().y < st_top_pos_buff + s_size_buff * 0.5) 
			m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5f));
		if (m_slider.getPosition().y > st_top_pos_buff + st_size_buff - s_size_buff * 0.5f)
			m_slider.setPosition(sf::Vector2f(m_slider_track.getPosition().x, st_top_pos_buff + st_size_buff - s_size_buff * 0.5));


		// click check
		if (m_slider.isClicked(button, mousePosition, event))
		{
			m_holded = true;
			m_catchDiff = mousePosition.y - m_slider.getPosition().y;
		}
		else if (!sf::Mouse::isButtonPressed(button))
		{
			m_holded = false;
		}


		if (sf::Mouse::isButtonPressed(button) && m_holded && s_size_buff < st_size_buff)
		{
			// set slider position 
			m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, mousePosition.y - m_catchDiff));


			// position guard
			if (m_slider.getPosition().y < st_top_pos_buff + s_size_buff * 0.5)
				m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5));
			if (m_slider.getPosition().y > st_top_pos_buff + st_size_buff - s_size_buff * 0.5f)
				m_slider.setPosition(sf::Vector2f(m_slider_track.getPosition().x, st_top_pos_buff + st_size_buff - s_size_buff * 0.5));

			// slider position - default position
			m_shift = m_slider.getPosition().y - (st_top_pos_buff + s_size_buff * 0.5);

			// move view if it's not nullptr
			if (view)
			{
				view->setCenter(view->getCenter().x, m_shift * ((m_field_height) - view->getSize().y) / ((st_size_buff - s_size_buff)) + view->getSize().y * 0.5);

				if (m_top_pos)
					view->setCenter(view->getCenter().x, view->getCenter().y + m_top_pos);
			}
		}

		// when you click on track without holding slider
		else if (isTrackInvaded(mousePosition) && m_slider_track.isClicked(button, mousePosition, event) && !m_holded && s_size_buff < st_size_buff)
		{
			// set slider position
			m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, mousePosition.y - m_catchDiff));

			// slider position - default position
			m_shift = m_slider.getPosition().y - (st_top_pos_buff + s_size_buff * 0.5);

			// position guard
			if (m_slider.getPosition().y < st_top_pos_buff + s_size_buff * 0.5)
				m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x, st_top_pos_buff + s_size_buff * 0.5));
			if (m_slider.getPosition().y > st_top_pos_buff + st_size_buff - s_size_buff * 0.5)
				m_slider.setPosition(sf::Vector2f(m_slider_track.getPosition().x, st_top_pos_buff + st_size_buff - s_size_buff * 0.5));

			// move view if it's not nullptr
			if (view)
			{
				view->setCenter(sf::Vector2f(view->getCenter().x, m_shift * ((m_field_height)-view->getSize().y) / ((st_size_buff - s_size_buff)) + view->getSize().y * 0.5));

				if (view->getCenter().y < view->getSize().y * 0.5) view->setCenter(view->getCenter().x, view->getSize().y * 0.5);
				if (view->getCenter().y > m_field_height - view->getSize().y * 0.5) view->setCenter(view->getCenter().x, m_field_height - view->getSize().y * 0.5);

				if (m_top_pos)
					view->setCenter(view->getCenter().x, view->getCenter().y + m_top_pos);
			}

			// set slider as holded
			m_holded = true;
		}

		// return y posiiton for objects that moves without using view
		return m_top_pos + m_shift * ((m_field_height)) / ((st_size_buff - s_size_buff));
	}



	////////////////////////////////////////////////////////////////



	void Slider::render(sf::RenderWindow* window)
	{
		if (m_slider.isActive())
			if (m_slider.getSize().y < m_slider_track.getSize().y)
				m_slider.render(window);
		if (m_slider_track.isActive())
			m_slider_track.render(window);
	}



	////////////////////////////////////////////////////////////////



	bool Slider::created() const
	{
		return m_created;
	}

} // namespace ke