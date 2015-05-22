#pragma once

class Actor abstract
{
public:
	virtual ~Actor(){}

	virtual void Init() = 0;
	virtual void Update(float _DeltaTime) = 0;
	// Should we add get/set Position? Not every actor may want to move..
};