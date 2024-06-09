#include "Clock_chrono.hpp"
#include <chrono>


namespace coco {

Clock_chrono::Clock_chrono(Loop_native &loop)
    : loop(loop)
    , callback(makeCallback<Clock_chrono, &Clock_chrono::handle>(this))
{
    loop.invoke(this->callback, this->time = loop.now() + 1s);
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
    return {this->tasks};
}

void Clock_chrono::handle() {
    // next activation in 1s
    this->loop.invoke(this->callback, this->time += 1s);

    // resume all waiting coroutines
    this->tasks.doAll();
}

} // namespace coco
