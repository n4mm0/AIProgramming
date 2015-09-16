#pragma once

#include "SFML\Graphics.hpp"

class Tile
{
	public:
		Tile(float _number, const sf::Font& _font, float _x = 0.0f, float _y = 0.0f);
		void setPosition(float _x, float _y);
		void draw(sf::RenderWindow* _window);
	
	private:
		sf::RectangleShape sTile;
		sf::Text tNumber;
		float x;
		float y;
		int number;
};