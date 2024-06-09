#include <coco/ClockTime.hpp>
#include <gtest/gtest.h>


using namespace coco;


// ClockTime
// ---------

TEST(cocoClockTest, ClockTime) {
    ClockTime t(10, 50, 37);

    EXPECT_EQ(t.getHours(), 10);
    EXPECT_EQ(t.getMinutes(), 50);
    EXPECT_EQ(t.getSeconds(), 37);
}


// AlarmTime
// ---------

TEST(cocoClockTest, AlarmTime) {
    WeekTime t(0, 10, 50, 37); // monday
    AlarmTime a1(1, 10, 50, 37);
    AlarmTime a2(2, 10, 50, 37);

    EXPECT_TRUE(a1.matches(t));
    EXPECT_FALSE(a2.matches(t));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    int success = RUN_ALL_TESTS();
    return success;
}
