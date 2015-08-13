#include "utilities.h"
#include "variantcollection.h"

#include <iostream>
#include <sstream>

using namespace std;





std::istream &operator>>(std::istream &in, VariantCollection &vc) {

	return in;
}

std::ostream &operator<<(std::ostream &out, const VariantCollection &vc) {

	return out;
}
