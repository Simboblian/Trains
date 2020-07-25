#include "Engine.h"

bool Engine::Init()
{
	srand(time(NULL));

	_window = new sf::RenderWindow(sf::VideoMode(WINDOWSIZEX, WINDOWSIZEY), "Trains", 7U, sf::ContextSettings(0, 0, 8));
	_window->setFramerateLimit(60);
	_rails = Railroad();
	_mouse = Mouse();

	;

	if (!_window)
		return false;

	return true;
}

void Engine::MainLoop()
{
	while (_window->isOpen())
	{
		ProcessInput();

		Update();

		RenderFrame();
	}
}

void Engine::ProcessInput()
{
	sf::Event evt;

	_mouse.ProcessInput(*_window);

	while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			_window->close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_mouse.DeselectAll();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
			_rails.DeleteFromMouse(_mouse);

		if (_mouse.GetSelection().size() == 2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				_rails.StraightenLine((TrackPoint*)_mouse.GetSelection().front(), (TrackPoint*)_mouse.GetSelection().back());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				_rails.ConnectTwoPoints((TrackPoint*)_mouse.GetSelection().front(), (TrackPoint*)_mouse.GetSelection().back());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				_rails.CreateStation((TrackPoint*)_mouse.GetSelection().front(), (TrackPoint*)_mouse.GetSelection().back());
		}
	}

}

void Engine::Update()
{
	_mouse.Update();

	if (_mouse.isLeftDown())
	{
		if (_mouse.isLeftClicked())
		{
			if (_rails.GetPointCount() > 0)
			{
				if (Utility::GetDistance(_rails.SelectClosestPoint(_mouse.GetPosition())->GetPosition(), _mouse.GetPosition()) < _mouse.GetSelectRadius())
				{
					if (_mouse.GetSelection().size() == 0)
					{
						_mouse.SelectPoint(_rails.SelectClosestPoint(_mouse.GetPosition()), sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
					}
					else
					{
						if (_mouse.GetLastSelected()->GetType() == Type::CONTROLPOINT || _rails.SelectClosestPoint(_mouse.GetPosition())->GetType() == Type::CONTROLPOINT)
							_mouse.SelectPoint(_rails.SelectClosestPoint(_mouse.GetPosition()), false);
						else
							_mouse.SelectPoint(_rails.SelectClosestPoint(_mouse.GetPosition()), sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
					}

					_mouse.SetDragging(true);
				}
				else
				{
					_mouse.DeselectAll();
					_mouse.SetSelecting(true);
				}
			}
		}

		if (_mouse.GetLastSelected() != nullptr && (_mouse.GetDragging() && !_mouse.GetSelecting()))
		{
			for (int i = 0; i < _mouse.GetSelection().size(); i++)
			{
				if (_mouse.GetLastSelected()->GetType() == Type::CONTROLPOINT && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
					for (int j = 0; j < _rails.GetPointCount(); j++)
					{
						for (int k = 0; k < _rails.GetPointAtIndex(j)->GetControlPoints().size(); k++)
						{
							if (_mouse.GetLastSelected() == _rails.GetPointAtIndex(j)->GetControlPoints()[k])
							{
								ControlPoint* p = (ControlPoint*)_mouse.GetLastSelected();
								float rotation = p->GetRotationAroundPoint(_rails.GetPointAtIndex(j)->GetPosition());
								p->Move(_mouse.GetMouseMovement());
								p->SetRotationAroundPoint(rotation, _rails.GetPointAtIndex(j)->GetPosition());
							}
						}
					}
				}
				else
				{
					_mouse.GetSelection()[i]->Move(_mouse.GetMouseMovement());
				}
			}
		}
	}

	if (_mouse.isLeftReleased())
	{
		if (_mouse.GetSelecting())
		{
			for (int i = 0; i < _rails.GetPointCount(); i++)
			{
				if (Utility::PointInBounds(_rails.GetPointAtIndex(i)->GetPosition(), _mouse.GetSelectionRect()))
					_mouse.AddToSelection(_rails.GetPointAtIndex(i));
			}
		}

		_mouse.SetDragging(false);
		_mouse.SetSelecting(false);
	}

	if (_mouse.isRightDown())
	{
		if (_mouse.isRightClicked())
		{
			_rails.AddPoint(_mouse);
		}
	}

	_rails.Update();
}

void Engine::RenderFrame()
{
	_window->clear(sf::Color::Black);

	_rails.Draw(*_window);
	_mouse.Draw(*_window);

	_window->display();
}

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}

Engine::Engine()
{
	_window = new sf::RenderWindow();
}

Engine::~Engine()
{
}
