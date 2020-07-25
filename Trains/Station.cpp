#include "Station.h"

void Station::Draw(sf::RenderWindow& Window)
{
	if (_viewable.getVertexCount() > 0)
		Window.draw(_viewable);

	Window.draw(*_platform);
}

void Station::Update()
{
}

Station::Station(TrackPoint& tPointA, TrackPoint& tPointB)
{
	ObjectType = Type::STATION;

	_selected = false;
	_colour = sf::Color::Magenta;

	Point* pointA = &tPointA;
	Point* pointB = &tPointB;
	Point* pointC = new Point();
	Point* pointD = new Point();

	if (Utility::GetDistance(tPointA.GetControlPoints().back()->GetPosition(), tPointB.GetPosition())
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

	_platform = new sf::RectangleShape();
	_platform->setPosition(sf::Vector2f((tPointA.GetPosition().x + tPointB.GetPosition().x) / 2, (tPointA.GetPosition().y + tPointB.GetPosition().y) / 2));
	_platform->setRotation(Utility::CalculateAngle(tPointA.GetPosition(), tPointB.GetPosition()) / PI * 180);
	_platform->setSize(sf::Vector2f(Utility::GetDistance(tPointA.GetPosition(), tPointB.GetPosition()), THICKNESS));
	_platform->setOrigin(sf::Vector2f(Utility::GetDistance(tPointA.GetPosition(), tPointB.GetPosition())/2, THICKNESS + 5));

}

Station::Station()
{
}

Station::~Station()
{
}
