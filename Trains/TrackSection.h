#ifndef _TRACKSECTION_H
#define _TRACKSECTION_H

#include <SFML/Graphics.hpp>
#include "TrackPoint.h"

#define RESOLUTION 32

//possibly keep track of the angle (tightness) of the curve so that it doesn't become impassable.
class TrackSection
{
private:
	std::vector<Point*> _controlPoints;
	std::vector<sf::VertexArray> _controlLines;
	sf::VertexArray _line;
	bool _selected = false;

	Point CreateControl(sf::Vector2f Position);

	void CalculateLine();

public:
	void Select() { _selected = true; };
	void Deselect() { _selected = false; };
	bool isSelected() { return _selected; };

	void MovePoint(sf::Vector2f oldPos, sf::Vector2f currentPos);
	void Draw(sf::RenderWindow& Window);
	void Update();

	TrackSection(TrackPoint& tPointA, TrackPoint& tPointB);
	TrackSection();
	~TrackSection();
};

#endif