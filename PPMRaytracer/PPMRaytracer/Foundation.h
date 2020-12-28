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
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> distrib(0.0, 1.0);
	return distrib(gen);
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

#include "Ray.h"
#endif
