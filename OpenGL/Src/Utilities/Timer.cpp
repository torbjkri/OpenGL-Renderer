#include "Timer.h"


typedef std::chrono::steady_clock my_clock;

/*
TODO: Show FPS on screen. (Overlay)
*/

Timer::Timer(unsigned int interval)
	: time_spent_(0)
	, last_update_(my_clock::now())
	, time_since_last_update_(0)
	, last_tick_(my_clock::now())
	, time_since_last_tick_(0)
	, average_interval_(interval)
	, ticks_since_last_update_(0)
{
	clock();
	std::cout << "Timer started!\n";
}

void Timer::Tick()
{
	ticks_since_last_update_++;
	auto now = my_clock::now();

	time_since_last_tick_ = now - last_tick_;
	time_spent_ += time_since_last_tick_;
	last_tick_ = now;

	if (ticks_since_last_update_ == average_interval_) {
		ticks_since_last_update_ = 0;
		time_since_last_update_ = now - last_update_;
		last_update_ = now;
		std::cout << "Average FPS: " << static_cast<double>(average_interval_) / time_since_last_update_.count() << std::endl;
	}
}

double Timer::GetDeltaTime()
{
	return time_since_last_tick_.count();
}
