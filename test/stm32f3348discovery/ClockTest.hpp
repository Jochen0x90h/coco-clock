#pragma once

#include <coco/platform/Loop_TIM2.hpp>
#include <coco/platform/Clock_Loop.hpp>
#include <coco/board/config.hpp>


using namespace coco;

// drivers for ClockTest
struct Drivers {
    Loop_TIM2 loop{SYS_CLOCK};

    Clock_Loop clock{loop};
};

Drivers drivers;
