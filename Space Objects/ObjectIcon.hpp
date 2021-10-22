#pragma once

#include "KEngine/Graphics.hpp"
#include "Space Objects/ObjectBuffer.hpp"

class ObjectBuffer;


class ObjectIcon
{
public:

	ObjectIcon();

	ObjectIcon(
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
		const sf::Vector3f& color);

	~ObjectIcon();

	ObjectIcon& operator= (ObjectIcon& right);

	void load(const std::string& icon_filename,
		const std::string& object_filename,
		const std::string& obj_name,
		int type,
		int _class,
		int subtype,
		long double obj_mass,
		long double obj_radius,
		float brightness,
		const sf::Vector3f& color);

	void load(const ObjectBuffer& buffer);

	std::string filename() const;
	std::string object_name() const;
	long double radius() const;
	long double mass() const;
	int type() const;
	int object_class() const;
	int subtype() const;
	float brightness() const;
	sf::Vector3f color() const;

	std::string iconFilename() const;

	ke::Button icon;
	sf::Texture obj_texture;

private:


	std::string m_filename;
	std::string m_name;

	long double m_obj_radius;
	long double m_obj_mass;
	float m_obj_brightness;
	sf::Vector3f m_obj_color;

	int m_obj_type;
	int m_obj_class;
	int m_obj_subtype;

	std::string m_icon_filename;
};

