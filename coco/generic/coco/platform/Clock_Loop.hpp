#pragma once

#include <coco/Clock.hpp>
#include <coco/Loop.hpp>


namespace coco {

/**
 * Implementation of the Clock interface using the event loop
 */
class Clock_Loop : public Clock {
public:
    /**
     * Constructor
     * @param loop event loop
     */
    Clock_Loop(Loop &loop);

    ~Clock_Loop() override;

    WeekTime now() override;
    void set(WeekTime time) override;
    [[nodiscard]] Awaitable<> secondTick() override;

protected:
    // gets called from the event loop to update the clock and notify the main application
    Coroutine update();

    Loop &loop;

    uint8_t seconds = 0;
    uint8_t minutes = 0;
    uint8_t hours = 0;
    uint8_t weekday = 0;

    // coroutines waiting on secondTick()
    CoroutineTaskList<> tasks;

    // must be last
    Coroutine updateCoroutine;
};

} // namespace coco
