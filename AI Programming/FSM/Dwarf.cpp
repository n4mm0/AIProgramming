#include "Dwarf.h"
#include "DwarfIdleState.h"
#include <iostream>

Dwarf::Dwarf() : m_fStamina(0.0f), m_sTarget("")
{
	std::cout << "Dwarf: Init" << std::endl << std::endl;
	m_oFSM = new FiniteStateMachine<Dwarf>(this);
}

Dwarf::~Dwarf()
{
	delete m_oFSM;
}

void Dwarf::Init()
{
	m_oFSM->ChangeState(DwarfIdleState::GetInstance());
}

void Dwarf::Update(float _DeltaTime)
{
	m_oFSM->Update();
}

void Dwarf::SetTarget(string _Target)
{
	m_sTarget = _Target;
}

string Dwarf::GetTarget() const
{
	return m_sTarget;
}

void Dwarf::SetStamina(float _Stamina)
{
	m_fStamina = _Stamina;
}

float Dwarf::GetStamina() const
{
	return m_fStamina;
}

void Dwarf::SetTime(float _Time)
{
	m_fTime = _Time;
}

float Dwarf::GetTime() const
{
	return m_fTime;
}

void Dwarf::ChangeState(State<Dwarf>* _State)
{
	std::cout << "Dwarf: Calling ChangeState on FSM" << std::endl;
	m_oFSM->ChangeState(_State);
}