#include "ObjectBuffer.hpp"

ObjectBuffer::ObjectBuffer()
	: m_mass(0.0)
	, m_radius(0.0)
	, m_type(ObjectType::UNDEFINED)
	, m_class(ObjectClass::CLASS_UNDEFINED)
	, m_subtype(ObjectSubtype::SUBTYPE_UNDEFINED)
	, m_brightness(0.0)
	, m_color(sf::Vector3f(1.0, 1.0, 1.0))
{

}

ObjectBuffer::ObjectBuffer(const ObjectIcon& object_icon)
{
	m_type = object_icon.type();
	m_class = object_icon.object_class();
	m_subtype = object_icon.subtype();

	m_mass = object_icon.mass();
	m_radius = object_icon.radius();

	m_brightness = object_icon.brightness();
	m_color = object_icon.color();

	m_name = object_icon.object_name();
	m_filename = object_icon.filename();
	m_icon_filename = object_icon.iconFilename();
}

ObjectBuffer::ObjectBuffer(int type, int _class, int subtype, long double mass, long double radius, const std::string& name, const std::string& filename, const std::string& icon_filename, float brightness, const sf::Vector3f& color)
{
	m_type = type;
	m_class = _class;
	m_subtype = subtype;

	m_mass = mass;
	m_radius = radius;

	m_brightness = brightness;
	m_color = color;

	m_name = name;
	m_filename = filename;
	m_icon_filename = icon_filename;
}

void ObjectBuffer::load(const ObjectIcon& object_icon)
{
	m_type = object_icon.type();
	m_class = object_icon.object_class();
	m_subtype = object_icon.subtype();

	m_mass = object_icon.mass();
	m_radius = object_icon.radius();

	m_brightness = object_icon.brightness();
	m_color = object_icon.color();

	m_name = object_icon.object_name();
	m_filename = object_icon.filename();
	m_icon_filename = object_icon.iconFilename();
}

void ObjectBuffer::load(objvector::iterator selected_object)
{
	m_type = (*selected_object)->type();
	m_class = (*selected_object)->objectClass();
	m_subtype = (*selected_object)->subtype();

	m_mass = (*selected_object)->data.mass;
	m_radius = (*selected_object)->data.radius;

	m_brightness = (*selected_object)->data.brightness;
	m_color = (*selected_object)->data.color;

	m_name = (*selected_object)->name();
	m_filename = (*selected_object)->filename();
	m_icon_filename = (*selected_object)->iconFilename();
}

void ObjectBuffer::load(int type, int _class, int subtype, long double mass, long double radius, const std::string& name, const std::string& filename, const std::string& icon_filename, float brightness, const sf::Vector3f& color)
{
	m_type = type;
	m_class = _class;
	m_subtype = subtype;

	m_mass = mass;
	m_radius = radius;

	m_brightness = brightness;
	m_color = color;

	m_name = name;
	m_filename = filename;
	m_icon_filename = icon_filename;
}

long double ObjectBuffer::mass() const
{
	return m_mass;
}

void ObjectBuffer::mass(long double mass)
{
	m_mass = mass;
}

long double ObjectBuffer::radius() const
{
	return m_radius;
}

void ObjectBuffer::radius(long double radius)
{
	m_radius = radius;
}

float ObjectBuffer::brightness() const
{
	return m_brightness;
}

void ObjectBuffer::brightness(float val)
{
	m_brightness = val;
}

sf::Vector3f ObjectBuffer::color() const
{
	return m_color;
}

void ObjectBuffer::color(const sf::Vector3f& rgb)
{
	m_color = rgb;
}

int ObjectBuffer::type() const
{
	return m_type;
}

void ObjectBuffer::type(int type)
{
	m_type = type;
}

int ObjectBuffer::objectClass() const
{
	return m_class;
}

void ObjectBuffer::objectClass(int _class)
{
	m_class = _class;
}

int ObjectBuffer::subtype() const
{
	return m_subtype;
}

void ObjectBuffer::subtype(int subtype)
{
	m_subtype = subtype;
}

std::string ObjectBuffer::name() const
{
	return m_name;
}

void ObjectBuffer::name(const std::string& name)
{
	m_name = name;
}

std::string ObjectBuffer::filename() const
{
	return m_filename;
}

void ObjectBuffer::filename(const std::string& filename)
{
	m_filename = filename;
}

std::string ObjectBuffer::iconFilename() const
{
	return m_icon_filename;
}

void ObjectBuffer::iconFilename(const std::string& icon_filename)
{
	m_icon_filename = icon_filename;
}
