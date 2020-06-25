#include "Engine.h"

bool Engine::Init()
{
	srand(time(NULL));

	_window = new sf::RenderWindow(sf::VideoMode(WINDOWSIZEX, WINDOWSIZEY), "Trains");
	pointA = sf::Vector2f(WINDOWSIZEX / 3, WINDOWSIZEY / 2);
	pointB = sf::Vector2f(WINDOWSIZEX / 3 * 2, WINDOWSIZEY / 2);
	rails = Railroad();
	grab = false;

	if (!_window)
		return false;

	oldMousePos = curMousePos = sf::Vector2f(0, 0);

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
	curMousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
	sf::Vector2f mouseDif = sf::Vector2f(curMousePos.x - oldMousePos.x, curMousePos.y - oldMousePos.y);

	TrackPoint* p1 = new TrackPoint();
	TrackPoint* p2 = new TrackPoint();

	while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window->close();
		
		switch (state)
		{
		case State::Draw:
			_window->setTitle("DRAW");
			if (evt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			{
				state = State::Edit;
				rails.DeselectAll();
			}

			if (evt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				_window->setTitle("RAILS");
				drawMode = DrawMode::Rails;
			}

			if (evt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				_window->setTitle("STOPS");
				drawMode = DrawMode::Stops;
			}

			if (evt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
					if(rails.GetSectionCount() > 0)
						rails.DeleteLastSection();
			}

			if (evt.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				switch (drawMode)
				{
				case DrawMode::Rails:
					if (rails.GetPointCount() > 0)
					{
						if (Utility::GetDistance(rails.SelectClosestPoint(curMousePos)->GetPosition(), curMousePos) > MOUSESELECTDISTANCE)
						{
							rails.DeselectAllPoints();
						}
					}
					break;
				case DrawMode::Stops:
					if (rails.AddLine(*rails.SelectClosestPoint(curMousePos)))
					{
						rails.ColourLine(sf::Color::Magenta);
					}
					break;
				default:
					break;
				}
			}

			if (evt.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				switch (drawMode)
				{
				case DrawMode::Rails:
					if (rails.GetPointCount() > 0)
					{
						p1 = rails.GetSelectedTrackPoint();
						if (Utility::GetDistance(rails.SelectClosestTrackPoint(curMousePos)->GetPosition(), curMousePos) > MOUSESELECTDISTANCE)
							p2 = nullptr;
						else
							p2 = rails.SelectClosestTrackPoint(curMousePos);

						rails.AddPoint(curMousePos, p1, p2);
					}
					else
						rails.AddPoint(curMousePos);
					break;
				case DrawMode::Stops:
					if (rails.AddLine(*rails.SelectClosestPoint(curMousePos)))
					{
						rails.ColourLine(sf::Color::Magenta);
					}
					break;
				default:
					break;
				}
			}
			break;
		case State::Edit:
			_window->setTitle("EDIT");

			if (evt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			{
				state = State::Draw;
				rails.DeselectAll();
			}

			if (evt.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				rails.DeselectAllTracks();
				rails.DeselectAllPoints();
				if (Utility::GetDistance(rails.SelectClosestPoint(curMousePos)->GetPosition(), curMousePos) > MOUSESELECTDISTANCE)
				{
					if (!Utility::PointInBounds(rails.SelectClosestTrack(curMousePos)->GetBounds(), curMousePos))
						rails.DeselectAllTracks();
					else
						rails.DeselectAllPoints();
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				rails.GetSelectedPoint()->Move(mouseDif);
			}
			break;
		default:
			break;
		}
	}

	oldMousePos = curMousePos;
}

void Engine::Update()
{
	switch (state)
	{
	case State::Draw:
		rails.Update();
		break;
	case State::Edit:
		rails.Update();
		break;
	default:
		break;
	}
}

void Engine::RenderFrame()
{
	_window->clear(sf::Color::Black);

	switch (state)
	{
	case State::Draw:
		rails.Draw(*_window, false);
		break;
	case State::Edit:
		rails.Draw(*_window, true);
		break;
	default:
		break;
	}
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
}

Engine::~Engine()
{
}
