/*
 * =====================================================================================
 *
 *       Filename:  calendar.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10.03.2011 23:15:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Przemysław Liszka (mistix), mistix@op.pl
 *        Company:  
 *
 * =====================================================================================
 */
#include "calendar.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>

using std::string;
using std::vector;
using std::set;
using std::istringstream;
using std::ostringstream;
using std::cout;
using std::endl;

string& Calendar::getMarkersName(const string& marker)
{
	findTasks();
	vector<TaskContainer*>::iterator it;
	TaskContainer* tc = NULL;
	task = "";
	for(it=vtask.begin(); it!=vtask.end(); it++) {
		tc = *it;
		string tmp = tc->getTask();
		size_t found;
		found = tmp.find("@"+marker);
		if(found != string::npos) {
			found = tmp.find(" ", found);
			task = "<span color=\"#cdf18f\">" + (tc->getTaskEnd()).getDay2str() + " " \
					+ month[tc->getTaskEnd().getMonth()-1] + "</span>" + \
				   	": " + (tc->getTask()).substr(found+1) +"\n";
		}
	}
	return task;
}

string& Calendar::getTagsName(const string& name)
{
	findTasks();
	vector<TaskContainer*>::iterator it;
	TaskContainer* tc = NULL;
	for(it=vtask.begin(); it!=vtask.end(); it++) {
		tc = *it;
		string tmp = tc->getTask();
		size_t found;
		found = tmp.find(":"+name);
		if(found != string::npos) {
			found = tmp.find(" ", found);
			task += "<span color=\"#cdf18f\">" + (tc->getTaskEnd()).getDay2str() + " " + \
			month[tc->getTaskEnd().getMonth()-1] + "</span>" + \
			": " + (tc->getTask()).substr(found+1) +"\n";
		}
	}
	return task;
}

void Calendar::setDirPath(const string& path)
{
	parser.add_dir(path);
}

Calendar::~Calendar()
{
	vector<TaskContainer*>::iterator it;
	for(it=vtask.begin(); it != vtask.end(); it++) {
		delete *it;
	}
}

bool Calendar::isData(const string& data)
{
	if(isTaskDone(data)) return false;
	size_t found, local = 0;
	string pattern = "0123456789-.";
	int i = 0;

	while((found = data.find_first_of(pattern,local)) != string::npos) {
		i++;
		local = found + 1;
	}
	if(i >= 10) return true;

	return false;
}

bool Calendar::isTaskDone(const string& task)
{
	if(task.at(0) == 'x') return true;
	return false;
}

int Calendar::taskPrior(const string& type)
{
	if(type.length() == 2) return 0;
	istringstream iss(type.substr(2,1));
	int prior = 0;
	iss >> prior;
	return prior;
}

/*-----------------------------------------------------------------------------
 *  Function used for sorting container
 *-----------------------------------------------------------------------------*/
static bool sortfunc(TaskContainer* t1, TaskContainer* t2)
{
	if(t1->getTaskEnd() < t2->getTaskEnd()) {
		return true;
	} else if(t1->getTaskEnd() == t2->getTaskEnd()) {
		if(t1->getTypeID() < t2->getTypeID()) {
			return true;
		}
	}
	return false;
}

string Calendar::trim(const string& str)
{
	if(str.length() == 0) return str;
	size_t beg = str.find_first_not_of(" \a\b\f\n\r\t\v");
	size_t end = str.find_last_not_of(" \a\b\f\n\r\t\v");
	if(beg == string::npos) return "";
	return string(str,beg,end-beg+1);
}

string& Calendar::getTagsName()
{
	return getMarkers(":");
}

string& Calendar::getMarkersName()
{
	return getMarkers("@");
}

