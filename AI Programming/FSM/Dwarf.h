#pragma once

#include "FiniteStateMachine.h"
#include "AnimatedSprite.h"
#include "Actor.h"
#include "SteeringBehaviors.h"

class Dwarf : public Actor
{
public:
	Dwarf();
	~Dwarf();
	Dwarf(float _MaxStamina, float _MinStamina, int _BackpackCapacity);

	void Init();
	void Update(float _DeltaTime);
	
	void ChangeState(State<Dwarf>* _State);

	void SetupSprite(const sf::Texture& _texture, unsigned int _fw, unsigned int _fh);
	AnimatedSprite* GetSprite(); //E se tornasse una reference invece che un puntatore?

	//void SetPosition(const sf::Vector2f& _position);
	//const sf::Vector2f& GetPosition();
	//void AddForce(const sf::Vector2f& _vector);
	//void SetTarget(sf::Vector2f _Target);
	//sf::Vector2f GetTarget() const;
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
	//sf::Vector2f				m_vVelocity;
	//Vector2					m_vVelocity;
	/*sf::Vector2f				m_vPosition;
	sf::Vector2f				m_vMoveDirection;
	sf::Vector2f				m_vTarget;*/
	float						m_fStamina, m_fMaxStamina, m_fMinStamina;
	int							m_iBackpackSize, m_iBackpackCapacity, m_iTimer;
};