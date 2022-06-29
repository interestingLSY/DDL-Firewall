#pragma once

#include <random>
#include <chrono>

typedef long long uuid_t;

inline uuid_t get_uuid() {
	static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	return rng();
}