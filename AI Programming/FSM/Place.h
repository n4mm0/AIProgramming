#pragma once

#include "Vector2.h"
#include "SFML\Graphics.hpp"

class Place : public sf::Sprite
{
public:
	Place();
	Place(Vector2 _position, float _radius, sf::Texture& _texture);
	~Place();

	void Draw(sf::RenderWindow* _window);

	const Vector2& GetPosition();
	float GetRadius();

private:
	sf::Texture* m_tSprite;

	Vector2 m_vPosition;
	float m_fRadius;
};