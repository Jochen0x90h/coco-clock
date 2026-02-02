#pragma once

#include "ClockTime.hpp"
#include <coco/Coroutine.hpp>


namespace coco {

/// @brief Wall clock interface
///
class Clock {
public:

    virtual ~Clock();

    /// @brief Get current wall clock time including weekday
    /// @return clock time
    virtual WeekTime now() = 0;

    /// @brief Set current wall clock time
    ///
    virtual void set(WeekTime time) = 0;

    /// @brief Suspend execution using co_await until next second tick
    ///
    [[nodiscard]] virtual Awaitable<> secondTick() = 0;
};

} // namespace coco
