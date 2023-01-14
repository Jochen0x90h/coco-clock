#include <coco/loop.hpp>
#include <coco/debug.hpp>
#include <ClockTest.hpp>
#ifdef NATIVE
#include <iostream>
#endif


using namespace coco;

Coroutine test(Clock &clock) {
	while (true) {
		co_await clock.secondTick();
		debug::toggleBlue();

		auto time = clock.now();

#ifdef NATIVE
		const char *weekdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
		std::cout << weekdays[time.getWeekday()] << ' ' << time.getHours() << ':' << time.getMinutes() << ':' << time.getSeconds() << std::endl;
#else
		debug::setRed((time.getMinutes() & 1) != 0);
		debug::setGreen((time.getHours() & 1) != 0);
#endif
	}
}

int main() {
	debug::init();
	board::ClockTest drivers;

	test(drivers.clock);
	
	loop::run();
}
