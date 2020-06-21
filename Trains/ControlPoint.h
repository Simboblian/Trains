#ifndef _CONTROLPOINT_H
#define _CONTROLPOINT_H

#include "Point.h"

class ControlPoint : public Point
{
public:
	ControlPoint(sf::Vector2f Position);
	ControlPoint();
	~ControlPoint();
};

#endif
