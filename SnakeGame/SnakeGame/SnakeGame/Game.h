#pragma once

#include <iostream>
#include <vector>
#include<SFML/Graphics.hpp>

// try to reducce the scope of the files within the project some areas dont need to call certain other areas
class Snake;
// tells compilier we will declare a class

class Fruits;

class Game
{
public:
	void Run();

	int screeny = 800;
	int screenx = 600;
	int centerscreenx = screenx / 2;
	int centerscreeny =  screeny / 2;


private:

	std::vector<Snake*> m_snakeVector;
	std::vector<Fruits*> m_collectables;

	bool HandleCollisions();

};

