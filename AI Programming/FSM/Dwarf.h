#pragma once

#include "FiniteStateMachine.h"
#include "AnimatedSprite.h"
#include <string>

using namespace std;

class Dwarf
{
public:

	Dwarf();
	~Dwarf();
	Dwarf(float _MaxStamina, int _BackpackCapacity);

	void Init();
	void SetupSprite(const sf::Texture& _texture, unsigned int _fw, unsigned int _fh);
	void Update(float _DeltaTime);
	
	AnimatedSprite* GetSprite(); //E se tornasse una reference invece che un puntatore?
	void SetPosition(const sf::Vector2f& _position);
	const sf::Vector2f& GetPosition();
	//void Move(const sf::Vector2f& _position);
	void AddForce(const sf::Vector2f& _vector);
	void SetTarget(sf::Vector2f _Target);
	sf::Vector2f GetTarget() const;
	void SetStamina(float _Stamina);
	float GetStamina() const;
	float GetMaxStamina() const;
	void AddDiamond();
	int GetBackpackSize() const;
	int GetBackpackCapacity() const;
	void EmptyBackPack();

	void ChangeState(State<Dwarf>* _State);

private:
	FiniteStateMachine<Dwarf>*	m_oFSM;
	AnimatedSprite*				m_oSprite;
	sf::Vector2f				m_vPosition;
	sf::Vector2f				m_vMoveDirection;
	sf::Vector2f				m_vTarget;
	float						m_fStamina, m_fMaxStamina;
	int							m_iBackpackSize, m_iBackpackCapacity;
};