#include "Planet.hpp"

Planet::Planet(
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

    p_type = PLANET;
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

    p_click_radius.getShape()->setPointCount(64);
    //p_click_radius.setActiveStatus(false);


    for (int i = 0; i < p_trail.getVertexCount(); ++i)
    {
        p_trail[i].color = sf::Color(64, 64, 255, 255 - ((256.f / AppSettings::TrailSize())) * i);
        p_trail[i].position = position;
    }


    p_name_tag.create({ 10, 10 }, position, ke::Origin::LEFT_BOTTOM, ke::fixed::stow(p_name), 8, ke::Origin::LEFT_BOTTOM, sf::Color::Transparent, sf::Color(128, 128, 255, 255));
}

Planet::Planet(const Planet& other)
{
    p_name = other.name(); // default name
    p_basic_filename = other.filename();
    p_icon_filename = other.iconFilename();

    p_type = PLANET;
    p_class = other.objectClass();
    p_subtype = other.subtype();

    object.physics()->setMass(other.data.mass);

    object.physics()->setSpeed(data.velocity);

    data.mass = other.data.mass;
    data.radius = other.data.radius;
    data.brightness = other.data.brightness;
    data.color = other.data.color;
    //data.gravitational_field_intensity = gravitational_field_intensity(data.mass, data.radius);
    //data.first_space_speed = gravitational_field_intensity(data.mass, data.radius);
    //data.second_space_speed = gravitational_field_intensity(data.mass, data.radius);

    this->updatePhysicalData();


    object.create(other.data.radius, other.object.getPosition(), ke::Origin::MIDDLE_MIDDLE, other.filename());


    p_click_radius.create(0, other.object.getPosition(), ke::Origin::MIDDLE_MIDDLE, L"", 0, ke::Origin::MIDDLE_MIDDLE,
        sf::Color::Transparent, sf::Color::Transparent, 0, sf::Color(128, 128, 128, 64));

    p_click_radius.getShape()->setPointCount(64);
    //p_click_radius.setActiveStatus(false);


    for (int i = 0; i < p_trail.getVertexCount(); ++i)
    {
        p_trail[i].color = sf::Color(64, 64, 255, 255 - ((256.f / AppSettings::TrailSize())) * i);
        p_trail[i].position = other.object.getPosition();
    }


    p_name_tag.create({ 10, 10 }, other.object.getPosition(), ke::Origin::LEFT_BOTTOM, ke::fixed::stow(p_name), 8, ke::Origin::LEFT_BOTTOM, sf::Color::Transparent, sf::Color(128, 128, 255, 255));
}

Planet::~Planet()
{

}

bool Planet::update(float dt)
{
    //ke::SmoothRotation(&object, 359, data.rotation_speed, dt);
    object.updatePhysics(dt);
    
    // if (p_click_radius.isActive())
    p_click_radius.setPosition(object.getPosition());

    return false;
}

void Planet::updatePhysicalData()
{
    data.schwarzschild_radius = schwarzschild_radius(data.mass);

    data.gravitational_field_intensity = gravitational_field_intensity(data.mass, data.radius);
    data.first_space_speed = gravitational_field_intensity(data.mass, data.radius);
    data.second_space_speed = gravitational_field_intensity(data.mass, data.radius);
}