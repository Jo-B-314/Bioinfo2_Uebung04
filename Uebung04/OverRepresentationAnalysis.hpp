#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
 
namespace bmp = boost::multiprecision;
using big_float = bmp::number<bmp::cpp_dec_float<50>>;
 
#include <boost/math/special_functions/binomial.hpp>

class OverRepresentationAnalysis {

public:
    /**
     * computes the p value 
     * for a biological process
     * the p-values will be adjusted via bonferoni adjustment
     * i = #Testset
     * m = #Category
     * t = #(Testset n Category)
     * n = #Reference
     * c = #Categories
     **/
    static big_float p_value(int m, int t, int i, int n, int c);

    /**
     * computes the expected value for a biological process
     * m = #Category
     * i = #Testset
     * n = #Reference
     **/
    static double expected_value(int m, int i, int n);

};
