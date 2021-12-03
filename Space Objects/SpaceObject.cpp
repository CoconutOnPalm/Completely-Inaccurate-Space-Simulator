#include "SpaceObject.hpp"

SpaceObject::SpaceObject()
	: p_type(ObjectType::UNDEFINED)
	, p_class(ObjectClass::CLASS_UNDEFINED)
	, p_subtype(ObjectSubtype::SUBTYPE_UNDEFINED)
	, p_trail(sf::LinesStrip, 256)
	, p_trail_time(0)
{
	object.initPhysics(1.0, 0.0f);
	object.physics()->setTarget(&object);
}

SpaceObject::SpaceObject(long double mass)
	: p_type(ObjectType::UNDEFINED)
	, p_class(ObjectClass::CLASS_UNDEFINED)
	, p_subtype(ObjectSubtype::SUBTYPE_UNDEFINED)
{
	object.initPhysics(mass, 0.0f);
	object.physics()->setTarget(&object);
}

SpaceObject::~SpaceObject()
{

}


unsigned int SpaceObject::p_star_count = 0;


void SpaceObject::updateClickRadius()
{
	if (p_click_radius.getRadius() < object.getRadius())
		p_click_radius.setRadius(object.getRadius());
}

void SpaceObject::updateTrails(float dt, float simulation_speed)
{
	if (p_trail_timer.getElapsedTime().asMicroseconds() >=  dt * 10000 * simulation_speed)
	{
		p_trail_timer.restart();

		sf::Vector2f new_position = p_trail[0].position;
		sf::Vector2f old_position;

		p_trail[0].position = object.getPosition();

		for (int i = 1; i < p_trail.getVertexCount(); ++i)
		{
			old_position = p_trail[i].position;
			p_trail[i].position = new_position;
			new_position = old_position;
		}
	}
}

bool SpaceObject::invaded(const sf::Vector2f& mousePosition)
{
	return (pow(object.getPosition().x - mousePosition.x, 2) + pow(object.getPosition().y - mousePosition.y, 2) < pow(p_click_radius.getRadius(), 2));
}

bool SpaceObject::clicked(sf::Mouse::Button button, const sf::Vector2f& mousePosition, sf::Event& event)
{
	return p_click_radius.isClicked(button, mousePosition, event);
}

void SpaceObject::render(sf::RenderWindow* window)
{
	if (AppSettings::TrailsEnabled())
		window->draw(p_trail);

	p_click_radius.render(window);
	object.render(window);
}


void SpaceObject::setName(const std::string& new_name)
{
	p_name = new_name;
}

std::string SpaceObject::name() const
{
	return p_name;
}

void SpaceObject::setBasicFilename(const std::string& filename)
{
	p_basic_filename = filename;
}

std::string SpaceObject::filename() const
{
	return p_basic_filename;
}

void SpaceObject::setIconFilename(const std::string& filename)
{
	p_icon_filename = filename;
}

std::string SpaceObject::iconFilename() const
{
	return p_icon_filename;
}

void SpaceObject::setType(int type)
{
	if (p_type == ObjectType::STAR && type == ObjectType::STAR)
		return;
	else if (p_type == ObjectType::STAR && type == ObjectType::PLANET)
		p_star_count--;
	else if (p_type == ObjectType::PLANET && type == ObjectType::STAR)
		p_star_count++;

	p_type = type;
}

int SpaceObject::type() const
{
	return p_type;
}

void SpaceObject::setObjectClass(int object_class)
{
	p_class = object_class;
}

int SpaceObject::objectClass() const
{
	return p_class;
}

void SpaceObject::setSubtype(int subtype)
{
	p_subtype = subtype;
}

int SpaceObject::subtype() const
{
	return p_subtype;
}

sf::Shader* SpaceObject::getObjectShader()
{
	return &p_shader;
}

sf::Shader* SpaceObject::getGlowShader()
{
	return &p_glow_shader;
}

unsigned int SpaceObject::getStarCount() const
{
	return p_star_count;
}

ke::Circle* SpaceObject::clickRange()
{
	return &p_click_radius;
}
