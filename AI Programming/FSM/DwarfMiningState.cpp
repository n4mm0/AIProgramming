#include "DwarfMiningState.h"
#include "DwarfWalkState.h"
#include "GameConst.h"
#include <iostream>

/*DwarfMiningState* DwarfMiningState::m_oInstance = nullptr;

DwarfMiningState* DwarfMiningState::GetInstance()
{
	if (m_oInstance == nullptr)
	{
		m_oInstance = new DwarfMiningState();
	}
	return m_oInstance;
}*/

DwarfMiningState::~DwarfMiningState()
{
	DwarfMiningState::Release();
}

void DwarfMiningState::OnEnter(Dwarf* _Owner)
{
}

void DwarfMiningState::OnUpdate(Dwarf* _Owner)
{
	if (_Owner->GetBackpackSize() < _Owner->GetBackpackCapacity())
	{
		_Owner->SetStamina(_Owner->GetStamina() - 0.1f);
		_Owner->AddDiamond();
	}
	else
	{
		_Owner->ChangeState(DwarfWalkState::GetSingleton());
	}
}

void DwarfMiningState::OnExit(Dwarf* _Owner)
{
}