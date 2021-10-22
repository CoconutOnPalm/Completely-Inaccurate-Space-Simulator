#pragma once

#include "ObjectIcon.hpp"
#include "States/Modules/VisibleDataController.hpp"

#define objvector std::vector<std::unique_ptr<SpaceObject>>

class ObjectIcon;


class ObjectBuffer
{
public:

	ObjectBuffer();
	ObjectBuffer(const ObjectIcon& object_icon);
	ObjectBuffer(int type, int _class, int subtype, long double mass, long double radius, const std::string& name, const std::string& filename, const std::string& icon_filename, float brightness, const sf::Vector3f& color);

	void load(const ObjectIcon& object_icon);
	void load(objvector::iterator selected_object);
	void load(int type, int _class, int subtype, long double mass, long double radius, const std::string& name, const std::string& filename, const std::string& icon_filename, float brightness, const sf::Vector3f& color);

	long double mass() const;
	void mass(long double mass);

	long double radius() const;
	void radius(long double radius);

	float brightness() const;
	void brightness(float val);

	sf::Vector3f color() const;
	void color(const sf::Vector3f& rgb);

	int type() const;
	void type(int type);

	int objectClass() const;
	void objectClass(int _class);

	int subtype() const;
	void subtype(int subtype);

	std::string name() const;
	void name(const std::string& name);

	std::string filename() const;
	void filename(const std::string& filename);

	std::string iconFilename() const;
	void iconFilename(const std::string& icon_filename);

private:


	long double m_mass;
	long double m_radius;
	float m_brightness;
	sf::Vector3f m_color;

	int m_type;
	int m_class;
	int m_subtype;

	std::string m_name;
	std::string m_filename;

	std::string m_icon_filename;
};