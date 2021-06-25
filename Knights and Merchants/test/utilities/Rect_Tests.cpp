#include "gtest/gtest.h"
#include "utilities/Rect.h"

using knights_and_merchants::utilities::Rect;

TEST(RectTests, empty_rectangle_is_at_origin_with_no_size)
{
    // Arrange
    const Rect sut { };

    // Assert
    EXPECT_EQ(sut.left, 0);
    EXPECT_EQ(sut.top, 0);
    EXPECT_EQ(sut.getWidth(), 0);
    EXPECT_EQ(sut.getHeight(), 0);
}

TEST(RectTests, created_rectangle_)
{
    // Arrange
    const Rect sut { 10, 20, 30, 40 };

    // Assert
    EXPECT_EQ(sut.left, 10);
    EXPECT_EQ(sut.top, 20);
    EXPECT_EQ(sut.getWidth(), 30);
    EXPECT_EQ(sut.getHeight(), 40);
}
