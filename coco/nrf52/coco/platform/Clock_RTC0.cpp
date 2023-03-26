#include "Clock_RTC0.hpp"
#include <coco/platform/platform.hpp>


namespace coco {

Clock_RTC0::Clock_RTC0(Loop_RTC0 &loop) {
	// use channel 2 of RTC0
	NRF_RTC0->CC[2] = (NRF_RTC0->COUNTER + 16384 + 256) & ~16383;
	NRF_RTC0->INTENSET = N(RTC_INTENSET_COMPARE2, Set);

	// add to list of handlers
	loop.handlers.add(*this);
}

Clock_RTC0::~Clock_RTC0() {
}

WeekTime Clock_RTC0::now() {
	return WeekTime(this->weekday, this->hours, this->minutes, this->seconds);
}

void Clock_RTC0::set(WeekTime now) {
	this->seconds = now.getSeconds();
	this->minutes = now.getMinutes();
	this->hours = now.getHours();
	this->weekday = now.getWeekday();
}

[[nodiscard]] Awaitable<> Clock_RTC0::secondTick() {
	return {this->tasks};
}

void Clock_RTC0::handle() {
	if (NRF_RTC0->EVENTS_COMPARE[2]) {
		do {
			// advance CC[2]
			NRF_RTC0->CC[2] = NRF_RTC0->CC[2] + 16384;

			// increment clock time
			if (++this->seconds == 60) {
				this->seconds = 0;
				if (++this->minutes == 60) {
					this->minutes = 0;
					if (++this->hours == 24) {
						this->hours = 0;
						if (++this->weekday == 7)
							this->weekday = 0;
					}
				}
			}
		} while (int(NRF_RTC0->CC[2]) - int(NRF_RTC0->COUNTER + 16) <= 0);

		// clear pending interrupt flags at peripheral and NVIC
		NRF_RTC0->EVENTS_COMPARE[2] = 0;
		clearInterrupt(RTC0_IRQn);

		// resume all waiting coroutines
		this->tasks.resumeAll();
	}
}

} // namespace coco
