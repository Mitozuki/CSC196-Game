#pragma once
#include <cmath>

namespace kiko
{
	constexpr float pi = 3.1415926535f;
	constexpr float twoPi = 6.283185307f;
	constexpr float halfPi = 1.57079632675f;

	constexpr float RadiansToDeg(float radians) { return radians * (180.0f / pi); }
	constexpr float DegreesToRad(float degrees) { return degrees * (pi / 180.0f); }

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}
} 