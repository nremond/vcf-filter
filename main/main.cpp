#include "utilities.h"
#include "variant.h"
#include "variantcollection.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


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

void printHelp() {
	cerr << "usage: vcfFilter -in <input.vcf> -out <output.vcf> -filter \"AF <= 0.5\"" << endl;
}

vector<string> parseFilter(char *buff) {
	string s(buff);
	vector<string> v;
	split(v, s, ' ');
	return v;
}

function<bool (double, double)> boolOperator(string op) {
	if(op == "<") {
		return [](double a, double b) { return a < b; };
	} else if(op == "<=") {
		return [](double a, double b) { return a <= b; };
	} else if(op == "==") {
		return [](double a, double b) { return a == b; };
	} else if(op == ">") {
		return [](double a, double b) { return a > b; };
	} else if(op == ">=") {
		return [](double a, double b) { return a >= b; };
	} else {
		throw;
	}
}

int main(int argc, char *argv[]) {
    if(cmdOptionExists(argv, argv+argc, "-h")) {
        printHelp();
        return 0;
    }

    char *infilename = getCmdOption(argv, argv + argc, "-in");

    if(!infilename) {
    	cerr << "Missing input vcf filename, use the '-in' argument." << endl;
    	printHelp();
    	return 1;
    }

    char *outfilename = getCmdOption(argv, argv + argc, "-out");

    if(!outfilename) {
    	cerr << "Missing output vcf filename, use the '-out' argument." << endl;
    	printHelp();
    	return 1;
    }

	char *filterDef = getCmdOption(argv, argv + argc, "-filter");

    ifstream infile(infilename);
	if (infile.is_open()) {

		VariantCollection vc;
		infile >> vc;
		infile.close();

		cout << "input file has " << vc.getVariants().size() << " variants" << endl;

		auto filterArgs = parseFilter(filterDef);
		function<bool (const Variant&)> filter;
		Filter filterDoc;
		try {
			auto varName = filterArgs[0];
			auto opSymbol = filterArgs[1];
			auto op = boolOperator(opSymbol);
			auto rhs = stod(filterArgs[2]);

			filter = [&](const Variant &v) 
				{ 
					try	{
					    double lhs = stod(v.getInfos().at(varName));
					    return op(lhs, rhs);
					} catch(...) {
						return true; 
					} 
				};

			std::ostringstream filterId;
			filterId << "Del-" << varName << opSymbol << rhs;

			std::ostringstream filterDesc;
			filterDesc << "Delete when "<< varName << " " << opSymbol << rhs; 

			filterDoc = Filter(filterId.str(), filterDesc.str());
		} catch(...) { 
			cerr << "Invalid filter definition, it should be composed of a '<variable name> <boolean op> <float value>'" << endl;
			printHelp();
			return 1;
		}

		
		VariantCollection vc2(vc, filterDoc, filter);

		cout << "output file has " << vc2.getVariants().size() << " variants" << endl;

		ofstream outFile;
		outFile.open(outfilename);

		outFile << vc2;
		outFile.close();
	} else {
		cerr << "Can't open input file" << endl;
		return 1;
	}

    return 0;
}

	