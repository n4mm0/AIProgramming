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
	
	void SetVelocity(float _Velo)
	{
		m_fVelocity = _Velo;
	}
	
	float GetVelocity() const
	{
		return m_fVelocity;
	}
	
	float GetMaxVelocity() const
	{
		return m_fMaxVelocity;
	}
	
protected:
	float			m_fVelocity, m_fMaxVelocity;
	//sf::Vector2f	m_vPosition;
	Vector2			m_vPosition;
};