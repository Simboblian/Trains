#ifndef _LINE_H
#define _LINE_H

#include "Point.h"

class Line
{
private:
	std::vector<Point*> _points;
public:
	void AddPoint(Point& NewPoint) { _points.push_back(&NewPoint); };
	std::vector<Point*> GetPoints() { return _points; };
	void SetColour(sf::Color Colour);

	Line();
	~Line();
};

#endif