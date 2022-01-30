#include "Circle.hpp"

namespace ke
{


	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	Circle::Circle()
		: m_origin(MIDDLE_MIDDLE)
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


	Circle::Circle(
		float radius, 
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
		, m_created(true)
	{
		m_shape.setRadius(radius);
		m_shape.setPosition(position);
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
	}


	////////////////////////////////


	Circle::Circle(
		float radius,
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

		m_shape.setRadius(radius);
		m_shape.setPosition(position);
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setTexture(&m_texture);
		m_shape.setFillColor(Settings::DefaultTextureColor());
	}


	////////////////////////////////


	Circle::Circle(
		float radius,
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

		m_shape.setRadius(radius);
		m_shape.setPosition(position);
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setTexture(&m_texture);
		m_shape.setFillColor(Settings::DefaultTextureColor());
	}


	////////////////////////////////


	Circle::~Circle()
	{

	}



	////////////////////////////////////////////////////////////////



	Circle::Circle(Circle& other)
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
		m_shape.setPosition(other.getPosition());
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



	Circle& Circle::operator= (Circle& other)
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
		m_shape.setPosition(other.getPosition());
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



	void Circle::create(
		float radius,
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


		m_shape.setRadius(radius);
		m_shape.setPosition(position);
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

		std::this_thread::sleep_for(std::chrono::microseconds(10)); // actually this fixes issue with text loading in threads

		this->fullTextUpdate();

		m_text.setFillColor(text_color);

		m_active = active;
		m_created = true;
	}


	////////////////////////////////


	void Circle::create(
		float radius,
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


		m_shape.setRadius(radius);
		m_shape.setPosition(position);
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setTexture(&m_texture);
		m_shape.setFillColor(Settings::DefaultTextureColor());

		m_active = active;
		m_created = true;
	}


	////////////////////////////////


	void Circle::create(
		float radius,
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


		m_shape.setRadius(radius);
		m_shape.setPosition(position);
		m_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_shape.setTexture(&m_texture);
		m_shape.setFillColor(Settings::DefaultTextureColor());

		m_active = active;
		m_created = true;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                       P R I V A T E   F U N C T I O N S                       ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void Circle::shapeUpdate()
	{
		switch (m_origin)
		{
		case LEFT_TOP:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case MIDDLE_TOP:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case RIGHT_TOP:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x - m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case LEFT_MIDDLE:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y);
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_shapeCenter = m_shape.getPosition();
		}
		break;

		case RIGHT_MIDDLE:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x - m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y);
		}
		break;

