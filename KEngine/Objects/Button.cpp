#include "Button.hpp"

namespace ke
{


	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//============== C O N S T R U C T O R S ,   D E S T R U C T O R S   A N D   O P E R A T O R S ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	Button::Button()
		: m_origin(MIDDLE_MIDDLE)
		, m_texture_path(Settings::EmptyTexturePath())
		, m_texture_set(false)
		, m_shapeCenter(0, 0)
		, m_physics(nullptr)
		, m_text_shift(0, 0)
		, m_text_position(MIDDLE_MIDDLE)
		, m_text_font(Arial)
		, m_render_order(0)
		, m_active(false)
		, m_created(false)
	{

	}


	////////////////////////////////


	Button::Button(
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
		, m_render_order(0)
		, m_active(active)
		, m_created(true)
	{
		m_texture_shape.setSize(size);
		m_color_shape.setSize(size);
		m_texture_shape.setPosition(position);
		m_color_shape.setPosition(position);
		m_texture_shape.setRotation(rotation);
		m_color_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_color_shape.setFillColor(object_color);
		m_color_shape.setOutlineColor(outline_color);
		m_color_shape.setOutlineThickness(outline_thickness);

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

		m_texture_shape.setTexture(&m_texture);
		m_texture_shape.setFillColor(Settings::DefaultTextureColor());


		m_text.setCharacterSize(character_size);

		this->fontUpdate(font);

		m_text.setStyle(text_style);
		m_text.setString(text);
		m_text.setRotation(rotation);

		this->fullTextUpdate();

		m_text.setFillColor(text_color);
	}


	////////////////////////////////


	Button::Button(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const std::string& filename,
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

		: m_texture_path(filename)
		, m_origin(origin)
		, m_text_position(text_position)
		, m_text_shift(text_shift)
		, m_physics(nullptr)
		, m_render_order(0)
		, m_active(active)
		, m_created(true)
	{
		m_texture_shape.setSize(size);
		m_color_shape.setSize(size);
		m_texture_shape.setPosition(position);
		m_color_shape.setPosition(position);
		m_texture_shape.setRotation(rotation);
		m_color_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_color_shape.setFillColor(object_color);
		m_color_shape.setOutlineColor(outline_color);
		m_color_shape.setOutlineThickness(outline_thickness);

		m_texture_set = true;

		if (!m_texture.loadFromFile(m_texture_path))
		{
			throw_error("Rectangle::Rectange(...)", "could not load texture from the given path", "ERROR");
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}

		m_texture_shape.setTexture(&m_texture);
		m_texture_shape.setFillColor(Settings::DefaultTextureColor());


		m_text.setCharacterSize(character_size);

		this->fontUpdate(font);

		m_text.setStyle(text_style);
		m_text.setString(text);
		m_text.setRotation(rotation);

		this->fullTextUpdate();

		m_text.setFillColor(text_color);
	}


	////////////////////////////////


	Button::~Button()
	{
		
	}



	////////////////////////////////////////////////////////////////



	Button::Button(Button& other)
		: m_texture_path(other.getTexturePath())
		, m_texture_set(other.isTextureSet())
		, m_texture(*other.getTexture())
		, m_origin(other.getOrigin())
		, m_text_position(other.getTextPosition())
		, m_text_shift(other.getTextShift())
		, m_render_order(other.getRenderOrder())
		, m_active(other.isActive())
		, m_created(true)
	{
		m_texture_shape.setSize(other.getSize());
		m_color_shape.setSize(other.getSize());
		m_texture_shape.setPosition(other.getPosition());
		m_color_shape.setPosition(other.getPosition());
		m_texture_shape.setRotation(other.getRotation());
		m_color_shape.setRotation(other.getRotation());

		fullShapeUpdate();

		m_color_shape.setFillColor(other.getFillColor());
		m_color_shape.setOutlineColor(other.getOutlineColor());
		m_color_shape.setOutlineThickness(other.getOutlineThickness());

		m_texture_shape.setTexture(&m_texture);
		m_texture_shape.setFillColor(Settings::DefaultTextureColor());


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



	////////////////////////////////



	Button& Button::operator= (Button& other)
	{
		m_texture_path = other.getTexturePath();
		m_texture_set = other.isTextureSet();
		m_texture = *other.getTexture();

		m_origin = other.getOrigin();

		m_text_position = other.getTextPosition();
		m_text_shift = other.getTextShift();


		m_texture_shape.setSize(other.getSize());
		m_color_shape.setSize(other.getSize());
		m_texture_shape.setPosition(other.getPosition());
		m_color_shape.setPosition(other.getPosition());
		m_texture_shape.setRotation(other.getRotation());
		m_color_shape.setRotation(other.getRotation());

		fullShapeUpdate();

		m_color_shape.setFillColor(other.getFillColor());
		m_color_shape.setOutlineColor(other.getOutlineColor());
		m_color_shape.setOutlineThickness(other.getOutlineThickness());

		m_texture_shape.setTexture(&m_texture);
		m_texture_shape.setFillColor(Settings::DefaultTextureColor());


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

		m_render_order = other.getRenderOrder();
		m_active = other.isActive();
		m_created = true;

		return *this;
	}



	////////////////////////////////////////////////////////////////



	void Button::create(const sf::Vector2f& size,
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
		float rotation,
		unsigned int text_style,
		const sf::Vector2f& text_shift,
		int font,
		bool active)
	{
		m_origin = origin;
		m_text_position = text_position;
		m_text_shift = text_shift;


		m_texture_shape.setSize(size);
		m_color_shape.setSize(size);
		m_texture_shape.setPosition(position);
		m_color_shape.setPosition(position);
		m_texture_shape.setRotation(rotation);
		m_color_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_color_shape.setFillColor(object_color);
		m_color_shape.setOutlineColor(outline_color);
		m_color_shape.setOutlineThickness(outline_thickness);

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

		m_texture_shape.setTexture(&m_texture);
		m_texture_shape.setFillColor(Settings::DefaultTextureColor());


		m_text.setCharacterSize(character_size);

		this->fontUpdate(font);

		m_text.setStyle(text_style);
		m_text.setString(text);
		m_text.setRotation(rotation);

		this->fullTextUpdate();

		m_text.setFillColor(text_color);

		m_physics = nullptr;
		m_render_order = 0;
		m_active = active;
		m_created = true;
	}


	////////////////////////////////


	void Button::create(const sf::Vector2f& size,
		const sf::Vector2f& position,
		int origin,
		const std::string& filename,
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
		m_origin = origin;
		m_text_position = text_position;
		m_text_shift = text_shift;


		m_texture_shape.setSize(size);
		m_color_shape.setSize(size);
		m_texture_shape.setPosition(position);
		m_color_shape.setPosition(position);
		m_texture_shape.setRotation(rotation);
		m_color_shape.setRotation(rotation);

		this->fullShapeUpdate();

		m_color_shape.setFillColor(object_color);
		m_color_shape.setOutlineColor(outline_color);
		m_color_shape.setOutlineThickness(outline_thickness);

		m_texture_set = true;
		m_texture_path = filename;

		if (!m_texture.loadFromFile(m_texture_path))
		{
			throw_error("Rectangle::Rectange(...)", "could not load texture from the given path", "ERROR");
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}

		m_texture_shape.setTexture(&m_texture);
		m_texture_shape.setFillColor(Settings::DefaultTextureColor());


		m_text.setCharacterSize(character_size);

		this->fontUpdate(font);

		m_text.setStyle(text_style);
		m_text.setString(text);
		m_text.setRotation(rotation);

		this->fullTextUpdate();

		m_text.setFillColor(text_color);

		m_physics = nullptr;
		m_render_order = 0;
		m_active = active;
		m_created = true;
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============                       P R I V A T E   F U N C T I O N S                       ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	void Button::shapeUpdate()
	{
		switch (m_origin)
		{
		case LEFT_TOP:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case MIDDLE_TOP:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x, m_texture_shape.getPosition().y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case RIGHT_TOP:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case LEFT_MIDDLE:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y);
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_shapeCenter = m_texture_shape.getPosition();
		}
		break;

		case RIGHT_MIDDLE:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y);
		}
		break;

		case LEFT_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x, m_texture_shape.getPosition().y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		default:
		{
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
			throw_error("Button::shapeUpdate()", "Given shape origin is incorrect", "ERROR");
		}
		break;
		}
	}


