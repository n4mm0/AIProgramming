#include "Dwarf.h"
#include "SFML\Graphics.hpp"

int main(void)
{
	Dwarf myDwarf;
	myDwarf.Init();

	sf::Texture texture;
	texture.loadFromFile("assets/dwarf.png");
	myDwarf.SetupSprite(texture, 22, 38);

	unsigned int animarray[] = { 0, 1, 0, 2};
	myDwarf.GetSprite()->addAnim("walkDown", animarray, 4, false);
	animarray[0] = 3;
	animarray[1] = 4;
	animarray[2] = 3;
	animarray[3] = 5;
	myDwarf.GetSprite()->addAnim("walkUp", animarray, 4, false);

	myDwarf.GetSprite()->playAnim("walkDown");

	sf::RenderWindow window(sf::VideoMode(800, 600), "Dwarf Job");

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
		window.draw(*(myDwarf.GetSprite()));
		window.display();
	}

	return 0;
}