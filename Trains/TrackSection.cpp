#include "TrackSection.h"

void TrackSection::CalculateLine()
{
	_viewable = sf::VertexArray(sf::PrimitiveType::LineStrip);

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

		_viewable.append(sf::Vertex(point, _colour));
	}

	_viewable.append(sf::Vertex(sf::Vector2f(_controlPoints[1]->GetPosition()), _colour));
}

std::vector<sf::Vector2f> TrackSection::GetVertexPoints()
{
	std::vector<sf::Vector2f> values = std::vector<sf::Vector2f>();

	for (int i = 0; i < _viewable.getVertexCount(); i++)
	{
		values.push_back(_viewable[i].position);
	}

	return values;
}

void TrackSection::SetColour(sf::Color Colour)
{
	for (int i = 0; i < _viewable.getVertexCount(); i++)
	{
		_viewable[i].color = Colour;
	}
}

void TrackSection::Draw(sf::RenderWindow& Window)
{
	if (_viewable.getVertexCount() > 0)
		Window.draw(_viewable);
}

void TrackSection::Update()
{
	if (isSelected())
		_colour = sf::Color::Green;
	else
		_colour = sf::Color::Cyan;

	for (int i = 0; i < _controlPoints.size(); i++)
	{
		if (_controlPoints[i]->GetPosition() != _controlPoints[i]->GetPreviousPosition())
			CalculateLine();
	}
}

TrackSection::TrackSection(TrackPoint &tPointA, TrackPoint &tPointB)
{
	ObjectType = Type::TRACKSECTION;

	_selected = false;
	_colour = sf::Color::Cyan;

	Point* pointA = &tPointA;
	Point* pointB = &tPointB;
	Point* pointC = new Point();
	Point* pointD = new Point();

	if(Utility::GetDistance(tPointA.GetControlPoints().back()->GetPosition(), tPointB.GetPosition())
		< Utility::GetDistance(tPointA.GetControlPoints().front()->GetPosition(), tPointB.GetPosition()))
		pointC = tPointA.GetControlPoints().back();
	else
		pointC = tPointA.GetControlPoints().front();


	if (Utility::GetDistance(tPointB.GetControlPoints().back()->GetPosition(), tPointA.GetPosition())
		< Utility::GetDistance(tPointB.GetControlPoints().front()->GetPosition(), tPointA.GetPosition()))
		pointD = tPointB.GetControlPoints().back();
	else
		pointD = tPointB.GetControlPoints().front();

	_controlPoints.push_back(pointA);
	_controlPoints.push_back(pointB);
	_controlPoints.push_back(pointC);
	_controlPoints.push_back(pointD);

	CalculateLine();
}

TrackSection::TrackSection()
{
	ObjectType = Type::TRACKSECTION;
}

TrackSection::~TrackSection()
{
}
