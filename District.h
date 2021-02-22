#pragma once
#include "ElectorsList.h"
#include "Party.h"
#include "Citizen.h"
#include "ElectorDivision.h"
#include "DynamicArray.h"

enum class DistrictType { UNIFORM = 1, DIVIDED = 2 };

class District
{
private:
	string _name;
	int _electorsCount;
	int _ID;
	int _partyWon;
	int _maxVotes;
	int _citizenCount;
	int _votesCount;
	CitizenList _citizenList;
	static int count;

	void sortElectorDivision(int size);
protected:
	ElectorDivision* _electorDivision = nullptr;
	int electorsDivisionArrSize;
public:
	District(const string disName, int _electorsCount);
	District(const District& dis);
	virtual ~District();
	District(istream& in_file);

	friend ostream& operator<<(ostream& os, const District& obj);
	void operator=(const District& dis);

	int getCitizenCount()const;
	int getElectorCount()const { return _electorsCount; }
	const string getDistrictName()const;
	Citizen* getCitizenByID(int ID)const;
	int getDistrictID()const;
	int getVotesCount()const;
	int getMaxVotes()const;
	int getPartyWon()const;

	void setDistrictID(int id);
	void setPartyWon(int partyID);
	void printCitizenList()const;
	void addVoteCount();
	void addCitizen(const Citizen& cit);
	void setMaxVotes(int newMaxVote);
	void setElectorsCount(int numOfElec);
	void printDistrictInfo()const;
	void printPartyElectorsFromDistrict(const DynamicArray<DynamicArray<ElectorsList>>& electorsList)const;
	void CreateElectorsDivision(DynamicArray<int> votes, int partyCount, DynamicArray<Party*> parties);

	virtual void distributeElectors(int partyCount) = 0;
	virtual void printDistrict(const DynamicArray<DynamicArray<ElectorsList>>& electorsList, int typeOfElec)const = 0;
	virtual const string getTypeOfDistrict()const = 0;
	void save(ostream& out_file)const;
	void load(istream& out_file);
};