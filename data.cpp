#include "data.h"
#include <iostream>
#include <sstream>
#include <ctime>

using std::string;
using std::istringstream;
using std::ostringstream;
using std::cout;
using std::endl;
using std::cerr;

Data::Data()
{
	year = 0;
	month = 0;
	day = 0;
	february = 0;
	leapYear = false;
}

Data::Data(const string& data)
{
	try {
		istringstream iss;
		iss.str(data.substr(0,4));
		iss >> year;
		iss.clear();
		iss.str(data.substr(5,2));
		iss >> month;
		iss.clear();
		iss.str(data.substr(8,2));
		iss >> day;

		if((year%4 == 0) && ((year%100 == 0) || (year%400 == 0))) {
			february = 29;
			leapYear = true;
		} else {
			february = 28;
			leapYear = false;
		}

		if((month < 1) || (month > 12)) throw DataExcept("Month out of range 1-12");
		if((day < 1) || (day > 31)) {
			throw DataExcept("Day out of range 1-31");
		} else if((month == 2) && (day < 1 || day > february)) {
			throw DataExcept("February has to many days");
		}
	} catch(const DataExcept& e) {
		cerr << e.what() << endl;
	}
}

Data::Data(const Data& d)
{
	if(this != &d) {
		this->year = d.year;
		this->month = d.month;
		this->day = d.day;
		this->february = d.february;
		this->leapYear = d.leapYear;
	}
}

Data::~Data()
{
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Data
 *      Method:  Data :: difftime
 * Description:  Give number of days past from actual date
 *--------------------------------------------------------------------------------------
 */
int Data::difftime(const Data& d)
{
	struct tm *timeinfo, *endtime;
	time_t end, start, rawtime;
	double time_s;
	
	time(&rawtime);
	// poczatek czasu
	timeinfo = localtime(&rawtime);
	timeinfo->tm_year = this->getYear() - 1900;
	timeinfo->tm_mon = this->getMonth() - 1;
	timeinfo->tm_mday = this->getDay();
	start = mktime(timeinfo);

	// koniec czasu
	endtime = localtime(&rawtime);
	endtime->tm_year = d.getYear() - 1900;
	endtime->tm_mon = d.getMonth() - 1;
	endtime->tm_mday = d.getDay();
	end = mktime(endtime);

	if(*this < d) {
		time_s = std::difftime(end,start);
	} else {
		time_s = std::difftime(start,end);
	}

	int days = time_s / 86400;
	return days;
}

int Data::difftime()
{
	struct tm* timeinfo;
	time_t rawtime;
	time_t end, start;
	double time_s;
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_year = getYear() - 1900;
	timeinfo->tm_mon = getMonth() - 1;
	timeinfo->tm_mday = getDay();

	time(&start); // local time
	end = mktime(timeinfo);
	time_s = std::difftime(end,start);

	int days = time_s / 86400;
	return days;
}

Data& Data::operator=(const Data& r) 
{
	if(this != &r) {
		year = r.year;
		month = r.month;
		day = r.day;
		february = r.february;
		leapYear = r.leapYear;
	}

	return *this;
}

/* TODO poprawić ten operator !! */
int operator<(const Data& l, const Data& r)
{
	if(l.getYear() < r.getYear()) {
		return 1;
	} else {
		if(l.getYear() == r.getYear()) {
			if(l.getMonth() < r.getMonth()) {
				return 1;
			} else {
				if(l.getMonth() == r.getMonth()) {
					if(l.getDay() < r.getDay()) {
						return 1;
					} else {
						return 0;
					}
				} else {
					return 0;
				}
			}
		} else {
			return 0;
		}
	}
	return 0;
}

int operator>(const Data& left, const Data& right)
{
	if(left.getYear() > right.getYear()) {
		return 1;
	} else if(left.getMonth() > right.getMonth()) {
		return 1;
	} else if(left.getDay() > right.getDay()) {
		return 1;
	}

	return 0;
}

int operator==(const Data& left, const Data& right)
{
	if(left.getYear() == right.getYear()) {
		if(left.getMonth() == right.getMonth()) {
			if(left.getDay() == right.getDay()) {
				return 1;
			}
		}
	}

	return 0;
}

string Data::getDay2str()
{
	ostringstream oss;
	oss << day;
	if(day == 0) return "";
	return oss.str();
}

string Data::getMonth2str()
{
	ostringstream oss;
	oss << month;
	if(month == 0) return "";
	return oss.str();
}

string Data::getYear2str()
{
	ostringstream oss;
	oss << year;
	if(year == 0) return "";
	return oss.str();
}
