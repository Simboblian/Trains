#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H

#include "SFML/Graphics.hpp"

enum class Type { GAMEENTITY, POINT, CONTROLPOINT, TRACKPOINT, TRACKSECTION, STATION };

class GameEntity
{
protected:
	Type ObjectType = Type::GAMEENTITY;

	bool _selected = false;
	sf::Vector2f _position = sf::Vector2f(0, 0);
public:
	Type GetType() { return ObjectType; };

	void Select() { _selected = true; };
	void Deselect() { _selected = false; };
	bool isSelected() { return _selected; };

	sf::Vector2f GetPosition() { return _position; };
	virtual void Move(sf::Vector2f Distance) { _position = sf::Vector2f(_position.x + Distance.x, _position.y + Distance.y); };

	virtual void Draw(sf::RenderWindow& Window) {};
	virtual void Update() {};

	GameEntity();
	~GameEntity();
};

#endif