void Calendar::findTasks()
{
	istringstream iss;
	vector<string>::iterator it;
	vector<string>& p = parser.getRawTasks();
	size_t found;
	size_t imhear;
	size_t last;
	int enter;

	string typ, task;
	int typ_id;
	bool done;
	Data* begin, *end;

	for(it=p.begin(); it!=p.end(); it++) {
		enter = 0;
		imhear = 0;
		typ_id = 0;
		done = false;
		string tasks = *it;
		while((found = tasks.find(" ",imhear)) != string::npos) {
			imhear = found +1;
			if(++enter > 1) break;
			last = found;
		}
		string type = tasks.substr(0,last); // #A1 e.g
		/* FIXME poprawić datę bo źle działa w przypadku gdy jest jej
		 * brak */
		string data = tasks.substr(last+1, found-last-1); // 2011-03-03..2011-03-09
		if(isData(data) && !isTaskDone(data)) {
			if(data.length() > 10) {
				begin = new Data(data.substr(0,10));
				end = new Data(data.substr(12));
			} else {
				begin = new Data();
				end = new Data(data.substr(0));
			}
			task = tasks.substr(found+1); // task
		} else {
			begin = new Data();
			end = new Data();
			task = tasks.substr(last+1);
		}
		typ_id = taskPrior(type);
		typ = type.substr(1,1); // A W P R etc.
		TaskContainer* tc = new TaskContainer(typ, typ_id, done, task, 
				*begin, *end);
		vtask.push_back(tc);
	} // for
	sort(vtask.begin(), vtask.end(), sortfunc);
}

string& Calendar::Tasks(char c)
{
	findTasks();
	vector<TaskContainer*>::iterator it;
	for(it=vtask.begin(); it != vtask.end(); it++) {
		TaskContainer* tc = *it;
		char cc = (tc->getType()).at(0);
		if(cc == c) {
			task += "<span color=\"#cdf18f\">" + tc->getTask() + "</span>\n";
		}
	}
	return task;
}

string& Calendar::getMarkers(const string& marker)
{
	set<string> alltags;
	findTasks();
	vector<TaskContainer*>::iterator it;
	for(it=vtask.begin(); it != vtask.end(); it++) {
		size_t space;
		size_t colon;
		TaskContainer* tc = *it;
		string tag = tc->getTask();
		colon = tag.find(marker);
		if(colon != string::npos) {
			space = tag.find(" ", colon);
			if(space != string::npos) {
				alltags.insert(tag.substr(colon+1, space-colon));
			}
		}
	} // ! ----- for end ------ !
	
	set<string>::iterator sit;
	for(sit=alltags.begin(); sit != alltags.end(); sit++) {
		task += *sit;
		task += "\n";
	}
	return task;
}

string& Calendar::Tasks()
{
	findTasks();
	vector<TaskContainer*>::iterator it;
	for(it=vtask.begin(); it != vtask.end(); it++) {
		if((*it)->getTaskEnd().getYear() == 0) continue;
		if((((*it)->getTaskEnd()).difftime() <= 7) && (((*it)->getTaskEnd()).difftime() > 3)) {
			task += "<span color=\"green\">" + ((*it)->getTaskEnd()).getDay2str();
			task += " " + month[((*it)->getTaskEnd()).getMonth()-1] + "</span>";
			task += " : " + ((*it)->getTask()) + "\n";
		}
		if((((*it)->getTaskEnd()).difftime() <= 3) && (((*it)->getTaskEnd()).difftime() > 1)) {
			task += "<span color=\"yellow\">" + ((*it)->getTaskEnd()).getDay2str();
			task += " " + month[((*it)->getTaskEnd()).getMonth()-1] + "</span>";
			task += " : " + ((*it)->getTask()) + "\n";
		}
		if(((*it)->getTaskEnd()).difftime() == 1) {
			task += "<span color=\"red\">" + ((*it)->getTaskEnd()).getDay2str();
			task += " " + month[((*it)->getTaskEnd()).getMonth()-1] + "</span>";
			task += " : " + ((*it)->getTask()) + "\n";
		}
	}
	return task;
}

string& Calendar::simpleTask()
{
	ostringstream oss;
	findTasks();
	std::sort(vtask.begin(), vtask.end(), sortfunc);
	one = 0;
	three = 0;
	seven = 0;
	vector<TaskContainer*>::iterator it;
	for(it=vtask.begin(); it != vtask.end(); it++) {
		if((*it)->getTaskEnd().getYear() == 0) continue;
		if((((*it)->getTaskEnd()).difftime() <= 7) && (((*it)->getTaskEnd()).difftime() > 3)) seven++;
		if((((*it)->getTaskEnd()).difftime() <= 3) && (((*it)->getTaskEnd()).difftime() > 1)) three++;
		if(((*it)->getTaskEnd()).difftime() == 1) one++;
	}
	simple = "";
	oss << one;
	simple += "<span color=\"red\">" + oss.str() + "</span>";
	simple += "/";
	oss.str(" ");
	oss << three;
	simple += "<span color=\"yellow\">" + oss.str() + "</span>";
	simple += "/";
	oss.str(" ");
	oss << seven;
	simple += "<span color=\"green\">" + oss.str() + "</span>";
	return simple;
}
