#include <iostream>
#include "AStar.h"
#include "SFML\Graphics.hpp"

int main(int argc, const char * argv[])
{
    AStar algorithm;
	algorithm.Setup();
    
	sf::RenderWindow window(sf::VideoMode(500, 500), "AStar");

	sf::RectangleShape board[100];
	for (int i = 0; i < 100; ++i)
	{
		board[i].setFillColor(sf::Color(50,50,50,255));
		board[i].setOutlineColor(sf::Color::Black);
		board[i].setOutlineThickness(2.0f);
		board[i].setPosition(sf::Vector2f((i / 10)*50, (i % 10)*50));
		board[i].setSize(sf::Vector2f(50, 50));
	}

	bool found = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!found)
		{
			found = algorithm.Step(board);
		}

		//algorithm.UpdateBoardGraphic(board);

		window.clear();
		for (int i = 0; i < 100; ++i)
		{
			window.draw(board[i]);
		}
		window.display();
	}

	//getchar();
    return 0;
}

