#define _CRT_SECURE_NO_WARNINGS
#include "District.h"
#include "cstring"

int District::count = 0;

District::District(const string disName, int electorsCount) : _name(disName), _electorsCount(_electorsCount), electorsDivisionArrSize(0), _ID(count++), _citizenCount(0), _votesCount(0), _maxVotes(0), _partyWon(-1)
{
	setElectorsCount(electorsCount);
}

District::~District()
{
	delete[]_electorDivision;
}

District::District(const District& dis) :_electorsCount(dis._electorsCount), _ID(dis._ID), _partyWon(dis._partyWon), _maxVotes(dis._maxVotes), _votesCount(dis._votesCount), _citizenCount(dis._citizenCount)
{
	_name = dis._name;
	_citizenList = dis._citizenList;
}

District::District(istream& in_file)
{
	load(in_file);   // if load fail an exception will be thrown.
}

void District::operator=(const District& dis)
{
	if (this != &dis)
	{
		_electorsCount = dis._electorsCount;
		_ID = dis._ID;
		_partyWon = dis._partyWon;
		_maxVotes = dis._maxVotes;
		_votesCount = dis._votesCount;
		_citizenCount = dis._citizenCount;
		_name = dis._name;
		_citizenList = dis._citizenList;
		_electorDivision = dis._electorDivision;
	}
}

void District::addCitizen(const Citizen& cit)
{
	_citizenList.addToTail(cit);
	_citizenCount++;
}

int District::getCitizenCount()const {

	return _citizenCount;
}

int District::getDistrictID()const
{
	return _ID;
}

const string District::getDistrictName()const
{
	return _name;
}

void District::printCitizenList()const
{
	_citizenList.printCitizenList();
}

Citizen* District::getCitizenByID(int ID)const
{
	return _citizenList.getCitizenByID(ID);
}

void District::addVoteCount()
{
	_votesCount++;
}

int District::getVotesCount()const
{
	return _votesCount;
}

int District::getMaxVotes()const
{
	return _maxVotes;
}

void District::setPartyWon(int partyID)
{
	if (partyID < 0)
		throw invalid_argument("Invalid party ID");
	_partyWon = partyID;
}

void District::setElectorsCount(int numOfElec)
{
	if (numOfElec <= 0)
		throw invalid_argument("Invalid number of electors");
	_electorsCount = numOfElec;
}

void District::setDistrictID(int id)
{
	if (id < 0)
		throw invalid_argument("invalid district ID");

	_ID = id;
}

int District::getPartyWon()const
{
	return _partyWon;
}

void District::setMaxVotes(int newMaxVote)
{
	if (newMaxVote < 0)
		throw invalid_argument("Invalid newMaxVote");
	_maxVotes = newMaxVote;
}

ostream& operator<<(ostream& os, const District& obj)
{
	cout << "District Name:" << obj.getDistrictName() << " ID: " << obj.getDistrictID() << endl;
	return os;
}

void District::CreateElectorsDivision(DynamicArray<int> votes, int partyCount, DynamicArray<Party*> parties)
{
	try {
		delete[] _electorDivision;
		_electorDivision = new ElectorDivision[partyCount];
		int numberOfVotes, NumbersOfElectors, numberOfPartyElectors, totalvotes;
		float precentageOfVotesP;
		totalvotes = this->getVotesCount();
		NumbersOfElectors = this->getElectorCount();

		for (int i = 0; i < partyCount; ++i)
		{
			numberOfVotes = votes[i];
			precentageOfVotesP = ((static_cast<float>(numberOfVotes) / static_cast<float>(totalvotes))) * 100;
			numberOfPartyElectors = static_cast<int>(precentageOfVotesP / 100 * (static_cast<float>(NumbersOfElectors)));

			_electorDivision[i].setNumOfElectors(numberOfPartyElectors);
			_electorDivision[i].setParty(parties[i]);
			_electorDivision[i].setNumOfVotes(numberOfVotes);
		}
		electorsDivisionArrSize = partyCount;
		sortElectorDivision(partyCount);
	}
	catch (bad_alloc & ex)
	{
		system("CLR");
		cout << ex.what() << endl;
		exit(1);
	}
	catch (const std::invalid_argument & ia)
	{
		system("cls");
		cout << "Failed to load district," << endl;
		cout << ia.what() << endl;
		throw invalid_argument("error - can't load district from this file");
		exit(1);
	}
}

