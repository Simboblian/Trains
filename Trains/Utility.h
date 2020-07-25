#ifndef _UTILITY_H
#define _UTILITY_H

#include <SFML/Graphics.hpp>

#define PI 3.14159265359f

static class Utility
{
public:
	static float GetMagnitude(sf::Vector2f v)
	{
		return sqrt((v.x * v.x) + (v.y * v.y));
	};

	static float GetDistance(sf::Vector2f PosA, sf::Vector2f PosB)
	{
		sf::Vector2f v = sf::Vector2f(PosA.x - PosB.x, PosA.y - PosB.y);

		return sqrt((v.x * v.x) + (v.y * v.y));
	};

	static float CalculateAngle(sf::Vector2f PosA, sf::Vector2f PosB)
	{
		return atan2((PosB.y - PosA.y), (PosB.x - PosA.x));
	};

	static bool PointInBounds(sf::Vector2f p, sf::FloatRect b)
	{
		if ((p.x >= b.left) && (p.x <= b.left + b.width))
			if ((p.y >= b.top) && (p.y <= b.top + b.height))
				return true;
		return false;
	};
};

#endif