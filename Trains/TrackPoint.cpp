#include "TrackPoint.h"

void TrackPoint::Draw(sf::RenderWindow& Window, bool Edit)
{
	if (Edit)
	{
		for (int i = 0; i < _controlConnectors.size(); i++)
		{
			Window.draw(_controlConnectors[i]);
		}

		for (int i = 0; i < _controlPoints.size(); i++)
		{
			_controlPoints[i].Draw(Window);
		}
	}

	Window.draw(_viewable);
}

void TrackPoint::Update()
{
	for (int i = 0; i < _controlPoints.size(); i++)
	{
		_controlPoints[i].Update();
	}

	for (int i = 0; i < _controlConnectors.size(); i++)
	{
		_controlConnectors[i][0].position = _controlPoints[i].GetPosition();
		_controlConnectors[i][1].position = GetPosition();
	}
}

TrackPoint::TrackPoint(sf::Vector2f Position)
{
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(Position);
	_selected = false;

	_controlPoints = std::vector<ControlPoint>();
	_controlConnectors = std::vector<sf::VertexArray>();

	ControlPoint pointA = ControlPoint(sf::Vector2f(_viewable.getPosition().x, _viewable.getPosition().y + 100));
	ControlPoint pointB = ControlPoint(sf::Vector2f(_viewable.getPosition().x, _viewable.getPosition().y - 100));
	_controlPoints.push_back(pointA);
	_controlPoints.push_back(pointB);

	//Draw lines to the control points.
	sf::VertexArray lineA = sf::VertexArray(sf::PrimitiveType::LineStrip);
	lineA.append(sf::Vertex(pointA.GetPosition(), sf::Color::Red));
	lineA.append(sf::Vertex(_viewable.getPosition(), sf::Color::Red));

	sf::VertexArray lineB = sf::VertexArray(sf::PrimitiveType::LineStrip);
	lineB.append(sf::Vertex(pointB.GetPosition(), sf::Color::Red));
	lineB.append(sf::Vertex(_viewable.getPosition(), sf::Color::Red));

	_controlConnectors.push_back(lineA);
	_controlConnectors.push_back(lineB);
}

TrackPoint::TrackPoint()
{
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_selected = false;

	_controlPoints = std::vector<ControlPoint>();
	_controlConnectors = std::vector<sf::VertexArray>();

	ControlPoint pointA = ControlPoint(sf::Vector2f(_viewable.getPosition().x, _viewable.getPosition().y + 100));
	ControlPoint pointB = ControlPoint(sf::Vector2f(_viewable.getPosition().x, _viewable.getPosition().y - 100));
	_controlPoints.push_back(pointA);
	_controlPoints.push_back(pointB);

	//Draw lines to the control points.
	sf::VertexArray lineA = sf::VertexArray(sf::PrimitiveType::LineStrip);
	lineA.append(sf::Vertex(pointA.GetPosition(), sf::Color::Red));
	lineA.append(sf::Vertex(_viewable.getPosition(), sf::Color::Red));

	sf::VertexArray lineB = sf::VertexArray(sf::PrimitiveType::LineStrip);
	lineB.append(sf::Vertex(pointB.GetPosition(), sf::Color::Red));
	lineB.append(sf::Vertex(_viewable.getPosition(), sf::Color::Red));

	_controlConnectors.push_back(lineA);
	_controlConnectors.push_back(lineB);
}

TrackPoint::~TrackPoint()
{
}
