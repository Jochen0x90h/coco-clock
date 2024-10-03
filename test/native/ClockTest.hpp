#pragma once

#include <coco/platform/Clock_chrono.hpp>


using namespace coco;

// drivers for ClockTest
struct Drivers {
    Loop_native loop;
    Clock_chrono clock{loop};
};

Drivers drivers;
