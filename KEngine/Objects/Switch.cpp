#include "Switch.hpp"

namespace ke
{


	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	Switch::Switch()
		: m_signal(false)
		, m_moving(false)
	{

	}


	////////////////////////////////


	Switch::Switch(
		const sf::Vector2f& size,
		float button_radius,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* button_texture,
		const sf::Texture* m_object_texture,
		const sf::Color& button_color,
		const sf::Color& m_object_color,
		float button_outline_thickness,
		const sf::Color& button_outline_color,
		float m_object_outline_thickness,
		const sf::Color& m_object_outline_color,
		bool active)

		: m_signal(false)
		, m_moving(false)
	{
		m_object.create(size, position, origin, m_object_texture, L"", 0, MIDDLE_MIDDLE, m_object_color, sf::Color::Transparent, m_object_outline_thickness, m_object_outline_color, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_texture_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - m_object.getButton()->getSize().x / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, button_texture, active);
		m_color_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - m_object.getButton()->getSize().x / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, L"", 0, MIDDLE_MIDDLE, button_color, sf::Color::Transparent, button_outline_thickness, button_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
	}



	Switch::Switch(
		const sf::Vector2f& size,
		float button_radius,
		const sf::Vector2f& position,
		int origin,
		const std::string& button_texture_path,
		const std::string& m_object_texture_path,
		const sf::Color& button_color,
		const sf::Color& m_object_color,
		float button_outline_thickness,
		const sf::Color& button_outline_color,
		float m_object_outline_thickness,
		const sf::Color& m_object_outline_color,
		bool active)

		: m_signal(false)
		, m_moving(false)
	{
		m_object.create(size, position, origin, m_object_texture_path, L"", 0, MIDDLE_MIDDLE, m_object_color, sf::Color::Transparent, m_object_outline_thickness, m_object_outline_color, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_texture_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - m_object.getButton()->getSize().x / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, button_texture_path, active);
		m_color_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - m_object.getButton()->getSize().x / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, L"", 0, MIDDLE_MIDDLE, button_color, sf::Color::Transparent, button_outline_thickness, button_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
	}


	////////////////////////////////


	Switch::~Switch()
	{
		
	}



	////////////////////////////////////////////////////////////////



	Switch::Switch(Switch& other)
		: m_signal(other.signal())
		, m_moving(other.isMoving())
	{
		m_texture_button = (*other.getTextureButton());
		m_color_button = (*other.getColorButton());
		m_object = (*other.getObject());
	}


	////////////////////////////////


	Switch& Switch::operator= (Switch& other)
	{
		m_texture_button = (*other.getTextureButton());
		m_color_button = (*other.getColorButton());
		m_object = (*other.getObject());

		m_signal = other.signal();
		m_moving = other.isMoving();

		return *this;
	}



	////////////////////////////////////////////////////////////////



	void Switch::create(
		const sf::Vector2f& size,
		float button_radius,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* button_texture,
		const sf::Texture* m_object_texture,
		const sf::Color& button_color,
		const sf::Color& m_object_color,
		float button_outline_thickness,
		const sf::Color& button_outline_color,
		float m_object_outline_thickness,
		const sf::Color& m_object_outline_color,
		bool active)
	{
		m_object.create(size, position, origin, m_object_texture, L"", 0, MIDDLE_MIDDLE, m_object_color, sf::Color::Transparent, m_object_outline_thickness, m_object_outline_color, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_texture_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - m_object.getButton()->getSize().x / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, button_texture, active);
		m_color_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - m_object.getButton()->getSize().x / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, L"", 0, MIDDLE_MIDDLE, button_color, sf::Color::Transparent, button_outline_thickness, button_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);

