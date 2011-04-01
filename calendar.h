/*
 * =====================================================================================
 *
 *       Filename:  calendar.h
 *
 *    Description:  Calendar class final class
 *
 *        Version:  1.0
 *        Created:  10.03.2011 22:39:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Przemysław Liszka (mistix), mistix@op.pl
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef CALENDAR_H
#define CALENDAR_H

#include "taskcontainer.h"
#include "parser.h"
#include <vector>

class Calendar {
	int one;
	int three;
	int seven;
	std::string simple;
	std::string task;
	std::string month[12];
	Parser parser;

	std::vector<TaskContainer*> vtask;
	void findTasks();
	bool isTaskDone(const std::string& task);
	bool isData(const std::string& data);
	int taskPrior(const std::string& type);
	std::string trim(const std::string& str);
	std::string& getMarkers(const std::string& marker); // pobieranie wszystkich tagów :Programowanie, imion @Mariola
public:
	Calendar(): one(0), three(0), seven(0) {
		month[0] = "styczeń";
		month[1] = "luty";
		month[2] = "marzec";
		month[3] = "kwiecień";
		month[4] = "maj";
		month[5] = "czerwiec";
		month[6] = "lipiec";
		month[7] = "sierpień";
		month[8] = "wrzesień";
		month[9] = "październik";
		month[10] = "listopad";
		month[11] = "grudzień";
	};
	Calendar(const std::string& path): one(0), three(0), seven(0) { 
		month[0] = "styczeń";
		month[1] = "luty";
		month[2] = "marzec";
		month[3] = "kwiecień";
		month[4] = "maj";
		month[5] = "czerwiec";
		month[6] = "lipiec";
		month[7] = "sierpień";
		month[8] = "wrzesień";
		month[9] = "październik";
		month[10] = "listopad";
		month[11] = "grudzień";
		parser.add_dir(path); 
	};
	~Calendar();

	void setDirPath(const std::string& path);
	std::string& simpleTask(); //uproszczona forma w postaci 1/2/3
	std::string& Tasks(); // zadanie kolorowe do kalendarza
	std::string& Tasks(char c); // wyswietlanie konkretnych zadan a w r 
	std::string& getMarkersName(); // pobieranie nazwy wszystkich makrkerów
	std::string& getMarkersName(const std::string& marker);
	std::string& getTagsName();
	std::string& getTagsName(const std::string& name);
};

#endif   /* ----- #ifndef CALENDAR_H  ----- */
