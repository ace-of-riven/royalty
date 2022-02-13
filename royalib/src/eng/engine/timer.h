#pragma once

#include <chrono>

class Timer {
	std::chrono::steady_clock::time_point zero;
	std::chrono::steady_clock::time_point update;
public:
	void Reset ( ) ;
	void Update ( ) ;

	float Clock;
	float deltaTime;
};
