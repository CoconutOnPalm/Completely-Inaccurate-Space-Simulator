#pragma once

#include <KEngine/Graphics.hpp>

#include "ConstObjectData.hpp"
#include "Equasions/Constants.hpp"
#include "Equasions/Equasions.hpp"


struct PhysicalData
{
	PhysicalData()
		: total_force(0.0, 0.0)
		, velocity(0.0, 0.0)
		, mass(1)
		, radius(1)
		, schwarzschild_radius(0)
		, gravitational_field_intensity(0)
		, first_space_speed(0)
		, second_space_speed(0)
		, rotation_speed(0.f)
	{};

	sf::Vector2<double> total_force;
	sf::Vector2<double> velocity;

	long double mass;
	long double radius;

	long double schwarzschild_radius;

	long double gravitational_field_intensity;
	long double first_space_speed;
	long double second_space_speed;

	float rotation_speed;

	float brightness;
	sf::Vector3f color;
};



class SpaceObject
{
public:

	SpaceObject();
	SpaceObject(long double mass);
	virtual ~SpaceObject();


	virtual bool update(float dt) = 0;
	virtual void updatePhysicalData() = 0;
	virtual void updateClickRadius();

	virtual bool invaded(const sf::Vector2f& mousePosition);
	virtual bool clicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition,  sf::Event& event);

	virtual void render(sf::RenderWindow* window);
	
	//virtual ke::Circle* object();
	//virtual PhysicalData* data();

	virtual void setName(const std::string& new_name);
	virtual std::string name() const;

	virtual void setBasicFilename(const std::string& filename);
	virtual std::string filename() const;

	virtual void setIconFilename(const std::string& filename);
	virtual std::string iconFilename() const;

	virtual void setType(int type);
	virtual int type() const;

	virtual void setObjectClass(int object_class);
	virtual int objectClass() const;

	virtual void setSubtype(int subtype);
	virtual int subtype() const;

	virtual sf::Shader* getObjectShader();
	virtual sf::Shader* getGlowShader();

	unsigned int getStarCount() const;

	ke::Circle* clickRange();


	ke::Circle object;
	PhysicalData data;


protected:


	std::string p_name;
	std::string p_basic_filename;
	std::string p_icon_filename;

	int p_type;
	int p_class;
	int p_subtype;

	static unsigned int p_star_count;

	ke::Circle p_click_radius;

	sf::Shader p_shader;
	sf::Shader p_glow_shader;

private:

	
};

