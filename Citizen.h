#pragma once
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include "Exceptions.h"

using namespace std;
class District;

class Citizen
{
private:
	string _name;
	int _ID;
	int _yearOfBirth;
	bool _votedStatus = false;
	District* _district = nullptr;
	int _DistrictID;  /// this is for printing only! we use it in other classes.
public:
	Citizen(const string name, int id, int yearOfBirth, District* _district, int DistrictID);
	~Citizen();
	Citizen(const Citizen& cit);
	Citizen(istream& in_file, District* myDis = nullptr);

	void operator=(const Citizen& cit);
	friend ostream& operator<<(ostream& os, const Citizen& obj);

	int getID() const;
	const string getName() const;
	int getYearOfDate() const;
	bool getVotedStatus()const;
	int getDistrictID() const;
	District* getDistrict()const;

	void setID(int id);
	void setYearOfBirth(int year);
	void setVotedStatus(bool vote);
	void setDistrict(District* _district);
	void save(ostream& out_file)const;
	void load(istream& in_file, District* myDis = nullptr);
	void setDistrictID(int district_id);
};