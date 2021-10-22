#include "CurvedButton.hpp"

namespace ke
{


	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	CurvedButton::CurvedButton()
		: m_origin(MIDDLE_MIDDLE)
	{
		
	}


	////////////////////////////////


	CurvedButton::CurvedButton(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* texture,
		const std::wstring& text,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool active)

		: m_origin(origin)
	{
		m_shape.create({ size.x - size.y, size.y }, position, MIDDLE_MIDDLE, texture, text, character_size, text_position, object_color, text_color, outline_thickness, outline_color, 0.f, text_style, text_shift, font, active);

		m_cCicle_L.setRadius(size.y / 2);
		m_cCicle_R.setRadius(size.y / 2);

		m_cCicle_L.setOrigin(m_cCicle_L.getRadius(), m_cCicle_L.getRadius());
		m_cCicle_R.setOrigin(m_cCicle_R.getRadius(), m_cCicle_R.getRadius());

		this->setPosition(position);

		m_cCicle_L.setFillColor(object_color);
		m_cCicle_R.setFillColor(object_color);
		m_cCicle_L.setOutlineColor(outline_color);
		m_cCicle_R.setOutlineColor(outline_color);
		m_cCicle_L.setOutlineThickness(outline_thickness);
		m_cCicle_R.setOutlineThickness(outline_thickness);
	}


	////////////////////////////////


	CurvedButton::CurvedButton(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const std::string& texture_path,
		const std::wstring& text,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool active)

		: m_origin(origin)
	{
		m_shape.create({ size.x - size.y, size.y }, position, MIDDLE_MIDDLE, texture_path, text, character_size, text_position, object_color, text_color, outline_thickness, outline_color, 0.f, text_style, text_shift, font, active);

		m_cCicle_L.setRadius(size.y / 2);
		m_cCicle_R.setRadius(size.y / 2);

		m_cCicle_L.setOrigin(m_cCicle_L.getRadius(), m_cCicle_L.getRadius());
		m_cCicle_R.setOrigin(m_cCicle_R.getRadius(), m_cCicle_R.getRadius());

		this->setPosition(position);

		m_cCicle_L.setFillColor(object_color);
		m_cCicle_R.setFillColor(object_color);
		m_cCicle_L.setOutlineColor(outline_color);
		m_cCicle_R.setOutlineColor(outline_color);
		m_cCicle_L.setOutlineThickness(outline_thickness);
		m_cCicle_R.setOutlineThickness(outline_thickness);
	}


	////////////////////////////////


	CurvedButton::~CurvedButton()
	{
		
	}



	////////////////////////////////////////////////////////////////




	CurvedButton::CurvedButton(CurvedButton& other)
		: m_origin(other.getOrigin())
		, m_shape(*other.getButton())
	{
		m_cCicle_L = *other.getLeftCircle();
		m_cCicle_R = *other.getRightCircle();

		this->setPosition(other.getPosition());
	}


	////////////////////////////////


	CurvedButton& CurvedButton::operator= (CurvedButton& other)
	{
		m_origin = other.getOrigin();

		m_shape = *other.getButton();

		m_cCicle_L = *other.getLeftCircle();
		m_cCicle_R = *other.getRightCircle();

		this->setPosition(other.getPosition());

		return *this;
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* texture,
		const std::wstring& text,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool active)
	{
		m_origin = origin;

		m_shape.create({ size.x - size.y, size.y }, position, MIDDLE_MIDDLE, texture, text, character_size, text_position, object_color, text_color, outline_thickness, outline_color, 0.f, text_style, text_shift, font, active);

		m_cCicle_L.setRadius(size.y / 2);
		m_cCicle_R.setRadius(size.y / 2);

		m_cCicle_L.setOrigin(m_cCicle_L.getRadius(), m_cCicle_L.getRadius());
		m_cCicle_R.setOrigin(m_cCicle_R.getRadius(), m_cCicle_R.getRadius());

		this->setPosition(position);

		m_cCicle_L.setFillColor(object_color);
		m_cCicle_R.setFillColor(object_color);
		m_cCicle_L.setOutlineColor(outline_color);
		m_cCicle_R.setOutlineColor(outline_color);
		m_cCicle_L.setOutlineThickness(outline_thickness);
		m_cCicle_R.setOutlineThickness(outline_thickness);
	}


