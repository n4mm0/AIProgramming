#pragma once

#include "Vector2.h"

inline bool LineCircleIntersection(const Vector2& line, const Vector2& cPosition, float cRadius)
{
	return cPosition.Distance(line) <= cRadius;
}

inline float RandomRange(float low, float high)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}