		m_signal = false;
		m_moving = false;
	}



	void Switch::create(
		const sf::Vector2f& size,
		float button_radius,
		const sf::Vector2f& position,
		int origin,
		const std::string& button_texture_path,
		const std::string& m_object_texture_path,
		const sf::Color& button_color,
		const sf::Color& m_object_color,
		float button_outline_thickness,
		const sf::Color& button_outline_color,
		float m_object_outline_thickness,
		const sf::Color& m_object_outline_color,
		bool active)
	{
		m_object.create(size, position, origin, m_object_texture_path, L"", 0, MIDDLE_MIDDLE, m_object_color, sf::Color::Transparent, m_object_outline_thickness, m_object_outline_color, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);
		m_texture_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - m_object.getButton()->getSize().x / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, button_texture_path, active);
		m_color_button.create(button_radius, sf::Vector2f(m_object.getShapeCenter().x - m_object.getButton()->getSize().x / 2, m_object.getShapeCenter().y), MIDDLE_MIDDLE, L"", 0, MIDDLE_MIDDLE, button_color, sf::Color::Transparent, button_outline_thickness, button_outline_color, 0.f, sf::Text::Regular, sf::Vector2f(0, 0), Arial, active);

		m_signal = false;
		m_moving = false;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                           M O D    F U N C T I O N S                          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void Switch::setPosition(const sf::Vector2f& position)
	{
		m_object.setPosition(position);

		if (m_signal)
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
		else
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
	}


	void Switch::setPosition(float x, float y)
	{
		this->setPosition(sf::Vector2f(x, y));
	}


	sf::Vector2f Switch::getPosition() const
	{
		return m_object.getPosition();
	}



	////////////////////////////////////////////////////////////////



	void Switch::setSize(const sf::Vector2f& size)
	{
		m_object.setSize(size);

		if (m_signal)
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
		else
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
	}


	void Switch::setSize(float size_x, float size_y)
	{
		m_object.setSize(size_x, size_y);

		if (m_signal)
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
		else
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
	}


	sf::Vector2f Switch::getSize() const
	{
		return m_object.getSize();
	}


	////////////////////////////////


	void Switch::setButtonRadius(float radius)
	{
		m_texture_button.setRadius(radius);
		m_color_button.setRadius(radius);

		if (m_signal)
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
		else
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
	}


	float Switch::getButtonRadius() const
	{
		return m_color_button.getRadius();
	}



	////////////////////////////////////////////////////////////////



	void Switch::move(const sf::Vector2f& offset)
	{
		m_object.move(offset);
		m_texture_button.move(offset);
		m_color_button.move(offset);
	}


	void Switch::move(float offset_x, float offset_y)
	{
		m_object.move(offset_x, offset_y);
		m_texture_button.move(offset_x, offset_y);
		m_color_button.move(offset_x, offset_y);
	}



	////////////////////////////////////////////////////////////////



	void Switch::setText(const std::wstring& text)
	{
		// Does nothing - not available in this object
	}


	std::wstring Switch::getText() const
	{
		// Does nothing - not available in this object

		return std::wstring();
	}



	////////////////////////////////////////////////////////////////



	void Switch::setOrigin(int origin)
	{
		m_object.setOrigin(origin);

		if (m_signal)
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
		else
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
	}


	int Switch::getOrigin() const
	{
		return m_object.getOrigin();
	}



	////////////////////////////////////////////////////////////////



	void Switch::setRotation(float angle)
	{
		// Does nothing - not available in this object
	}


	void Switch::rotate(float angle)
	{
		// Does nothing - not available in this object
	}


	float Switch::getRotation() const
	{
		// Does nothing - not available in this object

		return 0.0f;
	}



	////////////////////////////////////////////////////////////////



	void Switch::setScale(const sf::Vector2f& factors)
	{
		m_object.setScale(factors);

		this->setPosition(m_object.getPosition());
	}


	void Switch::setScale(float factor_x, float factor_y)
	{
		m_object.setScale(factor_x, factor_y);

		this->setPosition(m_object.getPosition());
	}


	////////////////////////////////


	void Switch::setButtonScale(const sf::Vector2f& factors)
	{
		m_color_button.setScale(factors);
		m_texture_button.setScale(factors);
	}


	void Switch::setButtonScale(float factor_x, float factor_y)
	{
		m_color_button.setScale(factor_x, factor_y);
		m_texture_button.setScale(factor_x, factor_y);
	}


	////////////////////////////////


	void Switch::scale(const sf::Vector2f& factors)
	{
		m_object.scale(factors);

		this->setPosition(m_object.getPosition());
	}


	void Switch::scaleButton(const sf::Vector2f& factors)
	{
		m_color_button.scale(factors);
		m_texture_button.scale(factors);
	}


	////////////////////////////////


	sf::Vector2f Switch::getScale() const
	{
		return m_object.getScale();
	}


	sf::Vector2f Switch::getButtonScale() const
	{
		return m_texture_button.getScale();
	}



	////////////////////////////////////////////////////////////////



	void Switch::setPositionByCenter(const sf::Vector2f& position)
	{
		m_object.setPositionByCenter(position);

		if (m_signal)
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
		else
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
	}


	sf::Vector2f Switch::getShapeCenter() const
	{
		return m_object.getShapeCenter();
	}


	sf::Vector2f Switch::getButtonCenter() const
	{
		return m_texture_button.getShapeCenter();
	}



	////////////////////////////////////////////////////////////////



	void Switch::setTexture(const sf::Texture* texture)
	{
		m_object.setTexture(texture);
	}


	void Switch::setButtonTexture(const sf::Texture* texture)
	{
		m_texture_button.setTexture(texture);
	}



	void Switch::setTexture(const std::string& texture_path)
	{
		m_object.setTexture(texture_path);
	}


	void Switch::setButtonTexture(const std::string& texture_path)
	{
		m_texture_button.setTexture(texture_path);
	}



	const sf::Texture* Switch::getTexture() const
	{
		return m_object.getTexture();
	}


	const sf::Texture* Switch::getButtonTexture() const
	{
		return m_texture_button.getTexture();
	}



	////////////////////////////////////////////////////////////////



	void Switch::setFillColor(const sf::Color& color)
	{
		m_object.setFillColor(color);
	}


	void Switch::setButtonColor(const sf::Color& color)
	{
		m_color_button.setFillColor(color);
	}



	const sf::Color& Switch::getFillColor() const
	{
		return m_object.getFillColor();
	}


	const sf::Color& Switch::getButtonColor() const
	{
		return m_color_button.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void Switch::setTextColor(const sf::Color& text_color)
	{
		///does nothing, no text in this m_object
	}


	const sf::Color& Switch::getTextColor() const
	{
		///does nothing, no text in this m_object

		return sf::Color::Transparent;
	}



	////////////////////////////////////////////////////////////////



	void Switch::setOutlineColor(const sf::Color& outline_color)
	{
		m_object.setOutlineColor(outline_color);
	}


	void Switch::setOutlineButtonColor(const sf::Color& outline_color)
	{
		m_color_button.setOutlineColor(outline_color);
	}



	const sf::Color& Switch::getOutlineColor() const
	{
		return m_object.getOutlineColor();
	}


	const sf::Color& Switch::getOutlineButtonColor() const
	{
		return m_color_button.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void Switch::setOutlineThickness(float outline_thickness)
	{
		m_object.setOutlineThickness(outline_thickness);
	}


	void Switch::setOutlineButtonThickness(float outline_thickness)
	{
		m_color_button.setOutlineThickness(outline_thickness);
	}



	float Switch::getOutlineThickness() const
	{
		return m_object.getOutlineThickness();
	}


	float Switch::getOutlineButtonThickness() const
	{
		return m_color_button.getOutlineThickness();
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool Switch::isInvaded(const sf::Vector2f& mousePosition) const
	{
		return m_object.isInvaded(mousePosition);
	}



	bool Switch::isButtonInvaded(const sf::Vector2f& mousePosition) const
	{
		return m_texture_button.isInvaded(mousePosition);
	}


	////////////////////////////////


	bool Switch::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_object.isClicked(button, mousePosition, event);
	}


	bool Switch::isButtonClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return m_texture_button.isClicked(button, mousePosition, event);
	}



	////////////////////////////////////////////////////////////////



	bool Switch::isActive() const
	{
		return m_object.isActive();
	}


	void Switch::setActiveStatus(bool status)
	{
		m_color_button.setActiveStatus(status);
		m_texture_button.setActiveStatus(status);
		m_object.setActiveStatus(status);
	}



	////////////////////////////////////////////////////////////////



	Circle* Switch::getColorButton()
	{
		return &m_color_button;
	}


	Circle* Switch::getTextureButton()
	{
		return &m_texture_button;
	}


	CurvedButton* Switch::getObject()
	{
		return &m_object;
	}



	////////////////////////////////////////////////////////////////



	void Switch::setSignal(bool m_signal)
	{
		m_signal = m_signal;

		if (m_signal)
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
		else
		{
			m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
		}
	}


	bool Switch::getSignal() const
	{
		return m_signal;
	}


	bool Switch::signal() const
	{
		return m_signal;
	}


	////////////////////////////////


	bool Switch::isMoving() const
	{
		return m_moving;
	}



	////////////////////////////////////////////////////////////////



	float Switch::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		if (!m_object.isActive())
			return 0.f;

		if (this->isClicked(button, mousePosition, event))
		{
			m_signal ^= 1;

			if (m_signal)
			{
				m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
				m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			}
			else
			{
				m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
				m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
			}

			return 1.f;
		}

		return 0.f;
	}


	////////////////////////////////


	void Switch::SSC_click_update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button)
	{
		if (this->isClicked(button, mousePosition, event) && !m_moving)
		{
			m_moving = true;

			m_signal ^= 1;
		}
	}


	bool Switch::SmoothSignalChange(float speed, float dt)
	{
		if (m_moving)
		{
			if (m_signal)
			{
				m_texture_button.move(speed * dt, 0);
				m_color_button.move(speed * dt, 0);
			}
			else
			{
				m_texture_button.move(-speed * dt, 0);
				m_color_button.move(-speed * dt, 0);
			}

			if (m_texture_button.getPosition().x < m_object.getShapeCenter().x - m_object.getButton()->getSize().x * m_object.getScale().x * 0.5f)
			{
				m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
				m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x - (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));

				m_moving = false;
			}
			else if (m_texture_button.getPosition().x > m_object.getShapeCenter().x + m_object.getButton()->getSize().x * m_object.getScale().x * 0.5f)
			{
				m_texture_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));
				m_color_button.setPosition(sf::Vector2f(m_object.getShapeCenter().x + (m_object.getButton()->getSize().x * m_object.getScale().x) / 2, m_object.getShapeCenter().y));

				m_moving = false;
			}

			return 1;
		}
		else return 0;
	}



	////////////////////////////////////////////////////////////////



	void Switch::render(sf::RenderWindow* window)
	{
		m_object.render(window);

		m_color_button.render(window);
		m_texture_button.render(window);
	}



	////////////////////////////////////////////////////////////////



	bool Switch::created() const
	{
		return m_object.created();
	}

} // namespace ke