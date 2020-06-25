#ifndef _POINT_H
#define _POINT_H

#include <SFML/Graphics.hpp>

class Point
{
protected:
	sf::CircleShape _viewable;
	sf::Vector2f _position;

	bool _selected;
public:
	virtual void Draw(sf::RenderWindow& Window);
	virtual void Update();
	void Select() { _selected = true; };
	void Deselect() { _selected = false; };
	bool isSelected() { return _selected; };

	sf::Vector2f GetPosition() { return _position; };
	void SetPosition(sf::Vector2f Position) { _position = Position; };
	sf::CircleShape GetShape() { return _viewable; };

	virtual void Move(sf::Vector2f Distance) { _position = sf::Vector2f(_position.x + Distance.x, _position.y + Distance.y); };

	Point();
	Point(sf::Vector2f Position);
	~Point();
};

#endif