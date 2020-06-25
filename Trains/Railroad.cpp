#include "Railroad.h"

void Railroad::AddPoint(sf::Vector2f Position, TrackPoint* PreviousPoint, TrackPoint* NextPoint)
{
	DeselectAll();
	TrackPoint* p = new TrackPoint(Position);
	if (NextPoint != nullptr)
	{
		NextPoint->Select();

		if (PreviousPoint != nullptr)
		{
			if (_points.size() > 1)
			{
				TrackSection* s = new TrackSection(*PreviousPoint, *NextPoint);
				_sections.push_back(s);
			}
		}
	}
	else
	{
		p->Select();
		_points.push_back(p);

		if (PreviousPoint != nullptr)
		{
			if (_points.size() > 1)
			{
				TrackSection* s = new TrackSection(*PreviousPoint, *_points[_points.size() - 1]);
				_sections.push_back(s);
			}
		}
	}
}

bool Railroad::AddLine(Point& NewPoint)
{
	//if (_lines.size() == 0)
	//	_lines.push_back(new Line());
	//else if (_lines.back()->GetPoints().size() == 2)
	//	_lines.push_back(new Line());

	//if(_lines.back()->GetPoints().size() == 0)
	//	_lines.back()->AddPoint(NewPoint);
	//else if (_lines.back()->GetPoints().size() < 2)
	//	if(&NewPoint != _lines.back()->GetPoints().back())
	//		_lines.back()->AddPoint(NewPoint);

	//if (_lines.back()->GetPoints().size() == 2)
	//	return true;
	return false;
}

void Railroad::ColourLine(sf::Color Colour)
{
	//_lines.back()->SetColour(Colour);
}

void Railroad::DeselectAllPoints()
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i]->Deselect();

		for (int j = 0; j < _points[i]->GetControlPoints().size(); j++)
		{
			_points[i]->GetControlPoints()[j]->Deselect();
		}
	}
}

void Railroad::DeselectAllTracks()
{
	for (int i = 0; i < _sections.size(); i++)
	{
		_sections[i]->Deselect();
	}
}

void Railroad::Draw(sf::RenderWindow& Window, bool Edit)
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i]->Draw(Window, Edit);
	}

	for (int i = 0; i < _sections.size(); i++)
	{
		_sections[i]->Draw(Window);
	}
}

void Railroad::Update()
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i]->Update();
	}

	for (int i = 0; i < _sections.size(); i++)
	{
		_sections[i]->Update();
	}
}

Point* Railroad::GetSelectedPoint()
{
	std::vector<Point*> pointList;

	for (int i = 0; i < _points.size(); i++)
	{
		pointList.push_back(_points[i]);

		for (int j = 0; j < _points[i]->GetControlPoints().size(); j++)
		{
			pointList.push_back(_points[i]->GetControlPoints()[j]);
		}
	}

	Point* value = pointList[0];
	for (int i = 0; i < pointList.size(); i++)
	{
		if (pointList[i]->isSelected())
		{
			value = pointList[i];
			break;
		}
	}
	pointList.clear();
	return value;
}

TrackPoint* Railroad::GetSelectedTrackPoint()
{
	if (_points.size() <= 0)
		return nullptr;

	bool selected = false;

	TrackPoint* value = _points[0];
	for (int i = 0; i < _points.size(); i++)
	{
		if (_points[i]->isSelected())
		{
			selected = true;
			value = _points[i];
			break;
		}
	}

	if(!selected)
		return nullptr;

	return value;
}

TrackPoint* Railroad::SelectClosestTrackPoint(sf::Vector2f Position)
{
	if (_points.size() <= 0)
		return nullptr;

	TrackPoint* value = _points[0];
	for (int i = 0; i < _points.size(); i++)
	{
		if (Utility::GetDistance(Position, _points[i]->GetPosition()) < Utility::GetDistance(Position, value->GetPosition()))
		{
			value = _points[i];
		}
	}

	value->Select();
	return value;
}

Point* Railroad::SelectClosestPoint(sf::Vector2f Position)
{
	if (_points.size() <= 0)
		return nullptr;

	std::vector<Point*> pointList;

	for (int i = 0; i < _points.size(); i++)
	{
		pointList.push_back(_points[i]);

		for (int j = 0; j < _points[i]->GetControlPoints().size(); j++)
		{
			pointList.push_back(_points[i]->GetControlPoints()[j]);
		}
	}

	Point* value = pointList[0];
	for (int i = 0; i < pointList.size(); i++)
	{
		pointList[i]->Deselect();
		if (Utility::GetDistance(Position, pointList[i]->GetPosition()) < Utility::GetDistance(Position, value->GetPosition()))
			value = pointList[i];
	}
	pointList.clear();
	value->Select();
	return value;
}

TrackSection* Railroad::SelectClosestTrack(sf::Vector2f Position)
{
	TrackSection* value = _sections[0];

	float valueDistance = Utility::GetDistance(Position, _sections[0]->GetVertexPoints()[0]);

	for (int i = 0; i < _sections.size(); i++)
	{
		for (int j = 0; j < _sections[i]->GetVertexPoints().size(); j++)
		{
			if (Utility::GetDistance(Position, _sections[i]->GetVertexPoints()[j]) < valueDistance)
			{
				valueDistance = Utility::GetDistance(Position, _sections[i]->GetVertexPoints()[j]);
				value = _sections[i];
			}
		}
	}

	value->Select();
	return value;
}

Railroad::Railroad()
{
}

Railroad::~Railroad()
{
}
