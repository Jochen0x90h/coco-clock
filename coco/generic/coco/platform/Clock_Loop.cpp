#include "Clock_Loop.hpp"


namespace coco {

Clock_Loop::Clock_Loop(Loop &loop)
    : loop(loop)
    , updateCoroutine(update())
{
}

Clock_Loop::~Clock_Loop() {
    this->updateCoroutine.destroy();
}

void Clock_Loop::set(WeekTime now) {
    this->seconds = now.getSeconds();
    this->minutes = now.getMinutes();
    this->hours = now.getHours();
    this->weekday = now.getWeekday();
}

WeekTime Clock_Loop::now() {
    WeekTime time(this->weekday, this->hours, this->minutes, this->seconds);
    return time;
}

[[nodiscard]] Awaitable<> Clock_Loop::secondTick() {
    return {this->tasks};
}

Coroutine Clock_Loop::update() {
    auto time = this->loop.now();
    while (true) {
        // increment time and sleep
        co_await this->loop.sleep(time += 1s);

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

        // notify application
        this->tasks.doAll();
    }
}

} // namespace coco
