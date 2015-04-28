#pragma once

#include "FiniteStateMachine.h"
#include "AnimatedSprite.h"
#include <string>

using namespace std;

class Dwarf
{
public:
	const float MAX_STAMINA = 10.0f;
	const float MAX_TIME = 2.0f;

	Dwarf();
	~Dwarf();

	void Init();
	void SetupSprite(const sf::Texture& _texture, unsigned int _fw, unsigned int _fh);
	void Update(float _DeltaTime);
	
	AnimatedSprite* GetSprite(); //E se tornasse una const reference invece che un puntatore?
	void SetPosition(const sf::Vector2f& _position);
	const sf::Vector2f& GetPosition();
	void SetTarget(string _Target);
	string GetTarget() const;
	void SetStamina(float _Stamina);
	float GetStamina() const;
	void SetTime(float _Time);
	float GetTime() const;

	void ChangeState(State<Dwarf>* _State);

private:
	FiniteStateMachine<Dwarf>*	m_oFSM;
	AnimatedSprite*				m_oSprite;
	sf::Vector2f				m_vPosition;
	float						m_fStamina;
	float						m_fTime;
	string						m_sTarget;
};