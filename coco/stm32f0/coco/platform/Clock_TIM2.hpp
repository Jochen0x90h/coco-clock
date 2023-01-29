#pragma once

#include <coco/Clock.hpp>
#include <coco/platform/Loop_TIM2.hpp>


namespace coco {

/**
 * Implementation of the Clock interface using RTC0
 * 
 * Resources:
 *	TIM2
 *		CCR3
 */
class Clock_TIM2 : public Clock, public Handler {
public:

	Clock_TIM2(Loop_TIM2 &loop);
	~Clock_TIM2() override;

	WeekTime now() override;
	void set(WeekTime now) override;
	[[nodiscard]] Awaitable<> secondTick() override;

	void handle() override;

protected:

	uint8_t seconds = 0;
	uint8_t minutes = 0;
	uint8_t hours = 0;
	uint8_t weekday = 0;

	// waiting coroutines
	Waitlist<> waitlist;
};

} // namespace coco
