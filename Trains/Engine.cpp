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
	curMousePos = (sf::Vector2f)sf::Mouse::getPosition(*_window);

	while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window->close();
		
		switch (state)
		{
		case State::Draw:
			_window->setTitle("DRAW");
			if (evt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
				state = State::Edit;

			if (evt.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				rails.AddPoint(curMousePos);
			}
			break;
		case State::Edit:
			_window->setTitle("EDIT");
			if (evt.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
				state = State::Draw;

			if (evt.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

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
		break;
	case State::Edit:
		rails.GetClosestPoint((sf::Vector2f)sf::Mouse::getPosition(*_window)).GetShape().setOutlineColor(sf::Color::Red);
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
