#include "Tile.h"

#include "Constants.h"
#include <sstream>

Tile::Tile(float _number, const sf::Font& _font, float _x, float _y) : number(_number)
{
	sTile.setFillColor(sf::Color::White);
	sTile.setOutlineColor(sf::Color::Color(0,0,128,128));
	sTile.setOutlineThickness(5.0f);
	sTile.setSize(sf::Vector2f(Constants::tileSize, Constants::tileSize));

	std::ostringstream ostr;
	if (number!=16) ostr << number;

	tNumber.setFont(_font);
	tNumber.setString(ostr.str());
	tNumber.setColor(sf::Color::Black);
	sf::FloatRect textRect = tNumber.getGlobalBounds();
	tNumber.setOrigin(sf::Vector2f(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f));
	
	setPosition(_x, _y);
}

void Tile::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
	sTile.setPosition(sf::Vector2f(_x * Constants::tileSize, _y * Constants::tileSize));
	tNumber.setPosition(sf::Vector2f(sTile.getPosition().x + Constants::tileSize / 2.0f, sTile.getPosition().y + Constants::tileSize / 2.0f));
}

void Tile::draw(sf::RenderWindow* _window)
{
	_window->draw(sTile);
	_window->draw(tNumber);
}