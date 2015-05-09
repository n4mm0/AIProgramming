#include "DwarfIdleState.h"
#include "DwarfWalkState.h"
#include "GameConst.h"
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
	std::cout << "Sleeping..." << std::endl;
	_Owner->SetTarget(GameConst::VEC2_ZERO);
	_Owner->EmptyBackPack();
}

void DwarfIdleState::OnUpdate(Dwarf* _Owner)
{
	if (_Owner->GetStamina() < _Owner->GetMaxStamina())
	{
		_Owner->SetStamina(_Owner->GetStamina() + 0.1f);
		std::cout << "Current stamina " << _Owner->GetStamina() << std::endl;
	}
	else
	{
		_Owner->ChangeState(DwarfWalkState::GetInstance());
	}
}

void DwarfIdleState::OnExit(Dwarf* _Owner)
{
	_Owner->SetTarget(GameConst::MINES_POSITION);
}