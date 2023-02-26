// Copyright 2023 Caleb Magruder

#include "gtest/gtest.h"

#include "Variant.h"

TEST(tVariant, ParseDouble) {
    Variant a("4");    // Integer-valued double
    EXPECT_EQ(a, 4);     // Integer comparison
    EXPECT_EQ(a, 4.0);   // Double comparison

    Variant b("3.14");   // Fractional-valued double
    EXPECT_NE(b, 3);     // Integer comparison
    EXPECT_EQ(b, 3.14);  // Integer comparison

    Variant c(" 3");     // Preceding space
    EXPECT_EQ(c, 3);     // Integer comparison

    Variant d("2 ");     // Postceding space
    EXPECT_EQ(d, 2);     // Integer comparison
}
