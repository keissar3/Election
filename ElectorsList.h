#pragma once
#include "CitizenList.h"
#include "DynamicArray.h"

class ElectorsList : public CitizenList {

public:
	ElectorsList() :CitizenList() {}
	virtual ~ElectorsList() {}
	ElectorsList(const CitizenList& citlist) :CitizenList(citlist) {}
	void load(istream& in_file, DynamicArray<District*> disArray);
};