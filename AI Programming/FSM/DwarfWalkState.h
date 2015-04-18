#pragma once

#include "State.h"
#include "Dwarf.h"

class DwarfWalkState : public State<Dwarf>
{
public:
	static DwarfWalkState* GetInstance();
	~DwarfWalkState();

	void OnEnter(Dwarf* _Owner);
	void OnUpdate(Dwarf* _Owner);
	void OnExit(Dwarf* _Owner);
private:
	DwarfWalkState(){}
	DwarfWalkState(const DwarfWalkState& _Other){}
	DwarfWalkState& operator=(const DwarfWalkState& _Other){}

	static DwarfWalkState*	m_oInstance;
};