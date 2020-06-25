#include "ControlPoint.h"
#include <iostream>

float ControlPoint::GetRotationAroundPoint(sf::Vector2f Origin)
{
	float value = Utility::CalculateAngle(Origin, _viewable.getPosition()); //_position isn't used here because we need to get the change in rotation
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
