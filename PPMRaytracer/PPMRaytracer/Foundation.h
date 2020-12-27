#ifndef FOUNDATION_H
#define FOUNTACION_H

#include <cmath>
#include <limits>
#include <numbers>			// C++20 hypeee

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = std::numbers::pi;

static constexpr double DegreesToRadiands(double degrees)
{
	return degrees * pi / 180;
}

#include "Vector3.h"
#include "Ray.h"

#endif
