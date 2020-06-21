#include "ControlPoint.h"

ControlPoint::ControlPoint(sf::Vector2f Position)
{
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(Position);
	_selected = false;
}

ControlPoint::ControlPoint()
{
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_selected = false;
}

ControlPoint::~ControlPoint()
{
}
