#ifndef _RAILROAD_H
#define _RAILROAD_H

#include "Line.h"
#include "TrackPoint.h"
#include "TrackSection.h"
#include "Station.h"
#include "Mouse.h"

class Railroad
{
private:
	std::vector<TrackPoint*> _points;
	std::vector<TrackSection*> _sections;
	std::vector<Station*> _stations;

	void AddPointAtPos(sf::Vector2f Position);
public:
	void AddPoint(Mouse &CurrentMouse);
	void ConnectTwoPoints(TrackPoint* PointOne = nullptr, TrackPoint* PointTwo = nullptr);
	void StraightenLine(TrackPoint* PointOne, TrackPoint* PointTwo);
	void CreateStation(TrackPoint* PointOne, TrackPoint* PointTwo);

	void Rotate(float Angle);
	
	void DeleteLastSection() { _sections.back()->~TrackSection(); _sections.pop_back(); };
	void DeleteFromMouse(Mouse& CurrentMouse);

	void DeselectAllPoints();
	void DeselectAllTracks();
	void DeselectAll() { DeselectAllPoints(); DeselectAllTracks(); };

	void Draw(sf::RenderWindow& Window);
	void Update();

	int GetPointCount() { return _points.size(); };
	TrackPoint* GetPointAtIndex(int index) { return index < _points.size() ?  _points[index] : nullptr; }
	int GetSectionCount() { return _sections.size(); };

	Point* GetSelectedPoint();
	Point* SelectClosestPoint(sf::Vector2f Position);

	TrackPoint* GetSelectedTrackPoint();
	TrackPoint* SelectClosestTrackPoint(sf::Vector2f Position);

	TrackSection* SelectClosestTrack(sf::Vector2f Position);

	Railroad();
	~Railroad();
};

#endif