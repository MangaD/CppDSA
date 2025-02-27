#include <gtest/gtest.h>
#include <list>

// Test that push_back correctly increases the list size.
TEST(ListTest, PushBackSizeTest) {
    std::list<int> lst;
    for (int i = 0; i < 100; ++i) {
        lst.push_back(i);
    }
    EXPECT_EQ(lst.size(), 100);
}

// Test that the first and last elements are as expected.
TEST(ListTest, FirstAndLastElementTest) {
    std::list<int> lst;
    for (int i = 0; i < 100; ++i) {
        lst.push_back(i);
    }
    EXPECT_EQ(lst.front(), 0);
    EXPECT_EQ(lst.back(), 99);
}