void District::sortElectorDivision(int size)
{

	for (int i = 0; i < size - 1; i++)		   	//sort the "sortedParties" array according to the int array.
		for (int j = 0; j < size - i - 1; j++)
			if (_electorDivision[j].getNumOfElectors() < _electorDivision[j + 1].getNumOfElectors())
			{
				ElectorDivision temp = _electorDivision[j];
				_electorDivision[j] = _electorDivision[j + 1];
				_electorDivision[j + 1] = temp;
			}
	for (int i = 0; i < size - 1; i++)		   	//sort the parties with the same amount of electors according to their id.
		for (int j = 0; j < size - i - 1; j++)
			if (_electorDivision[j].getNumOfElectors() == _electorDivision[j + 1].getNumOfElectors() &&
				_electorDivision[j].getParty()->getPartyId() > _electorDivision[j + 1].getParty()->getPartyId())
			{
				ElectorDivision temp = _electorDivision[j];
				_electorDivision[j] = _electorDivision[j + 1];
				_electorDivision[j + 1] = temp;
			}
}

void District::printDistrictInfo()const
{
	float precentageOfVotesD = ((static_cast<float>(getVotesCount())) / (static_cast<float>(getCitizenCount()))) * 100;

	cout << "\t\t\t\t" << getDistrictName() << endl

		<< "- Number of electors: " << getElectorCount() << " ." << endl
		<< "- Percentage of vote: " << precentageOfVotesD << "% ." << endl;
}

void District::printPartyElectorsFromDistrict(const DynamicArray<DynamicArray<ElectorsList>>& electorsList)const
{
	float precentageOfVotes;

	for (int i = 0; i < electorsDivisionArrSize; i++)
	{
		precentageOfVotes = (((float)_electorDivision[i].getNumOfVotes()) / (float)getVotesCount()) * 100;

		cout << endl << "# Party name: " << _electorDivision[i].getParty()->getPartyName() << endl
			<< "- Number of votes: " << _electorDivision[i].getNumOfVotes() << endl
			<< "- Percentage of votes: " << precentageOfVotes << "% ." << endl
			<< "- Party Electors: " << endl;

		if (electorsList[getDistrictID()][i].getListCount() < _electorDivision[i].getNumOfElectors())
		{
			system("CLS");
			throw logic_error("Unable to print results. there is not enough electors.");
		}
		electorsList[getDistrictID()][i].printCitizenList(_electorDivision[i].getNumOfElectors());
	}
	cout << endl;
}

void District::save(ostream& out_file)const
{
	/*	binary data of citizen is saved in this order:
		1.char* _name;
		2.int _ID;
		3.int _electorsCount;
		4.int _partyWon;
		5.int _maxVotes;
		6.int _citizenCount;
		7.int _votesCount;
		8.CitizenList _citizenList; */

	int size = _name.size();
	out_file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	out_file.write(_name.c_str(), size);
	out_file.write(reinterpret_cast<const char*>(&_ID), sizeof(_ID));
	out_file.write(reinterpret_cast<const char*>(&_electorsCount), sizeof(_electorsCount));
	out_file.write(reinterpret_cast<const char*>(&_partyWon), sizeof(_partyWon));
	out_file.write(reinterpret_cast<const char*>(&_maxVotes), sizeof(_maxVotes));
	out_file.write(reinterpret_cast<const char*>(&_citizenCount), sizeof(_citizenCount));
	out_file.write(reinterpret_cast<const char*>(&_votesCount), sizeof(_votesCount));

	try {
		_citizenList.save(out_file);
	}
	catch (const std::invalid_argument & ia)
	{
		throw invalid_argument("error - can't save district to this file");
	}
	catch (const std::logic_error & le)
	{
		throw logic_error("error - can't save district to this file");
	}

	if (!out_file.good())
		throw logic_error("error- can't save district ");
}

void District::load(istream& in_file)
{
	try {
		int size;
		in_file.read(reinterpret_cast<char*>(&size), sizeof(size));
		_name.resize(size);
		in_file.read(&_name[0], size);

		int id, electorsCount, partyWon;

		in_file.read(reinterpret_cast<char*>(&id), sizeof(id));
		setDistrictID(id);

		in_file.read(reinterpret_cast<char*>(&electorsCount), sizeof(electorsCount));
		setElectorsCount(electorsCount);

		in_file.read(reinterpret_cast<char*>(&partyWon), sizeof(partyWon));
		setPartyWon(partyWon);

		in_file.read(reinterpret_cast<char*>(&_maxVotes), sizeof(_maxVotes));
		in_file.read(reinterpret_cast<char*>(&_citizenCount), sizeof(_citizenCount));
		in_file.read(reinterpret_cast<char*>(&_votesCount), sizeof(_votesCount));
		_citizenList.load(in_file, this);

		_electorDivision = nullptr;
		electorsDivisionArrSize = 0;
	}
	catch (const std::invalid_argument & ia)
	{
		throw invalid_argument("error - can't load district from this file");
	}
	catch (const std::logic_error & le)
	{
		throw logic_error("error - can't load district from this file");
	}

	if (!in_file.good())
		throw logic_error("error- can't load district ");
}