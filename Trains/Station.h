#ifndef _STATION_H
#define _STATION_H

#include "TrackSection.h"
#include "TrackPoint.h"

#define THICKNESS 10

class Station : public TrackSection
{
private:
	sf::RectangleShape* _platform;

public:
	void Draw(sf::RenderWindow& Window);
	void Update();

	Station(TrackPoint& tPointA, TrackPoint& tPointB);
	Station();
	~Station();
};

#endif