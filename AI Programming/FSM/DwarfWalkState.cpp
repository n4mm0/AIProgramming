#include "DwarfWalkState.h"
#include "DwarfMiningState.h"
#include "DwarfIdleState.h"
#include <iostream>

DwarfWalkState* DwarfWalkState::m_oInstance = nullptr;

DwarfWalkState* DwarfWalkState::GetInstance()
{
	if (m_oInstance == nullptr)
	{
		m_oInstance = new DwarfWalkState();
	}
	return m_oInstance;
}

DwarfWalkState::~DwarfWalkState()
{
	delete(m_oInstance);
}

void DwarfWalkState::OnEnter(Dwarf* _Owner)
{
	// Change colour
	std::cout << "Walking towards " << _Owner->GetTarget() << std::endl;
	_Owner->SetTime(0.0f);
}

void DwarfWalkState::OnUpdate(Dwarf* _Owner)
{
	if (_Owner->GetTime() < _Owner->MAX_TIME)
	{
		_Owner->SetTime(_Owner->GetTime() + 0.1f);
	}
	else
	{
		if (_Owner->GetTarget() == "Mines")
		{
			_Owner->ChangeState(DwarfMiningState::GetInstance());
		}
		else if (_Owner->GetTarget() == "Home")
		{
			_Owner->ChangeState(DwarfIdleState::GetInstance());
		}
	}
}

void DwarfWalkState::OnExit(Dwarf* _Owner)
{
	// Do nothing
}