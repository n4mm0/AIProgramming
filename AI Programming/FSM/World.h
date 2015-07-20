#pragma once

#include <vector>
#include "SFML\Graphics.hpp"

class Actor;
class Place; //We're going to need these for the obstacles! Check SteeringBehaviors.h::23

typedef std::vector<Actor*> vecActors;
typedef std::vector<Place*> vecPlaces;

class World
{
public:
	static World* GetInstance();
	~World();

	const vecActors& GetActors();

private:
	World();

	void SetupWorld();

	vecActors m_vActors;
	vecPlaces m_vPlaces;

	sf::Texture m_tDwarf;

	static World* m_oInstance;
};