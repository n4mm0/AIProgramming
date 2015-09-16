#include "Place.h"

Place::Place() : m_vPosition(0.0f, 0.0f), m_fRadius(0.0f)
{

}

Place::Place(Vector2 _position, float _radius, sf::Texture& _texture) : m_vPosition(_position), m_fRadius(_radius)
{
	setTexture(_texture);
	setPosition(sf::Vector2f(_position.x - getTexture()->getSize().x / 2, _position.y - getTexture()->getSize().y / 2));
}

Place::~Place()
{

}

void Place::Draw(sf::RenderWindow* _window)
{
	_window->draw(*this);
}

const Vector2& Place::GetPosition()
{
	return m_vPosition;
}

float Place::GetRadius()
{
	return m_fRadius;
}