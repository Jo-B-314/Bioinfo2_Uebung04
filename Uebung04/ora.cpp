#include "OverRepresentationAnalysis.hpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <fstream>

using namespace std;
namespace bmp = boost::multiprecision;
using big_float = bmp::number<bmp::cpp_dec_float<50>>;

#include <boost/math/special_functions/binomial.hpp>

int main(int argc, char* argv[]) {
	string h = "-h";
	string help = "--help";
	for (int i = 0; i < argc; i++) {
		if (h.compare(argv[i]) == 0 || help.compare(argv[i]) == 0) {
			//-h or --help found
			cout << "Help window:\n";
			cout << "-r[FILE]: required, file with our reference set\n";
			cout << "-s[FILE]: required, file with our test set\n ";
			cout << "-b[FILE]: required, file with the biological processes\n";
			return 0;
		}
	}
	if (argc != 7) {
		cerr << "Wrong number of arguments. Use -h or --help to open the help menu.\n";
		return 1;
	}
	string r = "-r";
	string reference_path;
	string s = "-s";
	string test_path;
	string b = "-b";
	string bio_path;
	for (int i = 0; i < argc; i++) {
		if (!r.compare(argv[i])) {
			if (i+1 >= argc) {
				cerr << "No reference file given. Use -h or --help to open the help menu.\n";
				return 1;
			}
			if (!reference_path.empty()) {
				cerr << "More than one reference file given. Use -h or --help to open the help menu.\n";
				return 1;
			}
			reference_path = argv[i+1];
		} 
		if (!s.compare(argv[i])) {
			if (i+1 >= argc) {
				cerr << "No test file given. Use -h or --help to open the help menu.\n";
				return 1;
			}
			if (!test_path.empty()) {
				cerr << "More than one test file given. Use -h or --help to open the help menu.\n";
				return 1;
			}
			test_path = argv[i+1];
		}
		if (!b.compare(argv[i])) {
			if (i+1 >= argc) {
				cerr << "No file with biological processes given. Use -h or --help to open the help menu.\n";
				return 1;
			}
			if (!bio_path.empty()) {
				cerr << "More than one file with biological processes given. Use -h or --help to open the help menu.\n";
				return 1;
			}
			bio_path = argv[i+1];
		}
	}
	if (bio_path.empty() || test_path.empty() || reference_path.empty()) {
		cerr << "Not all required arguments given. Use -h or --help to open the help menu.\n";
		return 1;
	}
	
	//read reference_set.txt, test_set.txt and biological_processes.txt
	ifstream reference_set(reference_path);
	vector<string> ref_vec;
	string line;
	while (getline(reference_set, line)) {
		ref_vec.push_back(line);
	}
	ifstream test_set(test_path);
	vector<string> test_vec;
	while (getline(test_set, line)) {
		test_vec.push_back(line);
	}
	ifstream bio_proc(bio_path);
	vector<vector<string>> bio_vec;
	vector<string> names;
	while (getline(bio_proc, line)) {
		vector<string> genes;
		char c = '\t';
		size_t pos = line.find(c);
		size_t initialPos = 0;
		int m = 0;
		for ( ; pos != std::string::npos; m++) {
			if (m >= 2) {
				genes.push_back(line.substr(initialPos, pos - initialPos));
			}
			if (m == 0) {
				names.push_back(line.substr(initialPos, pos - initialPos));
			}
			initialPos = pos + 1;
			pos = line.find(c, initialPos);
		}
		bio_vec.push_back(genes);
	}
	reference_set.close();
	test_set.close();
	bio_proc.close();

	//erwartungswert und p-value berechnen und in zugehörigen vector schreiben
	vector<double> exp_values;
	vector<big_float> p_value;
	int n = ref_vec.size();
	int i = test_vec.size();
	cout << "angereicherte Prozesse:\n";
	for (size_t j = 0; j < bio_vec.size(); j++) {
		//erwartungswert
		double exp_val = OverRepresentationAnalysis::expected_value(bio_vec[j].size(), i, n);
		exp_values.push_back(exp_val);
		//p-value
		int t = 0;
		for (size_t k = 0; k < bio_vec[j].size(); k++) {
			for (size_t l = 0; l < test_vec.size(); l++) {
				if ( !bio_vec[j][k].compare(test_vec[l]) ) {
					t++;
				}
			}
		}
		big_float p = OverRepresentationAnalysis::p_value(bio_vec[j].size(), t, i, n, bio_vec.size());
		p_value.push_back(p);
		if (p < 0.05) {
			cout << names[j] << " p-value = " << p << endl;
		}
	}


	return 0;
}