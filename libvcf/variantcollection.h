#ifndef VARIANTCOLLECTION_H
#define VARIANTCOLLECTION_H

#include "variant.h"

#include <string>
#include <vector>
#include <map>

class VariantCollection {
private:
	//std:string fileFormat;
	std::string chromosome;                   //1

public:
    VariantCollection();
    // default copy-constructor is fine

    friend std::istream &operator>>(std::istream &in, VariantCollection &vc);
	friend std::ostream &operator<<(std::ostream &out, const VariantCollection &vc);
};


#endif /* VARIANTCOLLECTION_H */