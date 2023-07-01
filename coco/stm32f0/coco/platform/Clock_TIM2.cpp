#include "Clock_TIM2.hpp"
#include <coco/platform/platform.hpp>


namespace coco {

Clock_TIM2::Clock_TIM2(Loop_TIM2 &loop) {
	// use channel 2 of RTC0
	TIM2->CCR3 = TIM2->CNT + 1000;
	TIM2->DIER = TIM2->DIER | TIM_DIER_CC3IE; // interrupt enable

	// add to list of handlers
	loop.handlers.add(*this);
}

Clock_TIM2::~Clock_TIM2() {
}

void Clock_TIM2::set(WeekTime now) {
	this->seconds = now.getSeconds();
	this->minutes = now.getMinutes();
	this->hours = now.getHours();
	this->weekday = now.getWeekday();
}

WeekTime Clock_TIM2::now() {
	return WeekTime(this->weekday, this->hours, this->minutes, this->seconds);
}

[[nodiscard]] Awaitable<> Clock_TIM2::secondTick() {
	return {this->tasks};
}

void Clock_TIM2::handle() {
	if (TIM2->SR & TIM_SR_CC3IF) {
		do {
			// advance CCR3
			TIM2->CCR3 = TIM2->CCR3 + 1000;

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
		} while (int(TIM2->CCR3) - int(TIM2->CNT + 1) <= 0);

		// clear pending interrupt flags at peripheral and NVIC
		TIM2->SR = ~TIM_SR_CC3IF;
		clearInterrupt(TIM2_IRQn);

		// resume all waiting coroutines
		this->tasks.resumeAll();
	}
}

} // namespace coco
