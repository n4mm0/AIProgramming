#pragma once

#include "FiniteStateMachine.h"
#include <string>

using namespace std;

class Dwarf
{
public:
	const float MAX_STAMINA = 10.0f;
	const float MAX_TIME = 2.0f;

	Dwarf();
	~Dwarf();

	void Init();
	void Update(float _DeltaTime);
	
	void SetTarget(string _Target);
	string GetTarget() const;
	void SetStamina(float _Stamina);
	float GetStamina() const;
	void SetTime(float _Time);
	float GetTime() const;

	void ChangeState(State<Dwarf>* _State);

private:
	FiniteStateMachine<Dwarf>*	m_oFSM;
	float						m_fStamina;
	float						m_fTime;
	string						m_sTarget;
};