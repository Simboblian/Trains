#include "Point.h"

void Point::Draw(sf::RenderWindow& Window)
{
	Window.draw(_viewable);
}

void Point::Update()
{
	if (_selected)
		_viewable.setOutlineColor(sf::Color::Red);
	else
		_viewable.setOutlineColor(sf::Color::Transparent);
}

Point::Point()
{
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_selected = false;
}

Point::Point(sf::Vector2f Position)
{
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(Position);
	_selected = false;
}

Point::~Point()
{
}
