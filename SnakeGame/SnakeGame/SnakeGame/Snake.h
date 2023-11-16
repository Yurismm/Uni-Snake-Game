#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include <list>
// linked list?

class Fruits;

// easy way to declare varible names as numbers (eg west as 1 or south as 2)
enum class Direction {

	North, //0
	East, //1
	South, // 2
	West,  // 3
	None // 4
	//reset to none?
};

class Snake {


	// update some of the public and private valubles

private:

	// note to self : careful putting values in the private area it 
	// may cause issues down the line within other cpp files
	// (error - inaccessible)
	int m_growAmount{ 0 };
	Direction m_direction{ Direction::None };

	// init the game with no direction until the player clicks
	// maybe a screem with like "Click to play" before you play?

	std::list<sf::Vector2f> m_tail;

	sf::Vector2f length;
	int m_controlScheme{ 0 };
	bool isElectric_;
	float speedMultiplier_;

public:

	// a function that is static doesnt belong to any specific iteration of the class
	static float GetRadius() { return 10.f; };
	sf::Color color_;
	sf::Color electricColor_ = sf::Color::White;

	Snake(sf::Vector2f pos, int controlScheme, int score, sf::Color snakeColor );

	// powerup
	bool isElectric() const;
	sf::Clock electricTimer;

	// score things
	int getScore() const;
	void setScore(int score);
	bool fruit_collected = false;
	int m_score = 0;

	// Updates
	void Render(sf::RenderWindow& window);
	void Update();
	void ChangeDirection(Direction newDirection);
	void HandleInput();

	// collisions
	bool CheckCollision(Snake* other);
	void CheckCollision(std::vector<Fruits*>& fruits, bool& fruit_collected);
	bool CheckSelfCollision();
	bool CheckWallCollision(const sf::RenderWindow& window);

	/*void setElectricMode(bool enabled); */

	void AddScore(int score);

	sf::Vector2f GetPosition() const { return m_tail.front(); }


};
