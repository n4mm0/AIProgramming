#pragma once

#include "State.h"

template <typename T>
class FiniteStateMachine
{
public:
	FiniteStateMachine(T* _Owner, State<T>* _GlobalState) : m_oOwner(_Owner), m_oGlobalState(_GlobalState), m_oActualState(nullptr), m_oPreviousState(nullptr){};
	void ChangeState(State<T>* _newState)
	{
		if (m_oActualState != nullptr)
		{
			m_oActualState->OnExit(m_oOwner);
		}
		m_oPreviousState = m_oActualState;
		m_oActualState = _newState;
		m_oActualState->OnEnter(m_oOwner);
	}
	void Update()
	{
		m_oGlobalState->OnUpdate(m_oOwner);
		m_oActualState->OnUpdate(m_oOwner);
	}
private:
	State<T>*	m_oPreviousState;
	State<T>*	m_oActualState;
	State<T>*	m_oGlobalState;
	T*		m_oOwner;
};