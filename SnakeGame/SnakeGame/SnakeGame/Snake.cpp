#include "Snake.h"
#include <iostream>
#include "Fruits.h"

#include <SFML/Graphics.hpp>

#define DEBUG_MODE



Snake::Snake(sf::Vector2f pos, int controlScheme, int score, sf::Color snakeColor) :
	m_controlScheme(controlScheme)
{
	//front of the list? back? both dont matter

	m_tail.push_back(pos);

	// list of positions, loop through the list

	color_ = snakeColor;

};
void Snake::HandleInput()
{

	// unsure with what to do with this old input though 
	// i see that there is some
	// lag to the inputs meaning that 
	// the tickrate should go up a little


	// movement is handled by liinked list
	// this is by using a pointer to the new position and deleting the node from the back

	sf::Vector2f newPosition = m_tail.front();

	switch (m_direction) {
	case Direction::North:
		newPosition.y -= Snake::GetRadius() * 2.0f;
		break;
	case Direction::East:
		newPosition.x += Snake::GetRadius() * 2.0f;
		break;
	case Direction::South:
		newPosition.y += Snake::GetRadius() * 2.0f;
		break;
	case Direction::West:
		newPosition.x -= Snake::GetRadius() * 2.0f;
		break;
	default:
		break;
	}

	m_tail.push_front(newPosition);

	if (m_growAmount == 0) {
		m_tail.pop_back();
	}
	else {
		m_growAmount--;
	}

#if defined(DEBUG_MODE)



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {

		m_growAmount;

		std::cout << "Set grow amount to test: " << std::endl;

		std::cin >> m_growAmount;

		std::cout << "Grew tail by " << m_growAmount << std::endl;

	}



#endif

	// UPDATED DIRECTION CONTROL

	// add switch functionality between wasd and arrow keys?

	if (m_controlScheme == 0) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_direction != Direction::South) {
			m_direction = Direction::North;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_direction != Direction::East) {
			m_direction = Direction::West;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_direction != Direction::North) {
			m_direction = Direction::South;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_direction != Direction::West) {
			m_direction = Direction::East;
		}


	}


	if (m_controlScheme == 1) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_direction != Direction::South) {
			m_direction = Direction::North;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_direction != Direction::East) {
			m_direction = Direction::West;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_direction != Direction::North) {
			m_direction = Direction::South;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_direction != Direction::West) {
			m_direction = Direction::East;
		}

	}
	// quality of life / allowing people to customize controls?
}


bool Snake::CheckCollision(Snake* other)
{
	for (auto it : m_tail) {
	if (it == other->m_tail.front())
		return true;
	}
		return false;	

	return false; // no collision
}
void Snake::CheckCollision(std::vector<Fruits*>& fruits, bool& fruit_collected)
{
	for (Fruits* f : fruits) {

		if (f->GetVisible() && f->GetPosition() == m_tail.front()) {

			if (f->IsElectric()) {
				isElectric_ = true;
				AddScore(f->GetScore());
				electricTimer.restart();
			}
			else {

				AddScore(f->GetScore());
				fruit_collected = true;

			}

			f->Die();
		}
		// checking if the fruit is visible and
		// checking if the positions overlap with each other 

	}
}
bool Snake::CheckSelfCollision()
{
	// iterators

	std::list<sf::Vector2f>::iterator it = m_tail.begin();
	it++; // Skip the head of the snake

	while (it != m_tail.end()) {
		if (*it == m_tail.front())
			return true;
		it++;
	}

	return false;
}
bool Snake::CheckWallCollision(const sf::RenderWindow& window)
{
	sf::Vector2f head_pos = m_tail.front();

	if (head_pos.x < 0 || head_pos.x >= window.getSize().x) {

		return true;

	}

	if (head_pos.y < 0 || head_pos.y >= window.getSize().y) {

		return true;

	}

	return false;

}

// powerup things
bool Snake::isElectric() const {
	return isElectric_;
}

// score
int Snake::getScore() const {
	return m_score;
}

void Snake::setScore(int score) {
	m_score = score;
}

void Snake::AddScore(int score)
{
	m_growAmount += score;
	m_score += score;
	std::cout << m_score << std::endl;
}

void Snake::Update()
{
	Snake::HandleInput();

	// size of head is radius * 2

	if (isElectric_) {
		
		if (isElectric_) {

			if (electricTimer.getElapsedTime().asSeconds() >= 3.0f) {
				isElectric_ = false;  // disable the power-up after 3 seconds
			

			}
		}
			
	}

};

void Snake::ChangeDirection(Direction newDirection)
{
	m_direction = newDirection;
}

void Snake::Render(sf::RenderWindow& window)
{

	sf::CircleShape shape(Snake::GetRadius());
	shape.setOrigin(sf::Vector2f(Snake::GetRadius(), Snake::GetRadius()));



	// std::list<sf::Vector2f>::iterator it = m_tail.begin();it != m_tail.end(); ++it 
	// use an iterator to go thru a list
	// can use it for a vector

	for (auto it : m_tail)
		// using auto means the compilier finds out what the type is
		// doesnt take into account if there is a copy of the refence
	{
		if (isElectric_) {
			shape.setFillColor(sf::Color::White);
		}
		else {
			shape.setFillColor(color_);
		}
		shape.setPosition(it);
		window.draw(shape);
	}


}