#include "Star.hpp"

Star::Star(
	const sf::Vector2f& position,
	const std::string& name,
	const std::string& filename,
	const std::string& icon_filename,
	int _class,
	int subtype,
	long double mass,
	long double radius,
	long double click_radius,
	long double click_radius_thickness,
	float rotation_speed,
	const sf::Vector2<double>& start_velocity,
	float brightness,
	const sf::Vector3f& color)
{
	p_name = name; // default name
	p_basic_filename = filename;
	p_icon_filename = icon_filename;
	p_star_count++;

	p_type = STAR;
	p_class = _class;
	p_subtype = subtype;

	object.physics()->setMass(mass);

	object.physics()->setSpeed(data.velocity);

	data.mass = mass;
	data.radius = radius;
	data.brightness = brightness;
	data.color = color;
	//data.gravitational_field_intensity = gravitational_field_intensity(data.mass, data.radius);
	//data.first_space_speed = gravitational_field_intensity(data.mass, data.radius);
	//data.second_space_speed = gravitational_field_intensity(data.mass, data.radius);

	this->updatePhysicalData();


	object.create(radius, position, ke::Origin::MIDDLE_MIDDLE, filename);

	if (click_radius < radius)
		click_radius = radius;

	p_click_radius.create(click_radius, position, ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::MIDDLE_MIDDLE,
		sf::Color::Transparent, sf::Color::Transparent, click_radius_thickness, sf::Color(128, 128, 128, 64));

	p_click_radius.getShape()->setPointCount(128);

	if (_class == ObjectClass::CLASS_NEUTRON_STAR)
	{
		float rotation_speed;

		if (subtype == ObjectSubtype::SUBTYPE_PULSAR || subtype == ObjectSubtype::SUBTYPE_PULSAR_AND_MAGNETAR)
			rotation_speed = 100;
		else
			rotation_speed = 10;

		p_shader.loadFromFile("Textures/Shaders/neutron_star_shader.frag", sf::Shader::Fragment);
		p_shader.setUniform("light_sharpness_modifier", 1024.f);
		p_shader.setUniform("size", 0.f);
		p_shader.setUniform("basic_a", 1.f);
		p_shader.setUniform("basic_color", sf::Glsl::Vec3(color));
		p_shader.setUniform("position", sf::Glsl::Vec2(0, 0));
		p_shader.setUniform("rotation_speed", rotation_speed);
		p_shader.setUniform("max_rotation_angle", .05f);
	}
	else
	{
		p_shader.loadFromFile("Textures/Shaders/star_shader.frag", sf::Shader::Fragment);
		p_shader.setUniform("light_sharpness_modifier", 128.f);
		p_shader.setUniform("size", brightness);
		p_shader.setUniform("basic_a", 1.f);
		p_shader.setUniform("basic_color", sf::Glsl::Vec3(color));
		p_shader.setUniform("position", sf::Glsl::Vec2(0, 0));
	}

	p_glow_shader.loadFromFile("Textures/Shaders/glow.frag", sf::Shader::Fragment);
	p_glow_shader.setUniform("position", sf::Glsl::Vec2(0, 0));
	p_glow_shader.setUniform("size", 0.f);
	p_glow_shader.setUniform("color", sf::Glsl::Vec3(color));
	p_glow_shader.setUniform("basic_a", 0.4f);
}

Star::~Star()
{

}


sf::Clock Star::s_clock;
float Star::s_time = 0;


bool Star::update(float dt)
{
	if (p_class == ObjectClass::CLASS_NEUTRON_STAR)
	{
		s_time = s_clock.restart().asMilliseconds();
		p_shader.setUniform("time", s_time);
	}



	//ke::SmoothRotation(&object, 360, data.rotation_speed, dt);
	object.updatePhysics(dt);

	//if (p_click_radius.isActive())
	p_click_radius.setPosition(object.getPosition());

	return false;
}

void Star::updatePhysicalData()
{
	data.schwarzschild_radius = schwarzschild_radius(data.mass, data.radius);

	data.gravitational_field_intensity = gravitational_field_intensity(data.mass, data.radius);
	data.first_space_speed = gravitational_field_intensity(data.mass, data.radius);
	data.second_space_speed = gravitational_field_intensity(data.mass, data.radius);
}
