#include "Dwarf.h"
#include "GameConst.h"
#include "SFML\Graphics.hpp"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dwarf Job");

	sf::Texture tDwarf;
	tDwarf.loadFromFile("assets/dwarf.png");

	Dwarf dwarves[7];
	for (int i = 0; i < 7; ++i)
	{
		dwarves[i].Init();
		dwarves[i].SetPosition(GameConst::HOME_POSITION + sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50));
		dwarves[i].SetupSprite(tDwarf, 22, 38);
		dwarves[i].GetSprite()->setOrigin(GameConst::VEC2_ZERO);

		unsigned int animarray[] = { 0, 1, 0, 2 };
		dwarves[i].GetSprite()->addAnim("walkDown", animarray, 4, false);
		animarray[0] = 3;
		animarray[1] = 4;
		animarray[2] = 3;
		animarray[3] = 5;
		dwarves[i].GetSprite()->addAnim("walkUp", animarray, 4, false);

		dwarves[i].GetSprite()->playAnim("walkDown");
	}

	/*Dwarf myDwarf(50.0f,100);
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

	myDwarf.GetSprite()->playAnim("walkDown");*/

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

		//myDwarf.Update(0.1f);
		for (int i = 0; i < 7; ++i)
		{
			dwarves[i].Update(0.1f);
		}

		//Let's sort the dwarves for the Y coordinate
		/*bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			for (int i = 0; i < 6; ++i)
			{
				if (dwarves[i].GetPosition().y > dwarves[i + 1].GetPosition().y)
				{
					//Dwarf temporaryDwarf = dwarves[i];
					//dwarves[i] = dwarves[i + 1];
					//dwarves[i + 1] = temporaryDwarf;
					std::swap(dwarves[i], dwarves[i + 1]);
					sorted = false;
				}
			}
		}*/

		window.clear();
		window.draw(sBackground);
		//window.draw(*(myDwarf.GetSprite()));
		for (int i = 0; i < 7; ++i)
		{
			window.draw(*(dwarves[i].GetSprite()));
		}
		window.display();
	}

	return 0;
}