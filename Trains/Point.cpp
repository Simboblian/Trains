#include "Point.h"

void Point::Draw(sf::RenderWindow& Window)
{
	Window.draw(_viewable);
}

void Point::Update()
{
	_viewable.setPosition(_position);
	if (isSelected())
		_viewable.setOutlineColor(sf::Color::Green);
	else
		_viewable.setOutlineColor(sf::Color::Transparent);
}

Point::Point()
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

Point::Point(sf::Vector2f Position)
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

Point::~Point()
{
}
