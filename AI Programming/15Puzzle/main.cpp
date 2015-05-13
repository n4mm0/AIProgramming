#include "AStar.h"
#include <iostream>
#include <vector>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

using namespace sf;

void setTilePosition(vector<Configuration> &result, vector<Sprite> &sprites)
{
	if (!result.empty())
	{
		Configuration config = result.back();
		result.pop_back();

		for (int index = 0; index < 16; ++index)
			if (config.Config[index] != 16)
				sprites.at(config.Config[index] - 1).setPosition((index % 4) * 100.0f, (index / 4) * 100.0f);
	}
}

int main()
{
	RenderWindow window;
	window.create(VideoMode(400, 400), "15 Puzzle", Style::Close);
	window.setVerticalSyncEnabled(true); 

	Configuration* Config = new Configuration();
	int initConfig[] = { 2, 5, 3, 4, 1, 10, 6, 8, 9, 14, 7, 11, 13, 16, 15, 12 };
	Config->SetConfig(initConfig);
	Config->findIndexOfBlankPosition();
	Config->ComputeConfigurationHeuristic();

	AStar algorithm;
	algorithm.SetInitialConfiguration(Config);
	std::vector<Configuration> result;
	algorithm.Run(result);

	Texture texture;
	if (!texture.loadFromFile("Sprites/15.png"))
		return -1;
	texture.setSmooth(true);

	Sprite sprite;
	sprite.setTexture(texture);

	vector<Sprite> sprites;

	for (int index = 0; index < 15; ++index)
	{
		sprite.setTextureRect(IntRect((index % 4) * 100, (index / 4) * 100, 100, 100));
		sprites.push_back(sprite);
	}

	setTilePosition(result, sprites);

	Music music;
	if (!music.openFromFile("Audio/Traccia1.wav"))
		return -2;
	music.setLoop(true);
	music.play();

	while (window.isOpen())
	{
		window.clear(Color(33, 33, 33));

		for (int index = 0; index < 15; ++index)
			window.draw(sprites[index]);

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					window.close();
				else if (event.key.code == Keyboard::R)
					setTilePosition(result, sprites);
		}

		window.display();
	}
	delete Config;
	return 0;
}