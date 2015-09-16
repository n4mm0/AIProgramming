#include <SFML/Graphics.hpp>

#include "AStar.h"
#include "Constants.h"
#include "Puzzle15.h"
#include "Configuration.h"

int main()
{	
	sf::RenderWindow window(sf::VideoMode(Constants::screenWidth, Constants::screenHeight), "Puzzle15");
	
	Puzzle15 puzzle;

	srand(time(NULL));
	Configuration config;

	int solvable[16] ={ 2, 5, 3, 4, 1, 10, 6, 8, 9, 14, 7, 11, 13, 16, 15, 12 };
	config.setConfiguration(solvable);

	puzzle.changeConfiguration(config);

	std::vector<Configuration> result;

	AStar solver;
	solver.Run(config, result);

	//puzzle.changeConfiguration(config);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						if (!result.empty())
						{
							puzzle.changeConfiguration(result.back());
							result.pop_back();
						}
					}
				}
			}
		}

		window.clear();
		puzzle.draw(&window);
		window.display();
	}
	
	return 0;

	/*AStar algorithm;
	algorithm.Run();
	system("pause");*/
}