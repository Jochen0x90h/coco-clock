#pragma once

#include <coco/platform/Loop_RTC0.hpp>
#include <coco/platform/Clock_Loop.hpp>


using namespace coco;

// drivers for ClockTest
struct Drivers {
    Loop_RTC0 loop;

    Clock_Loop clock{loop};
};

Drivers drivers;
