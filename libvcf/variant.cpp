#include "variant.h"
#include "utilities.h"

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


////////////

std::ostream& operator<<(std::ostream& out, ReferenceBase rb)
{
    return out << static_cast<char>(rb);
}

std::ostream& operator<<(std::ostream& out, AlternateBase rb)
{
    return out << static_cast<char>(rb);
}

////////////

Variant::Variant() {};

istream &operator>>(istream  &in, Variant &v) {
	string buff;

	//1
	in >> v.chromosome;
	
	//2
	in >> v.position;
	
	//3
	in >> buff;
	splitn(v.identifier, buff, ';');

	//4
	in >> buff;
	for(char c : buff) {
		v.refBase.push_back(static_cast<ReferenceBase>(c));
	}

	//5
	in >> buff;
	for(char c : buff) {
		v.altBase.push_back(static_cast<AlternateBase>(c));
	}

	//6
	in >> v.quality;

	//7
	in >> v.filterStatus;

	//8
	in >> buff;
	vector<string> keyValues;
	splitn(keyValues, buff, ';');
	for(auto kv : keyValues) {
		auto p = split2(kv, '=');
		v.infos[p.first] = p.second;
	}

	//9
	while(in.good()) {
		in >> buff;
		v.extras.push_back(buff);
	}

	return in;
}

ostream &operator<<(ostream &out, const Variant &v) {
	auto delim = "\t";

	//1
	out << v.chromosome << delim;

	//2
	out << v.position << delim;

	//3
	out << join(v.identifier, ";") << delim;

	//4 
	copy(v.refBase.begin(), v.refBase.end(), ostream_iterator<ReferenceBase>(out));
	out << delim;

	//5 
	copy(v.altBase.begin(), v.altBase.end(), ostream_iterator<AlternateBase>(out));
	out << delim;

	//6
	int quality = v.quality;
	if((v.quality-quality) < 0.01) {
		out << quality << delim;
	} else {
		out << setprecision (2) << fixed << v.quality << delim;
	}

	//7
	out << v.filterStatus << delim;

	//8 
	vector<string> keyValues;
  	transform(v.infos.begin(), v.infos.end(), std::back_inserter(keyValues),
                 [](auto p) { return (p.second.empty())? p.first : p.first + "=" + p.second; });
  	out << join(keyValues, ";") << delim;

	//9
	out << join(v.extras, delim);

	return out;
}