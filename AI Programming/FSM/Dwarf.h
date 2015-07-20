#pragma once

#include "FiniteStateMachine.h"
#include "AnimatedSprite.h"
#include "Actor.h"
#include "SteeringBehaviors.h"
#include "SFML\Graphics.hpp"

class Dwarf : public Actor
{
public:
	Dwarf();
	~Dwarf();
	Dwarf(float _MaxStamina, float _MinStamina, float _MaxVelocity, float _MaxForce, int _BackpackCapacity);

	void Init();
	void Update(float _DeltaTime);
	void Draw(sf::RenderWindow* _window);
	
	void ChangeState(State<Dwarf>* _State);

	void SetupSprite(const sf::Texture& _texture, unsigned int _fw, unsigned int _fh);
	AnimatedSprite* GetSprite(); //E se tornasse una reference invece che un puntatore?

	SteeringBehaviors* GetSteeringBehaviors();
	const FiniteStateMachine<Dwarf>* const GetFSM() const;
	void SetStamina(float _Stamina);
	float GetStamina() const;
	float GetMaxStamina() const;
	float GetMinStamina() const;
	void AddDiamond();
	int GetBackpackSize() const;
	int GetBackpackCapacity() const;
	void EmptyBackPack();

private:
	FiniteStateMachine<Dwarf>*	m_oFSM;
	AnimatedSprite*				m_oSprite;
	SteeringBehaviors*			m_oSteering;

	float						m_fStamina, m_fMaxStamina, m_fMinStamina;
	int							m_iBackpackSize, m_iBackpackCapacity, m_iTimer;
};