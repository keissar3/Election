#include "DistrictLoader.h"


void DistrictLoader::save(District* district, ostream& out_file)
{
	DistrictType disType;

	if (typeid(*district) == typeid(DividedDistrict))
		disType = DistrictType::DIVIDED;
	else if (typeid(*district) == typeid(UniformDistrict))
		disType = DistrictType::UNIFORM;

	out_file.write(reinterpret_cast<const char*>(&disType), sizeof(disType));

	try {
		district->save(out_file);
	}
	catch (const std::invalid_argument & ia)
	{
		system("cls");
		cout << "Failed to save district," << endl;
		cout << ia.what() << endl;
		throw invalid_argument("error - can't save district to this file");

	}
	catch (const std::logic_error & le)
	{
		system("cls");
		cout << "Failed to save district," << endl;
		cout << le.what() << endl;
		throw logic_error("error - can't save district to this file");
	}

	if (!out_file.good())
		throw logic_error("error- can't save district .");
}

void DistrictLoader::load(istream& in_file, DynamicArray<District*>* loadedDistrict)
{
	try {
		DistrictType disType;
		in_file.read(reinterpret_cast<char*>(&disType), sizeof(disType));

		switch (disType)
		{
		case DistrictType::UNIFORM:
		{
			District* newDis = new UniformDistrict(in_file);
			(*loadedDistrict).push_back(newDis);
			break;
		}
		case DistrictType::DIVIDED:
		{
			District* newDis = new DividedDistrict(in_file);
			(*loadedDistrict).push_back(newDis);
			break;
		}
		}
	}
	catch (bad_alloc & ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	catch (const std::invalid_argument & ia)
	{
		system("cls");
		cout << "Failed to load district," << endl;
		cout << ia.what() << endl;
		throw invalid_argument("error - can't load district from this file");

	}
	catch (const std::logic_error & le)
	{
		system("cls");
		cout << "Failed to load district," << endl;
		cout << le.what() << endl;
		throw logic_error("error - can't load district from this file");
	}

	if (!in_file.good())
		throw logic_error("error- can't load district .");
}