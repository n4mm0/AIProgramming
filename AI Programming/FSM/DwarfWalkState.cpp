#include "DwarfWalkState.h"
#include "DwarfMiningState.h"
#include "DwarfIdleState.h"
#include "GameConst.h"
#include <iostream>
#include <math.h>

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
	if (_Owner->GetFSM()->GetPreviousState() == DwarfMiningState::GetInstance() || _Owner->GetStamina() <= _Owner->GetMinStamina())
	{
		_Owner->GetSteeringBehaviors()->SetTarget(GameConst::HOME_POSITION);
		_Owner->GetSteeringBehaviors()->SeekOn();
	}
	else if (_Owner->GetFSM()->GetPreviousState() == DwarfIdleState::GetInstance())
	{
		_Owner->GetSteeringBehaviors()->SetTarget(GameConst::MINES_POSITION);
		_Owner->GetSteeringBehaviors()->SeekOn();
	}
}

void DwarfWalkState::OnUpdate(Dwarf* _Owner)
{
	/*sf::Vector2f*/ Vector2 _target = _Owner->GetSteeringBehaviors()->GetTarget();
	float distance = powf(_Owner->GetPosition().x - _target.x, 2) + powf(_Owner->GetPosition().y - _target.y, 2);
	distance = sqrtf(distance);

	//Visto la posizione del nano non arriverà mai ad essere esattamente uguale a quella del target,
	//Ho pensato di calcolare la distanza fra i due punti, se è minore di un certo limite, allora è arrivato!
	if (_target == GameConst::MINES_POSITION && distance <2.0f)
	{
		_Owner->ChangeState(DwarfMiningState::GetInstance());
	}
	else if (_target == GameConst::HOME_POSITION && distance <2.0f)
	{
		_Owner->ChangeState(DwarfIdleState::GetInstance());
	}
	//else
	//{
	//	sf::Vector2f direction = _Owner->GetTarget() - _Owner->GetPosition();
	//	//Let's normalize the vector!
	//	float length = sqrt(direction.x*direction.x + direction.y*direction.y);
	//	if (length != 0)
	//	{
	//		direction.x /= length;
	//		direction.y /= length;
	//	}
	//	direction *= 0.1f; //Apply deltatime!
	//	_Owner->AddForce(direction); //Move the damn dwarf!
	//}
}

void DwarfWalkState::OnExit(Dwarf* _Owner)
{
	_Owner->GetSteeringBehaviors()->SeekOff();
}