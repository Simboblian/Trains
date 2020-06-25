#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "Utility.h"
#include "Railroad.h"

#define WINDOWSIZEX 1024
#define WINDOWSIZEY 768
#define MOUSESELECTDISTANCE 20.0f

class Engine
{
private:
	enum class State { Draw = 0, Edit = 1 };
	enum class DrawMode { Rails = 0, Stops = 1 };

	State state = State::Draw;
	DrawMode drawMode = DrawMode::Rails;

	sf::RenderWindow* _window;

	sf::Vector2f pointA, pointB;
	sf::Vector2f oldMousePos, curMousePos;
	Railroad rails;

	bool grab;

	bool Init();
	void MainLoop();
	void RenderFrame();
	void ProcessInput();
	void Update();
public:
	void Go();

	Engine();
	~Engine();
};


#endif