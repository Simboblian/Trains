#ifndef _TRACKSECTION_H
#define _TRACKSECTION_H

#include <SFML/Graphics.hpp>
#include "TrackPoint.h"
#include "GameEntity.h"

#define RESOLUTION 32

//possibly keep track of the angle (tightness) of the curve so that it doesn't become impassable.
class TrackSection : public GameEntity
{
protected:
	std::vector<Point*> _controlPoints;
	sf::VertexArray _viewable;
	sf::Color _colour;

	void CalculateLine();
public:
	std::vector<Point*> GetControlPoints() { return _controlPoints; };

	std::vector<sf::Vector2f> GetVertexPoints();
	sf::FloatRect GetBounds() { return _viewable.getBounds(); };

	void SetColour(sf::Color Colour);

	void Draw(sf::RenderWindow& Window);
	void Update();

	TrackSection(TrackPoint& tPointA, TrackPoint& tPointB);
	TrackSection();
	~TrackSection();
};

#endif