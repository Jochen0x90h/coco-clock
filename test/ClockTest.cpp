#include <coco/loop.hpp>
#include <coco/debug.hpp>
#include <ClockTest.hpp>
#ifdef NATIVE
#include <iostream>
#include <iomanip>
#endif


using namespace coco;

Coroutine test(Clock &clock) {
	while (true) {
		co_await clock.secondTick();
		debug::toggleBlue();

		auto time = clock.now();

#ifdef NATIVE
		const char *weekdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
		std::cout << weekdays[time.getWeekday()]
			<< ' ' << time.getHours()
			<< ':' << std::setw(2) << std::setfill('0') << time.getMinutes()
			<< ':' << std::setw(2) << std::setfill('0') << time.getSeconds() << std::endl;
#else
		debug::setRed((time.getMinutes() & 1) != 0);
		debug::setGreen((time.getHours() & 1) != 0);
#endif
	}
}

int main() {
	debug::init();
	Drivers drivers;

	test(drivers.clock);

	drivers.loop.run();
}
