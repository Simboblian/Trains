#ifndef _UTILITY_H
#define _UTILITY_H

#include <SFML/Graphics.hpp>

static class Utility
{
public:
	static float GetMagnitude(sf::Vector2f v) { return sqrt((v.x * v.x) + (v.y * v.y)); };
};

#endif