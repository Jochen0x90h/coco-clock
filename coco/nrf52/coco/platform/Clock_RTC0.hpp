#pragma once

#include <coco/Clock.hpp>
#include <coco/platform/Loop_RTC0.hpp>


namespace coco {

/**
 * Implementation of the Clock interface using RTC0
 * 
 * Resources:
 *	NRF_RTC0
 *		CC[2]
 */
class Clock_RTC0 : public Clock, public Handler {
public:

	Clock_RTC0(Loop_RTC0 &loop);
	~Clock_RTC0() override;

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
