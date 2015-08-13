#ifndef VARIANTCOLLECTION_H
#define VARIANTCOLLECTION_H

#include "utilities.h"
#include "variant.h"

#include <string>
#include <vector>
#include <map>

class Filter {
private:
	std::string id;
	std::string desc;
public:
	Filter() {}
	Filter(const std::string id, const std::string desc)
		:id(id), desc(desc)	{}

	auto getId() { return id; }
	auto getDesc() { return desc; }
};

class VariantCollection {
private:
	std::string fileFormat;
	std::vector<Filter> filters;
	std::vector<std::string> headers;
	std::vector<Variant> variants;

public:
    VariantCollection();
    // default copy-constructor is fine
    VariantCollection(const VariantCollection &, Filter &, std::function<bool(const Variant&)>);

    auto getFileFormat() { return fileFormat; }
    auto getFilters() { return filters; }
    auto getHeaders() { return headers; }
    auto getVariants() { return variants; }

    friend std::istream &operator>>(std::istream &in, VariantCollection &vc);
	friend std::ostream &operator<<(std::ostream &out, const VariantCollection &vc);
};


#endif /* VARIANTCOLLECTION_H */