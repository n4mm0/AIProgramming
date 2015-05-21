#pragma once

template <typename T>
class Actor abstract
{
public:
	virtual ~Actor(){}

	virtual void Init() = 0;
	virtual void Update(float _DeltaTime) = 0;
	virtual void ChangeState(State<T>* _State) = 0;
	// Should we add get/set Position? Not every actor may want to move..
};