#pragma once

class Actor abstract
{
public:
	virtual ~Actor(){}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void ChangeState() = 0;
	// Should we add get/set Position? Not every actor may want to move..
};