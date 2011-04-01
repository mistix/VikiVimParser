#ifndef  DATA_H
#define  DATA_H

#include <string>

class Data {
	int year;
	int month;
	int day;
	int february;
	bool leapYear;

	class DataExcept {
		const std::string err;
	public:
		DataExcept(const std::string& error) : err(error) {}
		const std::string& what() const {
			return err;
		}
	};
public:
	Data();
	Data(const std::string& data);
	Data(const Data& d);
	~Data();

	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	std::string getDay2str();
	std::string getMonth2str();
	std::string getYear2str();

	Data& operator=(const Data& right);
	friend int operator<(const Data& left, const Data& right);
	friend int operator>(const Data& left, const Data& right);
	friend int operator==(const Data& left, const Data& right);
	int difftime(const Data& day);
	int difftime();
};

#endif   /* ----- #ifndef DATA_H  ----- */
