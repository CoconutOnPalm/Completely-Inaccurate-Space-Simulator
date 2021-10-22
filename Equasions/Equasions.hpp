#pragma once

#include "Constants.hpp"
#include <cmath>


inline long double gravitational_force(long double m1, long double m2, long double r)
{
	return (G * m1 * m2) / (r * r);
}

inline long double gravitational_force_2(long double m1, long double m2, long double r2)
{
	return G * (m1 * m2) / r2;
}


inline long double round_orbit_velocity(long double M, long double r)
{
	return std::sqrt(G * M / r);
}


inline long double gravitational_field_intensity(long double M, long double r)
{
	return (G * M) / (r * r);
}


inline long double first_space_speed(long double M, long double r)
{
	return std::sqrt((G * M) / r);
}

inline long double second_space_speed(long double M, long double r)
{
	return std::sqrt((2 * G * M) / r);
}


inline long double surface_gravity(long double M, long double r)
{
	return G * M / (r * r);
}


inline long double schwarzschild_radius(long double M, long double r)
{
	return 2 * G * M / (c * c);
}


template <typename T1, typename T2>
inline long double position_to_destance(const sf::Vector2<T1>& vector1, const sf::Vector2<T2>& vector2)
{
	return std::sqrt(std::pow(vector2.x - vector1.x, 2) + std::pow(vector2.y - vector1.y, 2));
}


inline long double Volume(long double radius)
{
	return 1.33333333333333333 * PI * radius * radius * radius;
}