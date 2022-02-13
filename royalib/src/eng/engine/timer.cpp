#include "timer.h"

void Timer::Reset ( ) {
	zero = std::chrono::steady_clock::now ( );
	update = std::chrono::steady_clock::now ( );
}

void Timer::Update ( ) {
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now ( );
	Clock = std::chrono::duration<float> ( now - zero ).count ( );
	deltaTime = std::chrono::duration<float> ( now - update ).count ( );
	update = now;
}