	////////////////////////////////


	void CurvedButton::create(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const std::string& texture_path,
		const std::wstring& text,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool active)
	{
		m_origin = origin;

		m_shape.create({ size.x - size.y, size.y }, position, MIDDLE_MIDDLE, texture_path, text, character_size, text_position, object_color, text_color, outline_thickness, outline_color, 0.f, text_style, text_shift, font, active);

		m_cCicle_L.setRadius(size.y / 2);
		m_cCicle_R.setRadius(size.y / 2);

		m_cCicle_L.setOrigin(m_cCicle_L.getRadius(), m_cCicle_L.getRadius());
		m_cCicle_R.setOrigin(m_cCicle_R.getRadius(), m_cCicle_R.getRadius());

		this->setPosition(position);

		m_cCicle_L.setFillColor(object_color);
		m_cCicle_R.setFillColor(object_color);
		m_cCicle_L.setOutlineColor(outline_color);
		m_cCicle_R.setOutlineColor(outline_color);
		m_cCicle_L.setOutlineThickness(outline_thickness);
		m_cCicle_R.setOutlineThickness(outline_thickness);
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                       P R I V A T E   F U N C T I O N S                       ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void CurvedButton::shapeUpdate()
	{
		m_cCicle_L.setPosition(m_shape.getShapeCenter().x - m_shape.getSize().x * m_shape.getScale().x / 2, m_shape.getShapeCenter().y);
		m_cCicle_R.setPosition(m_shape.getShapeCenter().x + m_shape.getSize().x * m_shape.getScale().x / 2, m_shape.getShapeCenter().y);
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                           M O D    F U N C T I O N S                          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void CurvedButton::setPosition(const sf::Vector2f& position)
	{
		switch (m_origin)
		{
		case LEFT_TOP:
		{
			m_shape.setPosition(position.x + (m_shape.getSize().y * m_shape.getScale().y + m_shape.getSize().x * m_shape.getScale().x) * 0.5f, position.y + m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case MIDDLE_TOP:
		{
			m_shape.setPosition(position.x, position.y + m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case RIGHT_TOP:
		{
			m_shape.setPosition(position.x - (m_shape.getSize().y * m_shape.getScale().y + m_shape.getSize().x * m_shape.getScale().x) * 0.5f, position.y + m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case LEFT_MIDDLE:
		{
			m_shape.setPosition(position.x + (m_shape.getSize().y * m_shape.getScale().y + m_shape.getSize().x * m_shape.getScale().x) * 0.5f, position.y);
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_shape.setPosition(position);
		}
		break;

		case RIGHT_MIDDLE:
		{
			m_shape.setPosition(position.x - (m_shape.getSize().y * m_shape.getScale().y + m_shape.getSize().x * m_shape.getScale().x) * 0.5f, position.y);
		}
		break;

		case LEFT_BOTTOM:
		{
			m_shape.setPosition(position.x + (m_shape.getSize().y * m_shape.getScale().y + m_shape.getSize().x * m_shape.getScale().x) * 0.5f, position.y - m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_shape.setPosition(position.x, position.y - m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_shape.setPosition(position.x - (m_shape.getSize().y * m_shape.getScale().y + m_shape.getSize().x * m_shape.getScale().x) * 0.5f, position.y - m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		default:
		{
			m_shape.setPosition(position);
			throw_error("CurvedButton::setPosition(..)", "Shape origin is incorrect", "ERROR");
		}
		break;
		}

		this->shapeUpdate();
	}


	void CurvedButton::setPosition(float x, float y)
	{
		this->setPosition(sf::Vector2f(x, y));
	}


	sf::Vector2f CurvedButton::getPosition() const
	{
		switch (m_origin)
		{
		case LEFT_TOP:
		{
			return sf::Vector2f(m_shape.getShapeCenter().x - (m_shape.getSize().x * m_shape.getScale().x + m_shape.getSize().y * m_shape.getScale().y) * 0.5f, m_shape.getShapeCenter().y - m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case MIDDLE_TOP:
		{
			return sf::Vector2f(m_shape.getShapeCenter().x, m_shape.getShapeCenter().y - m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case RIGHT_TOP:
		{
			return sf::Vector2f(m_shape.getShapeCenter().x + (m_shape.getSize().x * m_shape.getScale().x + m_shape.getSize().y * m_shape.getScale().y) * 0.5f, m_shape.getShapeCenter().y - m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case LEFT_MIDDLE:
		{
			return sf::Vector2f(m_shape.getShapeCenter().x - (m_shape.getSize().x * m_shape.getScale().x + m_shape.getSize().y * m_shape.getScale().y) * 0.5f, m_shape.getShapeCenter().y);
		}
		break;
		
		case MIDDLE_MIDDLE:
		{
			return m_shape.getShapeCenter();
		}
		break;

		case RIGHT_MIDDLE:
		{
			return sf::Vector2f(m_shape.getShapeCenter().x + (m_shape.getSize().x * m_shape.getScale().x + m_shape.getSize().y * m_shape.getScale().y) * 0.5f, m_shape.getShapeCenter().y);
		}
		break;

		case LEFT_BOTTOM:
		{
			return sf::Vector2f(m_shape.getShapeCenter().x - (m_shape.getSize().x * m_shape.getScale().x + m_shape.getSize().y * m_shape.getScale().y) * 0.5f, m_shape.getShapeCenter().y + m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case MIDDLE_BOTTOM:
		{
			return sf::Vector2f(m_shape.getShapeCenter().x, m_shape.getShapeCenter().y + m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		case RIGHT_BOTTOM:
		{
			return sf::Vector2f(m_shape.getShapeCenter().x + (m_shape.getSize().x * m_shape.getScale().x + m_shape.getSize().y * m_shape.getScale().y) * 0.5f, m_shape.getShapeCenter().y + m_shape.getSize().y * m_shape.getScale().y * 0.5f);
		}
		break;

		default:
		{
			return m_shape.getShapeCenter();
			throw_error("CurvedButton::setPosition(..)", "Shape origin is incorrect", "ERROR");
		}
		break;
		}
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::move(const sf::Vector2f& offset)
	{
		m_shape.move(offset);
		m_cCicle_L.move(offset);
		m_cCicle_R.move(offset);
	}


	void CurvedButton::move(float offset_x, float offset_y)
	{
		move(sf::Vector2f(offset_x, offset_y));
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setSize(const sf::Vector2f& size)
	{
		m_shape.setSize(sf::Vector2f(size.x - size.y, size.y));
		m_cCicle_L.setRadius(size.y / 2);
		m_cCicle_R.setRadius(size.y / 2);

		m_cCicle_L.setOrigin(m_cCicle_L.getRadius(), m_cCicle_L.getRadius());
		m_cCicle_R.setOrigin(m_cCicle_R.getRadius(), m_cCicle_R.getRadius());

		this->shapeUpdate();
	}


	void CurvedButton::setSize(float size_x, float size_y)
	{
		this->setSize(sf::Vector2f(size_x, size_y));
	}


	sf::Vector2f CurvedButton::getSize() const
	{
		return sf::Vector2f(m_shape.getSize().x + m_shape.getSize().y, m_shape.getSize().y);
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setText(const std::wstring& text)
	{
		m_shape.setText(text);
	}


	std::wstring CurvedButton::getText() const
	{
		return m_shape.getText();
	}



	////////////////////////////////////////////////////////////////



	Button* CurvedButton::getButton()
	{
		return &m_shape;
	}


	sf::CircleShape* CurvedButton::getLeftCircle()
	{
		return &m_cCicle_L;
	}


	sf::CircleShape* CurvedButton::getRightCircle()
	{
		return &m_cCicle_R;
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setOrigin(int origin)
	{
		sf::Vector2f posbuffer(this->getPosition());

		if (origin != m_origin)
		{
			m_origin = origin;
			this->setPosition(posbuffer);
		}
	}


	int CurvedButton::getOrigin() const
	{
		return m_origin;
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setRotation(float angle)
	{
		// not available in CurvedButton
	}


	void CurvedButton::rotate(float angle)
	{
		// not available in CurvedButton
	}


	float CurvedButton::getRotation() const
	{
		// not available in CurvedButton

		return 0.f;
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setPositionByCenter(const sf::Vector2f& postion)
	{
		m_shape.setPosition(postion);

		this->shapeUpdate();
	}


	sf::Vector2f CurvedButton::getShapeCenter() const
	{
		return m_shape.getShapeCenter();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setScale(const sf::Vector2f& factors)
	{
		m_shape.setScale(factors);
		m_cCicle_L.setScale(factors);
		m_cCicle_R.setScale(factors);

		this->shapeUpdate();
	}


	void CurvedButton::setScale(float factor_x, float factor_y)
	{
		m_shape.setScale(factor_x, factor_y);
		m_cCicle_L.setScale(factor_x, factor_y);
		m_cCicle_R.setScale(factor_x, factor_y);

		this->shapeUpdate();
	}


	void CurvedButton::scale(const sf::Vector2f& factors)
	{
		m_shape.scale(factors);
		m_cCicle_L.scale(factors);
		m_cCicle_R.scale(factors);

		this->shapeUpdate();
	}


	sf::Vector2f CurvedButton::getScale() const
	{
		return m_shape.getScale();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setTexture(const sf::Texture* texture)
	{
		m_shape.setTexture(texture);
	}


	void CurvedButton::setTexture(const std::string& texture_path)
	{
		m_shape.setTexture(texture_path);
	}


	const sf::Texture* CurvedButton::getTexture() const
	{
		return m_shape.getTexture();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setFillColor(const sf::Color& color)
	{
		m_shape.setFillColor(color);
		m_cCicle_L.setFillColor(color);
		m_cCicle_R.setFillColor(color);
	}


	const sf::Color& CurvedButton::getFillColor() const
	{
		return m_shape.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setTextColor(const sf::Color& text_color)
	{
		m_shape.setTextColor(text_color);
	}
	

	const sf::Color& CurvedButton::getTextColor() const
	{
		return m_shape.getTextColor();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setOutlineColor(const sf::Color& outline_color)
	{
		m_cCicle_L.setOutlineColor(outline_color);
		m_cCicle_L.setOutlineColor(outline_color);
		m_cCicle_R.setOutlineColor(outline_color);
	}


	const sf::Color& CurvedButton::getOutlineColor() const
	{
		return m_shape.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setOutlineThickness(float outline_thickness)
	{
		m_shape.setOutlineThickness(outline_thickness);
		m_cCicle_L.setOutlineThickness(outline_thickness);
		m_cCicle_R.setOutlineThickness(outline_thickness);
	}


	float CurvedButton::getOutlineThickness() const
	{
		return m_shape.getOutlineThickness();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setTextPosition(int position, const sf::Vector2f& text_shift)
	{
		/**available origins: <br>
		  * RIGHT_TOP     = top right corner <br>
		  * MIDDLE_TOP    = top <br>
		  * LEFT_TOP      = top left corner <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * MIDDLE_MIDDLE = center <br>
		  * LEFT_MIDDLE   = left side <br>
		  * RIGHT_BOTTOM  = bottom right corner <br>
		  * MIDDLE_BOTTOM = bottom <br>
		  * LEFT_BOTTOM   = bottom left corner*/

		m_shape.setTextPosition(position, text_shift);
	}


	int CurvedButton::getTextPosition() const
	{
		/**available origins: <br>
		  * RIGHT_TOP     = top right corner <br>
		  * MIDDLE_TOP    = top <br>
		  * LEFT_TOP      = top left corner <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * MIDDLE_MIDDLE = center <br>
		  * LEFT_MIDDLE   = left side <br>
		  * RIGHT_BOTTOM  = bottom right corner <br>
		  * MIDDLE_BOTTOM = bottom <br>
		  * LEFT_BOTTOM   = bottom left corner*/

		return m_shape.getTextPosition();
	}


	////////////////////////////////


	sf::Vector2f CurvedButton::getTextShift() const
	{
		return m_shape.getTextShift();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setTextStyle(int style)
	{
		m_shape.setTextStyle(style);
	}


	unsigned int CurvedButton::getTextStyle() const
	{
		return m_shape.getTextStyle();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setFont(int font)
	{
		/**  available fonts <br>
		  *  airal <br>
		  *  airal unicode <br>
		  *  calimbri <br>
		  *  camic sans <br>
		  *  courier new <br>
		  *  times now roman <br>
		  *  trebuchet MS <br>
		  *  verdana */

		m_shape.setFont(font);
	}


	int CurvedButton::getFont() const
	{
		/**  available fonts <br>
		  *  airal <br>
		  *  airal unicode <br>
		  *  calimbri <br>
		  *  camic sans <br>
		  *  courier new <br>
		  *  times now roman <br>
		  *  trebuchet MS <br>
		  *  verdana */

		return m_shape.getFont();
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::setCharacterSize(unsigned int char_size)
	{
		m_shape.setCharacterSize(char_size);
	}


	unsigned int CurvedButton::getCharacterSize() const
	{
		return m_shape.getCharacterSize();
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool CurvedButton::isInvaded(const sf::Vector2f& mousePosition) const
	{
		return 
			(m_shape.isInvaded(mousePosition) || 
			(pow(m_shape.getShapeCenter().x - m_shape.getSize().x * m_shape.getScale().x * 0.5f - mousePosition.x, 2) + pow(m_shape.getShapeCenter().y - mousePosition.y, 2) < pow(m_cCicle_L.getRadius() * m_shape.getScale().y, 2)) || 
			(pow(m_shape.getShapeCenter().x + m_shape.getSize().x * m_shape.getScale().x * 0.5f - mousePosition.x, 2) + pow(m_shape.getShapeCenter().y - mousePosition.y, 2) < pow(m_cCicle_R.getRadius() * m_shape.getScale().y, 2)));
	}



	////////////////////////////////



	bool CurvedButton::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return (this->isInvaded(mousePosition) && event.type == sf::Event::MouseButtonPressed && event.key.code == button);
	}



	////////////////////////////////////////////////////////////////



	bool CurvedButton::isActive() const
	{
		return m_shape.isActive();
	}


	void CurvedButton::setActiveStatus(bool status)
	{
		m_shape.setActiveStatus(status);
	}



	////////////////////////////////////////////////////////////////



	float CurvedButton::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		return m_shape.update(mousePosition, event, button, view);
	}



	////////////////////////////////////////////////////////////////



	void CurvedButton::render(sf::RenderWindow* window)
	{
		if (m_shape.isActive())
		{
			window->draw(m_cCicle_L);
			window->draw(m_cCicle_R);
			
			m_shape.render(window);
		}
	}



	////////////////////////////////////////////////////////////////



	bool CurvedButton::created() const
	{
		return m_shape.created();
	}

} // namespace ke