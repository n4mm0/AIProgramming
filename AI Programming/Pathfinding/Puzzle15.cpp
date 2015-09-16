#include "Puzzle15.h"

Puzzle15::Puzzle15()
{
	boardFont.loadFromFile("comic.ttf");

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			board[i + (j*4)] = new Tile(i + (j*4) + 1, boardFont, i, j);
		}
	}
}

void Puzzle15::draw(sf::RenderWindow* _window)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			board[(i * 4) + j]->draw(_window);
		}
	}
}

void Puzzle15::changeConfiguration(const Configuration& _config)
{
	int p = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			board[_config.getElementAt(p) - 1]->setPosition(j, i);
			++p;
		}
	}
}