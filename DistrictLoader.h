#pragma once
#include "District.h"
#include "UniformDistrict.h"
#include "DividedDistrict.h"
#include <typeinfo>

class DistrictLoader
{
public:
	static void save(District* district, ostream& out);
	static void load(istream& in, DynamicArray<District*>* districtLoader);
};