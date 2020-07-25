#include "TrackPoint.h"

void TrackPoint::Rotate(float Angle)
{
	_controlPoints[0]->SetRotationAroundPoint(Angle, _position);
	_controlPoints[1]->SetRotationAroundPoint(Angle + PI, _position);
}

void TrackPoint::Draw(sf::RenderWindow& Window)
{
	if (_visible)
	{
		for (int i = 0; i < _controlPoints.size(); i++)
		{
			_controlPoints[i]->Draw(Window);
			if(_controlPoints[i]->isVisible())
				Window.draw(_controlConnectors[i]);
		}

		Window.draw(_viewable);
	}
}

void TrackPoint::Update()
{
	if (_stopRotation)
		Rotate(_rotation);

	_previousPos = _viewable.getPosition();
	_viewable.setPosition(_position);

	if (isSelected())
	{
		_viewable.setOutlineColor(sf::Color::Green);
	}
	else
	{
		_viewable.setOutlineColor(sf::Color::Transparent);
	}

	for (int i = 0; i < _controlPoints.size(); i++)
	{
		if (_controlPoints[i]->isSelected())
		{
			if (i == 0)
				_controlPoints[1]->SetRotationAroundPoint(_controlPoints[0]->GetRotationAroundPoint(_position) + PI, _position);
			else if (i == 1)
				_controlPoints[0]->SetRotationAroundPoint(_controlPoints[1]->GetRotationAroundPoint(_position) + PI, _position);
		}

		_controlPoints[i]->Update();
	}

	//This is to allow the points to update() to where they need to be before stopping their rotation completely.
	if (!_rotatable)
		_stopRotation = true;

	if(isAnySelected())
		for (int i = 0; i < _controlPoints.size(); i++)
			_controlPoints[i]->SetVisible(true);
	else
		for (int i = 0; i < _controlPoints.size(); i++)
			_controlPoints[i]->SetVisible(false);

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

void TrackPoint::StopRotation()
{
	_rotation = _controlPoints[0]->GetRotationAroundPoint(_position);
	_rotatable = false;
}

void TrackPoint::Move(sf::Vector2f Distance)
{ 
	if (_movable)
	{
		_position = sf::Vector2f(_position.x + Distance.x, _position.y + Distance.y);

		for (int i = 0; i < _controlPoints.size(); i++)
		{
			_controlPoints[i]->Move(Distance);
		}
	}
}

TrackPoint::TrackPoint(sf::Vector2f Position)
{
	ObjectType = Type::TRACKPOINT;
	_visible = true;

	_position = Position;
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(_position);

	_controlPoints = std::vector<ControlPoint*>();
	_controlConnectors = std::vector<sf::VertexArray>();

	ControlPoint* pointA = new ControlPoint(sf::Vector2f(_position.x, _position.y + DEFAULTCONTROLOFFSET));
	ControlPoint* pointB = new ControlPoint(sf::Vector2f(_position.x, _position.y - DEFAULTCONTROLOFFSET));
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
	ObjectType = Type::TRACKPOINT;
	_visible = true;

	_position = sf::Vector2f(0,0);
	_viewable.setRadius(3);
	_viewable.setFillColor(sf::Color::White);
	_viewable.setOutlineColor(sf::Color::Transparent);
	_viewable.setOutlineThickness(2.0f);
	_viewable.setOrigin(3, 3);
	_viewable.setPosition(_position);

	_controlPoints = std::vector<ControlPoint*>();
	_controlConnectors = std::vector<sf::VertexArray>();

	ControlPoint* pointA = new ControlPoint(sf::Vector2f(_position.x, _position.y + DEFAULTCONTROLOFFSET));
	ControlPoint* pointB = new ControlPoint(sf::Vector2f(_position.x, _position.y - DEFAULTCONTROLOFFSET));
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
	for (int i = 0; i < _controlPoints.size(); i++)
	{
		_controlPoints[i]->~ControlPoint();
	}

	_controlPoints.clear();

	for (int i = 0; i < _controlConnectors.size(); i++)
	{
		_controlConnectors[i].clear();
	}

	_controlConnectors.clear();
}
