#include <gtest/gtest.h>

#include "../OverRepresentationAnalysis.hpp"

namespace bmp = boost::multiprecision;
using big_float = bmp::number<bmp::cpp_dec_float<50>>;

TEST(ExpectedValue, interg) {
    int m = 5;
    int n = 2;
    int i = 4;
    float erg = OverRepresentationAnalysis::expected_value(m, i,n);
    ASSERT_EQ(10, erg);
}

TEST(ExpectedValue, floaterg) {
    int m = 73;
    int n = 11;
    int i = 42;
    float x = ((float) (m*i))/n;
    float erg = OverRepresentationAnalysis::expected_value(m, i,n);
    ASSERT_EQ(x, erg); 
}

TEST(PValue, nosum) {
    int i = 1;
    int m = 1;
    int t = 1;
    int n = 2;
    int c = 1;
    big_float x = (big_float) 0.5;
    big_float erg = OverRepresentationAnalysis::p_value(m, t, i, n, c);
    ASSERT_EQ(x, erg);
}

TEST(PValue, sum) {
    int i = 3;
    int m = 2;
    int t = 1;
    int n = 4;
    int c = 1;
    big_float x = 1;
    big_float erg = OverRepresentationAnalysis::p_value(m, t, i, n, c);
    ASSERT_EQ(x, erg);
}

TEST(PValue, cnotnull) {
    int i = 3;
    int m = 2;
    int t = 1;
    int n = 4;
    int c = 3;
    big_float x = 3;
    big_float erg = OverRepresentationAnalysis::p_value(m, t, i, n, c);
    ASSERT_EQ(x, erg);
}