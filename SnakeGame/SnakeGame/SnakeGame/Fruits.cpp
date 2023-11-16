#include "Fruits.h"
#include "Snake.h"
#include <iostream>

//int Fruits::GetPoints()
//{
//	return 1;
//}

bool Fruits::IsElectric()
{
	return m_isElectric;
}

void Fruits::Render(sf::RenderWindow& window)
{

	if (!visiblef) {
		return;
	}

	// could randomize these values
	int xsize;
	int ysize;
	
	// for now going to make sure that it is the head size

	float headSize = Snake::GetRadius() * 2.0f;

	sf::RectangleShape rect_f(sf::Vector2f(headSize, headSize));

	rect_f.setOrigin(sf::Vector2f(Snake::GetRadius(), Snake::GetRadius()));
	rect_f.setPosition(positionf);

	// curly braces here means that the compliler convers it to a 2f itself


	if (m_isElectric) {

		rect_f.setFillColor(sf::Color::White);
	}else
	rect_f.setFillColor(sf::Color::Magenta);

	window.draw(rect_f);



}

void Fruits::Spawn(sf::Vector2f pos)
{

	std::cout << "Spawned new fruit " << std::endl;

	positionf = pos;
	visiblef = true;
	points = 1;

	float randomValue = static_cast<float>(rand()) / RAND_MAX; // random value between 0 and 1
	if (randomValue < 0.2) { //20% probability
		m_isElectric = true;
	}
	else {
		m_isElectric = false;
	}

	if (m_isElectric) {
		points = 5;
	}

}
;

