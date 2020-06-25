#include "Line.h"

void Line::SetColour(sf::Color Colour)
{
	for (int i = 0; i < _points.size(); i++)
	{
		//get the colloour
	}
}

Line::Line()
{
	_points = std::vector<Point*>();
}

Line::~Line()
{
}
