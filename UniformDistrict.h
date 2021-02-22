#ifndef __UNIFORMDISTRICT_H
#define __UNIFORMDISTRICT_H

#include "District.h"
class UniformDistrict : public District
{
private:

public:
	UniformDistrict(const string disName, int electorsCount);
	UniformDistrict(const UniformDistrict& dis);
	virtual ~UniformDistrict();
	virtual void distributeElectors(int partyCount) override;
	virtual void printDistrict(const DynamicArray<DynamicArray<ElectorsList>>& electorsList, int typeOfElec)const override;
	virtual const string getTypeOfDistrict()const override;
	UniformDistrict(istream& in_file);
};
#endif