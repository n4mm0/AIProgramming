#pragma once

#include "State.h"

template <typename T>
class FiniteStateMachine
{
public:
	FiniteStateMachine(T* _Owner) : m_oOwner(_Owner), m_oActualState(nullptr){};
	void ChangeState(State<T>* _newState)
	{
		std::cout << "FSM: Changing state..." << std::endl;
		if (m_oActualState != nullptr)
		{
			m_oActualState->OnExit(m_oOwner);
		}
		m_oActualState = _newState;
		m_oActualState->OnEnter(m_oOwner);
	}
	void Update()
	{
		m_oActualState->OnUpdate(m_oOwner);
	}
private:
	State<T>*	m_oActualState;
	T*		m_oOwner;
};