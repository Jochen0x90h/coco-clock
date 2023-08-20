#include <coco/loop.hpp>
#include <coco/debug.hpp>
#include <ClockTest.hpp>
#ifdef NATIVE
#include <iostream>
#include <iomanip>
#endif


using namespace coco;

Coroutine test(Clock &clock) {
	int s = 0;
	while (true) {
		co_await clock.secondTick();

		// toggle all LEDs every second
		s ^= 7;

		// get time
		auto time = clock.now();
		int t = (time.getMinutes() & 1) | ((time.getHours() & 1) << 2);

		debug::set(s ^ t);

#ifdef NATIVE
		const char *weekdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
		std::cout << weekdays[time.getWeekday()]
			<< ' ' << time.getHours()
			<< ':' << std::setw(2) << std::setfill('0') << time.getMinutes()
			<< ':' << std::setw(2) << std::setfill('0') << time.getSeconds() << std::endl;
#endif
	}
}

int main() {
	debug::init();
	Drivers drivers;

	test(drivers.clock);

	drivers.loop.run();
}
