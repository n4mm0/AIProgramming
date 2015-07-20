#include "SteeringBehaviors.h"

#include "Actor.h"
#include "Place.h"
#include "MathUtils.h"

SteeringBehaviors::SteeringBehaviors(Actor* bp) 
	: m_Actor(bp)
	, m_oTarget(nullptr)
	, m_iFlags(0)
{

}

SteeringBehaviors::~SteeringBehaviors()
{
	m_neighbors.clear();
	m_obstacles.clear();
}

void SteeringBehaviors::SetTarget(const Vector2 target)
{
	m_target = target;
}

void SteeringBehaviors::SetEvader(Actor* evader)
{
	m_oTarget = evader;
}

void SteeringBehaviors::Calculate()
{
	m_steering = Vector2::ZERO;
	SumForces();
	//Questo calcolo v� fatto nel calcolo della forza, non qua!
	//float length = sqrt(m_steering.x*m_steering.x + m_steering.y*m_steering.y); <--- Do we still need this? :|

	m_steering.Truncate(m_Actor->GetMaxForce());
}

void SteeringBehaviors::SumForces()
{
	// Single behaviors
	if (SeekIsOn())					m_steering += Seek(m_target);
	if (FleeIsOn())					m_steering += Flee(m_target);
	if (ArriveIsOn())				m_steering += Arrive(m_target);
	if (PursuitIsOn())				m_steering += Pursuit(m_oTarget); 
	if (EvadeIsOn())				m_steering += Evade(m_oTarget); 
	if (WanderIsOn())				m_steering += Wander();
	if (ObstacleAvoidanceIsOn())	m_steering += ObstacleAvoidance();
	if (WallAvoidanceIsOn())		m_steering += WallAvoidance(m_target);
	if (InterposeIsOn())			m_steering += Interpose(m_target);
	
	// Group behaviors
	if (SeparationIsOn())			m_steering += Separation(m_neighbors);
	if (CohesionIsOn())				m_steering += Cohesion(m_neighbors);
	if (AlignmentIsOn())			m_steering += Alignment(m_target);
}

Vector2 SteeringBehaviors::Seek(const Vector2& target)
{
	/*
	** We need to consider actor max velocity and apply it? In order to make it move slower, and not
	** teleport to the target..
	** Also we mentioned something about actor's turn rate at lesson.. Can we consider it 180 degrees
	** (aka instant) for now?
	*/

	Vector2 steering = target - m_Actor->GetPosition();
	steering = steering.NormalizeCopy() * m_Actor->GetMaxVelocity();
	steering = steering - m_Actor->GetVelocity();
	return steering;
}

Vector2 SteeringBehaviors::Flee(const Vector2& target)
{
	return -Seek(target);
}

Vector2 SteeringBehaviors::Arrive(const Vector2& target)
{
	Vector2 steering = target - m_Actor->GetPosition();
	float distance = steering.Length();

	if (distance < m_Actor->GetSightRadius()) //Slowing radius
	{
		steering = steering.NormalizeCopy() * m_Actor->GetMaxVelocity() * (distance / m_Actor->GetSightRadius());
	}
	else
	{
		steering = steering.NormalizeCopy() * m_Actor->GetMaxVelocity();
	}

	steering = steering - m_Actor->GetVelocity();
	return steering;
}

Vector2 SteeringBehaviors::Pursuit(const Actor* target)
{
	//From my notes...
	/*
	** sf::Vector2f d = target->GetPosition() - m_Actor->GetPosition(); 
	** d = d / m_Actor->GetVelocity();
	** d = target->GetVelocity() * d;
	** return Seek(d);
	*/
	return Vector2::ZERO;
}

Vector2 SteeringBehaviors::Evade(const Actor* target)
{
	return -Pursuit(target);
}

Vector2 SteeringBehaviors::Wander()
{
	//To-do
	return Vector2::ZERO;
}

Vector2 SteeringBehaviors::ObstacleAvoidance()
{
	//TO-DO: max see ahead!

	//Search the nearest obstacle since we're going to go around it.
	std::vector<Place*>::iterator it = m_obstacles.begin();
	std::vector<Place*>::iterator end = m_obstacles.end();

	float dynamic_length = m_Actor->GetVelocity().Length() / m_Actor->GetMaxVelocity();
	Vector2 _ahead = m_Actor->GetPosition() + m_Actor->GetVelocity().NormalizeCopy() * dynamic_length * m_Actor->GetSightRadius();

	Place* _nearestObstacle = nullptr;

	for (; it != end; ++it)
	{
		if (LineCircleIntersection(_ahead, (*it)->GetPosition(), (*it)->GetRadius()) 
			&& (_nearestObstacle == nullptr 
				|| (m_Actor->GetPosition().Distance((*it)->GetPosition()) < m_Actor->GetPosition().Distance(_nearestObstacle->GetPosition()))))
		{
			_nearestObstacle = (*it);
		}
	}

	//Calculate the avoidance force
	Vector2 steering;

	if (_nearestObstacle != nullptr)
	{
		steering.x = _ahead.x - _nearestObstacle->GetPosition().x;
		steering.y = _ahead.y - _nearestObstacle->GetPosition().y;
		steering.Truncate(3.0f); //truncate by max avoidance force
	}
	else steering = Vector2::ZERO;

	return steering;
}

Vector2 SteeringBehaviors::WallAvoidance(const Vector2& target)
{
	//To-do
	return Vector2::ZERO;
}

Vector2 SteeringBehaviors::Interpose(const Vector2& target)
{
	//To-do
	return Vector2::ZERO;
}

Vector2 SteeringBehaviors::Separation(const std::vector<Actor*>& neighbors)
{
	Vector2 vRes, vTemp;
	float fMagnitude;
	std::vector<Actor*>::const_iterator vIter = neighbors.cbegin();
	for (; vIter != neighbors.cend(); ++vIter)
	{
		vTemp = (m_Actor->GetPosition() - (*vIter)->GetPosition());
		vTemp.Normalize();
		float radius = 1;	// actor member
		float fProportion = 1.f - (vTemp.Length() / radius);
		vRes += vTemp * fProportion;
	}

	return vRes;
}
Vector2 SteeringBehaviors::Cohesion(const std::vector<Actor*>& neighbors)
{
	//To-do
	return Vector2::ZERO;
}

Vector2 SteeringBehaviors::Alignment(const Vector2& target)
{
	//To-do
	return Vector2::ZERO;
}