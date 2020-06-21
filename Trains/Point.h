#ifndef _POINT_H
#define _POINT_H

#include <SFML/Graphics.hpp>

// Each line point needs to have 2 (or more) control points eg. O--------O--------O
// More than 2 control points would only appear at juctions.

class Point
{
protected:
	sf::CircleShape _viewable;

	bool _selected;
public:
	virtual void Draw(sf::RenderWindow& Window);
	virtual void Update();
	void Select() { _selected = true; };
	void Deselect() { _selected = false; };
	bool isSelected() { return _selected; };

	sf::Vector2f GetPosition() { return _viewable.getPosition(); };
	void SetPosition(sf::Vector2f Position) { _viewable.setPosition(Position); };
	sf::CircleShape GetShape() { return _viewable; };

	Point();
	Point(sf::Vector2f Position);
	~Point();
};

#endif