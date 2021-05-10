#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

namespace bmp = boost::multiprecision;
using big_float = bmp::number<bmp::cpp_dec_float<50>>;

#include <boost/math/special_functions/binomial.hpp>

int main() {
	big_float example = boost::math::binomial_coefficient<big_float>(20000, 4328);
	std::cout << example.convert_to<double>() << std::endl;
}
