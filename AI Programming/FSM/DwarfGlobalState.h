#pragma once

#include "Singleton.h"
#include "State.h"
#include "Dwarf.h"

class DwarfGlobalState : public State<Dwarf>, public Singleton<DwarfGlobalState>
{
	IS_SINGLETON(DwarfGlobalState);
public:
	//static DwarfGlobalState* GetInstance();
	~DwarfGlobalState();

	void OnEnter(Dwarf* _Owner) {}
	void OnUpdate(Dwarf* _Owner);
	void OnExit(Dwarf* _Owner) {}
private:
	/*DwarfGlobalState(){}
	DwarfGlobalState(const DwarfGlobalState& _Other){}
	DwarfGlobalState& operator=(const DwarfGlobalState& _Other){}

	static DwarfGlobalState* m_oInstance;*/
};