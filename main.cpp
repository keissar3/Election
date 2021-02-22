#include "Citizen.h"
#include "CitizenList.h"
#include "District.h"
#include <iostream>
#include "Party.h"
#include "Election.h"
#include "Date.h"
#include <cstdlib>
#include <list>
#include "MyAlgorithms.h"

#define FILE_ERROR -1
using namespace std;
enum { ADD_DISTRICT = 1, ADD_CITIZEN = 2, ADD_PARTY = 3, ADD_ELECTOR = 4, SHOW_DISTRICTS = 5, SHOW_CITIZEN = 6, SHOW_PARTIES = 7, VOTE = 8, SHOW_RESULTS = 9, SAVE_ELECTION = 11, LOAD_ELECTION = 12, EXIT = 0 };
enum { NEW_ELECTION = 1, LOAD_ELECT = 2 };


int getElectionTypeFromUser(Election& election);
void createDistrictForSimpleElection(Election& election);


int main()
{
	try {

		Election* Israel2020 = new Election();
		int selection;
		int day, month, year;
		bool round = true;
		int electionType;
		string filename;
		bool choose = true;

		while (choose)
		{
			cout << "Press 1 to create new election," << endl
				<< "Press 2 to load previous election," << endl
				<< "Press 0 to exit." << endl << endl;

			cin >> selection;

			switch (selection)
			{
			case NEW_ELECTION:
			{
				cout << "Please enter election date (example: 01 01 1990)";
				cin >> day >> month >> year;

				try {
					Israel2020->setDate(Date(day, month, year));
				}
				catch (const std::invalid_argument & ia)
				{
					system("CLS");
					cout << ia.what() << endl;
					break;
				}
				system("CLS");
				cout << "Welcome to Election 2020!" << endl;
				electionType = getElectionTypeFromUser(*Israel2020);
				if (electionType == SIMPLE_ELECTION)
					createDistrictForSimpleElection(*Israel2020);
				choose = false;
				break;
			}
			case LOAD_ELECT:
			{
				cout << "Please enter file name including file extension: " << endl;
				cin >> filename;
				system("CLS");

				ifstream in(filename, ios::binary);
				if (!in)
				{
					system("CLS");
					cout << "Unable to load election from this file." << endl;
					break;
				}
				else
				{
					delete Israel2020;
					Israel2020 = new Election;
					try {
						Israel2020->load(in);
					}
					catch (const std::invalid_argument & ia)
					{
						system("CLR");
						cout << ia.what() << endl;
						delete Israel2020;
						break;
					}
					catch (const std::logic_error & le)
					{
						system("CLR");
						cout << le.what() << endl;
						delete Israel2020;
						break;
					}
				}
				in.close();
				choose = false;
				break;
			}
			case EXIT:
			{
				exit(1);
				break;
			}
			}
		}


		while (round) {

			cout << endl << endl
				<< "Press 1 to add a District," << endl
				<< "Press 2 to add a Citizen," << endl
				<< "Press 3 to add a Party," << endl
				<< "Press 4 to add a citizen as an elector," << endl
				<< "press 5 to display all the districts," << endl
				<< "press 6 to display all the citizens," << endl
				<< "press 7 to display all the Parties," << endl
				<< "press 8 to add a vote," << endl
				<< "press 9 to display election results," << endl
				<< "press 11 save election," << endl
				<< "press 12 load previous election," << endl
				<< "press 0 to exit. " << endl;

			int selection;
			cin >> selection;

			while (selection < 0 || selection > 12)
			{
				cout << "invalid selection - try again:" << endl;
				cin >> selection;
			}

			switch (selection)
			{
			case ADD_DISTRICT:
			{	system("CLS");
			if (electionType == REGULAR_ELECTION)
			{
				string disName;
				int numberOfElectors;
				int disType;

				cout << endl << "Please enter the District name, Elector count and district type (1 for Uniform, 2 for Divided) : " << endl;

				cin >> disName >> numberOfElectors >> disType;
				if (numberOfElectors < 0)
					cout << "ERROR! - Number of electros must be positive" << endl;
				else
				{
					DistrictType dis;
					if (disType == 1)
						dis = DistrictType::UNIFORM;
					else if (disType == 2)
						dis = DistrictType::DIVIDED;
					else {
						cout << "Invalid district type";
						break;

					}

					Israel2020->addDistrict(disName, numberOfElectors, dis);
					cout << "District added successfully!" << endl;
				}
			}
			else if (electionType == SIMPLE_ELECTION)
			{
				cout << "ERROR! - Unable to add districts to a simple election";
			}
			break;
			}
			case ADD_CITIZEN:
			{
				system("CLS");
				string citName;
				int ID;
				int yearOfBirth;
				int districtID;

				cout << endl << "please enter the name of the citizen, his ID, year of birth and the number of the district: " << endl;
				cin >> citName >> ID >> yearOfBirth >> districtID;

				if ((Israel2020->getElectionYear() - yearOfBirth) < 18)
				{
					cout << "Citizen must be 18 years old or older." << endl;
					break;
				}

				if (electionType == SIMPLE_ELECTION)
					districtID = 0;
				District* dis = Israel2020->getDistrictByID(districtID);
				if (dis)
				{
					try {
						Citizen newCiti(citName, ID, yearOfBirth, dis, districtID);
						dis->addCitizen(newCiti);
						cout << "Citizen added successfully!" << endl;
					}
					catch (const std::invalid_argument & ia)
					{
						system("cls");
						cout << ia.what() << endl;
						break;
					}
				}
				else
					cout << "ERROR- district ID isn't valid!" << endl;

				break;
			}
			case ADD_PARTY:
			{
				system("CLS");
				int candidateID;
				string partyName;
				cout << endl << "Please enter the name of the Party and candidate ID: " << endl;
				cin >> partyName >> candidateID;
				Citizen* candidate = Israel2020->getCitizenByID(candidateID);
				if (candidate == nullptr)
				{
					cout << "Candidate need to be first enterd as a citizen!";
				}
				else {
					Israel2020->addParty(partyName, candidate);
					cout << "Party added successfully!" << endl;
				}
				break;
			}
			case ADD_ELECTOR:
			{
				system("CLS");
				int ID;
				int districtID;
				int partyID;

				cout << endl << "please enter elector's ID, party ID, and district ID" << endl;
				cin >> ID >> partyID >> districtID;

				District* dis = Israel2020->getDistrictByID(districtID);
				if (dis)
				{
					Citizen* newElector = dis->getCitizenByID(ID);
					if (newElector)
					{
						Party* curParty = Israel2020->getPartyByID(partyID);
						if (curParty)
						{
							if (electionType == SIMPLE_ELECTION)
								districtID = 0;
							Israel2020->addElector(districtID, partyID, *newElector);
							cout << newElector->getName() << " Was added successfully as an elector for: " << Israel2020->getPartyByID(partyID)->getPartyName() << " in " << Israel2020->getDistrictByID(districtID)->getDistrictName() << endl;
						}
						else
							cout << "ERROR - Party not found!" << endl;
					}
					else
						cout << "ERROR - citizen not found!" << endl;
				}
				else
					cout << "ERROR- district ID isn't valid!" << endl;

				break;
			}
			case SHOW_DISTRICTS:
			{	system("CLS");
			if (Israel2020->getElectionType() == REGULAR_ELECTION)
				Israel2020->printDistricts();
			else {
				cout << "Error - there are no districts in simple election";
			}
			break;
			}
			case SHOW_CITIZEN:
			{
				system("CLS");
				Israel2020->printCitizens();
				break;
			}
			case SHOW_PARTIES:
			{
				system("CLS");
				Israel2020->printParties();
				break;
			}
			case VOTE:
			{
				system("CLS");
				int ID;
				int partyID;
				cout << endl << "Please enter voter's ID and the party ID" << endl;
				cin >> ID >> partyID;
				Party* currParty = Israel2020->getPartyByID(partyID);
				Citizen* currCitizen = Israel2020->getCitizenByID(ID);

				if (currParty == nullptr)
					cout << "ERROR - No party exist with this ID" << endl;
				else if (currCitizen == nullptr)
					cout << "ERROR - No citizen has this ID" << endl;
				else if (currCitizen->getVotedStatus() == true)
					cout << "ERROR - This citizen has already voted!" << endl;
				else
				{
					Israel2020->vote(currCitizen, partyID);
					cout << currCitizen->getName() << " voted successfully to party " << currParty->getPartyName() << endl;
				}

				break;
			}
			case SHOW_RESULTS:
			{
				Israel2020->printResults();
				break;
			}
			case SAVE_ELECTION:
			{
				system("CLS");
				cout << "Please enter file name including file extension: " << endl;
				cin >> filename;
				ofstream out(filename, ios::binary | ios::trunc);
				try {
					Israel2020->save(out);
				}
				catch (const char* str)
				{
					system("CLR");
					cout << str << endl;
					exit(FILE_ERROR);
				}

				out.close();
				break;
			}
			case LOAD_ELECTION:
			{
				cout << "Please enter file name including file extension: " << endl;
				cin >> filename;
				system("cls");
				ifstream in(filename, ios::binary);
				if (!in)
					cout << "Unable to load election from this file.";
				delete Israel2020;
				try {
					Israel2020 = new Election;
					Israel2020->load(in);
				}
				catch (const std::invalid_argument & ia)
				{
					system("cls");
					cout << ia.what() << endl;
					delete Israel2020;
				}

				in.close();
				break;
			}
			case EXIT:
				round = false;
				exit(1);
				break;
			}
		}
	}
	catch (bad_alloc & ex)
	{
		cout << ex.what() << endl;
		exit(-1);
	}
	catch (const std::invalid_argument & ia)
	{
		cout << ia.what();
		exit(-1);
	}
	catch (const std::logic_error & le)
	{
		cout << le.what();
		exit(-1);
	}
	catch (...)
	{
		cout << "Unknown Error";
		exit(-1);
	}
}


int getElectionTypeFromUser(Election& election)
{
	int electionType;
	cout << "Press 1 for regular election " << endl;
	cout << "Press 2 for simple Election " << endl;
	cin >> electionType;

	if (electionType != 1 && electionType != 2)
	{
		cout << "Unvalid entry, election will be set to regular";
		electionType = 1;
	}

	election.setElectionType(electionType);
	return electionType;
}

void createDistrictForSimpleElection(Election& election)
{
	int numberOfElectors;
	cout << "Please enter the number of electors for this election ";
	cin >> numberOfElectors;
	election.addDistrict("Simple Election", numberOfElectors, DistrictType::DIVIDED);
}