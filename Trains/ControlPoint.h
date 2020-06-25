#ifndef _CONTROLPOINT_H
#define _CONTROLPOINT_H

#include "Point.h"
#include "Utility.h"

//Must live in a TrackPoint

class ControlPoint : public Point
{
public:
	float GetRotationAroundPoint(sf::Vector2f Origin);
	void RotateAroundPoint(float Rotation, sf::Vector2f Origin);

	ControlPoint(sf::Vector2f Position);
	ControlPoint();
	~ControlPoint();
};

#endif
