#pragma once

#include <coco/platform/Loop_emu.hpp>
#include <coco/platform/Clock_chrono.hpp>


using namespace coco;

// drivers for ClockTest
struct Drivers {
    Loop_emu loop;
    Clock_chrono clock{loop};
};

Drivers drivers;
