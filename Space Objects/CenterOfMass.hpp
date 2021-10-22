#pragma once

#include "SpaceObject.hpp"


class CenterOfMass :
    public SpaceObject
{
public:

    CenterOfMass(long double radius = 1.0, float outline_thickness = 1.f);
    virtual ~CenterOfMass();

    bool update(float dt) override;
    void updatePhysicalData() override;

    void render(sf::RenderWindow* window) override;

private:
};

