#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Test that std::sort correctly sorts a vector.
TEST(SortTest, VectorSortTest) {
    std::vector<int> vec = { 5, 2, 9, 1, 5, 6 };
    std::vector<int> expected = { 1, 2, 5, 5, 6, 9 };

    std::sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, expected);
}
