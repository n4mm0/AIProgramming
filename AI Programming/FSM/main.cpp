#include "Dwarf.h"
#include "GameConst.h"
#include "World.h"
#include "SFML\Graphics.hpp"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dwarf Job");

	sf::Texture tBackground;
	tBackground.loadFromFile("assets/background.png");
	sf::Sprite sBackground;
	sBackground.setTexture(tBackground);

	vecActors actors = World::GetInstance()->GetActors();

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

		window.clear();
		window.draw(sBackground);

		vecActors::iterator it = actors.begin();
		vecActors::iterator end = actors.end();
		for (; it != end; ++it)
		{
			(*it)->Update(0.1f);
			(*it)->Draw(&window);
		}
		window.display();
	}

	return 0;
}