	////////////////////////////////


	void Button::fullShapeUpdate()
	{
		switch (m_origin)
		{
		case LEFT_TOP:
		{
			m_texture_shape.setOrigin(0, 0);
			m_color_shape.setOrigin(0, 0);
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case MIDDLE_TOP:
		{
			//m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, 0));
			//m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, 0));
			m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x / 2, 0));
			m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x / 2, 0));
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x, m_texture_shape.getPosition().y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case RIGHT_TOP:
		{
			//m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x, 0));
			//m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x, 0));
			m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x, 0));
			m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x, 0));
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case LEFT_MIDDLE:
		{
			//m_texture_shape.setOrigin(sf::Vector2f(0, m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2));
			//m_color_shape.setOrigin(sf::Vector2f(0, m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2));
			m_texture_shape.setOrigin(sf::Vector2f(0, m_texture_shape.getSize().y / 2));
			m_color_shape.setOrigin(sf::Vector2f(0, m_texture_shape.getSize().y / 2));
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y);
		}
		break;

		case MIDDLE_MIDDLE:
		{
			//m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2));
			//m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2));
			m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x / 2, m_texture_shape.getSize().y / 2));
			m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x / 2, m_texture_shape.getSize().y / 2));
			m_shapeCenter = m_texture_shape.getPosition();
		}
		break;

		case RIGHT_MIDDLE:
		{
			//m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x, m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2));
			//m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x, m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2));
			m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x, m_texture_shape.getSize().y / 2));
			m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x, m_texture_shape.getSize().y / 2));
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y);
		}
		break;

		case LEFT_BOTTOM:
		{
			//m_texture_shape.setOrigin(sf::Vector2f(0, m_texture_shape.getSize().y * m_texture_shape.getScale().y));
			//m_color_shape.setOrigin(sf::Vector2f(0, m_texture_shape.getSize().y * m_texture_shape.getScale().y));
			m_texture_shape.setOrigin(sf::Vector2f(0, m_texture_shape.getSize().y));
			m_color_shape.setOrigin(sf::Vector2f(0, m_texture_shape.getSize().y));
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		case MIDDLE_BOTTOM:
		{
			//m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getSize().y * m_texture_shape.getScale().y));
			//m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getSize().y * m_texture_shape.getScale().y));
			m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x / 2, m_texture_shape.getSize().y));
			m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x / 2, m_texture_shape.getSize().y));
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x, m_texture_shape.getPosition().y - m_texture_shape.getSize().y / 2);
		}
		break;

		case RIGHT_BOTTOM:
		{
			//m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x, m_texture_shape.getSize().y * m_texture_shape.getScale().y));
			//m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x * m_texture_shape.getScale().x, m_texture_shape.getSize().y * m_texture_shape.getScale().y));
			m_texture_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x, m_texture_shape.getSize().y));
			m_color_shape.setOrigin(sf::Vector2f(m_texture_shape.getSize().x, m_texture_shape.getSize().y));
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
		}
		break;

		default:
		{
			m_texture_shape.setOrigin(0, 0);
			m_color_shape.setOrigin(0, 0);
			m_shapeCenter = sf::Vector2f(m_texture_shape.getPosition().x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2, m_texture_shape.getPosition().y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2);
			throw_error("Button::fullShapeUpdate()", "Given shape origin is incorrect", "ERROR");
		}
		break;
		}
	}


	////////////////////////////////


	void Button::textUpdate()
	{
		switch (m_text_position)
		{
		case LEFT_TOP:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case MIDDLE_TOP:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case RIGHT_TOP:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case LEFT_MIDDLE:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case MIDDLE_MIDDLE:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case RIGHT_MIDDLE:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case LEFT_BOTTOM:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		default:
		{
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
			throw_error("Button::textUpdate()", "Given text position is incorrect", "ERROR");
		}
		break;
		}
	}



	////////////////////////////////////////////////////////////////



	void Button::fullTextUpdate()
	{
		switch (m_text_position)
		{
		case LEFT_TOP:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left, m_text.getLocalBounds().top));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case MIDDLE_TOP:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case RIGHT_TOP:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width, m_text.getLocalBounds().top));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case LEFT_MIDDLE:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left, m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
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
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y + m_text_shift.y));
		}
		break;

		case LEFT_BOTTOM:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left, m_text.getLocalBounds().top + m_text.getLocalBounds().height));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x - m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case MIDDLE_BOTTOM:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + m_text.getLocalBounds().height));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		case RIGHT_BOTTOM:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width, m_text.getLocalBounds().top + m_text.getLocalBounds().height));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_texture_shape.getSize().x * m_texture_shape.getScale().x / 2 + m_text_shift.x, m_shapeCenter.y + m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
		}
		break;

		default:
		{
			m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top));
			m_text.setPosition(sf::Vector2f(m_shapeCenter.x + m_text_shift.x, m_shapeCenter.y - m_texture_shape.getSize().y * m_texture_shape.getScale().y / 2 + m_text_shift.y));
			throw_error("Button::fullTextUpdate()", "Given text position is incorrect", "ERROR");
		}
		break;
		}
	}



	////////////////////////////////////////////////////////////////



	void Button::fontUpdate(int font)
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
				throw_error("Button::fontUpdate()", "Arial font is not available", "ERROR");
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
				throw_error("Button::fontUpdate()", "Arial Unicode font is not available", "ERROR");
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
				throw_error("Button::fontUpdate()", "Calibri font is not available", "ERROR");
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
				throw_error("Button::fontUpdate()", "Comic Sans font is not available", "ERROR");
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
				throw_error("Button::fontUpdate()", "Courier New font is not available", "ERROR");
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
				throw_error("Button::fontUpdate()", "Times New Roman font is not available", "ERROR");
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
				throw_error("Button::fontUpdate()", "TrebuchetMS font is not available", "ERROR");
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
				throw_error("Button::fontUpdate()", "Verdana font is not available", "ERROR");
			}
		}
		break;

		default:
		{
			if (s_arial_status)
			{
				m_text.setFont(f_arial);
				m_text_font = Arial;
				throw_error("Button::fontUpdate()", "Given Font does not exist, setting to Arial", "ERROR");
			}
			else
			{
				throw_error("Button::fontUpdate()", "Defaut font (Arial) is not available", "ERROR");
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





	void Button::setPosition(const sf::Vector2f& position)
	{
		m_texture_shape.setPosition(position);
		m_color_shape.setPosition(position);

		this->fullShapeUpdate();
		this->fullTextUpdate();
	}


	void Button::setPosition(float x, float y)
	{
		this->setPosition(sf::Vector2f(x, y));
	}


	sf::Vector2f Button::getPosition() const
	{
		return m_texture_shape.getPosition();
	}



	////////////////////////////////////////////////////////////////



	void Button::setSize(const sf::Vector2f& size)
	{
		m_texture_shape.setSize(size);
		m_color_shape.setSize(size);
		
		this->fullShapeUpdate();
		this->textUpdate();
	}


	void Button::setSize(float size_x, float size_y)
	{
		m_texture_shape.setSize(sf::Vector2f(size_x, size_y));
		m_color_shape.setSize(sf::Vector2f(size_x, size_y));

		this->fullShapeUpdate();
		this->textUpdate();
	}


	sf::Vector2f Button::getSize() const
	{
		return m_texture_shape.getSize();
	}



	////////////////////////////////////////////////////////////////



	void Button::move(const sf::Vector2f& offset)
	{
		m_texture_shape.move(offset);
		m_color_shape.move(offset);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Button::move(float offset_x, float offset_y)
	{
		this->move(sf::Vector2f(offset_x, offset_y));
	}



	////////////////////////////////////////////////////////////////



	void Button::setText(const std::wstring& text)
	{
		m_text.setString(text);

		this->fullTextUpdate();
	}


	std::wstring Button::getText() const
	{
		return m_text.getString();
	}



	////////////////////////////////////////////////////////////////



	sf::RectangleShape* Button::getTextureShape()
	{
		return &m_texture_shape;
	}


	sf::RectangleShape* Button::getColorShape()
	{
		return &m_color_shape;
	}


	sf::Text* Button::getSfText()
	{
		return &m_text;
	}



	////////////////////////////////////////////////////////////////



	void Button::setOrigin(int origin)
	{
		///changes origin of the KEngine Button
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
		this->fullTextUpdate();
	}


	int Button::getOrigin() const
	{
		///returns origin of the KEngine Button
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



	void Button::setRotation(float angle)
	{
		m_texture_shape.setRotation(angle);
		m_color_shape.setRotation(angle);
		m_text.setRotation(angle);
	}

	void Button::rotate(float angle)
	{
		m_texture_shape.rotate(angle);
		m_color_shape.rotate(angle);
		m_text.rotate(angle);
	}

	float Button::getRotation() const
	{
		return m_texture_shape.getRotation();
	}



	////////////////////////////////////////////////////////////////



	void Button::setPositionByCenter(const sf::Vector2f& postion)
	{
		this->setPosition(postion.x + m_texture_shape.getPosition().x - m_shapeCenter.x, postion.y + m_texture_shape.getPosition().y - m_shapeCenter.y);
	}


	sf::Vector2f Button::getShapeCenter() const
	{
		return m_shapeCenter;
	}



	////////////////////////////////////////////////////////////////



	void Button::setScale(const sf::Vector2f& factors)
	{
		m_texture_shape.setScale(factors);
		m_color_shape.setScale(factors);
		m_text.setScale(factors);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Button::setScale(float factor_x, float factor_y)
	{
		m_texture_shape.setScale(factor_x, factor_y);
		m_color_shape.setScale(factor_x, factor_y);
		m_text.setScale(factor_x, factor_y);

		this->shapeUpdate();
		this->textUpdate();
	}


	void Button::scale(const sf::Vector2f& factors)
	{
		m_texture_shape.scale(factors);
		m_color_shape.scale(factors);
		m_text.scale(factors);

		this->shapeUpdate();
		this->textUpdate();
	}
	

	sf::Vector2f Button::getScale() const
	{
		return m_texture_shape.getScale();
	}



	////////////////////////////////////////////////////////////////



	void Button::setTexture(const sf::Texture* texture)
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

		m_texture_shape.setTexture(&m_texture);
	}


	void Button::setTexture(const std::string& filename)
	{
		m_texture_set = true;
		m_texture_path = filename;

		if (!m_texture.loadFromFile(m_texture_path))
		{
			throw_error("Button::button(...)", "could not load texture from the given path", "ERROR");
			m_texture_path = Settings::EmptyTexturePath();
			m_texture.loadFromFile(m_texture_path);
			m_texture_set = false;
		}

		m_texture_shape.setTexture(&m_texture);
	}


	const sf::Texture* Button::getTexture() const
	{
		return &m_texture;
	}


	////////////////////////////////


	void Button::addPathToTexture(const std::string& path)
	{
		m_texture_path = path;
	}


	std::string Button::getTexturePath() const
	{
		return m_texture_path;
	}


	bool Button::isTextureSet() const
	{
		return m_texture_set;
	}



	////////////////////////////////////////////////////////////////



	void Button::setFillColor(const sf::Color& color)
	{
		if (m_color_shape.getFillColor() != color)
			m_color_shape.setFillColor(color);
	}


	const sf::Color& Button::getFillColor() const
	{
		return m_color_shape.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void Button::setTextColor(const sf::Color& text_color)
	{
		if (m_text.getFillColor() != text_color)
			m_text.setFillColor(text_color);
	}


	const sf::Color& Button::getTextColor() const
	{
		return m_text.getFillColor();
	}



	////////////////////////////////////////////////////////////////



	void Button::setOutlineColor(const sf::Color& outline_color)
	{
		if (m_color_shape.getOutlineColor() != outline_color)
		m_color_shape.setOutlineColor(outline_color);
	}


	const sf::Color& Button::getOutlineColor() const
	{
		return m_color_shape.getOutlineColor();
	}



	////////////////////////////////////////////////////////////////



	void Button::setOutlineThickness(float outline_thickness)
	{
		m_color_shape.setOutlineThickness(outline_thickness);
	}


	float Button::getOutlineThickness() const
	{
		return m_color_shape.getOutlineThickness();
	}



	////////////////////////////////////////////////////////////////



	void Button::setTextPosition(int position, const sf::Vector2f& text_shift)
	{
		///sets KEngine Button's text position and text shift
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

		m_text_position = position;
		m_text_shift = text_shift;

		this->fullTextUpdate();
	}


	int Button::getTextPosition() const
	{
		///returns KEngine Button's text position
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

		return m_text_position;
	}


	sf::Vector2f Button::getTextShift() const
	{
		return m_text_shift;
	}



	////////////////////////////////////////////////////////////////



	void Button::setTextStyle(int style)
	{
		m_text.setStyle(style);

		this->fullTextUpdate();
	}


	unsigned int Button::getTextStyle() const
	{
		return m_text.getStyle();
	}



	////////////////////////////////////////////////////////////////



	void Button::setFont(int font)
	{
		///sets KEngine Button's font
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


	int Button::getFont() const
	{
		///returns KEngine Button's font
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



	void Button::setCharacterSize(unsigned int char_size)
	{
		m_text.setCharacterSize(char_size);

		this->fullTextUpdate();
	}


	unsigned int Button::getCharacterSize() const
	{
		return m_text.getCharacterSize();
	}





	//-------------------------                                                         -------------------------//
	//+++                                                                                                     +++//
	//==============          R E N D E R   A N D   B E H A V I O U R   F U N C T I O N S          ==============//
	//+++                                                                                                     +++//
	//-------------------------                                                         -------------------------//





	bool Button::isInvaded(const sf::Vector2f& mousePosition) const
	{
		//  normal rectangle - point collision detection
		if (m_texture_shape.getRotation() == 0.0f)
			return abs(m_shapeCenter.x - mousePosition.x) < m_texture_shape.getSize().x * m_texture_shape.getScale().x * 0.5f && abs(m_shapeCenter.y - mousePosition.y) < m_texture_shape.getSize().y * m_texture_shape.getScale().y * 0.5f;

		// rotated rectangle - point collision detection
		// works only when m_origin is set to MIDDLE_MIDDLE
		return
			abs((cos(DTR(-m_texture_shape.getRotation())) * m_shapeCenter.x - sin(DTR(-m_texture_shape.getRotation())) * m_shapeCenter.y) - (cos(DTR(-m_texture_shape.getRotation())) * mousePosition.x - sin(DTR(-m_texture_shape.getRotation())) * mousePosition.y)) < m_texture_shape.getSize().x * m_texture_shape.getScale().x * 0.5f &&
			abs((cos(DTR(-m_texture_shape.getRotation())) * m_shapeCenter.y + sin(DTR(-m_texture_shape.getRotation())) * m_shapeCenter.x) - (cos(DTR(-m_texture_shape.getRotation())) * mousePosition.y + sin(DTR(-m_texture_shape.getRotation())) * mousePosition.x)) < m_texture_shape.getSize().y * m_texture_shape.getScale().y * 0.5f;
	}


	////////////////////////////////


	bool Button::isClicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event) const
	{
		return (this->isInvaded(mousePosition) && event.type == sf::Event::MouseButtonPressed && event.key.code == button);
	}



	////////////////////////////////////////////////////////////////



	bool Button::isActive() const
	{
		return m_active;
	}


	void Button::setActiveStatus(bool status)
	{
		m_active = status;
	}



	////////////////////////////////////////////////////////////////



	float Button::update(const sf::Vector2f& mousePosition, sf::Event& event, sf::Mouse::Button button, sf::View* view)
	{
		if (m_active)
			m_text.setPosition(static_cast<int>(m_text.getPosition().x), static_cast<int>(m_text.getPosition().y));

		return m_active;
	}



	////////////////////////////////////////////////////////////////



	void Button::render(sf::RenderWindow* window)
	{
		if (m_active)
		{
			if (m_render_order)
			{
				window->draw(m_color_shape);
				window->draw(m_texture_shape);
			}
			else
			{
				window->draw(m_texture_shape);
				window->draw(m_color_shape);
			}

			window->draw(m_text);
		}
	}


	////////////////////////////////


	void Button::reverseRenderOrder()
	{
		// 0: texture -> color
		// 1: color	  -> texture

		m_render_order ^= 1; // flipping booean value
	}


	void Button::setRenderOrder(bool order)
	{
		// 0: texture -> color
		// 1: color	  -> texture

		m_render_order = order;
	}


	bool Button::getRenderOrder()
	{
		return m_render_order;
	}



	////////////////////////////////////////////////////////////////



	void Button::initPhysics()
	{
		m_physics = std::make_unique<Physics>(this);
	}


	void Button::initPhysics(long double mass, float friction)
	{
		m_physics = std::make_unique<Physics>(this, mass, friction);
	}


	void Button::deletePhysics()
	{
		m_physics = nullptr;
	}


	////////////////////////////////


	void Button::updatePhysics(const float dt)
	{
		if (m_physics != nullptr)
			m_physics->update(dt);
		else
			throw_error("Rectangle::updatePhysics(...)", "physics are not initialized yet", "WARNING");
	}


	Physics* Button::physics()
	{
		return m_physics.get();
	}



	////////////////////////////////////////////////////////////////



	bool Button::created() const
	{
		return m_created;
	}


} // namespace ke