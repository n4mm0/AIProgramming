#pragma once

#include "State.h"
#include "Dwarf.h"

class DwarfMiningState : public State<Dwarf>
{
public:
	static DwarfMiningState* GetInstance();
	~DwarfMiningState();

	void OnEnter(Dwarf* _Owner);
	void OnUpdate(Dwarf* _Owner);
	void OnExit(Dwarf* _Owner);
private:
	DwarfMiningState(){}
	DwarfMiningState(const DwarfMiningState& _Other){}
	DwarfMiningState& operator=(const DwarfMiningState& _Other){}

	static DwarfMiningState*	m_oInstance;
};