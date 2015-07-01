#include "SteeringBehaviors.h"
#include "Actor.h"

SteeringBehaviors::SteeringBehaviors(Actor* bp) 
	: m_Actor(bp)
	, m_oTarget(nullptr)
	, m_iFlags(0)
{
	//m_Actor = bp; //Is m_Actor the owner of the behavior or the Actor to pursuit/evade?
	//Is there more stuff to initialize?
}

SteeringBehaviors::~SteeringBehaviors()
{
	m_neighbors.clear();
	m_obstacles.clear();
}

void SteeringBehaviors::SetTarget(const /*sf::Vector2f*/ Vector2 target)
{
	m_target = target;
}

void SteeringBehaviors::SetEvader(Actor* evader)
{
	//Where am I supposed to save the evader?? m_Actor?
	m_oTarget = evader;
}

void SteeringBehaviors::Calculate()
{
	m_steering = /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
	SumForces();
	/*float length = sqrt(m_steering.x*m_steering.x + m_steering.y*m_steering.y);
	if (length != 0)
	{
		m_steering.x /= length;
		m_steering.y /= length;
	}*/
	
	/*m_steering.Normalize();
	m_steering *= 0.1f * m_Actor->GetVelocity();*/

	if (m_steering.Length() > m_Actor->GetMaxVelocity())
	{
		m_steering.Truncate(m_Actor->GetMaxVelocity());
	}
}

void SteeringBehaviors::SumForces()
{
	//Why do these functions require data that the class already knows? Like target or its neighbors...
	if (SeekIsOn())					m_steering += Seek(m_target);
	if (FleeIsOn())					m_steering += Flee(m_target);
	if (ArriveIsOn())				m_steering += Arrive(m_target);
	if (PursuitIsOn())				m_steering += Pursuit(m_oTarget); //wtf do you want
	if (EvadeIsOn())				m_steering += Evade(m_oTarget); //wtf do you want
	if (WanderIsOn())				m_steering += Wander();
	if (ObstacleAvoidanceIsOn())	m_steering += ObstacleAvoidance();
	if (WallAvoidanceIsOn())		m_steering += WallAvoidance(m_target);
	if (InterposeIsOn())			m_steering += Interpose(m_target);
	
	//Group
	if (SeparationIsOn())			m_steering += Separation(m_neighbors);
	if (CohesionIsOn())				m_steering += Cohesion(m_neighbors);
	if (AlignmentIsOn())			m_steering += Alignment(m_target);
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Seek(const /*sf::Vector2f&*/ Vector2& target)
{
	/*return target - m_Actor->GetPosition();*/

	Vector2 temp = target - m_Actor->GetPosition();
	temp *= 0.1f;
	temp.Normalize();
	if (m_Actor->GetVelocity() == 0.0f)
	{
		//temp *= 0.1f;
		temp.Truncate(0.1f);
	}
	else
	{
		//temp *= 0.1f * m_Actor->GetVelocity();
		temp.Truncate(0.1f * m_Actor->GetVelocity());
	}
	return temp;

	/*
	** We need to consider actor max velocity and apply it? In order to make it move slower, and not
	** teleport to the target..
	** Also we mentioned something about actor's turn rate at lesson.. Can we consider it 180 degrees
	** (aka instant) for now?
	*/
	//return sf::Vector2f(0.0f, 0.0f);
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Flee(const /*sf::Vector2f&*/ Vector2& target)
{
	return -Seek(target); //Is it ok?
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Arrive(const /*sf::Vector2f&*/ Vector2& target)
{
	//Can't remember this one...
	/*
	** Seek the target but adjust your velocity while you are approaching it
	** in order to arrive without "crashing" on it
	*/
	return /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Pursuit(const Actor* target)
{
	//From my notes...
	/*
	** sf::Vector2f d = target->GetPosition() - m_Actor->GetPosition(); 
	** d = d / m_Actor->GetVelocity();
	** d = target->GetVelocity() * d;
	** return Seek(d);
	*/
	return /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Evade(const Actor* target)
{
	return -Pursuit(target);
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Wander()
{
	//To-do
	return /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::ObstacleAvoidance()
{
	//To-do
	return /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::WallAvoidance(const /*sf::Vector2f&*/ Vector2& target)
{
	//To-do
	return /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Interpose(const /*sf::Vector2f&*/ Vector2& target)
{
	//To-do
	return /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Separation(const std::vector<Actor*>& neighbors)
{
	//To-do
	//return sf::Vector2f(0.0f, 0.0f);

	/*sf::Vector2f*/ Vector2 vRes, vTemp;
	float fMagnitude;
	std::vector<Actor*>::const_iterator vIter = neighbors.cbegin();
	for (; vIter != neighbors.cend(); ++vIter)
	{
		vTemp = (m_Actor->GetPosition() - (*vIter)->GetPosition());
		/*fMagnitude = sqrt(vTemp.x*vTemp.x + vTemp.y*vTemp.y);
		if (fMagnitude != 0)
		{
			vTemp.x = vTemp.x / fMagnitude;
			vTemp.y = vTemp.y / fMagnitude;
		}*/
		vTemp.Normalize();
		float radius = 1;	// actor member
		float fProportion = 1.f - (/*fMagnitude*/ vTemp.Length() / radius);
		vRes += vTemp * fProportion;
	}

	return vRes;
}
/*sf::Vector2f*/ Vector2 SteeringBehaviors::Cohesion(const std::vector<Actor*>& neighbors)
{
	//To-do
	return /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
}

/*sf::Vector2f*/ Vector2 SteeringBehaviors::Alignment(const /*sf::Vector2f&*/ Vector2& target)
{
	//To-do
	return /*sf::Vector2f(0.0f, 0.0f)*/ Vector2::ZERO;
}