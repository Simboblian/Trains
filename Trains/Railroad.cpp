#include "Railroad.h"

void Railroad::AddPoint(sf::Vector2f Position)
{
	TrackPoint* p = new TrackPoint(Position);
	_points.push_back(p);
	if (_points.size() > 1)
	{
		TrackSection* s = new TrackSection(_points.back() - 1, _points.back());
		_sections.push_back(s);
	}
}

void Railroad::Draw(sf::RenderWindow& Window, bool Edit)
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i].Draw(Window, Edit);
	}

	for (int i = 0; i < _sections.size(); i++)
	{
		_sections[i].Draw(Window);
	}
}

void Railroad::Update()
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i].Update();
	}

	for (int i = 0; i < _sections.size(); i++)
	{
		_sections[i].Update();
	}
}

Point Railroad::GetClosestPoint(sf::Vector2f Position)
{
	std::vector<Point*> pointList;

	for (int i = 0; i < _points.size(); i++)
	{
		pointList.push_back(&_points[i]);

		for (int j = 0; j < _points[i].GetControlPoints().size(); j++)
		{
			pointList.push_back(&_points[i].GetControlPoints()[j]);
		}
	}

	Point value = *pointList[0];
	for (int i = 0; i < pointList.size(); i++)
	{
		pointList[i]->GetShape().setOutlineColor(sf::Color::Transparent);
		if (Utility::GetMagnitude(sf::Vector2f(sf::Vector2f(Position.x - pointList[i]->GetPosition().x, Position.y - pointList[i]->GetPosition().y))) < Utility::GetMagnitude(sf::Vector2f(Position.x - value.GetPosition().x, Position.y - value.GetPosition().y)))
			value = *pointList[i];
	}

	return value;
}

Railroad::Railroad()
{
}

Railroad::~Railroad()
{
}
