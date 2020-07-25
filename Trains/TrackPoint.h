#ifndef _LINEPOINT_H
#define _LINEPOINT_H

#include "Point.h"
#include "ControlPoint.h"
#include "Utility.h"

#define DEFAULTCONTROLOFFSET 50.0f

class TrackPoint : public Point
{
private:
	std::vector<ControlPoint*> _controlPoints;
	std::vector<sf::VertexArray> _controlConnectors;

	float _rotation;

	bool _connected = false;
	bool _rotatable = true;
	bool _stopRotation = false;
	bool _movable = true;
public:
	void Rotate(float Angle);

	void Draw(sf::RenderWindow& Window);
	void Update();

	bool isAnySelected();
	bool isConnected() { return _connected; };
	void SetConnection(bool Connected) { _connected = Connected; };
	void StopRotation();

	std::vector<ControlPoint*> GetControlPoints() { return _controlPoints; };
	void Move(sf::Vector2f Distance);

	TrackPoint(sf::Vector2f Position);

	TrackPoint();
	~TrackPoint();
};

#endif

