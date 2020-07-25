#include "Mouse.h"

int Mouse::GetPreviousIndex(int Behind)
{
	int checkIndex = _currIndex - Behind;

	if (checkIndex < 0)
	{
		return (INPUTBUFFERSIZE - checkIndex) - (Behind + 1);
	}
	else
	{
		return _currIndex - Behind;
	}
}

void Mouse::ProcessInput(sf::RenderWindow& Window)
{
	if (++_currIndex >= INPUTBUFFERSIZE)
		_currIndex = 0;

	_inputBuffer[_currIndex]->_left = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	_inputBuffer[_currIndex]->_right = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	_inputBuffer[_currIndex]->_currPos = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));

	if (isLeftClicked())
		_lPressPos = _inputBuffer[_currIndex]->_currPos;

	if (isRightClicked())
		_rPressPos = _inputBuffer[_currIndex]->_currPos;

	if (isLeftReleased())
		_lReleasePos = _inputBuffer[_currIndex]->_currPos;

	if (isRightReleased())
		_rReleasePos = _inputBuffer[_currIndex]->_currPos;
}

void Mouse::Update()
{
	_selectBox.setPosition(_lPressPos);
	_selectBox.setSize(sf::Vector2f(_inputBuffer[_currIndex]->_currPos.x - _lPressPos.x, _inputBuffer[_currIndex]->_currPos.y - _lPressPos.y));
}

void Mouse::Draw(sf::RenderWindow& Window)
{
	if (_selecting)
	{
		Window.draw(_selectBox);
	}
}

sf::Vector2f Mouse::GetMouseMovement()
{
	return sf::Vector2f(_inputBuffer[_currIndex]->_currPos.x - _inputBuffer[GetPreviousIndex(1)]->_currPos.x,
		_inputBuffer[_currIndex]->_currPos.y - _inputBuffer[GetPreviousIndex(1)]->_currPos.y);
}

void Mouse::SelectPoint(GameEntity* Entity, bool Shift)
{
	bool found = false;

	if (!Shift)
	{
		DeselectAll();
	}
	else
	{
		for (int i = 0; i < _selection.size(); i++)
			if (Entity == _selection[i])
			{
				found = true;
				_selection[i]->Deselect();
				_selection.erase(_selection.begin() + i);
			}
	}

	if (Utility::GetDistance(Entity->GetPosition(), _inputBuffer[_currIndex]->_currPos) < SELECTRADIUS && !found)
	{
		AddToSelection(Entity);
	}
}

void Mouse::AddToSelection(GameEntity* Entity)
{
	_selection.push_back(Entity);
	_selection.back()->Select();
}

void Mouse::DeselectAll()
{
	for (int i = 0; i < _selection.size(); i++)
		_selection[i]->Deselect();
	_selection.clear(); 
}

bool Mouse::isLeftClicked()
{
	return(_inputBuffer[_currIndex]->_left && !_inputBuffer[GetPreviousIndex(1)]->_left);
}

bool Mouse::isLeftReleased()
{
	return(!_inputBuffer[_currIndex]->_left && _inputBuffer[GetPreviousIndex(1)]->_left);
}

bool Mouse::wasLeftHeldForFrames(int FrameDuration)
{
	bool value = true;

	for (int i = 0; i < FrameDuration; i++)
	{

		if (!_inputBuffer[GetPreviousIndex(i)]->_left)
			value = false;
	}

	return value;
}


bool Mouse::wasRightHeldForFrames(int FrameDuration)
{
	bool value = true;

	for (int i = 0; i < FrameDuration; i++)
	{

		if (!_inputBuffer[GetPreviousIndex(i)]->_right)
			value = false;
	}

	return value;
}

bool Mouse::isRightClicked()
{
	return(_inputBuffer[_currIndex]->_right && !_inputBuffer[GetPreviousIndex(1)]->_right);
}

bool Mouse::isRightReleased()
{
	return(!_inputBuffer[_currIndex]->_right && _inputBuffer[GetPreviousIndex(1)]->_right);
}

Mouse::Mouse()
{
	for (int i = 0; i < INPUTBUFFERSIZE; i++)
	{
		_inputBuffer[i] = new MouseState(false, false, sf::Vector2f(0, 0));
	}

	_currIndex = 0;

	_selectBox.setOutlineColor(sf::Color::Green);
	_selectBox.setFillColor(sf::Color(0, 255, 0, 32));
	_selectBox.setOutlineThickness(1);
	_selectBox.setSize(sf::Vector2f(0, 0));

	_selection = std::vector<GameEntity*>();

	_selecting = false;
	_dragging = false;
}

Mouse::~Mouse()
{
}
