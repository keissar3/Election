#define _CRT_SECURE_NO_WARNINGS
#include "Election.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

Election::Election(Date day, int type = 1) :_electionDay(day), _electionType(type) {}

Election::Election()
{
	_electionDay = (Date(1, 1, 2020));
}

Election::~Election() {}

Election::Election(istream& in_file)
{
	load(in_file);   // if load fail an exception will be thrown.
}

void Election::setElectionType(int electionType)
{
	if (electionType != 1 && electionType != 2)
		throw invalid_argument("invalid election type");
	_electionType = electionType;
};

int Election::getElectionType() const
{
	return _electionType;

}

void Election::addDistrict(const string disName, int electorsCount, DistrictType districtType)
{
	try {
		switch (districtType)
		{
		case DistrictType::UNIFORM:
		{
			_districts.push_back(new UniformDistrict(disName, electorsCount));
			break;
		}
		case DistrictType::DIVIDED:
		{
			_districts.push_back(new DividedDistrict(disName, electorsCount));
			break;
		}
		}
		_votes.push_back(DynamicArray<int>());					// adding a row
		_electorsList.push_back(DynamicArray<ElectorsList>());  // adding a row

	}
	catch (std::bad_alloc & ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	catch (const std::invalid_argument & ia)
	{
		cout << ia.what() << endl;
		throw invalid_argument("error - can't add a district");
	}
}

void Election::addParty(const string partyName, Citizen* _candidate)
{
	try {
		_parties.push_back(new Party(partyName, _candidate));
		for (int i = 0; i < _votes.size(); i++)
		{
			_votes[i].push_back(0);						        // adding a col
			_electorsList[i].push_back(ElectorsList());	        // adding a col
		}
	}
	catch (bad_alloc & ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	catch (const std::invalid_argument & ia)
	{
		cout << ia.what() << endl;
		throw invalid_argument("error - can't add a party");
	}
}

District* Election::getDistrictByID(int id)const
{
	if (id >= 0 && id < _districts.size())
		return (_districts[id]);
	else
		return nullptr;
}

Party* Election::getPartyByID(int id)const
{
	if (id >= 0 && id <= _parties.size())
		return (_parties[id]);
	else
		return nullptr;
}

void Election::setDate(Date elecDate)
{
	_electionDay = elecDate;
}

void Election::printDistricts()const
{
	cout << "District's name" << setw(30) << "District's ID" << setw(30) << "Number of Electors" << setw(30) << "Type of district" << endl;

	for (int i = 0; i < _districts.size(); i++)
	{
		District* CurDistrict = getDistrictByID(i);
		cout << CurDistrict->getDistrictName() << setw(30) << (CurDistrict)->getDistrictID() << setw(30) << CurDistrict->getElectorCount() << setw(30) << CurDistrict->getTypeOfDistrict() << endl;
	}
}

void Election::printParties()const
{
	for (int i = 0; i < _parties.size(); i++)
	{
		Party* curParty = getPartyByID(i);

		cout << "Party name: " << curParty->getPartyName() << endl <<
			"Party ID: " << curParty->getPartyId() << endl
			<< "Candidate for presidency: " << getCitizenByID(curParty->getCandidateID())->getName() << endl << endl;

		for (int j = 0; j < _districts.size(); j++)
		{
			cout << "- Electors from " << getDistrictByID(j)->getDistrictName() << ":" << endl << endl;
			cout << "Citizen's ID" << setw(30) << "Citizen's Name" << setw(30) << "Citizen's Year of birth " << setw(30) << "District ID" << endl;
			cout << _electorsList[j][i];
			cout << endl;
		}
		cout << endl << endl;
	}
}

void Election::printCitizens()const
{
	cout << "Citizen's ID" << setw(30) << "Citizen's Name" << setw(30) << "Citizen's Year of birth " << setw(30) << "District ID" << endl;

	for (int i = 0; i < _districts.size(); i++)
	{
		District* CurDistrict = getDistrictByID(i);
		CurDistrict->printCitizenList();
	}
}

Citizen* Election::getCitizenByID(int ID)const
{
	Citizen* cit = nullptr;
	for (int i = 0; i < _districts.size(); i++)
	{
		District* CurDistrict = getDistrictByID(i);
		cit = CurDistrict->getCitizenByID(ID);
		if (cit)
			return cit;
	}
	return nullptr;
}

void Election::vote(Citizen* currCitizen, int partyID)
{
	try {
		int districtID = currCitizen->getDistrictID();
		_votes[districtID][partyID]++;

		int lmaxVotes = getDistrictByID(districtID)->getMaxVotes();
		if ((_votes[districtID][partyID]) > lmaxVotes)
		{
			getDistrictByID(districtID)->setPartyWon(partyID);
			getDistrictByID(districtID)->setMaxVotes(_votes[districtID][partyID]);
		}

		currCitizen->setVotedStatus(true);
		_districts[districtID]->addVoteCount();
		getPartyByID(partyID)->addVoteCount();
	}
	catch (const std::invalid_argument & ia)
	{
		cout << ia.what() << endl;
		throw invalid_argument("error - can't vote.");
	}
}

void Election::addElector(int districtID, int partyID, const Citizen& newElector)
{
	_electorsList[districtID][partyID].addToTail(newElector);
}

int Election::getNumOfVotes(int districtID, int partyID)const
{
	return _votes[districtID][partyID];
}

void Election::printResults()const
{
	try {
		system("CLS");
		cout << "Results date:" << _electionDay << endl << endl;

		for (int i = 0; i < _parties.size(); i++)
			_parties[i]->setElectorsCount(0);

		for (int i = 0; i < _districts.size(); i++)
			_districts[i]->CreateElectorsDivision(_votes[i], _parties.size(), _parties);    // generate the elector division array field for each district

		for (int i = 0; i < _districts.size(); i++)
			_districts[i]->distributeElectors(_parties.size());     //The district distributes their electors to that parites according to their own specific law.

		for (int i = 0; i < _districts.size(); i++)
		{
			District* currDist = getDistrictByID(i);
			(*currDist).printDistrict(_electorsList, _electionType);
		}
		cout << endl;
		printSortedCandidateResults();
	}
	catch (const std::invalid_argument & ia)
	{
		cout << "Unable to print results:" << endl;
		cout << ia.what();
	}
	catch (const std::logic_error & le)
	{
		cout << "Unable to print results:" << endl;
		cout << le.what();
	}
	catch (...)
	{
		cout << "Unable to print results:" << endl;
		cout << "Unknown reason";
	}
}

void Election::printSortedCandidateResults()const
{
	try {

		DynamicArray<int> voteCount(_parties.size());

		DynamicArray<Party*> sortedParties(_parties.size());

		for (int i = 0; i < _parties.size(); i++)				 //init both arrays
		{
			voteCount[i] = 0;
			sortedParties[i] = _parties[i];
		}

		for (int i = 0; i < _parties.size(); i++)                //count how many electors votes for the array with the id i
			voteCount[i] = +_parties[i]->getTotalElectors();


		for (int i = 0; i < _parties.size() - 1; i++)			 //sort the "sortedParties" array according to the int array.
			for (int j = 0; j < _parties.size() - i - 1; j++)
				if (voteCount[j] < voteCount[j + 1])
				{
					Party* tempParty = sortedParties[j];
					int tempCount = voteCount[j];
					sortedParties[j] = sortedParties[j + 1];
					voteCount[j] = voteCount[j + 1];
					sortedParties[j + 1] = tempParty;
					voteCount[j + 1] = tempCount;
				}
		// the sortedparties array now holds pointer to parties sorted by votes

		for (int i = 0; i < _parties.size(); i++)
			cout << "The Candidate:\t " << getCitizenByID(sortedParties[i]->getCandidateID())->getName() << " Won \t" << sortedParties[i]->getTotalElectors() << " electors "
			<< " with a total of " << sortedParties[i]->getTotalVotes() << " votes !!" << endl;
	}
	catch (bad_alloc & ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}

void Election::save(ostream& out_file)const
{
	/* binary data of election is saved in this order:
	1.Date _electionDay;
	2.int _electionType;
	3.int _partiesLogical;
	4.int _partiesPhysical;
	5.Party first~last;
	6.int _districtsLogical;
	7.int _districtsPhysical;
	8.District first~last ;
	9.int** _votes;                //uses -party cols- -districts rows
	10.CitizenList**  first~last;*/

	try {
		_electionDay.save(out_file);
		out_file.write(reinterpret_cast<const char*>(&_electionType), sizeof(_electionType));

		int _districtsLogical = _districts.size();
		out_file.write(reinterpret_cast<const char*>(&_districtsLogical), sizeof(_districtsLogical));

		for (int i = 0; i < _districtsLogical; ++i)
			DistrictLoader::save(_districts[i], out_file);

		int _partiesLogical = _parties.size();
		out_file.write(reinterpret_cast<const char*>(&_partiesLogical), sizeof(_partiesLogical));

		for (int i = 0; i < _partiesLogical; ++i)
			_parties[i]->save(out_file);

		for (int i = 0; i < _districtsLogical; ++i)
			for (int j = 0; j < _partiesLogical; ++j)
				out_file.write(reinterpret_cast<const char*>(&(_votes[i][j])), sizeof(_votes[i][j]));

		for (int i = 0; i < _districtsLogical; ++i)
			for (int j = 0; j < _partiesLogical; ++j)
				_electorsList[i][j].save(out_file);
	}
	catch (const std::invalid_argument & ia)
	{
		cout << "Failed to save election to file." << endl;
		cout << ia.what();
		throw invalid_argument("error - can't save election to this file");
	}
	catch (const std::logic_error & le)
	{
		cout << "Failed to save election to file." << endl;
		cout << le.what();
		throw logic_error("error - can't save election to this file");
	}

	if (!out_file.good())
		throw logic_error("error - can't save election to this file");
}

void Election::load(istream& in_file)
{
	try {
		_electionDay = Date(in_file);

		in_file.read(reinterpret_cast<char*>(&_electionType), sizeof(_electionType));

		int _districtsLogical;
		in_file.read(reinterpret_cast<char*>(&_districtsLogical), sizeof(_districtsLogical));

		for (int i = 0; i < _districtsLogical; i++)
			DistrictLoader::load(in_file, &(_districts));

		int _partiesLogical;
		in_file.read(reinterpret_cast<char*>(&_partiesLogical), sizeof(_partiesLogical));

		for (int i = 0; i < _partiesLogical; i++)
		{
			int candidateID;
			in_file.read(reinterpret_cast<char*>(&candidateID), sizeof(candidateID));
			Citizen* candidate = getCitizenByID(candidateID);
			Party* newP = new Party(in_file, candidate);
			_parties.push_back(newP);
		}

		for (int i = 0; i < _districtsLogical; i++)
		{
			_votes.push_back(DynamicArray<int>());
			for (int j = 0; j < _partiesLogical; j++)
				_votes[i].push_back(0);
		}

		for (int i = 0; i < _districtsLogical; i++)
			for (int j = 0; j < _partiesLogical; j++)
				in_file.read(reinterpret_cast<char*>(&(_votes[i][j])), sizeof((_votes[i][j])));

		for (int i = 0; i < _districtsLogical; i++)
			_electorsList.push_back(DynamicArray<ElectorsList>(_partiesLogical));

		for (int i = 0; i < _districtsLogical; i++)
			for (int j = 0; j < _partiesLogical; j++)
				_electorsList[i][j].load(in_file, _districts);
	}

	catch (bad_alloc & ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	catch (const std::invalid_argument & ia)
	{
		cout << "Failed to load election from file." << endl;
		throw invalid_argument("error - can't load election from this file");
	}
	catch (const std::logic_error & le)
	{
		cout << "Failed to load election from file." << endl;
		throw logic_error("error - can't load election from this file");
	}
	catch (...)
	{
		cout << "Failed to load election from file for unknown reason";
		throw invalid_argument("error - can't load election from this file");
	}

	if (!in_file.good())
		throw "error - can't load election from this file";
}