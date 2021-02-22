#pragma once
#include "CitizenList.h"
#include "Citizen.h"
class District;
class Citizen;

class Party
{
private:
	string _partyName;
	Citizen* _candidate = nullptr;
	int _partyID;
	int _totalVotes;
	int _totalElectors;
	static int count;
	void setPartyID(int id);
public:
	Party() :Party(" ", nullptr) {};
	Party(const string partyName, Citizen* candidate);
	~Party();
	Party(istream& in_file, Citizen* candidate = nullptr);
	Party(const Party& party);

	void operator=(const Party& party);
	friend ostream& operator<<(ostream& os, const Party& obj);

	const string getPartyName() const;
	int getCandidateID()const;
	int getPartyId()const;
	int getTotalVotes()const;
	int getTotalElectors()const;

	void setCandidate(Citizen* candidate);
	void addVoteCount();
	void addElectorsCount(int num);
	void setElectorsCount(int num);
	Citizen* getCandidate()const;
	void save(ostream& out_file)const;
	void load(istream& out_file, Citizen* candidate = nullptr);
};