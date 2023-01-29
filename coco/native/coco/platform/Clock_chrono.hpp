#include <coco/Clock.hpp>
#include <coco/platform/Loop_native.hpp>


namespace coco {

/**
 * Implementation of the Clock interface using std::chrono
*/
class Clock_chrono : public Clock, public TimeHandler {
public:

	Clock_chrono(Loop_native &loop);
	~Clock_chrono() override;

	WeekTime now() override;
	void set(WeekTime now) override;
	[[nodiscard]] Awaitable<> secondTick() override;

protected:
	void handle();

	// waiting coroutines
	Waitlist<> waitlist;
};

} // namespace coco
