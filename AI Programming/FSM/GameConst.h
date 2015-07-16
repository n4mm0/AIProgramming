#pragma once
#include "SFML\Graphics.hpp"

namespace GameConst
{
	const Vector2		HOME_POSITION		=	Vector2(50.0f, 50.0f);
	const Vector2		MINES_POSITION		=	Vector2(100.0f, 400.0f);
	const sf::Vector2f	SFVEC2_ZERO			=	sf::Vector2f(0.0f, 0.0f);

	const float			MAX_STAMINA			= 50.0f;
	const float			MAX_DWARF_SPD		= 3.0f;
	const int			BACKPACK_CAPACITY	= 10;
}