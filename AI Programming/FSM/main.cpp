#include "Dwarf.h"
#include "SFML\Graphics.hpp"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dwarf Job");

	Dwarf myDwarf;
	myDwarf.Init();
	myDwarf.SetPosition(sf::Vector2f(50.0f, 50.0f));

	sf::Texture tDwarf;
	tDwarf.loadFromFile("assets/dwarf.png");
	myDwarf.SetupSprite(tDwarf, 22, 38);
	myDwarf.GetSprite()->setOrigin(sf::Vector2f(0.0f, 0.0f));
	
	unsigned int animarray[] = { 0, 1, 0, 2};
	myDwarf.GetSprite()->addAnim("walkDown", animarray, 4, false);
	animarray[0] = 3;
	animarray[1] = 4;
	animarray[2] = 3;
	animarray[3] = 5;
	myDwarf.GetSprite()->addAnim("walkUp", animarray, 4, false);

	myDwarf.GetSprite()->playAnim("walkDown");

	sf::Texture tBackground;
	tBackground.loadFromFile("assets/background.png");
	sf::Sprite sBackground;
	sBackground.setTexture(tBackground);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		myDwarf.Update(0.1f);

		window.clear();
		window.draw(sBackground);
		window.draw(*(myDwarf.GetSprite()));
		window.display();
	}

	return 0;
}