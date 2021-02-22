#include "ElectorDivision.h"

ElectorDivision::ElectorDivision() :_numOfElectors(0), _numOfVotes(0), _party(nullptr) {}

void ElectorDivision::setNumOfElectors(int n)
{
	if (n < 0)
		throw invalid_argument("Invalid number of electors");
	_numOfElectors = n;
}

void ElectorDivision::setParty(Party* party)
{
	Party* check_party = dynamic_cast<Party*>(party);
	if (!check_party)
		throw invalid_argument("Invalid candidate");
	_party = check_party;
}

void ElectorDivision::setNumOfVotes(int n)
{
	if (n < 0)
		throw invalid_argument("Invalid number of votes");
	_numOfVotes = n;
}
