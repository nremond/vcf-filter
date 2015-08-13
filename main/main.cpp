#include "variant.h"
#include "variantcollection.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// string str = "chr6	44387517	rs6923521	C	G	184.84	PASS	AC=2;AF=1.00;AN=2;DB;DP=6;FS=0.000;MLEAC=2;MLEAF=1.00;MQ=60.00;MQ0=0;POSITIVE_TRAIN_SITE;QD=30.81;SOR=3.912;VQSLOD=6.47;culprit=FS	GT:AD:DP:GQ:PL	1/1:0,6:6:18:213,18,0";
//     stringstream ss(str);    

//     Variant v;
// 	ss >> v;

// 	cout << "Yo Nico" << endl;
// 	cout << v << endl;
// }


char* getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[]) {
    if(cmdOptionExists(argv, argv+argc, "-h")) {
        // Do stuff
    }

    char *infilename = getCmdOption(argv, argv + argc, "-in");

    if(!infilename) {
    	cout << "Missing input vcf filename, use the '-in' argument." << endl;
    	return 0;
    }

    char *outfilename = getCmdOption(argv, argv + argc, "-out");

    if(!outfilename) {
    	cout << "Missing output vcf filename, use the '-out' argument." << endl;
    	return 0;
    }


    ifstream infile(infilename);
	if (infile.is_open()) {

		VariantCollection vc;
		infile >> vc;
		infile.close();

		cout << "YO NICO nb variants= " << vc.getVariants().size() << endl;
		cout << "YO NICO nb headers= " << vc.getHeaders().size() << endl;

	

		ofstream outFile;
		outFile.open(outfilename);

		outFile << vc;
		outFile.close();
	}

    return 0;
}

	