#include "Railroad.h"

void Railroad::AddPoint(Mouse& CurrentMouse)
{
	if (_points.size() == 0)
	{
		AddPointAtPos(CurrentMouse.GetPosition());
		return;
	}

	TrackPoint* originalPoint = nullptr;
	if (CurrentMouse.GetSelection().size() == 1)
	{
		if (CurrentMouse.GetLastSelected()->GetType() == Type::TRACKPOINT)
		{
			originalPoint = (TrackPoint*)CurrentMouse.GetLastSelected();
		}

		if (CurrentMouse.GetLastSelected()->GetType() == Type::CONTROLPOINT)
		{
			for (int i = 0; i < _points.size(); i++)
			{
				for (int j = 0; j < _points[i]->GetControlPoints().size(); j++)
				{
					if (_points[i]->GetControlPoints()[j] == (ControlPoint*)CurrentMouse.GetLastSelected())
						originalPoint = _points[i];
				}
			}
		}

		if (Utility::GetDistance(SelectClosestTrackPoint(CurrentMouse.GetPosition())->GetPosition(), CurrentMouse.GetPosition()) < CurrentMouse.GetSelectRadius())
		{
			if (SelectClosestTrackPoint(CurrentMouse.GetPosition()) != CurrentMouse.GetLastSelected())
			{
				ConnectTwoPoints(originalPoint, SelectClosestTrackPoint(CurrentMouse.GetPosition()));
					return;
			}
		}

		AddPointAtPos(CurrentMouse.GetPosition());
		ConnectTwoPoints(originalPoint, _points.back());
	}
	else
	{
		AddPointAtPos(CurrentMouse.GetPosition());
	}
}

void Railroad::AddPointAtPos(sf::Vector2f Position)
{
	TrackPoint* p = new TrackPoint(Position);
	_points.push_back(p);
}

void Railroad::ConnectTwoPoints(TrackPoint* PointOne, TrackPoint* PointTwo)
{
	if (!PointOne->isConnected())
	{
		PointOne->Rotate(Utility::CalculateAngle(PointOne->GetPosition(), PointTwo->GetPosition()));
		PointOne->SetConnection(true);
	}
	if (!PointTwo->isConnected())
	{
		PointTwo->Rotate(Utility::CalculateAngle(PointTwo->GetPosition(), PointOne->GetPosition()));
		PointTwo->SetConnection(true);
	}

	TrackSection* s = new TrackSection(*PointOne, *PointTwo);
	_sections.push_back(s);
}

void Railroad::StraightenLine(TrackPoint* PointOne, TrackPoint* PointTwo)
{
	if (Utility::GetDistance(PointOne->GetControlPoints().front()->GetPosition(), PointTwo->GetPosition()) < Utility::GetDistance(PointOne->GetControlPoints().back()->GetPosition(), PointTwo->GetPosition()))
		PointOne->Rotate(Utility::CalculateAngle(PointOne->GetPosition(), PointTwo->GetPosition()));
	else
		PointOne->Rotate(Utility::CalculateAngle(PointOne->GetPosition(), PointTwo->GetPosition()) + PI);

	if (Utility::GetDistance(PointTwo->GetControlPoints().front()->GetPosition(), PointOne->GetPosition()) < Utility::GetDistance(PointTwo->GetControlPoints().back()->GetPosition(), PointOne->GetPosition()))
		PointTwo->Rotate(Utility::CalculateAngle(PointTwo->GetPosition(), PointOne->GetPosition()));
	else
		PointTwo->Rotate(Utility::CalculateAngle(PointTwo->GetPosition(), PointOne->GetPosition()) + PI);
}

void Railroad::CreateStation(TrackPoint* PointOne, TrackPoint* PointTwo)
{
	for (int i = 0; i < _sections.size(); i++)
	{
		bool matchA = false;
		bool matchB = false;

		for (int j = 0; j < _sections[i]->GetControlPoints().size(); j++)
		{
			if (PointOne == _sections[i]->GetControlPoints()[j])
				matchA = true;
			if (PointTwo == _sections[i]->GetControlPoints()[j])
				matchB = true;
		}

		if (matchA && matchB)
		{
			_sections[i]->~TrackSection();
			_sections.erase(_sections.begin() + i);
		}
	}

	//not a fan of all this below

	PointOne->SetConnection(false);
	PointTwo->SetConnection(false);

	StraightenLine(PointOne, PointTwo);

	PointOne->Update();
	PointTwo->Update();

	PointOne->StopRotation();
	PointTwo->StopRotation();

	PointOne->SetConnection(true);
	PointTwo->SetConnection(true);

	_sections.push_back(new Station(*PointOne, *PointTwo));
}

void Railroad::Rotate(float Angle)
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i]->Rotate(Angle);
	}
}

void Railroad::DeleteFromMouse(Mouse& CurrentMouse)
{
	for (int i = 0; i < CurrentMouse.GetSelection().size(); i++)
	{
		bool deleted = false;
		bool iterate = false;

		for (int j = 0; j < _points.size(); j++)
		{
			if (CurrentMouse.GetSelection()[i] == _points[j])
			{
				for (int k = 0; k < _sections.size(); iterate ? k++ : k)
				{
					iterate = true;
					for (int l = 0; l < _sections[k]->GetControlPoints().size(); l++)
					{
						if (_sections[k]->GetControlPoints()[l] == _points[j])
						{
							_sections[k]->~TrackSection();
							_sections.erase(_sections.begin() + k);
							iterate = false;
							k = 0;
							l = 0;
							break;
						}
					}
				}
				_points[j]->~TrackPoint();
				_points.erase(_points.begin() + j);
				deleted = true;
			}
		}

		if (!deleted)
		{
			for (int j = 0; j < _sections.size(); j++)
			{
				if (CurrentMouse.GetSelection()[i] == _sections[j])
				{
					_sections[j]->~TrackSection();
					_sections.erase(_sections.begin() + j);
					deleted = true;
				}
			}
		}
	}

	CurrentMouse.DeselectAll();
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

void Railroad::Draw(sf::RenderWindow& Window)
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i]->Draw(Window);
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
		if (_points[i]->isVisible())
		{
			if (Utility::GetDistance(Position, _points[i]->GetPosition()) < Utility::GetDistance(Position, value->GetPosition()))
			{
				value = _points[i];
			}
		}
	}

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
		if (pointList[i]->isVisible())
		{
			if (Utility::GetDistance(Position, pointList[i]->GetPosition()) < Utility::GetDistance(Position, value->GetPosition()))
				value = pointList[i];
		}
	}
	pointList.clear();
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

	return value;
}

Railroad::Railroad()
{
}

Railroad::~Railroad()
{
}
