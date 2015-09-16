#pragma once

#include "State.h"
#include "Dwarf.h"

class DwarfIdleState : public State<Dwarf>, public Singleton<DwarfIdleState>
{
	IS_SINGLETON(DwarfIdleState);
public:
	//static DwarfIdleState* GetInstance();
	~DwarfIdleState();

	void OnEnter(Dwarf* _Owner);
	void OnUpdate(Dwarf* _Owner);
	void OnExit(Dwarf* _Owner);
private:
	/*DwarfIdleState(){}
	DwarfIdleState(const DwarfIdleState& _Other){}
	DwarfIdleState& operator=(const DwarfIdleState& _Other){}

	static DwarfIdleState* m_oInstance;*/
};