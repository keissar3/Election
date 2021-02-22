#include "ElectorsList.h"

void ElectorsList::load(istream& in_file, DynamicArray<District*> disArray)
{
	int size;
	in_file.read(reinterpret_cast<char*>(&size), sizeof(size));

	try {
		for (int i = 0; i < size; ++i)
		{
			Citizen newCitizen(in_file);
			District* citDis = disArray[newCitizen.getDistrictID()];
			newCitizen.setDistrict(citDis);
			addToTail(newCitizen);
		}
	}
	catch (const std::invalid_argument & ia)
	{
		cout << "Error While trying to load electors list form file:" << endl;
		cout << ia.what() << endl;
		throw invalid_argument("error- can't load electors list.");
	}
	catch (const std::logic_error & le)
	{
		cout << "Error While trying to load electors list form file:" << endl;
		cout << le.what() << endl;
		throw invalid_argument("error- can't load electors list.");
	}

	if (!in_file.good())
		throw logic_error("error- can't load electors list.");
}