		case LEFT_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y - m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y - m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x - m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y - m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		default:
		{
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
			throw_error("Circle::shapeUpdate()", "Given shape origin is incorrect", "ERROR");
		}
		break;
		}
	}


	////////////////////////////////


	void Circle::fullShapeUpdate()
	{
		switch (m_origin)
		{
		case LEFT_TOP:
		{
			m_shape.setOrigin(sf::Vector2f(0, 0));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case MIDDLE_TOP:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), 0));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case RIGHT_TOP:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius() * 2, 0));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x - m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case LEFT_MIDDLE:
		{
			m_shape.setOrigin(sf::Vector2f(0, m_shape.getRadius()));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y);
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));
			m_shapeCenter = m_shape.getPosition();
		}
		break;

		case RIGHT_MIDDLE:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius() * 2, m_shape.getRadius()));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x - m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y);
		}
		break;

		case LEFT_BOTTOM:
		{
			m_shape.setOrigin(sf::Vector2f(0, m_shape.getRadius() * 2));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y - m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), m_shape.getRadius() * 2));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y - m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_shape.setOrigin(sf::Vector2f(m_shape.getRadius() * 2, m_shape.getRadius() * 2));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x - m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y - m_shape.getRadius() * m_shape.getScale().y);
		}
		break;

		default:
		{
			m_shape.setOrigin(sf::Vector2f(0, 0));
			m_shapeCenter = sf::Vector2f(m_shape.getPosition().x + m_shape.getRadius() * m_shape.getScale().x, m_shape.getPosition().y + m_shape.getRadius() * m_shape.getScale().y);
			throw_error("Circle::fullShapeUpdate()", "Given shape origin is incorrect", "ERROR");
		}
		break;
		}
	}



	////////////////////////////////////////////////////////////////



	void Circle::textUpdate()
	{
		switch (m_text_position)
		{
		case MIDDLE_TOP:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y - m_shape.getRadius() * m_shape.getScale().y + m_text_shift.y));
		}
		break;

		case LEFT_MIDDLE:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x - m_shape.getRadius() * m_shape.getScale().x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case RIGHT_MIDDLE:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_shape.getRadius() * m_shape.getScale().x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_shape.getRadius() * m_shape.getScale().y + m_text_shift.y));
		}
		break;

		default:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			throw_error("Circle::textUpdate()", "Given text position is incorrect", "ERROR");
		}
		break;
		}
	}


	////////////////////////////////


	void Circle::fullTextUpdate()
	{
		switch (m_text_position)
		{
		case MIDDLE_TOP:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y - m_shape.getRadius() * m_shape.getScale().y + m_text_shift.y));
		}
		break;

		case LEFT_MIDDLE:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left, m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x - m_shape.getRadius() * m_shape.getScale().x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case RIGHT_MIDDLE:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width, m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_shape.getRadius() * m_shape.getScale().x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + m_text.getLocalBounds().height));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_shape.getRadius() * m_shape.getScale().y + m_text_shift.y));
		}
		break;

		default:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
			throw_error("Circle::fullTextUpdate()", "Given text position is incorrect", "ERROR");
		}
		break;
		}
	}



	////////////////////////////////////////////////////////////////



	void Circle::fontUpdate(int font)
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
				throw_error("Circle::fontUpdate()", "Arial font is not available", "ERROR");
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
				throw_error("Circle::fontUpdate()", "Arial Unicode font is not available", "ERROR");
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
				throw_error("Circle::fontUpdate()", "Calibri font is not available", "ERROR");
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
				throw_error("Circle::fontUpdate()", "Comic Sans font is not available", "ERROR");
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
				throw_error("Circle::fontUpdate()", "Courier New font is not available", "ERROR");
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
				throw_error("Circle::fontUpdate()", "Times New Roman font is not available", "ERROR");
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
				throw_error("Circle::fontUpdate()", "TrebuchetMS font is not available", "ERROR");
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
				throw_error("Circle::fontUpdate()", "Verdana font is not available", "ERROR");
			}
		}
		break;

		default:
		{
			if (s_arial_status)
			{
				m_text.setFont(f_arial);
				m_text_font = Arial;
				throw_error("Circle::fontUpdate()", "Given Font does not exist, setting to Arial", "ERROR");
			}
			else
			{
				throw_error("Circle::fontUpdate()", "Defaut font (Arial) is not available", "ERROR");
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





	void Circle::setPosition(const sf::Vector2f& position)
	{
		m_shape.setPosition(position);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Circle::setPosition(float x, float y)
	{
		this->setPosition(sf::Vector2f(x, y));
	}


	sf::Vector2f Circle::getPosition() const
	{
		return m_shape.getPosition();
	}

	

	////////////////////////////////////////////////////////////////



	void Circle::setSize(const sf::Vector2f& size)
	{
		m_shape.setRadius(size.x / 2);

		this->fullShapeUpdate();
		this->fullTextUpdate ();
	}


	void Circle::setSize(float size_x, float size_y)
	{
		m_shape.setRadius(size_x / 2);

		this->fullShapeUpdate();
		this->fullTextUpdate();
	}


	sf::Vector2f Circle::getSize() const
	{
		return sf::Vector2f(m_shape.getRadius() * 2, m_shape.getRadius() * 2);
	}



	////////////////////////////////////////////////////////////////



	void Circle::move(const sf::Vector2f& offset)
	{
		m_shape.move(offset);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Circle::move(float offset_x, float offset_y)
	{
		m_shape.move(offset_x, offset_y);

		this->shapeUpdate();
		this->textUpdate();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setRadius(float radius)
	{
		m_shape.setRadius(radius);

		this->fullShapeUpdate();
		this->fullTextUpdate ();
	}


	float Circle::getRadius() const
	{
		return m_shape.getRadius();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setText(const std::wstring& text)
	{
		m_text.setString(text);

		this->fullTextUpdate();
	}


	std::wstring Circle::getText() const
	{
		return m_text.getString();
	}



	////////////////////////////////////////////////////////////////



	sf::CircleShape* Circle::getShape()
	{
		return &m_shape;
	}


	sf::Text* Circle::getSfText()
	{
		return &m_text;
	}



	////////////////////////////////////////////////////////////////



	void Circle::setOrigin(int origin)
	{
		///changes origin of the KEngine Circle
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

		m_origin = origin;

		this->fullShapeUpdate();
		this->fullTextUpdate ();
	}


	int Circle::getOrigin() const
	{
		///returns origin of the KEngine Circle
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

		return m_origin;
	}



	////////////////////////////////////////////////////////////////



	void Circle::setRotation(float angle)
	{
		m_shape.setRotation(angle);
		m_text.setRotation(angle);
	}


	void Circle::rotate(float angle)
	{
		m_shape.rotate(angle);
		m_text.rotate(angle);
	}


	float Circle::getRotation() const
	{
		return m_shape.getRotation();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setPositionByCenter(const sf::Vector2f& postion)
	{
		this->setPosition(postion.x + m_shape.getPosition().x - m_shapeCenter.x, postion.y + m_shape.getPosition().y - m_shapeCenter.y);
	}


	sf::Vector2f Circle::getShapeCenter() const
	{
		return m_shapeCenter;
	}



	////////////////////////////////////////////////////////////////



	void Circle::setScale(const sf::Vector2f& factors)
	{
		m_shape.setScale(factors);
		m_text.setScale(factors);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Circle::setScale(float factor_x, float factor_y)
	{
		this->setScale(sf::Vector2f(factor_x, factor_y));

		this->shapeUpdate();
		this->textUpdate();
	}


	void Circle::scale(const sf::Vector2f& factors)
	{
		m_shape.scale(factors);
		m_text.scale(factors);

		this->shapeUpdate();
		this->textUpdate();
	}


	sf::Vector2f Circle::getScale() const
	{
		return m_shape.getScale();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setTexture(const sf::Texture* texture)
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


	void Circle::setTexture(const std::string& filename)
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


	const sf::Texture* Circle::getTexture() const
	{
		if (!m_texture_set)
			return nullptr;
		else
			return &m_texture;
	}


	////////////////////////////////


	void Circle::addPathToTexture(const std::string& path)
	{
		m_texture_path = path;
	}


	std::string Circle::getTexturePath() const
	{
		return m_texture_path;
	}


	bool Circle::isTextureSet() const
	{
		return m_texture_set;
	}



	////////////////////////////////////////////////////////////////



	void Circle::setFillColor(const sf::Color& color)
	{
		if (m_shape.getFillColor() != color)
			m_shape.setFillColor(color);
	}


	const sf::Color& Circle::getFillColor() const
	{
		return m_shape.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setTextColor(const sf::Color& text_color)
	{
		if (m_text.getFillColor() != text_color)
			m_text.setFillColor(text_color);
	}


	const sf::Color& Circle::getTextColor() const
	{
		return m_text.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setOutlineColor(const sf::Color& outline_color)
	{
		if (m_shape.getOutlineColor() != outline_color)
			m_shape.setOutlineColor(outline_color);
	}


	const sf::Color& Circle::getOutlineColor() const
	{
		return m_shape.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setOutlineThickness(float outline_thickness)
	{
		m_shape.setOutlineThickness(outline_thickness);
	}


	float Circle::getOutlineThickness() const
	{
		return m_shape.getOutlineThickness();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setTextPosition(int position, const sf::Vector2f& text_shift)
	{
		///sets KEngine Circle's m_text position and m_text shift
		/**available origins: <br>
		  * MIDDLE_TOP    = top <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * MIDDLE_MIDDLE = center <br>
		  * LEFT_MIDDLE   = left side <br>
		  * MIDDLE_BOTTOM = bottom */

		m_text_position = position;
		m_text_shift = text_shift;

		this->fullTextUpdate();
	}


	int Circle::getTextPosition() const
	{
		///returns KEngine Circle's m_text position
		/**available origins: <br>
		  * MIDDLE_TOP    = top <br>
		  * RIGHT_MIDDLE  = right side <br>
		  * MIDDLE_MIDDLE = center <br>
		  * LEFT_MIDDLE   = left side <br>
		  * MIDDLE_BOTTOM = bottom */

		return m_text_position;
	}


	sf::Vector2f Circle::getTextShift() const
	{
		return m_text_shift;
	}



	////////////////////////////////////////////////////////////////



	void Circle::setTextStyle(int style)
	{
		m_text.setStyle(style);

		this->fullTextUpdate();
	}


	unsigned int Circle::getTextStyle() const
	{
		return m_text.getStyle();
	}



	////////////////////////////////////////////////////////////////



	void Circle::setFont(int font)
	{
		///sets KEngine Circle's font
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

	int Circle::getFont() const
	{
		///returns KEngine Circle's font
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



	void Circle::setCharacterSize(unsigned int char_size)
	{
		m_text.setCharacterSize(char_size);

		this->fullTextUpdate();
	}

	unsigned int Circle::getCharacterSize() const
	{
		return m_text.getCharacterSize();
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool Circle::isInvaded(const sf::Vector2f& mousePosition) const
	{
		return (pow(m_shapeCenter.x - mousePosition.x, 2) + pow(m_shapeCenter.y - mousePosition.y, 2) < pow(m_shape.getRadius() * m_shape.getScale().x, 2));
	}


	bool Circle::isInvaded_rect(const sf::Vector2f& mousePosition) const
	{
		//  normal rectangle - point collision detection
		if (m_shape.getRotation() == 0.0f)
			return abs(m_shapeCenter.x - mousePosition.x) < m_shape.getRadius() * m_shape.getScale().x && abs(m_shapeCenter.y - mousePosition.y) < m_shape.getRadius() * m_shape.getScale().y;

		// rotated rectangle - point collision detection
		// works only when m_origin is set to MIDDLE_MIDDLE
		return
			abs((cos(DTR(-m_shape.getRotation())) * m_shapeCenter.x - sin(DTR(-m_shape.getRotation())) * m_shapeCenter.y) - (cos(DTR(-m_shape.getRotation())) * mousePosition.x - sin(DTR(-m_shape.getRotation())) * mousePosition.y)) < m_shape.getRadius() * m_shape.getScale().x &&
			abs((cos(DTR(-m_shape.getRotation())) * m_shapeCenter.y + sin(DTR(-m_shape.getRotation())) * m_shapeCenter.x) - (cos(DTR(-m_shape.getRotation())) * mousePosition.y + sin(DTR(-m_shape.getRotation())) * mousePosition.x)) < m_shape.getRadius() * m_shape.getScale().y;
	}


	////////////////////////////////


	bool Circle::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return (this->isInvaded(mousePosition) && event.type == sf::Event::MouseButtonPressed && event.key.code == button);
	}



	////////////////////////////////////////////////////////////////



	bool Circle::isActive() const
	{
		return m_active;
	}


	void  Circle::setActiveStatus(bool status)
	{
		m_active = status;
	}



	////////////////////////////////////////////////////////////////



	float Circle::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		if (m_active)
			m_text.setPosition(sf::Vector2f(static_cast<int>(m_text.getPosition().x), static_cast<int>(m_text.getPosition().y)));

		return m_active;
	}



	////////////////////////////////////////////////////////////////



	void Circle::render(sf::RenderWindow* window)
	{
		if (m_active)
		{
			window->draw(m_shape);
			window->draw(m_text);
		}
	}



	////////////////////////////////////////////////////////////////



	void Circle::initPhysics()
	{
		m_physics = std::make_unique<Physics>(this);
	}


	void Circle::initPhysics(long double mass, float friction)
	{
		m_physics = std::make_unique<Physics>(this, mass, friction);
	}


	void Circle::deletePhysics()
	{
		m_physics = nullptr;
	}


	////////////////////////////////


	void Circle::updatePhysics(const float dt)
	{
		if (m_physics != nullptr)
			m_physics->update(dt);
		else
			throw_error("Rectangle::updatePhysics(...)", "physics are not initialized yet", "WARNING");
	}


	Physics* Circle::physics()
	{
		return m_physics.get();
	}



	////////////////////////////////////////////////////////////////



	bool Circle::created() const
	{
		return m_created;
	}


} // namespace ke