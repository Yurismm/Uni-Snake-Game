#include "Game.h"
#include "Snake.h"
#include "Walls.h"
#include "Fruits.h"


#include <iostream>
#include <vector>
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

#define DEBUG_MODE


// #define kTimeBetweekTicks   500
// replaces all values with said name above with that value before the code is compiled
// is dangerous because it replaces all values with that number/value and does not have a type

constexpr float kTimeBetweenTicks = 250;
// tickrate

// render window sizes here just in case they want changing (could be a private value if you want?)

constexpr int screeny = 800;
constexpr int screenx = 600;

sf::Vector2f GetRandomPos() {

	// need diameter, not radius
	int x = rand() % 40 * Snake::GetRadius() * 2;
	int y = rand() % 30 * Snake::GetRadius() * 2;

	return sf::Vector2f((float)x, (float)y);

}

void Game::Run()
{

	sf::RenderWindow window(sf::VideoMode(screeny, screenx), "C++ Snake ICA : C2454177");
	// screen varibles for easy change
	window.setFramerateLimit(60);
	m_snakeVector.emplace_back(new Snake({ 400.0f,300.0f }, 0, 1, sf::Color::Yellow));
	m_snakeVector.emplace_back(new Snake({ 600.0f,300.0f }, 1, 1, sf::Color::Blue));


	std::cout << "SnakeGame: Starting" << std::endl;

	// Main loop that continues until we call window.close()

	sf::Clock clock;
	// tick rate

	Walls walls;
	//  walls

	sf::Font press_start;

	if (!press_start.loadFromFile("Hybridge.ttf")) {
		std::cout << "cant load font" << std::endl;
		return;
	}

	sf::Text press_start_text;

	press_start_text.setFont(press_start);
	press_start_text.setCharacterSize(20);
	press_start_text.setString("Press a button to start");
	press_start_text.setStyle(sf::Text::Bold);

	press_start_text.setPosition(centerscreenx, centerscreeny);

	for (int i = 0; i < 10; i++) {

		m_collectables.emplace_back(new Fruits(false)); // non-electric fruit
		m_collectables.emplace_back(new Fruits(true));  // electric fruit

#if defined(DEBUG_MODE)

		std::cout << "DEBUG_MODE ON" << std::endl;

		std::cout << "Spawned " << i << " of" << " available fruits" << std::endl;

#endif

	}


	while (window.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		// sim update

		if (clock.getElapsedTime().asMilliseconds() >= kTimeBetweenTicks) {

			for (Snake* s : m_snakeVector) {
				{
					s->Update();
					if (HandleCollisions())
					{
						// Human Collision
						std::cout << "Game over, you collided with each other" << std::endl;
						return;

					}
					if (s->CheckWallCollision(window)) {
						// Wall collision checks
						std::cout << "You hit a wall :,D" << std::endl;
						return;
					}
				}

				for (Snake* s : m_snakeVector) {
					if (s->CheckSelfCollision()) {
						// Check 
						std::cout << "Oh no! I've killed myself ),:" << std::endl;
						std::cout << "Game over" << std::endl;
						return;
					}

				}

				// Update and print scores
				// PLEASE FIX *** PLEASE FIX *** PLEASE FIX ***// PLEASE FIX *** PLEASE FIX *** PLEASE FIX ***

				for (Snake* s : m_snakeVector) {

					bool fruit_collected = false;

					s->CheckCollision(m_collectables, fruit_collected);

				}

				if (s->fruit_collected) {

					int playerOneScore = m_snakeVector[0]->getScore();
					int playerTwoScore = m_snakeVector[1]->getScore();

					std::cout << "Player one score: " << playerOneScore << std::endl;
					std::cout << "Player two score: " << playerTwoScore << std::endl;

					if (playerOneScore == 30) {

						std::cout << "Player One wins." << std::endl;
						break;
					}

					if (playerTwoScore == 30) {

						std::cout << "Player Two wins." << std::endl;
						break;
					}

					s->fruit_collected = false;
				}
				// PLEASE FIX *** PLEASE FIX *** PLEASE FIX ***// PLEASE FIX *** PLEASE FIX *** PLEASE FIX ***

				clock.restart();

			}



		}

		// We must clear the window each time around the loop
		window.clear();
		// after this we can start the graphics loops 

		// Graphics

		// rendering the snake
		for (Snake* s : m_snakeVector)
		{
			s->Render(window);
		}

		// affects the speed of the spawning
		if (rand() % 600 == 0) {

			for (Fruits* f : m_collectables) {

				if (f->GetVisible() == false)
				{
					f->Spawn(GetRandomPos());
					break;
				}

			}

		}
		//Rendering Fruits

		for (Fruits* f : m_collectables) {

			f->Render(window);

		}


		//// Render scores
		//window.draw(playerOneScoreText);
		//window.draw(playerTwoScoreText);

		// Rendering the walls
		walls.Render(window);

		window.draw(press_start_text);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			press_start_text.setString(" ");
		}

		// Get the window to display its contents
		window.display();
	}

	// loop for deleting memory as it is essential to delete memory

	for (Snake* s : m_snakeVector)
		delete s;

	for (Fruits* f : m_collectables)
		delete f;

	std::cout << "SnakeGame: Finished" << std::endl;
}

bool Game::HandleCollisions()
{

	// checking collision with the fruits 
	bool fruits_collected = false;

	for (Snake* s : m_snakeVector)
		s->CheckCollision(m_collectables, fruits_collected);
	// 


	for (size_t i = 0; i < m_snakeVector.size(); i++)
	{

		for (size_t j = i + 1; j < m_snakeVector.size(); j++)
		{
			bool collided{ m_snakeVector[i]->CheckCollision(m_snakeVector[j]) };
			if (collided) {
				return true;
			}


		}

	}

	return false;
}

