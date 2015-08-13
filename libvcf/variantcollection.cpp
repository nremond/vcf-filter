#include "utilities.h"
#include "variantcollection.h"

#include <iostream>
#include <sstream>
#include <ios>

using namespace std;

/////

bool startWith(const string &s, const string &prefix) {
	return s.size() >= prefix.size()
        && equal(prefix.begin(), prefix.end(), s.begin());
}

////

VariantCollection::VariantCollection() {}

VariantCollection::VariantCollection(const VariantCollection &vc, std::function<bool(const Variant&)> filter)
	:fileFormat(vc.fileFormat), filters(vc.filters), headers(vc.headers), variants(vc.variants.size()) {

	std::function<bool (const Variant&)> keep = [&](const Variant &v) { return filter(v); };
	auto it = copy_if(vc.variants.begin(), vc.variants.end(), variants.begin(), keep);
	variants.resize(std::distance(variants.begin(), it));  

	// TODO add a line in the filters
}

string FILTER_ID = "ID=";
string FILTER_DESC = "Description=\"";

std::istream &operator>>(std::istream &in, VariantCollection &vc) {

	std::getline(in, vc.fileFormat);

	string line;
	while (std::getline(in, line) && line[0]=='#') {
		if(startWith(line, "##FILTER")) {
			auto idStart = line.find(FILTER_ID) + FILTER_ID.size();
			auto idEnd = line.find(",", idStart) - idStart;
			auto descStart = line.find(FILTER_DESC, idEnd) + FILTER_DESC.size();
			auto descEnd = line.find("\"", descStart) - descStart;

			if(idStart!=std::string::npos && idEnd!=std::string::npos
				&& descStart!=std::string::npos && descEnd!=std::string::npos) {

				auto id = line.substr(idStart, idEnd);
				auto desc = line.substr(descStart, descEnd);
				vc.filters.push_back(Filter(id, desc));

			} else {
				in.setstate(ios::failbit);
			}
		} else {
			vc.headers.push_back(line);
		}
	}

	
	do {
		Variant v;
    	std::stringstream ss(line);
    	ss >> v;

    	vc.variants.push_back(v);
	} while(std::getline(in, line));

	return in;
}

std::ostream &operator<<(std::ostream &out, const VariantCollection &vc) {
	// File format
	out << vc.fileFormat << endl;

	// All filter declarations
	for(auto f : vc.filters) {
		out << "##FILTER=<ID=" << f.getId() << ",Description=\"" << f.getDesc() << "\">" << endl;
	}

	// All other headers
	copy(vc.headers.begin(), vc.headers.end(), ostream_iterator<string>(out, "\n") );

	// All variants
	copy(vc.variants.begin(), vc.variants.end(), ostream_iterator<Variant>(out, "\n") );	

	return out;
}
