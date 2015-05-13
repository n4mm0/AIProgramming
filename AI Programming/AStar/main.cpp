#include <iostream>
#include "AStar.h"
#include "SFML\Graphics.hpp"

int main(int argc, const char * argv[])
{
    AStar algorithm;
	algorithm.Setup();
    
	sf::RenderWindow window(sf::VideoMode(500, 500), "AStar");
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape board[100];

	int tileWidth = 50;
	int tileHeight = 50;
	int boardWidth = 10;
	int boardHeight = 10;

	for (int i = 0; i < 100; ++i)
	{
		board[i].setFillColor(sf::Color(50,50,50,255));
		board[i].setOutlineColor(sf::Color::Black);
		board[i].setOutlineThickness(2.0f);
		board[i].setPosition(sf::Vector2f((i % boardWidth)*tileWidth, (i / boardHeight) * tileHeight));
		board[i].setSize(sf::Vector2f(tileWidth, tileHeight));
	}

	bool found = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
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

