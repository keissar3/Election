#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include <cstring>
#include "District.h"

int Citizen::getID()const
{
	return _ID;
}

const string Citizen::getName()const
{
	return _name;
}

int Citizen::getYearOfDate()const
{
	return _yearOfBirth;
}

bool Citizen::getVotedStatus()const
{
	return _votedStatus;
}

int Citizen::getDistrictID()const
{
	return _DistrictID;
}

void Citizen::setID(int id)
{
	int idDigCount = count_digits(id);
	if (idDigCount != 9 || id < 0)
		throw invalid_argument("Invalid ID");
	_ID = id;
}

void Citizen::setDistrictID(int district_id)
{
	if (district_id < 0)
		throw invalid_argument("Invalid District ID");
	_DistrictID = district_id;
}

void Citizen::setYearOfBirth(int year)
{
	if (year < 0)
		throw invalid_argument("Invalid year");
	_yearOfBirth = year;
}

void Citizen::setVotedStatus(bool vote)
{
	_votedStatus = vote;
}

void Citizen::setDistrict(District* district)
{
	District* check_dis = dynamic_cast<District*>(district);
	if (!check_dis)
		throw invalid_argument("Invalid district");

	_DistrictID = district->getDistrictID();
	_district = district;
}

District* Citizen::getDistrict() const
{
	return _district;
}

Citizen::Citizen(const string name, int id, int _yearOfBirth, District* _district, int DisID) : _name(name), _ID(id), _yearOfBirth(_yearOfBirth), _district(_district)
{
	setID(id);
	setDistrictID(DisID);
	setYearOfBirth(_yearOfBirth);
	setDistrict(_district);
}

Citizen::~Citizen()
{
}

Citizen::Citizen(const Citizen& cit) :_name(cit._name), _ID(cit._ID), _DistrictID(cit._DistrictID), _yearOfBirth(cit._yearOfBirth), _district(cit._district)
{
	// no need to check for exceptions as this citizen is created from a valid citizen
}

Citizen::Citizen(istream& in_file, District* myDis) : _ID(0), _yearOfBirth(0), _district(nullptr)
{
	load(in_file, myDis);   // if load fail an exception will be thrown.
}

ostream& operator<<(ostream& os, const Citizen& obj)
{
	cout << "Citizen Name:" << obj.getName() << "Citizen ID: " << obj.getID() << "District: " << obj.getDistrict()->getDistrictName() << endl;
	return os;
}

void Citizen::operator=(const Citizen& cit)
{
	if (this != &cit)
	{
		_ID = cit._ID;
		_yearOfBirth = cit._yearOfBirth;
		_district = cit._district;
		_name = cit._name;
	}
}

void Citizen::save(ostream& out_file)const
{
	/*  binary data of citizen is saved in this order:
		1.int _DistrictID
		2.int _ID;
		3.int _yearOfBirth;
		4.bool _votedStatus = false;
		5.string _name; */

	out_file.write(reinterpret_cast<const char*>(&_DistrictID), sizeof(_DistrictID));
	out_file.write(reinterpret_cast<const char*>(&_ID), sizeof(_ID));
	out_file.write(reinterpret_cast<const char*>(&_yearOfBirth), sizeof(_yearOfBirth));
	out_file.write(reinterpret_cast<const char*>(&_votedStatus), sizeof(_votedStatus));
	int size = _name.size();
	out_file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	out_file.write(_name.c_str(), size);

	if (!out_file.good())
		throw logic_error("error - can't save citizen");
}

void Citizen::load(istream& in_file, District* myDis)
{
	try {

		int temp__DistrictID;
		in_file.read(reinterpret_cast<char*>(&temp__DistrictID), sizeof(_DistrictID));
		setDistrictID(temp__DistrictID);

		int temp_ID;
		in_file.read(reinterpret_cast<char*>(&temp_ID), sizeof(_ID));
		setID(temp_ID);

		int temp_yearOfBirth;
		in_file.read(reinterpret_cast<char*>(&temp_yearOfBirth), sizeof(_yearOfBirth));
		setYearOfBirth(temp_yearOfBirth);

		in_file.read(reinterpret_cast<char*>(&_votedStatus), sizeof(_votedStatus));
		int size;
		in_file.read(reinterpret_cast<char*>(&size), sizeof(size));
		_name.resize(size);
		in_file.read(&_name[0], (size));
		if (myDis)
			_district = myDis;
		else
			_district = nullptr;
	}
	catch (const std::invalid_argument & ia)
	{
		cout << "Error While trying to load a citizen form file:" << endl;
		cout << ia.what() << endl;
		throw invalid_argument("error - can't load citizen from this file");
	}

	if (!in_file.good())
		throw logic_error("error - can't load citizen from this file");
}