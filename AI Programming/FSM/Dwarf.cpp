#include "Dwarf.h"
#include "DwarfIdleState.h"
#include <iostream>

Dwarf::Dwarf() : m_fStamina(0.0f), m_oSprite(nullptr)
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

	//Let's apply the force!
	m_vPosition += m_vMoveDirection;

	//Change animation based on moveDirection
	if (m_vMoveDirection.y < 0)
	{
		m_oSprite->playAnim("walkUp");
	}
	else
	{
		m_oSprite->playAnim("walkDown");
	}

	//We're done with the forces of this frame
	m_vMoveDirection = sf::Vector2f(0.0f, 0.0f);

	//Time to update the sprite
	if (m_oSprite != nullptr)
	{
		m_oSprite->Update(m_vPosition);
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

void Dwarf::AddForce(const sf::Vector2f& _vector)
{
	m_vMoveDirection += _vector;
}

/*void Dwarf::Move(const sf::Vector2f& _position)
{
	m_vPosition += _position;
}*/

void Dwarf::SetTarget(sf::Vector2f _Target)
{
	m_vTarget = _Target;
}

sf::Vector2f Dwarf::GetTarget() const
{
	return m_vTarget;
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