#pragma once

#include "Vector2.h"

inline bool LineCircleIntersection(const Vector2& line, const Vector2& cPosition, float cRadius)
{
	return cPosition.Distance(line) <= cRadius;
}