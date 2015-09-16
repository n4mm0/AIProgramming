#include "World.h"
#include "Dwarf.h"
#include "Place.h"
#include "GameConst.h"

World* World::m_oInstance = nullptr;

World* World::GetInstance()
{
	if (m_oInstance == nullptr)
	{
		m_oInstance = new World();
	}

	return m_oInstance;
}

World::World()
{
	SetupWorld();
}

World::~World()
{
	delete(m_oInstance);
}

void World::SetupWorld()
{
	//DWARF SETUP

	/* Assuming we are thinking in m/s
	** Dwarf max speed -> 1.5 m/s (approx 5.5km/h)
	*/
	Dwarf* myDwarf = new Dwarf(50.0f, 1.0f, 1.5f, .5f, 30.0f, 100);
	myDwarf->Init();
	myDwarf->SetPosition(GameConst::HOME_POSITION);

	m_tDwarf.loadFromFile("assets/dwarf.png");
	myDwarf->SetupSprite(m_tDwarf, 22, 38);
	myDwarf->GetSprite()->setOrigin(GameConst::SFVEC2_ZERO);

	unsigned int animarray[] = { 0, 1, 0, 2 };
	myDwarf->GetSprite()->addAnim("walkDown", animarray, 4, false);
	animarray[0] = 3;
	animarray[1] = 4;
	animarray[2] = 3;
	animarray[3] = 5;
	myDwarf->GetSprite()->addAnim("walkUp", animarray, 4, false);

	unsigned int idleAnim[] = { 0 };
	myDwarf->GetSprite()->addAnim("idle", idleAnim, 1, false);

	myDwarf->GetSprite()->playAnim("walkDown");

	m_vActors.push_back(myDwarf);

	//OBSTACLES SETUP

	m_tRock.loadFromFile("assets/rock.png");
	Place* myPlace = new Place(Vector2(70.0f, 200.f), 40.f, m_tRock);
	Place* myPlace2 = new Place(Vector2(110.0f, 300.f), 40.f, m_tRock);
	//SFML is the dumbest thing ever
	//myPlace->setOrigin(16.0f, 16.0f);

	m_vPlaces.push_back(myPlace);
	m_vPlaces.push_back(myPlace2);
}

const vecActors& World::GetActors()
{
	return m_vActors;
}

const vecPlaces& World::GetPlaces()
{
	return m_vPlaces;
}