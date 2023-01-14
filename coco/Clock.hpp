#pragma once

#include "ClockTime.hpp"
#include <coco/Coroutine.hpp>


namespace coco {

/**
 * Wall clock interface
 */
class Clock {
public:

	virtual ~Clock();

	/**
	 * Get current wall clock time including weekday
	 * @return clock time
	 */
	virtual WeekTime now() = 0;

	/**
	 * Set current wall clock time
	 */
	virtual void set(WeekTime now) = 0;

	/**
	 * Suspend execution using co_await until next second tick
	 */
	[[nodiscard]] virtual Awaitable<> secondTick() = 0;
};

} // namespace coco
