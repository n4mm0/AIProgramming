#include "DwarfIdleState.h"
#include "DwarfWalkState.h"
#include "GameConst.h"
#include <iostream>

/*DwarfIdleState* DwarfIdleState::m_oInstance = nullptr;

DwarfIdleState* DwarfIdleState::GetInstance()
{
	if (m_oInstance == nullptr)
	{
		m_oInstance = new DwarfIdleState();
	}
	return m_oInstance;
}*/

DwarfIdleState::~DwarfIdleState()
{
	DwarfIdleState::Release();
}

void DwarfIdleState::OnEnter(Dwarf* _Owner)
{
	_Owner->SetStamina(_Owner->GetMinStamina() + 0.5f);
	_Owner->EmptyBackPack();
}

void DwarfIdleState::OnUpdate(Dwarf* _Owner)
{
	if (_Owner->GetStamina() < _Owner->GetMaxStamina())
	{
		_Owner->SetStamina(_Owner->GetStamina() + 0.1f);
	}
	else
	{
		_Owner->ChangeState(DwarfWalkState::GetSingleton());
	}
}

void DwarfIdleState::OnExit(Dwarf* _Owner)
{
}