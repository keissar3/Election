#include "UniformDistrict.h"

UniformDistrict::UniformDistrict(string disName, int electorsCount) :District(disName, electorsCount) {}
UniformDistrict::~UniformDistrict() {}
UniformDistrict::UniformDistrict(const UniformDistrict& dis) : District(dis) {}
UniformDistrict::UniformDistrict(istream& in_file) : District(in_file) {};

void UniformDistrict::distributeElectors(int partyCount)
{   //Uniform District gives all its electors to the party with the most votes.
	if (partyCount <= 0)
		return;

	Party* winner = _electorDivision[0].getParty();
	for (int i = 0; i < partyCount - 1; ++i)
	{
		if (_electorDivision[i + 1].getNumOfElectors() > _electorDivision->getNumOfElectors())
			winner = _electorDivision[i + 1].getParty();
		if (_electorDivision[i + 1].getNumOfElectors() == _electorDivision->getNumOfElectors()
			&& _electorDivision[i + 1].getParty()->getPartyId() < _electorDivision[i + 1].getParty()->getPartyId())
			winner = _electorDivision[i + 1].getParty();
	}
	winner->addElectorsCount(getElectorCount());
}

void UniformDistrict::printDistrict(const DynamicArray<DynamicArray<ElectorsList>>& electorsList, int typeOfElec)const
{
	printDistrictInfo();
	cout << "- Type of district: " << getTypeOfDistrict() << " ." << endl;
	cout << "- Chosen candidate: " << ((_electorDivision[0]).getParty())->getCandidate()->getName() << " ." << endl;
	printPartyElectorsFromDistrict(electorsList);
	cout << "\t\t\t\t\t ___________________" << endl << endl;
}

const string UniformDistrict::getTypeOfDistrict()const
{
	return "uniform";
}