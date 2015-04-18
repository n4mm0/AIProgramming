#pragma once

template <typename T>
class State abstract
{
public:
	virtual ~State(){}
	virtual void OnEnter(T* _Owner) = 0;
	virtual void OnUpdate(T* _Owner) = 0;
	virtual void OnExit(T* _Owner) = 0;
};