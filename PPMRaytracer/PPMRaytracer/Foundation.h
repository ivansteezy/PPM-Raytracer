#ifndef FOUNDATION_H
#define FOUNDATION_H

#include <cmath>
#include <limits>
#include <numbers>			// C++20 hypeee
#include <random>

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = std::numbers::pi;

[[nodiscard]] static constexpr double DegreesToRadiands(double degrees)
{
	return degrees * pi / 180;
}

[[nodiscard]] inline double GenRandomNumber()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	std::mt19937 generator;
	return distribution(generator);
}

[[nodiscard]] inline double GenRandomNumber(double min, double max)
{
	return min + (max - min) * GenRandomNumber();
}

[[nodiscard]] inline double Clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

#include "Vector3.h"
#include "Ray.h"

#endif
