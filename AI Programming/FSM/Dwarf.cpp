#include "Dwarf.h"
#include "DwarfIdleState.h"
#include <iostream>

Dwarf::Dwarf() : m_fStamina(0.0f), m_sTarget(""), m_oSprite(nullptr)
{
	std::cout << "Dwarf: Init" << std::endl << std::endl;
	m_oFSM = new FiniteStateMachine<Dwarf>(this);
}

Dwarf::~Dwarf()
{
	delete m_oFSM;
}

void Dwarf::Init()
{
	m_oFSM->ChangeState(DwarfIdleState::GetInstance());
}

void Dwarf::SetupSprite(const sf::Texture& _texture, unsigned int _fw, unsigned int _fh)
{
	m_oSprite = new AnimatedSprite(_fw, _fh);
	m_oSprite->setTexture(_texture);
}

void Dwarf::Update(float _DeltaTime)
{
	m_oFSM->Update();
	if (m_oSprite != nullptr)
	{
		m_oSprite->update(m_vPosition);
	}
}

AnimatedSprite* Dwarf::GetSprite()
{
	return m_oSprite;
}

void Dwarf::SetPosition(const sf::Vector2f& _position)
{
	m_vPosition.x = _position.x;
	m_vPosition.y = _position.y;
}

const sf::Vector2f& Dwarf::GetPosition()
{
	return m_vPosition;
}

void Dwarf::SetTarget(string _Target)
{
	m_sTarget = _Target;
}

string Dwarf::GetTarget() const
{
	return m_sTarget;
}

void Dwarf::SetStamina(float _Stamina)
{
	m_fStamina = _Stamina;
}

float Dwarf::GetStamina() const
{
	return m_fStamina;
}

void Dwarf::SetTime(float _Time)
{
	m_fTime = _Time;
}

float Dwarf::GetTime() const
{
	return m_fTime;
}

void Dwarf::ChangeState(State<Dwarf>* _State)
{
	std::cout << "Dwarf: Calling ChangeState on FSM" << std::endl;
	m_oFSM->ChangeState(_State);
}