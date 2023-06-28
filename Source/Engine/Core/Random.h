#pragma once
#include <random>

namespace kiko
{
	void seed_random(unsigned int seed) { srand(seed); }
	int random() { return rand(); }
	int random(unsigned int max) { return rand() % max; } //exlusive
	int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); } //inclusive
}