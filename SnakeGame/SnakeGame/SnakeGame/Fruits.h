#pragma once

#include <SFML/Graphics.hpp>

class Fruits {



public:
	bool PowerUp;
	// constucter
	Fruits(bool isElectric) : m_isElectric(isElectric) {};


	bool IsElectric();


	int GetScore() const { return points; };
	
	void Render(sf::RenderWindow& window);
	
	bool visiblef{false};  //m_visible
	
	bool GetVisible() const { return visiblef; };

	void Spawn(sf::Vector2f pos);

	// removing the fruit upon collision
	// setting the bool ofd visiblef to false

	void Die() { visiblef = false; }

	// flag for if it is visible to make sure 
	// you are not spawning an unneccicary amount of fruits

	sf::Vector2f GetPosition() const { return positionf; }

private:
	sf::Vector2f positionf;  // we can use a map for the positioning of the snake etc
	int points; // m_score
	bool m_isElectric;
};
