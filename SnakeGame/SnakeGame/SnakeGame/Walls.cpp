#include "Walls.h"
#include "Snake.h"


void Walls::Render(sf::RenderWindow& window) 
{

	float headSize = Snake::GetRadius() * 2.0f;

	sf::RectangleShape rect(sf::Vector2f(window.getSize().x, headSize));

	rect.setPosition({0,0});
	// curly braces here means that the compliler convers it to a 2f itself

	rect.setFillColor(sf::Color::Yellow);
	window.draw(rect);

	// setting for the height of the screen
	
	rect.setPosition({ 0, window.getSize().y - headSize});
	window.draw(rect);


	sf::RectangleShape rect2(sf::Vector2f(headSize, window.getSize().y));
	
	rect2.setPosition({ 0,0 });

	rect2.setFillColor(sf::Color::Yellow);
	window.draw(rect2);

	rect2.setPosition({ window.getSize().x - headSize , 0  });
	window.draw(rect2);


}