#include "DwarfWalkState.h"
#include "DwarfMiningState.h"
#include "DwarfIdleState.h"
#include "GameConst.h"
#include "World.h"
#include <iostream>
#include <math.h>

/*DwarfWalkState* DwarfWalkState::m_oInstance = nullptr;

DwarfWalkState* DwarfWalkState::GetInstance()
{
	if (m_oInstance == nullptr)
	{
		m_oInstance = new DwarfWalkState();
	}
	return m_oInstance;
}*/

DwarfWalkState::~DwarfWalkState()
{
	DwarfWalkState::Release();
}

void DwarfWalkState::OnEnter(Dwarf* _Owner)
{
	_Owner->GetSteeringBehaviors()->SetObstacles(World::GetInstance()->GetPlaces());
	_Owner->GetSteeringBehaviors()->ObstacleAvoidanceOn();
	if (_Owner->GetFSM()->GetPreviousState() == DwarfMiningState::GetSingleton() || _Owner->GetStamina() <= _Owner->GetMinStamina())
	{
		//_Owner->GetSteeringBehaviors()->SetTarget(GameConst::HOME_POSITION);
		//_Owner->GetSteeringBehaviors()->SeekOn();
		//_Owner->GetSteeringBehaviors()->ArriveOn();
		_Owner->GetSteeringBehaviors()->WanderOn();
	}
	else if (_Owner->GetFSM()->GetPreviousState() == DwarfIdleState::GetSingleton())
	{
		//_Owner->GetSteeringBehaviors()->SetTarget(GameConst::MINES_POSITION);
		//_Owner->GetSteeringBehaviors()->SeekOn();
		//_Owner->GetSteeringBehaviors()->ArriveOn();
		_Owner->GetSteeringBehaviors()->WanderOn();
	}
}

void DwarfWalkState::OnUpdate(Dwarf* _Owner)
{
	Vector2 target = _Owner->GetSteeringBehaviors()->GetTarget();
	float distance = target.Distance(_Owner->GetPosition());

	//Visto la posizione del nano non arriverà mai ad essere esattamente uguale a quella del target,
	//Ho pensato di calcolare la distanza fra i due punti, se è minore di un certo limite, allora è arrivato!
	if (target == GameConst::MINES_POSITION && distance < 2.0f)
	{
		_Owner->ChangeState(DwarfMiningState::GetSingleton());
	}
	else if (target == GameConst::HOME_POSITION && distance < 2.0f)
	{
		_Owner->ChangeState(DwarfIdleState::GetSingleton());
	}
}

void DwarfWalkState::OnExit(Dwarf* _Owner)
{
	_Owner->SetVelocity(Vector2::ZERO); //Not necessary but otherwise there's always some very small velocity left.
	//_Owner->GetSteeringBehaviors()->SeekOff();
	_Owner->GetSteeringBehaviors()->ObstacleAvoidanceOff();
	_Owner->GetSteeringBehaviors()->ArriveOff();
}