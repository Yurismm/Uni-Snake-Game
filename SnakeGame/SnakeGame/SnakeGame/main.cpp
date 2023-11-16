/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>

#include <vector>

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>

// Class header files

#include "AISnake.h"
// class for the aisnake

#include "Fruits.h"
// class for the fruit spawn

#include "Snake.h"
// player snake
// should have only ONE instance of this snake

#include "Circle.h"
// Circle class
//TODO: make retangle

#include "Rectangle.h"
// Rectangle class

#include "Game.h"
// game class

// adding text




int main()
{
    Game newGame;
    newGame.Run();

    return 0;
}
