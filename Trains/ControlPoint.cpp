#include "ControlPoint.h"
#include <iostream>

void ControlPoint::SetRotationAroundPoint(float Angle, sf::Vector2f Point)
{
	float magnitude = Utility::GetMagnitude(sf::Vector2f(_position.x - Point.x, _position.y - Point.y));

	sf::Vector2f newPos = sf::Vector2f(magnitude * cos(Angle), magnitude * sin(Angle));

	_position.x = Point.x + newPos.x;
	_position.y = Point.y + newPos.y;
}

float ControlPoint::GetRotationAroundPoint(sf::Vector2f Origin)
{
	float value = Utility::CalculateAngle(Origin, _viewable.getPosition());
	return value;
}

void ControlPoint::RotateAroundPoint(float Rotation, sf::Vector2f Origin)
{
	float _rotation = Rotation;

	float x1 = _position.x - Origin.x;
	float y1 = _position.y - Origin.y;

	float x2 = (x1 * cos(_rotation)) - (y1 * sin(_rotation));
	float y2 = (x1 * sin(_rotation)) + (y1 * cos(_rotation));

	_position = sf::Vector2f(x2 + Origin.x, y2 + Origin.y);
}

ControlPoint::ControlPoint(sf::Vector2f Position)
{
	ObjectType = Type::CONTROLPOINT;

	_position = Position;
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(_position);
	_selected = false;
}

ControlPoint::ControlPoint()
{
	ObjectType = Type::CONTROLPOINT;

	_position = sf::Vector2f(0, 0);
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(_position);
	_selected = false;
}

ControlPoint::~ControlPoint()
{
}
