#pragma once

class Actor
{
public:
	virtual ~Actor(){}

	virtual void Init(float _Velo)
	{
		m_fMaxVelocity = _Velo;
	};

	virtual void Update(float _DeltaTime)
	{
	};
	
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
	float	m_fVelocity, m_fMaxVelocity;

};