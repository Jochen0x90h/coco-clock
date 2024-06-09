#include <coco/Clock.hpp>
#include <coco/platform/Loop_native.hpp>


namespace coco {

/**
 * Implementation of the Clock interface using std::chrono
*/
class Clock_chrono : public Clock {
public:

    Clock_chrono(Loop_native &loop);
    ~Clock_chrono() override;

    WeekTime now() override;
    void set(WeekTime now) override;
    [[nodiscard]] Awaitable<> secondTick() override;

protected:
    void handle();

    Loop_native &loop;
    TimedTask<Callback> callback;

    TimeMilliseconds<> time;

    // waiting coroutines
    CoroutineTaskList<> tasks;
};

} // namespace coco
