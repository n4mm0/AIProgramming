#include "DwarfIdleState.h"
#include "DwarfWalkState.h"
#include <iostream>

DwarfIdleState* DwarfIdleState::m_oInstance = nullptr;

DwarfIdleState* DwarfIdleState::GetInstance()
{
	if (m_oInstance == nullptr)
	{
		m_oInstance = new DwarfIdleState();
	}
	return m_oInstance;
}

DwarfIdleState::~DwarfIdleState()
{
	delete(m_oInstance);
}

void DwarfIdleState::OnEnter(Dwarf* _Owner)
{
	// Change colour
	std::cout << "Sleeping..." << std::endl;
	_Owner->SetTarget("");
}

void DwarfIdleState::OnUpdate(Dwarf* _Owner)
{
	if (_Owner->GetStamina() < _Owner->MAX_STAMINA)
	{
		_Owner->SetStamina(_Owner->GetStamina() + 1.0f);
		std::cout << "Current stamina " << _Owner->GetStamina() << std::endl;
	}
	else
	{
		_Owner->ChangeState(DwarfWalkState::GetInstance());
	}
}

void DwarfIdleState::OnExit(Dwarf* _Owner)
{
	_Owner->SetTarget("Mines");
}