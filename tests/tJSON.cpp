// Copyright 2022 Caleb Magruder

#include "gtest/gtest.h"

#include "JSON.h"

TEST(tJSON, EqualityOperator) {
    JSON config("validTypes.json");

    EXPECT_EQ(config["number"], -1.0);
    EXPECT_NE(config["number"], true);

    EXPECT_EQ(config["bool"], true);
    EXPECT_NE(config["bool"], false);
    EXPECT_NE(config["bool"], std::string("wrong"));

    EXPECT_EQ(config["null"], nullptr);
    EXPECT_NE(config["null"], Array("[4,3]"));

    const char* s = "value";
    const char* t = "wrong value";
    EXPECT_EQ(config["string"], std::string(s));
    EXPECT_NE(config["string"], std::string(t));
    EXPECT_EQ(config["string"], s);
    EXPECT_NE(config["string"], t);

    EXPECT_EQ(config["array"], Variant("[4,3,16]"));
    EXPECT_EQ(config["array"], Array("[4,3,16]"));
    EXPECT_NE(config["array"], Variant("[-1,3,16]"));
    EXPECT_NE(config["array"], Array("[4,16]"));

    EXPECT_EQ(config["object"],
              Object("{\"key\":\"pair\",\"key2\":[3.14,false]}"));
    EXPECT_NE(config["object"],
              Object("{\"key\":\"pair\",\"key2\":[3.1,false]}"));
    EXPECT_NE(config["object"],
              Object("{\"key\":\"pair\",\"key2\":[3.14,false,4]}"));
    EXPECT_NE(config["object"], Array("[4,16]"));

    std::clog << config << std::endl;
}

TEST(tJSON, Array) {
    Array a("[4,6,7]");
    EXPECT_EQ(a[1], 6.0);
    Array b("[]");
    EXPECT_EQ(b.size(), 0);
    Array c("[3.14]");
    EXPECT_EQ(c.size(), 1);
    EXPECT_EQ(c[0], 3.14);
}

TEST(tJSON, Object) {
    Object a("{\"a\":4}");
    EXPECT_TRUE(a.contains("a"));
    EXPECT_FALSE(a.contains("b"));
    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(static_cast<double>(a["a"]), 4);
    Object b("{}");
    EXPECT_EQ(b.size(), 0);
    EXPECT_FALSE(b.contains("a"));
}

TEST(tJSON, TerminatingCommas) {
    Array a("[1,3,]");
    EXPECT_EQ(a[0], 1.);
    EXPECT_EQ(a[1], 3.);
    EXPECT_EQ(a.size(), 2);
    Object b("{\"a\":4.1,\"b\":false,}");
    EXPECT_EQ(static_cast<double>(b["a"]), 4.1);
    EXPECT_EQ(b["b"], false);
    EXPECT_EQ(b.size(), 2);
}
