#include "Clock_chrono.hpp"
#include <coco/loop.hpp>
#include <chrono>


namespace coco {

Clock_chrono::Clock_chrono() {
	this->time = loop::now() + 1s;
	coco::timeHandlers.add(*this);
}

Clock_chrono::~Clock_chrono() {	
}

WeekTime Clock_chrono::now() {
	auto time = std::chrono::system_clock::now();
	time_t tt = std::chrono::system_clock::to_time_t(time);
	tm local = *localtime(&tt);
	int seconds = local.tm_sec;
	int minutes = local.tm_min;
	int hours = local.tm_hour;
	int weekDay = (local.tm_wday + 6) % 7;
	return WeekTime(weekDay, hours, minutes, seconds);
}

void Clock_chrono::set(WeekTime now) {
	// not supported
}

Awaitable<> Clock_chrono::secondTick() {
	return {this->waitlist};
}

void Clock_chrono::activate() {
	// next activation in 1s
	this->time += 1s;

	// resume all waiting coroutines
	this->waitlist.resumeAll();
}

} // namespace coco
