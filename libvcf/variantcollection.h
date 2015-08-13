#ifndef VARIANTCOLLECTION_H
#define VARIANTCOLLECTION_H

#include "utilities.h"

#include <string>
#include <vector>
#include <map>

class VariantCollection {
private:
	//std:string fileFormat;

public:
    VariantCollection();
    // default copy-constructor is fine

    friend std::istream &operator>>(std::istream &in, VariantCollection &vc);
	friend std::ostream &operator<<(std::ostream &out, const VariantCollection &vc);
};


#endif /* VARIANTCOLLECTION_H */