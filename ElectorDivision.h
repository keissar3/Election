#pragma once
#include "Party.h"

class ElectorDivision {

private:
	int _numOfElectors;
	Party* _party = nullptr;
	int _numOfVotes;
public:

	ElectorDivision();
	void setNumOfElectors(int n);
	void setParty(Party* party);
	void setNumOfVotes(int n);

	int getNumOfElectors() const { return _numOfElectors; }
	Party* getParty() const { return _party; }
	int getNumOfVotes()const { return _numOfVotes; }
};