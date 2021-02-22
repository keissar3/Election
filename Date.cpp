#include "Date.h"

Date::Date(int day, int month, int year)
{
	setDay(day);
	setMonth(month);
	setYear(year);
}

Date::Date() : Date(1, 1, 1900) {}
Date::Date(const Date& date) : _day(date._day), _month(date._month), _year(date._year) {}

Date::Date(istream& in_file)
{
	load(in_file);    // if load fail an exception will be thrown.
}

void Date::operator=(const Date& date)
{
	_day = date._day;
	_month = date._month;
	_year = date._year;
}

void Date::setYear(int year)
{
	if (year < 0)
		throw invalid_argument("Invalid year");
	_year = year;
}
int Date::getYear()const { return _year; }

void Date::setMonth(int month)
{
	if (month < 0 || month>12)
		throw invalid_argument("Invalid month");

	_month = month;
}
int Date::getMonth()const { return _month; }

void Date::setDay(int day)
{
	if (day < 0 || day>31)
		throw invalid_argument("Invalid day");
	_day = day;
}
int Date::getDay()const { return _day; }

void Date::save(ostream& out_file)const
{
	/* binary data of citizen is saved in this order:
		1.day
		2.month
		3.year */

	out_file.write(reinterpret_cast<const char*>(&_day), sizeof(_day));
	out_file.write(reinterpret_cast<const char*>(&_month), sizeof(_month));
	out_file.write(reinterpret_cast<const char*>(&_year), sizeof(_year));

	if (!out_file.good())
		throw logic_error("error- can't save date.");
}

void Date::load(istream& in_file)
{
	try {
		int day, month, year;

		in_file.read(reinterpret_cast<char*>(&day), sizeof(day));
		in_file.read(reinterpret_cast<char*>(&month), sizeof(month));
		in_file.read(reinterpret_cast<char*>(&year), sizeof(year));
		setDay(day);
		setMonth(month);
		setYear(year);
	}
	catch (const std::invalid_argument & ia)
	{
		cout << "Error While trying load date from file:" << endl;
		cout << ia.what() << endl;
		throw invalid_argument("error - can't load date from this file");
	}

	if (!in_file.good())
		throw invalid_argument("error- can't load date from this file. ");
}

ostream& operator<<(ostream& os, const Date& date)
{
	os << date._day << "/" << date._month << "/" << date._year;
	return os;
}