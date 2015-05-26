#include "SteeringBehaviors.h"
#include "Actor.h"

SteeringBehaviors::SteeringBehaviors(Actor* bp)
{
	m_Actor = bp; //Is m_Actor the owner of the behavior or the Actor to pursuit/evade?
	//Is there more stuff to initialize?
}

SteeringBehaviors::~SteeringBehaviors()
{
	m_neighbors.clear();
	m_obstacles.clear();
}

void SteeringBehaviors::SetTarget(const sf::Vector2f target)
{
	m_target = target;
}

void SteeringBehaviors::SetEvader(Actor* evader)
{
	//Where am I supposed to save the evader?? m_Actor?
}

void SteeringBehaviors::Calculate()
{
	m_steering = sf::Vector2f(0.0f, 0.0f);
	SumForces();
}

void SteeringBehaviors::SumForces()
{
	//Why do these functions require data that the class already knows? Like target or its neighbors...
	if (SeekIsOn())					m_steering += Seek(m_target);
	if (FleeIsOn())					m_steering += Flee(m_target);
	if (ArriveIsOn())				m_steering += Arrive(m_target);
	if (PursuitIsOn())				m_steering += Pursuit(m_Actor); //wtf do you want
	if (EvadeIsOn())				m_steering += Evade(m_Actor); //wtf do you want
	if (WanderIsOn())				m_steering += Wander();
	if (ObstacleAvoidanceIsOn())	m_steering += ObstacleAvoidance();
	if (WallAvoidanceIsOn())		m_steering += WallAvoidance(m_target);
	if (InterposeIsOn())			m_steering += Interpose(m_target);
	
	//Group
	if (SeparationIsOn())			m_steering += Separation(m_neighbors);
	if (CohesionIsOn())				m_steering += Cohesion(m_neighbors);
	if (AlignmentIsOn())			m_steering += Alignment(m_target);
}

sf::Vector2f SteeringBehaviors::Seek(const sf::Vector2f& target)
{
	//return target - m_Actor->GetPosition();
	/*
	** We need to consider actor max velocity and apply it? In order to make it move slower, and not
	** teleport to the target..
	** Also we mentioned something about actor's turn rate at lesson.. Can we consider it 180 degrees
	** (aka instant) for now?
	*/
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f SteeringBehaviors::Flee(const sf::Vector2f& target)
{
	return -Seek(target); //Is it ok?
}

sf::Vector2f SteeringBehaviors::Arrive(const sf::Vector2f& target)
{
	//Can't remember this one...
	/*
	** Seek the target but adjust your velocity while you are approaching it
	** in order to arrive without "crashing" on it
	*/
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f SteeringBehaviors::Pursuit(const Actor* target)
{
	//From my notes...
	/*
	** sf::Vector2f d = target->GetPosition() - m_Actor->GetPosition(); 
	** d = d / m_Actor->GetVelocity();
	** d = target->GetVelocity() * d;
	** return Seek(d);
	*/
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f SteeringBehaviors::Evade(const Actor* target)
{
	return -Pursuit(target);
}

sf::Vector2f SteeringBehaviors::Wander()
{
	//To-do
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f SteeringBehaviors::ObstacleAvoidance()
{
	//To-do
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f SteeringBehaviors::WallAvoidance(const sf::Vector2f& target)
{
	//To-do
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f SteeringBehaviors::Interpose(const sf::Vector2f& target)
{
	//To-do
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f SteeringBehaviors::Separation(const std::vector<Actor*>& neighbors)
{
	//To-do
	return sf::Vector2f(0.0f, 0.0f);
}
sf::Vector2f SteeringBehaviors::Cohesion(const std::vector<Actor*>& neighbors)
{
	//To-do
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f SteeringBehaviors::Alignment(const sf::Vector2f& target)
{
	//To-do
	return sf::Vector2f(0.0f, 0.0f);
}