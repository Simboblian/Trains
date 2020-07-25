#ifndef _POINT_H
#define _POINT_H

#include <SFML/Graphics.hpp>
#include "GameEntity.h"

class Point : public GameEntity
{
protected:
	sf::Vector2f _previousPos;
	sf::CircleShape _viewable;
	bool _visible = false;
public:
	virtual void Draw(sf::RenderWindow& Window);
	virtual void Update();

	bool isVisible() { return _visible; };
	sf::CircleShape GetShape() { return _viewable; };
	sf::Vector2f GetPreviousPosition();

	void SetPosition(sf::Vector2f Position) { _position = Position; };
	void SetVisible(bool Visible) { _visible = Visible; };

	virtual void Move(sf::Vector2f Distance) { _position = sf::Vector2f(_position.x + Distance.x, _position.y + Distance.y); };

	Point();
	Point(sf::Vector2f Position);
	~Point();
};

#endif