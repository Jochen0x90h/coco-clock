#include <coco/Clock.hpp>
#include <coco/platform/Loop_native.hpp>


namespace coco {

/// @brief Implementation of the Clock interface using std::chrono
///
class Clock_chrono : public Clock, public Loop_native::TimeoutHandler {
public:

    Clock_chrono(Loop_native &loop);
    ~Clock_chrono() override;

    WeekTime now() override;
    void set(WeekTime now) override;
    [[nodiscard]] Awaitable<CoroutineTask<>> secondTick() override;

protected:
    void onTimeout() override;

    Loop_native &loop_;

    TimeMilliseconds<> time_;

    // waiting coroutines
    CoroutineTaskList<> tasks_;
};

} // namespace coco
