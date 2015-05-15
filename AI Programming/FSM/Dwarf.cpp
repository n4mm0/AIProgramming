#include "Dwarf.h"
#include "DwarfIdleState.h"
#include "DwarfGlobalState.h"
#include "GameConst.h"
#include <iostream>

Dwarf::Dwarf() : m_fStamina(0.0f), m_iBackpackSize(0), m_iTimer(0), m_oSprite(nullptr)
{
	std::cout << "Dwarf: Init" << std::endl << std::endl;
	m_fMaxStamina = GameConst::MAX_STAMINA;
	m_iBackpackCapacity = GameConst::BACKPACK_CAPACITY;
	m_oFSM = new FiniteStateMachine<Dwarf>(this, DwarfGlobalState::GetInstance());
}

Dwarf::~Dwarf()
{
	delete m_oFSM;
}

Dwarf::Dwarf(float _MaxStamina, float _MinStamina, int _BackpackCapacity) : m_fStamina(0.0f), m_iBackpackSize(0), m_iTimer(0), m_oSprite(nullptr)
{
	std::cout << "Dwarf: Init" << std::endl << std::endl;
	m_fMaxStamina = _MaxStamina;
	m_fMinStamina = _MinStamina;
	m_iBackpackCapacity = _BackpackCapacity;
	m_oFSM = new FiniteStateMachine<Dwarf>(this, DwarfGlobalState::GetInstance());
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

float Dwarf::GetMaxStamina() const
{
	return m_fMaxStamina;
}

float Dwarf::GetMinStamina() const
{
	return m_fMinStamina;
}

void Dwarf::AddDiamond()
{
	if (m_iTimer > 10)
	{
		++m_iBackpackSize;
		m_iTimer = 0;
	}
	else
	{
		++m_iTimer;
	}
}

int Dwarf::GetBackpackSize() const
{
	return m_iBackpackSize;
}

int Dwarf::GetBackpackCapacity() const
{
	return m_iBackpackCapacity;
}

void Dwarf::EmptyBackPack()
{
	m_iBackpackSize = 0;
}

void Dwarf::ChangeState(State<Dwarf>* _State)
{
	std::cout << "Dwarf: Calling ChangeState on FSM" << std::endl;
	m_oFSM->ChangeState(_State);
}