#include "DwarfGlobalState.h"
#include "DwarfWalkState.h"
#include "GameConst.h"

/*DwarfGlobalState* DwarfGlobalState::m_oInstance = nullptr;

DwarfGlobalState* DwarfGlobalState::GetInstance()
{
	if (m_oInstance == nullptr)
	{
		m_oInstance = new DwarfGlobalState();
	}
	return m_oInstance;
}*/

DwarfGlobalState::~DwarfGlobalState()
{
	DwarfGlobalState::Release();
}

void DwarfGlobalState::OnUpdate(Dwarf* _Owner)
{
	if (_Owner->GetStamina() <= _Owner->GetMinStamina() && _Owner->GetSteeringBehaviors()->GetTarget() != GameConst::HOME_POSITION)
	{
		_Owner->ChangeState(DwarfWalkState::GetSingleton());
	}
}