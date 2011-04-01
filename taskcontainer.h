/*
 * =====================================================================================
 *
 *       Filename:  taskcontainer.h
 *
 *    Description:  TaskContainer for all tasks container
 *
 *        Version:  1.0
 *        Created:  10.03.2011 21:48:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Przemysław Liszka (mistix), mistix@op.pl
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  TASKCONTAINER_H
#define  TASKCONTAINER_H

#include "data.h"
#include <string>

class TaskContainer {
	std::string task;
	std::string typ;
	int typ_id;
	bool done;
	Data d_begin;
	Data d_end;
	
	TaskContainer();
public:
	TaskContainer(const std::string& typ, int typ_id, bool completed,
			const std::string& task, const Data& task_begin, 
			const Data& task_end);

	std::string& getType();
	std::string& getTask();
	int getTypeID();
	bool isCompleted();
	Data& getTaskBegin();
	Data& getTaskEnd(); 

	friend int operator<(const TaskContainer& left, const TaskContainer& right);
};

#endif   /* ----- #ifndef TASKCONTAINER_H  ----- */
