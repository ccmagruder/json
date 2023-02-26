// Copyright 2023 Caleb Magruder

#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "Variant.h"

TEST(tVariant, ParseBool) {
    std::vector<std::string>::const_iterator i;

    const std::vector<std::string> valid_true = {
        "true", " true", "true ",
        "True", " True", "True ",
        "TRUE", " TRUE", "TRUE "
    }; 
    for (i = valid_true.begin(); i != valid_true.end(); i++) {
        EXPECT_EQ(Variant(*i), true);
    }

    const std::vector<std::string> valid_false = {
        "false", " false", "false ",
        "False", " False", "False ",
        "FALSE", " FALSE", "FALSE "
    }; 
    for (i = valid_false.begin(); i != valid_false.end(); i++) {
        EXPECT_EQ(Variant(*i), false);
    }

    const std::vector<std::string> invalid_bool = {
        "[2,5]", "4", "4.0", "null", "{\"a\":4}", "\"true\"", "\"false\""
    };
    for (i = invalid_bool.begin(); i != invalid_bool.end(); i++) {
        EXPECT_NE(Variant(*i), true);
        EXPECT_NE(Variant(*i), false);
    }
}

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
