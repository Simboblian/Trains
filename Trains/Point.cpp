#include "Point.h"

void Point::Draw(sf::RenderWindow& Window)
{
	if(_visible)
		Window.draw(_viewable);
}

void Point::Update()
{
	_previousPos = _viewable.getPosition();
	_viewable.setPosition(_position);
	if (isSelected())
		_viewable.setOutlineColor(sf::Color::Green);
	else
		_viewable.setOutlineColor(sf::Color::Transparent);
}

sf::Vector2f Point::GetPreviousPosition()
{
	return _previousPos;
}

Point::Point()
{
	ObjectType = Type::POINT;

	_position = sf::Vector2f(0, 0);
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(_position);
}

Point::Point(sf::Vector2f Position)
{
	ObjectType = Type::POINT;

	_position = Position;
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(_position);
}

Point::~Point()
{
}
