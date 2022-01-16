#pragma once

#include <iostream>
#include <chrono>

class Timer {
private:
	std::chrono::duration<double> time_spent_;
	std::chrono::steady_clock::time_point last_update_;
	std::chrono::duration<double> time_since_last_update_;
	std::chrono::steady_clock::time_point last_tick_;
	std::chrono::duration<double> time_since_last_tick_;
	unsigned int average_interval_;
	unsigned int ticks_since_last_update_;

public:
	Timer(const unsigned int interval);

	void Tick();
	double GetDeltaTime();
};