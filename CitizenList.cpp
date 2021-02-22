#include "CitizenList.h"
#include <iostream>
#include <iomanip>

using namespace std;

CitizenList::CitizenList(istream& in_file, District* myDis)
{
	load(in_file, myDis);
}

CitizenList::~CitizenList()
{
	for (auto citizen : _citizenList)
		delete citizen;
}

CitizenList::CitizenList(const CitizenList& citlist)
{
	*this = citlist;
}

void CitizenList::addToTail(const Citizen& cit)
{
	try {
		Citizen* newcit = new Citizen(cit);
		_citizenList.push_back(newcit);
	}
	catch (bad_alloc & ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}

int CitizenList::getListCount()const
{
	return _citizenList.size();
}

void CitizenList::printCitizenList()const
{
	for (auto citizen : _citizenList)
		cout << citizen->getID() << setw(30) << citizen->getName() << setw(30) << citizen->getYearOfDate() << setw(30) << citizen->getDistrictID() << endl;
}

Citizen* CitizenList::getCitizenByID(int ID)const
{
	for (auto citizen : _citizenList)
		if (citizen->getID() == ID)
			return citizen;
	return nullptr;
}

void CitizenList::printCitizenList(int num)const
{
	auto iter = _citizenList.begin();
	auto end = _citizenList.end();

	while (iter != end && num > 0)
	{
		cout << "\t\t\t" << (*iter)->getName() << endl;
		iter++;
		num--;
	}
}

ostream& operator<<(ostream& os, const CitizenList& obj)
{
	obj.printCitizenList();
	return os;
}

void CitizenList::save(ostream& out_file)const
{
	/* binary data of citizen is saved in this order:
			1.int listcount
			2.citizens */

	int size = _citizenList.size();
	out_file.write(reinterpret_cast<const char*>(&size), sizeof(size));

	try {
		for (auto citizen : _citizenList)
			citizen->save(out_file);
	}
	catch (const std::logic_error & le)
	{
		system("cls");
		cout << le.what() << endl;
		throw logic_error("error - can't save citizen list from this file");
	}

	if (!out_file.good())
		throw logic_error("error - can't save citizen list from this file");
}

void CitizenList::load(istream& in_file, District* myDis)
{
	try {
		int size;
		in_file.read(reinterpret_cast<char*>(&size), sizeof(size));
		for (int i = 0; i < size; ++i)
		{
			Citizen newCitizen(in_file, myDis);   // if fails, will throw exception
			addToTail(newCitizen);
		}
	}
	catch (const std::invalid_argument & ia)
	{
		system("cls");
		cout << ia.what() << endl;
		throw invalid_argument("error - can't load citizen list from this file");
	}
	catch (const std::logic_error & le)
	{
		system("cls");
		cout << le.what() << endl;
		throw invalid_argument("error - can't load citizen list from this file");
	}

	if (!in_file.good())
		throw logic_error("error - can't load citizen list from this file");
}