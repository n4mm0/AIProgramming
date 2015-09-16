#pragma once

#include "Tile.h"
#include "Configuration.h"

class Puzzle15
{
	public:
		Puzzle15();
		void draw(sf::RenderWindow* _window);
		void changeConfiguration(const Configuration& _config);

	private:
		Tile* board[16];
		sf::Font boardFont;
};