#pragma once

#include "SFML\System\Vector2.hpp"
#include "Vector2.h"

class Actor
{
public:
	virtual ~Actor(){}

	virtual void Init(float _MaxVelo)
	{
		m_fMaxVelocity = _MaxVelo;
	};

	virtual void Update(float _DeltaTime)
	{
	};

	void SetPosition(/*sf::Vector2f*/ Vector2 _newPosition)
	{
		m_vPosition = _newPosition;
	}

	/*sf::Vector2f*/ Vector2 GetPosition()
	{
		return m_vPosition;
	}
	
	void SetVelocity(Vector2 _Velo)
	{
		m_vVelocity = _Velo;
	}
	
	Vector2 GetVelocity() const
	{
		return m_vVelocity;
	}
	
	float GetMaxVelocity() const
	{
		return m_fMaxVelocity;
	}
	
protected:
	float			/*m_fVelocity*/ m_fMaxVelocity;
	//sf::Vector2f	m_vPosition;
	Vector2			m_vPosition, m_vVelocity;
};