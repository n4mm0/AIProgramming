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
}

void DwarfWalkState::OnUpdate(Dwarf* _Owner)
{
	float distance = powf(_Owner->GetPosition().x - _Owner->GetTarget().x, 2) + powf(_Owner->GetPosition().y - _Owner->GetTarget().y, 2);
	distance = sqrtf(distance);

	//Visto la posizione del nano non arriverà mai ad essere esattamente uguale a quella del target,
	//Ho pensato di calcolare la distanza fra i due punti, se è minore di un certo limite, allora è arrivato!
	if (_Owner->GetTarget() == GameConst::MINES_POSITION && distance <2.0f)
	{
		_Owner->ChangeState(DwarfMiningState::GetInstance());
	}
	else if (_Owner->GetTarget() == GameConst::HOME_POSITION && distance <2.0f)
	{
		_Owner->ChangeState(DwarfIdleState::GetInstance());
	}
	else
	{
		sf::Vector2f direction = _Owner->GetTarget() - _Owner->GetPosition();
		//Let's normalize the vector!
		float length = sqrt(direction.x*direction.x + direction.y*direction.y);
		if (length != 0)
		{
			direction.x /= length;
			direction.y /= length;
		}
		direction *= 0.1f; //Apply deltatime!
		_Owner->AddForce(direction); //Move the damn dwarf!
	}
}

void DwarfWalkState::OnExit(Dwarf* _Owner)
{
	// Do nothing
}