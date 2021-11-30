#include "ObjectIcon.hpp"

ObjectIcon::ObjectIcon()
{

}

ObjectIcon::ObjectIcon(
	const std::string& icon_filename,
	const std::string& object_filename,
	const sf::Vector2f& size, 
	const sf::Vector2f& position,
	const std::string& obj_name,
	int type,
	int _class,
	int subtype,
	long double obj_mass, 
	long double obj_radius,
	float brightness,
	const sf::Vector3f& color)

	: m_filename(object_filename)
	, m_icon_filename(icon_filename)
	, m_name(obj_name)

	, m_obj_type(type)
	, m_obj_class(_class)
	, m_obj_subtype(subtype)

	, m_obj_mass(obj_mass)
	, m_obj_radius(obj_radius)

	, m_obj_brightness(brightness)
	, m_obj_color(color)
{
	if (!obj_texture.loadFromFile(icon_filename))
	{
		ke::throw_error("ObjectIcon::ObjectIcon(...)", "could not load object texture", "ERROR");
		obj_texture.loadFromFile(ke::Settings::EmptyTexturePath());
	}
	else
	{
		obj_texture.setSmooth(true);
	}

	icon.create(size, position, ke::Origin::LEFT_TOP, &obj_texture);
}

ObjectIcon::~ObjectIcon()
{

}

ObjectIcon& ObjectIcon::operator= (ObjectIcon& right)
{
	sf::Vector2f posbuff = icon.getPosition();
	icon = right.icon;
	icon.setPosition(posbuff);
	obj_texture = right.obj_texture;
	//icon.setTexture();
	icon.getTextureShape()->setFillColor(sf::Color::White);

	m_filename = right.filename();
	m_icon_filename = right.iconFilename();
	m_name = right.object_name();

	m_obj_type = right.type();
	m_obj_class = right.object_class();
	m_obj_subtype = right.subtype();

	m_obj_radius = right.radius();
	m_obj_mass = right.mass();

	m_obj_brightness = right.brightness();
	m_obj_color = right.color();


	//icon.setOrigin(ke::Origin::MIDDLE_MIDDLE);

	return *this;
}

ObjectIcon::ObjectIcon(ObjectIcon& right)
{
	//sf::Vector2f posbuff = icon.getPosition();
	icon = right.icon;
	//icon.setPosition(posbuff);
	//obj_texture = right.obj_texture;
	//icon.setTexture();`
	//icon.getTextureShape()->setFillColor(sf::Color::White);

	m_filename = right.filename();
	m_icon_filename = right.iconFilename();
	m_name = right.object_name();

	m_obj_type = right.type();
	m_obj_class = right.object_class();
	m_obj_subtype = right.subtype();

	m_obj_radius = right.radius();
	m_obj_mass = right.mass();

	m_obj_brightness = right.brightness();
	m_obj_color = right.color();
}


void ObjectIcon::load(const std::string& icon_filename,
	const std::string& object_filename,
	const std::string& obj_name,
	int type,
	int _class,
	int subtype,
	long double obj_mass,
	long double obj_radius,
	float brightness,
	const sf::Vector3f& color)
{
	m_filename = object_filename;
	m_icon_filename = icon_filename;
	m_name = obj_name;

	m_obj_type = type;
	m_obj_class= _class;
	m_obj_subtype = subtype;

	m_obj_mass = obj_mass;
	m_obj_radius = obj_radius;

	m_obj_brightness = brightness;
	m_obj_color = color;

	//std::cout << m_icon_filename << '\n';

	if (!obj_texture.loadFromFile(icon_filename))
	{
		ke::throw_error("ObjectIcon::load(...)", "could not load object texture", "ERROR");
		obj_texture.loadFromFile(ke::Settings::EmptyTexturePath());
	}
	else
	{
		//icon.setTexture(&obj_texture);
		obj_texture.setSmooth(true);
	}

	icon.setTexture(m_icon_filename);

	//std::cout << "icon changed\n";
}

void ObjectIcon::load(const ObjectBuffer& buffer)
{
	m_filename = buffer.filename();
	m_icon_filename = buffer.iconFilename();
	m_name = buffer.name();

	m_obj_type = buffer.type();
	m_obj_class = buffer.objectClass();
	m_obj_subtype = buffer.subtype();


	//std::cout << "type: " << buffer.type() << '\n';

	m_obj_mass = buffer.mass();
	m_obj_radius = buffer.radius();

	m_obj_brightness = buffer.brightness();
	m_obj_color = buffer.color();

	//std::cout << m_icon_filename << '\n';

	if (!obj_texture.loadFromFile(m_icon_filename))
	{
		ke::throw_error("ObjectIcon::load(...)", "could not load object texture", "ERROR");
		obj_texture.loadFromFile(ke::Settings::EmptyTexturePath());
	}
	else
	{
		//icon.setTexture(&obj_texture);
		obj_texture.setSmooth(true);
	}

	icon.setTexture(m_icon_filename);

	//std::cout << "loaded\n";
}


std::string ObjectIcon::filename() const
{
	return m_filename;
}

std::string ObjectIcon::object_name() const
{
	return m_name;
}

long double ObjectIcon::radius() const
{
	return m_obj_radius;
}

long double ObjectIcon::mass() const
{
	return m_obj_mass;
}

int ObjectIcon::type() const
{
	return m_obj_type;
}

int ObjectIcon::object_class() const
{
	return m_obj_class;
}

int ObjectIcon::subtype() const
{
	return m_obj_subtype;
}

float ObjectIcon::brightness() const
{
	return m_obj_brightness;
}

sf::Vector3f ObjectIcon::color() const
{
	return m_obj_color;
}

std::string ObjectIcon::iconFilename() const
{
	return m_icon_filename;
}