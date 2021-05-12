#include "OverRepresentationAnalysis.hpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/special_functions/binomial.hpp>

namespace bmp = boost::multiprecision;
using big_float = bmp::number<bmp::cpp_dec_float<50>>;

big_float OverRepresentationAnalysis::p_value(int m, int t, int i, int n, int c) {
    big_float sum = 0;
    for (int k = t; k <= std::min(m,i); k++) {
        big_float p1 = boost::math::binomial_coefficient<big_float>(m, k);
	    big_float p2 = boost::math::binomial_coefficient<big_float>(n-m, i-k);
	    big_float p3 = boost::math::binomial_coefficient<big_float>(n, i);
	    sum += (p1*p2)/p3;
    }
    //bonferoni adjustment
	return sum * c;
}

double OverRepresentationAnalysis::expected_value(int m, int i, int n) {
    double erg = ((double) (m*i))/n;
    return erg;
}