#pragma once

#include "SpaceObject.hpp"


class Star :
    public SpaceObject
{
public:

    Star(
        const sf::Vector2f& position,
        const std::string& name,
        const std::string& filename,
        const std::string& icon_filename,
        int _class,
        int subtype,
        long double mass = 1.0,
        long double radius = 1.0,
        long double click_radius = 1.0,
        long double click_radius_thickness = 1.0,
        float rotation_speed = 0.f,
        const sf::Vector2<double>& start_velocity = sf::Vector2<double>(0, 0),
        float brightness = 100,
        const sf::Vector3f& color = sf::Vector3f(1.0, 1.0, 1.0));

    Star(const Star& other);

    virtual ~Star();

    bool update(float dt) override;
    void updatePhysicalData() override;

private:

    static sf::Clock s_clock;
    static float s_time;

};

