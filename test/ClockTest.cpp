#include <coco/loop.hpp>
#include <coco/debug.hpp>
#include <coco/StreamOperators.hpp>
#include <ClockTest.hpp>


using namespace coco;

Coroutine test(Clock &clock) {
    int s = 0;
    while (true) {
        co_await clock.secondTick();

        // get time
        auto time = clock.now();

        // toggle LEDs
        s ^= 1 | ((time.getMinutes() & 1) << 1) | ((time.getHours() & 1) << 2);
        debug::set(s);

        const char *weekdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
        debug::out << weekdays[int(time.getWeekday())]
            << ' ' << dec(time.getHours())
            << ':' << dec(time.getMinutes(), 2)
            << ':' << dec(time.getSeconds(), 2) << '\n';
    }
}

int main() {
    test(drivers.clock);

    drivers.loop.run();
}
