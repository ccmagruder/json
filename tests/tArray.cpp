// Copyright 2023 Caleb Magruder

#include "gtest/gtest.h"

#include "Array.h"

TEST(tArray, Parse) {
    Array a("[4,6,7]");
    EXPECT_EQ(a[1], 6.0);
    Array c("[3.14]");
    EXPECT_EQ(c.size(), 1);
    EXPECT_EQ(c[0], 3.14);
}

TEST(tArray, Empty) {
    Array b("[]");
    EXPECT_EQ(b.size(), 0);
}

TEST(tArray, TerminatingCommas) {
    Array a("[1,3,]");
    EXPECT_EQ(a[0], 1.);
    EXPECT_EQ(a[1], 3.);
    EXPECT_EQ(a.size(), 2);
}