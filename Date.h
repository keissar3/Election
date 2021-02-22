#pragma once
#include <fstream>
#include <iostream>
using namespace std;

class Date
{
private:
	int _day;
	int _month;
	int _year;
public:
	Date();
	Date(int day, int month, int year);
	Date(const Date& date);
	Date(istream& in_file);

	void operator=(const Date& date);

	void setYear(int year);
	int getYear()const;

	void setMonth(int month);
	int getMonth()const;

	void setDay(int day);
	int getDay()const;

	void save(ostream& out_file)const;
	void load(istream& in_file);
	friend ostream& operator<<(ostream& os, const Date& date);
};

