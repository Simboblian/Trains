#include "TrackSection.h"

Point TrackSection::CreateControl(sf::Vector2f Position)
{
	return Point(Position);
}

void TrackSection::CalculateLine()
{
	_line = sf::VertexArray(sf::PrimitiveType::LineStrip);

	for (int i = 0; i < RESOLUTION; i++)
	{
		float t = (float)i / (float)RESOLUTION;
		sf::Vector2f point;

		point.x = pow((1 - t), 3) * _controlPoints[0]->GetPosition().x
			+ 3 * pow((1 - t), 2) * t * _controlPoints[2]->GetPosition().x
			+ 3 * (1 - t) * pow(t, 2) * _controlPoints[3]->GetPosition().x
			+ pow(t, 3) * _controlPoints[1]->GetPosition().x;

		point.y = pow((1 - t), 3) * _controlPoints[0]->GetPosition().y
			+ 3 * pow((1 - t), 2) * t * _controlPoints[2]->GetPosition().y
			+ 3 * (1 - t) * pow(t, 2) * _controlPoints[3]->GetPosition().y
			+ pow(t, 3) * _controlPoints[1]->GetPosition().y;

		_line.append(sf::Vertex(*new sf::Vector2f(point), sf::Color::Cyan));
	}

	_line.append(sf::Vertex(*new sf::Vector2f(_controlPoints[1]->GetPosition()), sf::Color::Cyan));
}

void TrackSection::MovePoint(sf::Vector2f oldPos, sf::Vector2f currentPos)
{
	for (int i = 0; i < _controlPoints.size(); i++)
	{
		if (_controlPoints[i]->isSelected())
		{
			sf::Vector2f diff = sf::Vector2f((currentPos.x - oldPos.x), (currentPos.y - oldPos.y));

			sf::Vector2f newPos = sf::Vector2f(_controlPoints[i]->GetPosition().x + diff.x, _controlPoints[i]->GetPosition().y + diff.y);
			
			_controlPoints[i]->SetPosition(newPos);

			CalculateLine();
		}
	}
}

void TrackSection::Draw(sf::RenderWindow& Window)
{
	if (_line.getVertexCount() > 0)
		Window.draw(_line);
}

void TrackSection::Update()
{
	CalculateLine();
}

TrackSection::TrackSection(TrackPoint &tPointA, TrackPoint &tPointB)
{
	_selected = false;

	Point* pointA = &tPointA;
	Point* pointB = &tPointB;
	Point* pointC = &tPointA.GetControlPoints()[1];
	Point* pointD = &tPointB.GetControlPoints()[0];

	_controlPoints.push_back(pointA);
	_controlPoints.push_back(pointB);
	_controlPoints.push_back(pointC);
	_controlPoints.push_back(pointD);

	CalculateLine();
}

TrackSection::TrackSection()
{
}

TrackSection::~TrackSection()
{
}
