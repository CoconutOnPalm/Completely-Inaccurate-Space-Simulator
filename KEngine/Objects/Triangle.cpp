#include "Triangle.hpp"

namespace ke
{

	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//


	Triangle::Triangle()
		: m_origin(MIDDLE_MIDDLE)
		, a(0)
		, m_texture_path(Settings::EmptyTexturePath())
		, m_texture_set(false)
		, m_shapeCenter(0, 0)
		, m_physics(nullptr)
		, m_text_shift(0, 0)
		, m_text_position(MIDDLE_MIDDLE)
		, m_text_font(Arial)
		, m_active(false)
		, m_created(false)
	{

	}


	////////////////////////////////


	Triangle::Triangle(
		float side_length,
		const sf::Vector2f& position,
		int origin,
		const std::wstring& text,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		float rotation,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool active)

		: m_texture_path(Settings::EmptyTexturePath())
		, m_texture_set(false)
		, m_origin(origin)
		, m_text_position(text_position)
		, m_text_shift(text_shift)
		, m_physics(nullptr)
		, m_active(active)
	{
		m_shape.setRadius(side_length * sqrt_3 / 3);
		m_shape.setPointCount(3);
		m_shape.setPosition(position);
		a = side_length;
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setFillColor(object_color);
		m_shape.setOutlineColor(outline_color);
		m_shape.setOutlineThickness(outline_thickness);


		m_text.setCharacterSize(character_size);

		this->fontUpdate(font);

		m_text.setStyle(text_style);
		m_text.setString(text);
		m_text.rotate(rotation);

		this->fullTextUpdate();

		m_text.setFillColor(text_color);
	}


	////////////////////////////////


	Triangle::Triangle(
		float side_length,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* texture,
		float rotation,
		bool active)

		: m_origin(origin)
		, m_text_position(MIDDLE_MIDDLE)
		, m_text_shift(0, 0)
		, m_physics(nullptr)
		, m_active(active)
		, m_created(true)
	{
		if (texture)
		{
			m_texture_path = Settings::UnknownTexturePathName();
			m_texture = *texture;
			m_texture_set = true;
		}
		else
		{
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}

		m_shape.setRadius(side_length * sqrt_3 / 3);
		m_shape.setPointCount(3);
		m_shape.setPosition(position);
		a = side_length;
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setTexture(&this->m_texture);
		m_shape.setFillColor(Settings::DefaultTextureColor());
	}


	////////////////////////////////


	Triangle::Triangle(
		float side_length,
		const sf::Vector2f& position,
		int origin,
		const std::string& filename,
		float rotation,
		bool active)

		: m_texture_path(filename)
		, m_origin(origin)
		, m_text_position(MIDDLE_MIDDLE)
		, m_text_shift(0, 0)
		, m_physics(nullptr)
		, m_active(active)
		, m_created(true)
	{
		m_texture_set = true;

		if (!m_texture.loadFromFile(m_texture_path))
		{
			throw_error("Rectangle::Rectange(...)", "could not load texture from the given path", "ERROR");
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}

		m_shape.setRadius(side_length * sqrt_3 / 3);
		m_shape.setPointCount(3);
		m_shape.setPosition(position);
		a = side_length;
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setTexture(&m_texture);
		m_shape.setFillColor(Settings::DefaultTextureColor());
	}


	////////////////////////////////


	Triangle::~Triangle()
	{

	}



	////////////////////////////////////////////////////////////////



	Triangle::Triangle(Triangle& other)
		: m_origin(other.getOrigin())
		, m_text_position(other.getTextPosition())
		, m_text_shift(other.getTextShift())
		, m_active(other.isActive())
		, m_created(true)
	{
		// checking if texture exists
		if (other.isTextureSet())
		{
			m_texture_path = other.getTexturePath();
			m_texture = *other.getTexture();
			m_texture_set = true;
			m_shape.setTexture(&m_texture);
		}
		else
		{
			m_texture_path = Settings::EmptyTexturePath();
			m_texture_set = false;
		}
		

		m_shape.setRadius(other.getRadius());
		m_shape.setPointCount(3);
		m_shape.setPosition(other.getPosition());
		a = other.getSideSize();
		m_shape.setRotation(other.getRotation());

		this->fullShapeUpdate();

		m_shape.setFillColor(other.getFillColor());
		m_shape.setOutlineColor(other.getOutlineColor());
		m_shape.setOutlineThickness(other.getOutlineThickness());


		m_text.setCharacterSize(other.getCharacterSize());

		this->fontUpdate(other.getFont());

		m_text.setStyle(other.getTextStyle());
		m_text.setString(other.getText());
		m_text.setRotation(other.getRotation());

		this->fullTextUpdate();

		m_text.setFillColor(other.getTextColor());

		
		if (other.physics()) // when physics exists
		{
			m_physics->setTarget(this);

			for (auto& i : *other.physics()->getForceList())
				m_physics->addForce(i.first, i.second);

			m_physics->setSpeed(other.physics()->getSpeed());
			m_physics->setMass(other.physics()->getMass());
			m_physics->setFriction(other.physics()->getFriction());
		}
	}



