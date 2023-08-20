#pragma once

#include <coco/platform/Loop_TIM2.hpp>
#include <coco/platform/Clock_TIM2.hpp>
#include <coco/board/config.hpp>


using namespace coco;

// drivers for ClockTest
struct Drivers {
	Loop_TIM2 loop{CLOCK};
	Clock_TIM2 clock{loop};
};
