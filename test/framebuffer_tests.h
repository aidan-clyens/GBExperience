#include "gtest/gtest.h"


TEST(FrameBuffer, InitFrameBuffer) {
    int width = 256;
    int height = 256;

    FrameBuffer buffer(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            EXPECT_EQ(WHITE, buffer.get_pixel(x, y));
        }
    }
}


TEST(FrameBuffer, SetPixel) {
    int width = 256;
    int height = 256;

    int x_target = 10;
    int y_target = 25;

    FrameBuffer buffer(width, height);

    buffer.set_pixel(x_target, y_target, BLACK);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (x == x_target && y == y_target) {
                EXPECT_EQ(BLACK, buffer.get_pixel(x, y));
            }
            else {
                EXPECT_EQ(WHITE, buffer.get_pixel(x, y));
            }
        }
    }
}