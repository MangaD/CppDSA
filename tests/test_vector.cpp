#include <gtest/gtest.h>
#include <vector>

// Test that push_back correctly increases the vector size.
TEST(VectorTest, PushBackSizeTest) {
    std::vector<int> vec;
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }
    EXPECT_EQ(vec.size(), 100);
}

// Test that the elements are in the expected order.
TEST(VectorTest, ElementOrderTest) {
    std::vector<int> vec;
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}
