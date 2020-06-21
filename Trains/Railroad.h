#ifndef _RAILROAD_H
#define _RAILROAD_H

#include "TrackPoint.h"
#include "TrackSection.h"

class Railroad
{
private:
	std::vector<TrackPoint*> _points;
	std::vector<TrackSection*> _sections;
public:
	void AddPoint(sf::Vector2f Position);
	void Draw(sf::RenderWindow& Window, bool Edit);
	void Update();

	Point GetClosestPoint(sf::Vector2f Position);

	Railroad();
	~Railroad();
};

#endif