	////////////////////////////////////////////////////////////////



	Triangle& Triangle::operator= (Triangle& other)
	{
		// checking if texture exists
		if (other.isTextureSet())
		{
			m_texture_path = other.getTexturePath();
			m_texture = *other.getTexture();
			m_texture_set = true;
			m_shape.setTexture(&m_texture);
		}
		else
		{
			m_texture_path = Settings::EmptyTexturePath();
			m_texture_set = false;
		}


		m_origin = other.getOrigin();
		m_text_position = other.getTextPosition();
		m_text_shift = other.getTextShift();

		m_shape.setRadius(other.getRadius());
		m_shape.setPointCount(3);
		m_shape.setPosition(other.getPosition());
		a = other.getSideSize();
		m_shape.setRotation(other.getRotation());

		this->fullShapeUpdate();

		m_shape.setFillColor(other.getFillColor());
		m_shape.setOutlineColor(other.getOutlineColor());
		m_shape.setOutlineThickness(other.getOutlineThickness());


		m_text.setCharacterSize(other.getCharacterSize());

		this->fontUpdate(other.getFont());

		m_text.setStyle(other.getTextStyle());
		m_text.setString(other.getText());
		m_text.setRotation(other.getRotation());

		this->fullTextUpdate();

		m_text.setFillColor(other.getTextColor());


		if (other.physics()) // when physics exists
		{
			m_physics->setTarget(this);

			for (auto& i : *other.physics()->getForceList())
				m_physics->addForce(i.first, i.second);

			m_physics->setSpeed(other.physics()->getSpeed());
			m_physics->setMass(other.physics()->getMass());
			m_physics->setFriction(other.physics()->getFriction());
		}

		m_active = other.isActive();
		m_created = true;

		return *this;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::create(float side_length,
		const sf::Vector2f& position,
		int origin,
		const std::wstring& text,
		unsigned int character_size,
		int text_position,
		const sf::Color& object_color,
		const sf::Color& text_color,
		float outline_thickness,
		const sf::Color& outline_color,
		float rotation,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool active)
	{
		m_texture_path = Settings::EmptyTexturePath();
		m_texture_set = false;

		m_origin = origin;
		m_text_position = text_position;
		m_text_shift = text_shift;


		m_shape.setRadius(side_length * sqrt_3 / 3);
		m_shape.setPointCount(3);
		m_shape.setPosition(position);
		a = side_length;
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setFillColor(object_color);
		m_shape.setOutlineColor(outline_color);
		m_shape.setOutlineThickness(outline_thickness);


		m_text.setCharacterSize(character_size);

		this->fontUpdate(font);

		m_text.setStyle(text_style);
		m_text.setString(text);
		m_text.setRotation(rotation);

		this->fullTextUpdate();

		m_text.setFillColor(text_color);

		m_active = active;
		m_created = true;
	}


	////////////////////////////////


	void Triangle::create(float side_length,
		const sf::Vector2f& position,
		int origin,
		const sf::Texture* texture,
		float rotation,
		bool active)
	{
		// checking if texture exists
		if (texture)
		{
			m_texture_path = Settings::UnknownTexturePathName();
			m_texture = *texture;
			m_texture_set = true;
		}
		else
		{
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}

		m_origin = origin;
		m_text_position = MIDDLE_MIDDLE;
		m_text_shift = sf::Vector2f(0, 0);


		m_shape.setRadius(side_length * sqrt_3 / 3);
		m_shape.setPointCount(3);
		m_shape.setPosition(position);
		a = side_length;
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setTexture(&m_texture);
		m_shape.setFillColor(Settings::DefaultTextureColor());

		m_active = active;
		m_created = true;
	}


	////////////////////////////////


	void Triangle::create(float side_length,
		const sf::Vector2f& position,
		int origin,
		const std::string& filename,
		float rotation,
		bool active)
	{
		m_texture_path = filename;
		m_texture_set = true;

		if (!m_texture.loadFromFile(m_texture_path))
		{
			throw_error("Rectangle::Rectange(...)", "could not load texture from the given path", "ERROR");
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}


		m_origin = origin;
		m_text_position = MIDDLE_MIDDLE;
		m_text_shift = sf::Vector2f(0, 0);


		m_shape.setRadius(side_length * sqrt_3 / 3);
		m_shape.setPointCount(3);
		m_shape.setPosition(position);
		a = side_length;
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		this->m_shape.setTexture(&m_texture);
		this->m_shape.setFillColor(Settings::DefaultTextureColor());

		m_active = active;
		m_created = true;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                       P R I V A T E   F U N C T I O N S                       ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void Triangle::shapeUpdate()
	{
		switch (m_origin)
		{
		case MIDDLE_TOP:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_shapeCenter = m_shape.getPosition();
		}
		break;

		case LEFT_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y - a * sqrt_3 / 6 * m_shape.getScale().y);
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y - a * sqrt_3 / 6 * m_shape.getScale().y);
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x - m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y - m_shape.getRadius() * m_shape.getScale().y / 2);
		}
		break;

		default:
		{
			m_shapeCenter = m_shape.getPosition();
			throw_error("Triangle::shapeUpdate()", "Given shape origin is incorrect", "ERROR");
		}
		break;
		}
	}


	////////////////////////////////


	void Triangle::fullShapeUpdate()
	{
		switch (m_origin)
		{
		case MIDDLE_TOP:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), 0));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));
			m_shapeCenter = m_shape.getPosition();
		}
		break;

		case LEFT_BOTTOM:
		{
			m_shape.setOrigin(sf::Vector2f(0, a * sqrt_3 / 2));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y - a * sqrt_3 / 6 * m_shape.getScale().y);
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), a * sqrt_3 / 2));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y - a * sqrt_3 / 6 * m_shape.getScale().y);
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius() * 2, a * sqrt_3 / 2));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x - m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y - m_shape.getRadius() * m_shape.getScale().y / 2);
		}
		break;

		default:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));
			m_shapeCenter = m_shape.getPosition();
			throw_error("Triangle::fullShapeUpdate()", "Given shape origin is incorrect", "ERROR");
		}
		break;
		}
	}



	////////////////////////////////////////////////////////////////



	void Triangle::textUpdate()
	{
		switch (m_text_position)
		{
		case MIDDLE_MIDDLE:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + a * sqrt_3 / 6 * m_shape.getScale().y + m_text_shift.y));
		}
		break;

		default:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			throw_error("Triangle::textUpdate()", "Given text position is incorrect", "ERROR");
		}
		break;
		}
	}


	////////////////////////////////


	void Triangle::fullTextUpdate()
	{
		switch (m_text_position)
		{
		case MIDDLE_MIDDLE:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + m_text.getLocalBounds().height));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + a * sqrt_3 / 6 * m_shape.getScale().y + m_text_shift.y));
		}
		break;

		default:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			throw_error("Triangle::fullTextUpdate()", "Given text position is incorrect", "ERROR");
		}
		break;
		}
	}



	////////////////////////////////////////////////////////////////



	void Triangle::fontUpdate(int font)
	{
		switch (font)
		{
		case Arial:
		{
			if (s_arial_status)
			{
				m_text.setFont(f_arial);
				m_text_font = Arial;
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "Arial font is not available", "ERROR");
			}
		}
		break;

		case Arial_Uni:
		{
			if (s_arial_uni_status)
			{
				m_text.setFont(f_arial_unicode);
				m_text_font = Arial_Uni;
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "Arial Unicode font is not available", "ERROR");
			}
		}
		break;

		case Calibri:
		{
			if (s_calibri_status)
			{
				m_text.setFont(f_calibri);
				m_text_font = Calibri;
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "Calibri font is not available", "ERROR");
			}
		}
		break;

		case ComicSans:
		{
			if (s_comic_status)
			{
				m_text.setFont(f_comic_sans);
				m_text_font = ComicSans;
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "Comic Sans font is not available", "ERROR");
			}
		}
		break;

		case CourierNew:
		{
			if (s_courier_status)
			{
				m_text.setFont(f_courier_new);
				m_text_font = CourierNew;
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "Courier New font is not available", "ERROR");
			}
		}
		break;

		case TimesNewRoman:
		{
			if (s_times_nr_status)
			{
				m_text.setFont(f_times_new_roman);
				m_text_font = TimesNewRoman;
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "Times New Roman font is not available", "ERROR");
			}
		}
		break;

		case TrebuchetMS:
		{
			if (s_trebuchet_status)
			{
				m_text.setFont(f_trebuchet_MS);
				m_text_font = TrebuchetMS;
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "TrebuchetMS font is not available", "ERROR");
			}
		}
		break;

		case Verdana:
		{
			if (s_verdana_status)
			{
				m_text.setFont(f_verdana);
				m_text_font = Verdana;
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "Verdana font is not available", "ERROR");
			}
		}
		break;

		default:
		{
			if (s_arial_status)
			{
				m_text.setFont(f_arial);
				m_text_font = Arial;
				throw_error("Triangle::fontUpdate()", "Given Font does not exist, setting to Arial", "ERROR");
			}
			else
			{
				throw_error("Triangle::fontUpdate()", "Defaut font (Arial) is not available", "ERROR");
			}
		}
		break;
		}
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                           M O D    F U N C T I O N S                          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void Triangle::setPosition(const sf::Vector2f& position)
	{
		m_shape.setPosition(position);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Triangle::setPosition(float x, float y)
	{
		this->setPosition(sf::Vector2f(x, y));
	}


	sf::Vector2f Triangle::getPosition() const
	{
		return m_shape.getPosition();
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setSize(const sf::Vector2f& size)
	{
		this->setSideSize(size.x);
		this->fullShapeUpdate();
	}


	void Triangle::setSize(float size_x, float size_y)
	{
		this->setSideSize(size_x);
		this->fullShapeUpdate();
	}


	sf::Vector2f Triangle::getSize() const
	{
		return sf::Vector2f(a, a * sqrt_3 / 2);
	}



	////////////////////////////////////////////////////////////////



	void Triangle::move(const sf::Vector2f& offset)
	{
		m_shape.move(offset);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Triangle::move(float offset_x, float offset_y)
	{
		this->move(sf::Vector2f(offset_x, offset_y));
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setRadius(float radius)
	{
		m_shape.setRadius(radius);
		a = a * sqrt_3 / 3;

		this->fullShapeUpdate();
		this->fullTextUpdate();
	}


	float Triangle::getRadius() const
	{
		return m_shape.getRadius();
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setSideSize(float a)
	{
		m_shape.setRadius(a * sqrt_3 / 3);
		this->a = a;

		this->fullShapeUpdate();
		this->fullTextUpdate();
	}


	float Triangle::getSideSize() const
	{
		return 3 * m_shape.getRadius() / sqrt_3;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setText(const std::wstring& text)
	{
		m_text.setString(text);

		this->fullTextUpdate();
	}


	std::wstring Triangle::getText() const
	{
		return m_text.getString();
	}



	////////////////////////////////////////////////////////////////



	sf::CircleShape* Triangle::getShape()
	{
		return &m_shape;
	}


	sf::Text* Triangle::getSfText()
	{
		///returns pointer to sf::Text that this KEngine Triangle uses

		return &m_text;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setOrigin(int origin)
	{
		///changes origin of the KEngine Triangle
		/**available origins: <br>
		  * MIDDLE_TOP    = top <br>
		  * MIDDLE_MIDDLE = center <br>
		  * RIGHT_BOTTOM  = bottom right corner <br>
		  * MIDDLE_BOTTOM = bottom <br>
		  * LEFT_BOTTOM   = bottom left corner*/

		m_origin = origin;

		this->fullShapeUpdate();
		this->fullTextUpdate();
	}


	int Triangle::getOrigin() const
	{
		///returns origin of the KEngine Triangle
		/**available origins: <br>
		  * MIDDLE_TOP    = top <br>
		  * MIDDLE_MIDDLE = center <br>
		  * RIGHT_BOTTOM  = bottom right corner <br>
		  * MIDDLE_BOTTOM = bottom <br>
		  * LEFT_BOTTOM   = bottom left corner*/

		return m_origin;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setRotation(float angle)
	{
		m_shape.setRotation(angle);
		m_text.setRotation(angle);

		if (m_origin == MIDDLE_MIDDLE)
		{

			if (angle == 0)

				switch (m_text_position)
				{
				case MIDDLE_MIDDLE:
				{
					m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
				}
				break;

				case MIDDLE_BOTTOM:
				{
					m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + a * sqrt_3 / 6 + m_text_shift.y));
				}
				break;

				default:
				{
					m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
				}
				break;
				}
		}
		else if (angle == 90)
		{

			switch (m_text_position)
			{
			case MIDDLE_MIDDLE:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			case MIDDLE_BOTTOM:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x - a * sqrt_3 / 6 + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			default:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;
			}
		}
		else if (angle == 180)
		{

			switch (m_text_position)
			{
			case MIDDLE_MIDDLE:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			case MIDDLE_BOTTOM:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y - a * sqrt_3 / 6 + m_text_shift.y));
			}
			break;

			default:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;
			}

		}
		else if (angle == 270)
		{

			switch (m_text_position)
			{
			case MIDDLE_MIDDLE:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			case MIDDLE_BOTTOM:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + a * sqrt_3 / 6 + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			default:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;
			}
		}
	}


	void Triangle::rotate(float angle)
	{
		m_shape.rotate(angle);
		m_text.rotate(angle);

		if (m_origin == MIDDLE_MIDDLE)
		{

			if (angle == 0)

				switch (m_text_position)
				{
				case MIDDLE_MIDDLE:
				{
					m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
				}
				break;

				case MIDDLE_BOTTOM:
				{
					m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + a * sqrt_3 / 6 + m_text_shift.y));
				}
				break;

				default:
				{
					m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
				}
				break;
				}
		}
		else if (angle == 90)
		{

			switch (m_text_position)
			{
			case MIDDLE_MIDDLE:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			case MIDDLE_BOTTOM:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x - a * sqrt_3 / 6 + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			default:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;
			}
		}
		else if (angle == 180)
		{

			switch (m_text_position)
			{
			case MIDDLE_MIDDLE:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			case MIDDLE_BOTTOM:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y - a * sqrt_3 / 6 + m_text_shift.y));
			}
			break;

			default:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;
			}

		}
		else if (angle == 270)
		{

			switch (m_text_position)
			{
			case MIDDLE_MIDDLE:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			case MIDDLE_BOTTOM:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + a * sqrt_3 / 6 + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;

			default:
			{
				m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			}
			break;
			}
		}
	}


	float Triangle::getRotation() const
	{
		return m_shape.getRotation();
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setPositionByCenter(const sf::Vector2f& postion)
	{
		this->setPosition(postion.x + m_shape.getPosition().x - m_shapeCenter.x, postion.y + m_shape.getPosition().y - m_shapeCenter.y);
	}


	sf::Vector2f Triangle::getShapeCenter() const
	{
		return m_shapeCenter;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setScale(const sf::Vector2f& factors)
	{
		m_shape.setScale(factors);
		m_text.setScale(factors);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Triangle::setScale(float factor_x, float factor_y)
	{
		this->setScale(sf::Vector2f(factor_x, factor_y));

		this->shapeUpdate();
		this->textUpdate();
	}


	void Triangle::scale(const sf::Vector2f& factors)
	{
		m_shape.scale(factors);
		m_text.scale(factors);

		this->shapeUpdate();
		this->textUpdate();
	}


	sf::Vector2f Triangle::getScale() const
	{
		return m_shape.getScale();
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setTexture(const sf::Texture* texture)
	{
		if (texture)
		{
			m_texture_path = Settings::UnknownTexturePathName();
			m_texture = *texture;
			m_texture_set = true;
		}
		else
		{
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}

		this->m_shape.setTexture(&m_texture);
	}


	void Triangle::setTexture(const std::string& filename)
	{
		m_texture_set = true;
		m_texture_path = filename;

		if (!m_texture.loadFromFile(m_texture_path))
		{
			throw_error("Rectangle::Rectange(...)", "could not load texture from the given path", "ERROR");
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}

		m_shape.setTexture(&m_texture);
	}


	const sf::Texture* Triangle::getTexture() const
	{
		if (!m_texture_set)
			return nullptr;
		else
			return &m_texture;
	}


	////////////////////////////////


	void Triangle::addPathToTexture(const std::string& path)
	{
		m_texture_path = path;
	}


	std::string Triangle::getTexturePath() const
	{
		return m_texture_path;
	}


	bool Triangle::isTextureSet() const
	{
		return m_texture_set;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setFillColor(const sf::Color& color)
	{
		if (m_shape.getFillColor() != color)
			m_shape.setFillColor(color);
	}


	const sf::Color& Triangle::getFillColor() const
	{
		return m_shape.getFillColor();
	}


	
	////////////////////////////////////////////////////////////////



	void Triangle::setTextColor(const sf::Color& text_color)
	{
		if (m_text.getFillColor() != text_color)
			m_text.setFillColor(text_color);
	}


	const sf::Color& Triangle::getTextColor() const
	{
		return m_text.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setOutlineColor(const sf::Color& outline_color)
	{
		if (m_shape.getOutlineColor() != outline_color)
			m_shape.setOutlineColor(outline_color);
	}


	const sf::Color& Triangle::getOutlineColor() const
	{
		return m_shape.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setOutlineThickness(float outline_thickness)
	{
		m_shape.setOutlineThickness(outline_thickness);
	}


	float Triangle::getOutlineThickness() const
	{
		return m_shape.getOutlineThickness();
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setTextPosition(int position, const sf::Vector2f& text_shift)
	{
		///sets KEngine Triangle's text position and text shift
		/**available origins: <br>
		  * MIDDLE_MIDDLE = center <br>
		  * MIDDLE_BOTTOM = bottom <br> */

		m_text_position = position;
		m_text_shift = text_shift;

		this->fullTextUpdate();
	}


	int Triangle::getTextPosition() const
	{
		///returns KEngine Triangle's text position and text shift
		/**available origins: <br>
		  * MIDDLE_MIDDLE = center <br>
		  * MIDDLE_BOTTOM = bottom <br> */

		return m_text_position;
	}


	sf::Vector2f Triangle::getTextShift() const
	{
		return m_text_shift;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setTextStyle(int style)
	{
		m_text.setStyle(style);

		this->fullTextUpdate();
	}


	unsigned int Triangle::getTextStyle() const
	{
		return m_text.getStyle();
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setFont(int font)
	{
		///sets KEngine Triangle's font
		/**  available fonts <br>
		  *  airal <br>
		  *  airal unicode <br>
		  *  calimbri <br>
		  *  camic sans <br>
		  *  courier new <br>
		  *  times now roman <br>
		  *  trebuchet MS <br>
		  *  verdana */

		this->fontUpdate(font);

		this->fullTextUpdate();
	}


	int Triangle::getFont() const
	{
		///returns KEngine Triangle's font
		/**  available fonts <br>
		  *  airal <br>
		  *  airal unicode <br>
		  *  calimbri <br>
		  *  camic sans <br>
		  *  courier new <br>
		  *  times now roman <br>
		  *  trebuchet MS <br>
		  *  verdana */

		return m_text_font;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::setCharacterSize(unsigned int char_size)
	{
		m_text.setCharacterSize(char_size);

		this->fullTextUpdate();
	}


	unsigned int Triangle::getCharacterSize() const
	{
		return m_text.getCharacterSize();
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool Triangle::isInvaded(const sf::Vector2f& mousePosition) const
	{
		if (m_shape.getRotation() == 0)
		{
			sf::Vector2f bottom;
			bottom.x = m_shapeCenter.x;
			bottom.y = m_shapeCenter.y + m_shape.getRadius() / 2 * m_shape.getScale().x;

			if (mousePosition.y < bottom.y &&
				((mousePosition.x - bottom.x) / tan(30 * (TO_RAD)) < (mousePosition.y - (m_shapeCenter.y - m_shape.getRadius() * m_shape.getScale().x)) &&
					-((mousePosition.x - bottom.x) / tan(30 * (TO_RAD))) < (mousePosition.y - (m_shapeCenter.y - m_shape.getRadius() * m_shape.getScale().x))))
				return true;
			else    return false;
		}

		else if (m_shape.getRotation() == 90)
		{
			sf::Vector2f bottom;
			bottom.x = m_shapeCenter.x - m_shape.getRadius() / 2 * m_shape.getScale().x;
			bottom.y = m_shapeCenter.y;

			if (mousePosition.x > bottom.x &&
				((mousePosition.y - bottom.y) / tan(30 * (TO_RAD)) < ((m_shapeCenter.x + m_shape.getRadius() * m_shape.getScale().x) - mousePosition.x) &&
					-((mousePosition.y - bottom.y) / tan(30 * (TO_RAD))) < ((m_shapeCenter.x + m_shape.getRadius() * m_shape.getScale().x)) - mousePosition.x))
				return true;
			else    return false;
		}

		else if (m_shape.getRotation() == 180)
		{
			sf::Vector2f bottom;
			bottom.x = m_shapeCenter.x;
			bottom.y = m_shapeCenter.y - m_shape.getRadius() / 2 * m_shape.getScale().x;

			if (mousePosition.y > bottom.y &&
				((mousePosition.x - bottom.x) / tan(30 * (TO_RAD)) < ((m_shapeCenter.y + m_shape.getRadius() * m_shape.getScale().x) - mousePosition.y) &&
					-((mousePosition.x - bottom.x) / tan(30 * (TO_RAD))) < ((m_shapeCenter.y + m_shape.getRadius() * m_shape.getScale().x) - mousePosition.y)))
				return true;
			else    return false;
		}

		else if (m_shape.getRotation() == 270)
		{
			sf::Vector2f bottom;
			bottom.x = m_shapeCenter.x + m_shape.getRadius() / 2 * m_shape.getScale().x;
			bottom.y = m_shapeCenter.y;

			if (mousePosition.x < bottom.x &&
				((mousePosition.y - bottom.y) / tan(30 * (TO_RAD)) < (mousePosition.x - (m_shapeCenter.x - m_shape.getRadius() * m_shape.getScale().x)) &&
					-((mousePosition.y - bottom.y) / tan(30 * (TO_RAD))) < (mousePosition.x - (m_shapeCenter.x - m_shape.getRadius() * m_shape.getScale().x))))
				return true;
			else    return false;
		}

		return false;
	}


	////////////////////////////////


	bool Triangle::isInvaded_rect(const sf::Vector2f& mousePosition) const
	{
		//if (m_shape.getRotation() == 0.0f)
		//	return abs(m_shapeCenter.x - mousePosition.x) < m_shape.getRadius() * m_shape.getScale().x && abs(m_shapeCenter.y - mousePosition.y) < m_shape.getRadius() * m_shape.getScale().y;

		return 
			(mousePosition.x > m_shapeCenter.x - a * m_shape.getScale().x * 0.5 &&
			mousePosition.x < m_shapeCenter.x + a * m_shape.getScale().x * 0.5 &&
			mousePosition.y > m_shapeCenter.y - m_shape.getRadius() * m_shape.getScale().y &&
			mousePosition.y < m_shapeCenter.y + m_shape.getRadius() * m_shape.getScale().y * 0.5);
	}


	////////////////////////////////


	bool Triangle::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		if (this->isInvaded(mousePosition) && event.type == sf::Event::MouseButtonPressed && event.key.code == button)
			return true;
		return false;
	}



	////////////////////////////////////////////////////////////////



	bool Triangle::isActive() const
	{
		return m_active;
	}


	void Triangle::setActiveStatus(bool status)
	{
		m_active = status;
	}



	////////////////////////////////////////////////////////////////



	float Triangle::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		if (m_active)
			m_text.setPosition(sf::Vector2f(static_cast<int>(m_text.getPosition().x), static_cast<int>(m_text.getPosition().y)));

		return m_active;
	}



	////////////////////////////////////////////////////////////////



	void Triangle::render(sf::RenderWindow* window)
	{
		if (m_active)
		{
			window->draw(m_shape);
			window->draw(m_text);
		}
	}



	////////////////////////////////////////////////////////////////



	void Triangle::initPhysics()
	{
		m_physics = std::make_unique<Physics>(this);
	}


	void Triangle::initPhysics(long double mass, float friction)
	{
		m_physics = std::make_unique<Physics>(this, mass, friction);
	}


	void Triangle::deletePhysics()
	{
		m_physics = nullptr;
	}


	////////////////////////////////


	void Triangle::updatePhysics(const float dt)
	{
		if (m_physics != nullptr)
			m_physics->update(dt);
		else
			throw_error("Rectangle::updatePhysics(...)", "physics are not initialized yet", "WARNING");
	}


	Physics* Triangle::physics()
	{
		return m_physics.get();
	}



	////////////////////////////////////////////////////////////////



	bool Triangle::created() const
	{
		return m_created;
	}


} // namespace ke