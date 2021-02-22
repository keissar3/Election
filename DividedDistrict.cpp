#include "DividedDistrict.h"

DividedDistrict::DividedDistrict(const string disName, int electorsCount) :District(disName, electorsCount) {}
DividedDistrict::~DividedDistrict() {}
DividedDistrict::DividedDistrict(const DividedDistrict& dis) : District(dis) {}
DividedDistrict::DividedDistrict(istream& in_file) : District(in_file) {};

void DividedDistrict::distributeElectors(int partyCount)
{
	//Divided district give its elecor to the parties by percentage of votes.
	int numbersOfPartyElectors;

	for (int i = 0; i < partyCount; ++i)
	{
		Party* currParty = _electorDivision[i].getParty();
		numbersOfPartyElectors = _electorDivision[i].getNumOfElectors();
		currParty->addElectorsCount(numbersOfPartyElectors);
	}
}

void DividedDistrict::printDistrict(const DynamicArray<DynamicArray<ElectorsList>>& electorsList, int typeOfElec)const
{
	printDistrictInfo();
	if (typeOfElec == 1)
	{
		cout << "- Type of district: " << getTypeOfDistrict() << " ." << endl;
	}
	cout << "- The candidates and the number of electors: " << endl;
	printCandidatesInfo();
	printPartyElectorsFromDistrict(electorsList);
	cout << "\t\t\t\t\t ___________________" << endl << endl;
}

void DividedDistrict::printCandidatesInfo()const
{
	for (int i = 0; i < electorsDivisionArrSize; i++)
	{
		cout << "\t\t\t";

		if (_electorDivision[i].getNumOfElectors() > 0)
		{
			cout << "Candidate's name: " << _electorDivision[i].getParty()->getCandidate()->getName()
				<< " , number of electors: " << _electorDivision[i].getNumOfElectors() << endl;
		}
	}
}

const string DividedDistrict::getTypeOfDistrict()const
{
	return "Divided";
}