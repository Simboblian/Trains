#include "TrackPoint.h"

void TrackPoint::Draw(sf::RenderWindow& Window, bool Edit)
{
	if (isAnySelected() && Edit)
	{
		for (int i = 0; i < _controlConnectors.size(); i++)
		{
			Window.draw(_controlConnectors[i]);
		}

		for (int i = 0; i < _controlPoints.size(); i++)
		{
			_controlPoints[i]->Draw(Window);
		}
	}

	Window.draw(_viewable);
}

void TrackPoint::Update()
{
	_viewable.setPosition(_position);
	if (isSelected())
		_viewable.setOutlineColor(sf::Color::Green);
	else
		_viewable.setOutlineColor(sf::Color::Transparent);


	for (int i = 0; i < _controlPoints.size(); i++)
	{
		float before = _controlPoints[i]->GetRotationAroundPoint(_position);

		_controlPoints[i]->Update();

		float after = _controlPoints[i]->GetRotationAroundPoint(_position);
		if (before != after)
		{
			float diff = after - before;
			if (i == 0 && _controlPoints[0]->isSelected())
			{
				_controlPoints[1]->RotateAroundPoint(diff, _position);
			}
			else if (i == 1 && _controlPoints[1]->isSelected())
			{
				_controlPoints[0]->RotateAroundPoint(diff, _position);
			}
		}
	}

	for (int i = 0; i < _controlConnectors.size(); i++)
	{
		_controlConnectors[i][0].position = _controlPoints[i]->GetPosition();
		_controlConnectors[i][1].position = GetPosition();
	}
}

bool TrackPoint::isAnySelected()
{
	if (isSelected())
		return true;

	for (int i = 0; i < _controlPoints.size(); i++)
	{
		if (_controlPoints[i]->isSelected())
			return true;
	}

	return false;
}

void TrackPoint::Move(sf::Vector2f Distance)
{ 
	_position = sf::Vector2f(_position.x + Distance.x, _position.y + Distance.y);

	for (int i = 0; i < _controlPoints.size(); i++)
	{
		_controlPoints[i]->Move(Distance);
	}
}

TrackPoint::TrackPoint(sf::Vector2f Position)
{
	_position = Position;
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(_position);
	_selected = false;

	_controlPoints = std::vector<ControlPoint*>();
	_controlConnectors = std::vector<sf::VertexArray>();

	ControlPoint* pointA = new ControlPoint(sf::Vector2f(_position.x, _position.y + 100));
	ControlPoint* pointB = new ControlPoint(sf::Vector2f(_position.x, _position.y - 100));
	_controlPoints.push_back(pointA);
	_controlPoints.push_back(pointB);

	//Draw lines to the control points.
	sf::VertexArray lineA = sf::VertexArray(sf::PrimitiveType::LineStrip);
	lineA.append(sf::Vertex(pointA->GetPosition(), sf::Color::Red));
	lineA.append(sf::Vertex(_viewable.getPosition(), sf::Color::Red));

	sf::VertexArray lineB = sf::VertexArray(sf::PrimitiveType::LineStrip);
	lineB.append(sf::Vertex(pointB->GetPosition(), sf::Color::Red));
	lineB.append(sf::Vertex(_viewable.getPosition(), sf::Color::Red));

	_controlConnectors.push_back(lineA);
	_controlConnectors.push_back(lineB);
}

TrackPoint::TrackPoint()
{
	_position = sf::Vector2f(0,0);
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(_position);
	_selected = false;

	_controlPoints = std::vector<ControlPoint*>();
	_controlConnectors = std::vector<sf::VertexArray>();

	ControlPoint* pointA = new ControlPoint(sf::Vector2f(_position.x, _position.y + 100));
	ControlPoint* pointB = new ControlPoint(sf::Vector2f(_position.x, _position.y - 100));
	_controlPoints.push_back(pointA);
	_controlPoints.push_back(pointB);

	//Draw lines to the control points.
	sf::VertexArray lineA = sf::VertexArray(sf::PrimitiveType::LineStrip);
	lineA.append(sf::Vertex(pointA->GetPosition(), sf::Color::Red));
	lineA.append(sf::Vertex(_viewable.getPosition(), sf::Color::Red));

	sf::VertexArray lineB = sf::VertexArray(sf::PrimitiveType::LineStrip);
	lineB.append(sf::Vertex(pointB->GetPosition(), sf::Color::Red));
	lineB.append(sf::Vertex(_viewable.getPosition(), sf::Color::Red));

	_controlConnectors.push_back(lineA);
	_controlConnectors.push_back(lineB);
}

TrackPoint::~TrackPoint()
{
}
