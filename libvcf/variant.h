#ifndef VARIANT_H
#define VARIANT_H

#include <string>
#include <vector>
#include <map>

enum class ReferenceBase : char { A='A', C='C', G='G', T='T', N='N' };
enum class AlternateBase : char { A='A', C='C', G='G', T='T', N='N', Star='*' };

class Variant
{
private:
	std::string chromosome;                   //1
	int position;                             //2
	std::vector<std::string> identifier;      //3
	std::vector<ReferenceBase> refBase;       //4
	std::vector<AlternateBase> altBase;       //5
	double quality;                           //6
	std::string filterStatus;                 //7
	std::map<std::string, std::string> infos; //8
	std::vector<std::string> extras;          //...

public:
    Variant();
    // default copy-constructor is fine

	auto getChromosome() const { return chromosome; }
	auto getPosition() const { return position; }
	auto getIdentifier() const { return identifier; }
	auto getRefBase() const { return refBase; }
	auto getAltBase() const { return altBase; }
	auto getQuality() const { return quality; }
	auto getFilterStatus() const { return filterStatus; }
	auto getInfos() const { return infos; }
	auto getExtras() const { return extras; }

    friend std::istream &operator>>(std::istream &in, Variant &v);
	friend std::ostream &operator<<(std::ostream &out, const Variant &v);
};


#endif /* VARIANT_H */