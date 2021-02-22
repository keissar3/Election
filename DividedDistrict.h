#ifndef __DIVIDEDDISTRICT_H
#define __DIVIDEDDISTRICT_H
#include "District.h"

class DividedDistrict : public District
{
private:

public:
	DividedDistrict(const string disName, int electorsCount);
	DividedDistrict(const DividedDistrict& dis);
	virtual ~DividedDistrict();
	virtual void distributeElectors(int partyCount) override;
	virtual void printDistrict(const DynamicArray<DynamicArray<ElectorsList>>& electorsList, int typeOfElec)const override;
	void printCandidatesInfo()const;
	virtual const string getTypeOfDistrict()const override;
	DividedDistrict(istream& in_file);
};

#endif