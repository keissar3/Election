#define _CRT_SECURE_NO_WARNINGS
#include "Party.h"
#include "cstring"

int Party::count = 0;
Party::Party(const string partyName, Citizen* candidate) :_partyName(partyName), _partyID(count++), _totalVotes(0), _totalElectors(0)
{
	setCandidate(candidate);
}

Party::~Party()
{
}

Party::Party(const Party& party)
{
	_candidate = nullptr;
	*this = party;
}

Party::Party(istream& in_file, Citizen* candidate)
{
	load(in_file, candidate);   // if load fail an exception will be thrown.
}

void Party::operator=(const Party& party)
{
	if (this != &party)
	{
		setCandidate(party._candidate);
		_partyID = party._partyID;
		_totalVotes = party._totalVotes;
		_totalElectors = party._totalElectors;
		_partyName = party._partyName;
	}
}

const string Party::getPartyName() const
{
	return _partyName;
}

int Party::getCandidateID()const
{
	return _candidate->getID();
}

int Party::getPartyId()const
{
	return _partyID;
}

void Party::setCandidate(Citizen* candidate)
{
	Citizen* check_candidate = dynamic_cast<Citizen*>(candidate);
	if (!check_candidate)
		throw invalid_argument("Invalid candidate");
	_candidate = check_candidate;
}

void Party::setPartyID(int id)
{
	if (id < 0)
		throw invalid_argument("Invalid id");
	_partyID = id;

}

int Party::getTotalVotes()const
{
	return _totalVotes;
}

void Party::addVoteCount()
{
	_totalVotes++;
}

int Party::getTotalElectors()const
{
	return _totalElectors;
}

void Party::addElectorsCount(int num)
{
	_totalElectors += num;
}

void Party::setElectorsCount(int num)
{
	if (num < 0)
		throw invalid_argument("Invalid number of elector");
	_totalElectors = num;
}

Citizen* Party::getCandidate() const
{
	return _candidate;
}

ostream& operator<<(ostream& os, const Party& obj)
{
	cout << "Party Name:" << obj.getPartyName() << " ID: " << obj.getPartyId() << endl;
	return os;
}

void Party::save(ostream& out_file)const
{
	/*
		int candidateID
		string _partyName;
		int _partyID;
		int _totalVotes;
		int _totalElectors;
	*/

	int size = _partyName.size();
	int candidateID = getCandidateID();
	out_file.write(reinterpret_cast<const char*>(&candidateID), sizeof(candidateID));

	out_file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	out_file.write(reinterpret_cast<const char*>(_partyName.c_str()), (size));
	out_file.write(reinterpret_cast<const char*>(&_partyID), sizeof(_partyID));
	out_file.write(reinterpret_cast<const char*>(&_totalVotes), sizeof(_totalVotes));
	out_file.write(reinterpret_cast<const char*>(&_totalElectors), sizeof(_totalElectors));
	if (!out_file.good())
		throw logic_error("error- can't save party. ");
}

void Party::load(istream& in_file, Citizen* candidate)
{
	try {
		int size;
		in_file.read(reinterpret_cast<char*>(&size), sizeof(size));
		_partyName.resize(size);
		in_file.read(&_partyName[0], size);

		int partyID, totalElec;
		in_file.read(reinterpret_cast<char*>(&partyID), sizeof(partyID));
		setPartyID(partyID);

		in_file.read(reinterpret_cast<char*>(&_totalVotes), sizeof(_totalVotes));
		in_file.read(reinterpret_cast<char*>(&totalElec), sizeof(totalElec));
		setElectorsCount(totalElec);

		setCandidate(candidate);
	}
	catch (const std::invalid_argument & ia)
	{
		cout << "Error While trying to load a party form file:" << endl;
		cout << ia.what() << endl;
		throw invalid_argument("error - can't load party from this file");
	}

	if (!in_file.good())
		throw logic_error("error- can't load party.");
}