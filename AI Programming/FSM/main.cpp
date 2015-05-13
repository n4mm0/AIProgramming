#include "Dwarf.h"
#include "GameConst.h"
#include "SFML\Graphics.hpp"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dwarf Job");

	Dwarf myDwarf(50.0f,100);
	myDwarf.Init();
	myDwarf.SetPosition(GameConst::HOME_POSITION);

	sf::Texture tDwarf;
	tDwarf.loadFromFile("assets/dwarf.png");
	myDwarf.SetupSprite(tDwarf, 22, 38);
	myDwarf.GetSprite()->setOrigin(GameConst::VEC2_ZERO);
	
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
			else if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
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