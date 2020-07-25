#ifndef _MOUSE_H
#define _MOUSE_H

#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include "TrackPoint.h"

#define SELECTRADIUS 10
#define INPUTBUFFERSIZE 60

class Mouse
{
private:
	struct MouseState
	{
		MouseState()
		{
			_left = false;
			_right = false;
			_currPos = sf::Vector2f(0, 0);
		};

		MouseState(bool Left, bool Right, sf::Vector2f CurrPos)
		{
			_left = Left;
			_right = Right;
			_currPos = CurrPos;
		};

		bool _left, _right;
		sf::Vector2f _currPos;
	};

	int _currIndex;

	sf::Vector2f _lPressPos, _lReleasePos, _rPressPos, _rReleasePos;

	bool _selecting, _dragging;
	sf::RectangleShape _selectBox;

	std::vector<GameEntity*> _selection;
	MouseState* _inputBuffer[INPUTBUFFERSIZE];

	int GetPreviousIndex(int Behind);
public:
	void ProcessInput(sf::RenderWindow& Window);
	void Update();
	void Draw(sf::RenderWindow& Window);

	sf::Vector2f GetPosition() { return _inputBuffer[_currIndex]->_currPos; };
	sf::Vector2f GetMouseMovement();
	float GetSelectRadius() { return SELECTRADIUS; };

	std::vector<GameEntity*> GetSelection() { return _selection; };
	GameEntity* GetLastSelected() { return _selection.size() > 0 ? _selection.back() : nullptr; };
	void SelectPoint(GameEntity* Entity, bool Shift);
	void AddToSelection(GameEntity* Entity);
	void DeselectAll();

	void SetSelecting(bool value) { _selecting = value; };
	bool GetSelecting() { return _selecting; };

	void SetDragging(bool value) { _dragging = value; };
	bool GetDragging() { return _dragging; };


	sf::FloatRect GetSelectionRect() { return _selectBox.getGlobalBounds(); };

	bool isLeftClicked();
	bool isLeftReleased();
	bool isLeftDown() { return  _inputBuffer[_currIndex]->_left; };
	bool wasLeftHeldForFrames(int FrameDuration);

	bool isRightClicked();
	bool isRightReleased();
	bool isRightDown() { return  _inputBuffer[_currIndex]->_right; };
	bool wasRightHeldForFrames(int FrameDuration);


	Mouse();
	~Mouse();
};

#endif
