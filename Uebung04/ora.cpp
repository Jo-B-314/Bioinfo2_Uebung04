#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <fstream>

using namespace std;
namespace bmp = boost::multiprecision;
using big_float = bmp::number<bmp::cpp_dec_float<50>>;

#include <boost/math/special_functions/binomial.hpp>

int main() {
	big_float example = boost::math::binomial_coefficient<big_float>(20000, 4328);
	//std::cout << example.convert_to<double>() << std::endl;
	//read reference_set.txt, test_set.txt and biological_processes.txt
	ifstream reference_set("../reference_set.txt");
	vector<string> ref_vec;
	string line;
	while (getline(reference_set, line)) {
		ref_vec.push_back(line);
	}
	ifstream test_set("../test_set.txt");
	vector<string> test_vec;
	while (getline(test_set, line)) {
		test_vec.push_back(line);
	}
	ifstream bio_proc("../biological_processes.txt");
	vector<vector<string>> bio_vec;
	while (getline(bio_proc, line)) {
		vector<string> genes;
		char c = '\t';
		size_t pos = line.find(c);
		size_t initialPos = 0;
		int m = 0;
		for ( ; pos != std::string::npos; m++) {
			if (m >= 2) {
				cout << line.substr(initialPos, pos - initialPos) << endl;
				genes.push_back(line.substr(initialPos, pos - initialPos));
			}
			initialPos = pos + 1;
			pos = line.find(c, initialPos);
		}
		bio_vec.push_back(genes);
	}
	reference_set.close();
	test_set.close();
	bio_proc.close();
	return 0;
}
