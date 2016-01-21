#pragma once

#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics.hpp"
#include "Vector2.h"

class Actor
{
public:
	virtual ~Actor() {}

	virtual void Init() {}

	virtual void Update(float _DeltaTime) {}

	virtual void Draw(sf::RenderWindow* _window) {}
	
	void SetPosition(Vector2 _newPosition)
	{
		m_vPosition = _newPosition;
	}

	Vector2 GetPosition()
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

	float GetMaxForce() const
	{
		return m_fMaxForce;
	}
	
	float GetSightRadius() const
	{
		return m_fSightRadius;
	}

protected:
	Vector2			m_vPosition, m_vVelocity;
	float			m_fMaxVelocity, m_fMaxForce, m_fSightRadius;
};