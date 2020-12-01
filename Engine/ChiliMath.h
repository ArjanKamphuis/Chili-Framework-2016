#pragma once

#include <cmath>

static constexpr double PI_D = 3.14159265358979323846;
static constexpr float PI = static_cast<float>(PI_D);

inline int div_int_ceil(int lhs, int rhs)
{
	return (lhs + rhs - 1) / rhs;
}
