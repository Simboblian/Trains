#ifndef _LINEPOINT_H
#define _LINEPOINT_H

#include "Point.h"
#include "ControlPoint.h"
#include "Utility.h"

class TrackPoint : public Point
{
private:
	std::vector<ControlPoint*> _controlPoints;
	std::vector<sf::VertexArray> _controlConnectors;
public:
	void Draw(sf::RenderWindow& Window, bool Edit);
	void Update();

	bool isAnySelected();

	std::vector<ControlPoint*> GetControlPoints() { return _controlPoints; };
	void Move(sf::Vector2f Distance);

	TrackPoint(sf::Vector2f Position);

	TrackPoint();
	~TrackPoint();
};

#endif

