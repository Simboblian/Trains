#ifndef _RAILROAD_H
#define _RAILROAD_H

#include "Line.h"
#include "TrackPoint.h"
#include "TrackSection.h"

class Railroad
{
private:
	std::vector<TrackPoint*> _points;
	std::vector<TrackSection*> _sections;
	//std::vector<Line*> _lines;
public:
	void AddPoint(sf::Vector2f Position, TrackPoint* PreviousPoint = nullptr, TrackPoint* NextPoint = nullptr);
	bool AddLine(Point& NewPoint);
	
	void DeleteLastSection() { _sections.back()->~TrackSection(); _sections.pop_back(); };
	void ColourLine(sf::Color Colour);
	void DeselectAllPoints();
	void DeselectAllTracks();
	void DeselectAll() { DeselectAllPoints(); DeselectAllTracks(); };

	void Draw(sf::RenderWindow& Window, bool Edit);
	void Update();

	int GetPointCount() { return _points.size(); };
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