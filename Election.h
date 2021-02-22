#pragma once
#include "Date.h"
#include "Party.h"
#include "DistrictLoader.h"
#include "ElectorsList.h"
#include "DynamicArray.h"


enum { REGULAR_ELECTION = 1, SIMPLE_ELECTION = 2 };
class Election
{
private:
	Date _electionDay;

	DynamicArray<Party*> _parties;     // array of all the parties in this election
	DynamicArray<District*> _districts;      // array of all the districts in this election

	int _electionType;
	DynamicArray<DynamicArray<int>> _votes;                //uses -party cols- -districts rows
	DynamicArray<DynamicArray<ElectorsList>>_electorsList;

public:
	Election(Date day, int type);
	Election();
	~Election();
	Election(const Election& elec) = delete;
	Election(istream& in_file);

	void addParty(const string partyName, Citizen* candidateID);
	void addDistrict(const string disName, int _electorsCount, DistrictType districtType);
	District* getDistrictByID(int id)const;
	Party* getPartyByID(int id)const;
	int getNumOfVotes(int districtID, int partyID)const;
	void setDate(Date elecDate);

	int getElectionYear() { return _electionDay.getYear(); }
	Citizen* getCitizenByID(int ID)const;
	void printDistricts()const;
	void printCitizens()const;
	void printParties()const;
	void vote(Citizen* currCitizen, int partyID);
	void printResults()const;
	void addElector(int districtID, int partyID, const Citizen& newElector);
	void printSortedCandidateResults()const;
	void setElectionType(int electionType);
	int getElectionType() const;
	void save(ostream& out_file)const;
	void load(istream& in_file);
};