// Copyright 2023 Caleb Magruder

#include "gtest/gtest.h"

#include "Object.h"

TEST(tObject, Parse) {
    Object a("{\"a\":4}");
    EXPECT_TRUE(a.contains("a"));
    EXPECT_FALSE(a.contains("b"));
    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(a["a"], 4);
}

TEST(tObject, Empty) {
    Object b("{}");
    EXPECT_EQ(b.size(), 0);
    EXPECT_FALSE(b.contains("a"));
}
TEST(tObject, TerminatingCommas) {
    Object b("{\"a\":4.1,\"b\":false,}");
    EXPECT_EQ(b["a"], 4.1);
    EXPECT_EQ(b["b"], false);
    EXPECT_EQ(b.size(), 2);
}
