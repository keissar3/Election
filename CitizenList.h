#pragma once
#include "Citizen.h"
#include <list>

class CitizenList
{
private:
	list<Citizen*> _citizenList;
public:
	CitizenList() {};
	CitizenList(istream& in_file, District* myDis = nullptr);
	virtual ~CitizenList();
	CitizenList(const CitizenList& citlist);
	void addToTail(const Citizen& cit);
	int getListCount()const;
	void printCitizenList()const;
	void printCitizenList(int num)const;
	Citizen* getCitizenByID(int ID)const;
	friend ostream& operator<<(ostream& os, const CitizenList& obj);
	void save(ostream& out_file)const;
	void load(istream& in_file, District* myDis = nullptr);
};