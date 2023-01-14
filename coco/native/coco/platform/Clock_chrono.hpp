#include <coco/Clock.hpp>
#include <coco/platform/Handler.hpp>


namespace coco {

/**
 * Implementation of the Clock interface using std::chrono
*/
class Clock_chrono : public Clock, public TimeHandler {
public:

	Clock_chrono();
	~Clock_chrono() override;

	WeekTime now() override;
	void set(WeekTime now) override;
	[[nodiscard]] Awaitable<> secondTick() override;

	void activate();

protected:

	// waiting coroutines
	Waitlist<> waitlist;
};

} // namespace coco
