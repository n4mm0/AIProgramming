#include "DwarfMiningState.h"
#include "DwarfWalkState.h"
#include "GameConst.h"
#include <iostream>

DwarfMiningState* DwarfMiningState::m_oInstance = nullptr;

DwarfMiningState* DwarfMiningState::GetInstance()
{
	if (m_oInstance == nullptr)
	{
		m_oInstance = new DwarfMiningState();
	}
	return m_oInstance;
}

DwarfMiningState::~DwarfMiningState()
{
	delete(m_oInstance);
}

void DwarfMiningState::OnEnter(Dwarf* _Owner)
{
	// Change colour
	std::cout << "Mining..." << std::endl;
}

void DwarfMiningState::OnUpdate(Dwarf* _Owner)
{
	if (_Owner->GetStamina() > 0.0f)
	{
		_Owner->SetStamina(_Owner->GetStamina() - 0.1f);
		std::cout << "Current stamina " << _Owner->GetStamina() << std::endl;
	}
	else
	{
		_Owner->ChangeState(DwarfWalkState::GetInstance());
	}
}

void DwarfMiningState::OnExit(Dwarf* _Owner)
{
	//_Owner->SetTarget("Home");
	_Owner->SetTarget(GameConst::HOME_POSITION);
}