#include "Dwarf.h"
#include "DwarfIdleState.h"
#include "DwarfGlobalState.h"
#include "GameConst.h"
#include <iostream>

Dwarf::Dwarf() : m_fStamina(0.0f), m_iBackpackSize(0), m_iTimer(0), m_oSprite(nullptr)
{
	m_fMaxStamina = GameConst::MAX_STAMINA;
	m_iBackpackCapacity = GameConst::BACKPACK_CAPACITY;
	m_fMaxVelocity = GameConst::MAX_DWARF_SPD;
	m_oFSM = new FiniteStateMachine<Dwarf>(this, DwarfGlobalState::GetInstance());
	m_oSteering = new SteeringBehaviors(this);
}

Dwarf::~Dwarf()
{
	delete m_oFSM;
}

Dwarf::Dwarf(float _MaxStamina, float _MinStamina, float _MaxVelocity, float _MaxForce, float _SightRadius, int _BackpackCapacity)
	:	m_fStamina(0.0f), m_iBackpackSize(0), m_iTimer(0), m_oSprite(nullptr),
		m_fMaxStamina(_MaxStamina), m_fMinStamina(_MinStamina),
		m_iBackpackCapacity(_BackpackCapacity)
{
	m_fMaxVelocity = _MaxVelocity;
	m_fMaxForce = _MaxForce;
	m_fSightRadius = _SightRadius;
	m_oFSM = new FiniteStateMachine<Dwarf>(this, DwarfGlobalState::GetInstance());
	m_oSteering = new SteeringBehaviors(this);
}

void Dwarf::Init()
{
	Actor::Init();
	m_oFSM->ChangeState(DwarfIdleState::GetInstance());
}

void Dwarf::SetupSprite(const sf::Texture& _texture, unsigned int _fw, unsigned int _fh)
{
	m_oSprite = new AnimatedSprite(_fw, _fh);
	m_oSprite->setTexture(_texture);
}

void Dwarf::Update(float _DeltaTime)
{
	Actor::Update(_DeltaTime);
	m_oFSM->Update();

	m_oSteering->Calculate();
	//m_vVelocity = m_oSteering->GetForce();

	Vector2 vSteering = m_vVelocity + m_oSteering->GetForce(); //velocity = truncate (velocity + steering , max_speed)
	vSteering.Truncate(m_fMaxVelocity);
	m_vVelocity = vSteering;

	m_vPosition += m_vVelocity * _DeltaTime;

	//Change animation based on moveDirection
	if (m_vVelocity.y < 0)
	{
		m_oSprite->playAnim("walkUp");
	}
	else if (m_vVelocity.y > 0)
	{
		m_oSprite->playAnim("walkDown");
	}
	else
	{
		m_oSprite->playAnim("idle");
	}

	// We're done with the forces of this frame
	// m_vMoveDirection = sf::Vector2f(0.0f, 0.0f);

	//Time to update the sprite
	if (m_oSprite != nullptr)
	{
		m_oSprite->Update(m_vPosition.GetSfVec());
	}
}

void Dwarf::Draw(sf::RenderWindow* _window)
{
	Actor::Draw(_window);

	if (_window != nullptr)
	{
		_window->draw(*m_oSprite);
	}
}

AnimatedSprite* Dwarf::GetSprite()
{
	return m_oSprite;
}

const FiniteStateMachine<Dwarf>* const Dwarf::GetFSM() const
{
	return m_oFSM;
}

SteeringBehaviors* Dwarf::GetSteeringBehaviors()
{
	return m_oSteering;
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
	m_oFSM->ChangeState(_State);
}