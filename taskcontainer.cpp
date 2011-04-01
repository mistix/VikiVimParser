/*
 * =====================================================================================
 *
 *       Filename:  taskcontainer.cpp
 *
 *    Description:  TaskContainer methods
 *
 *        Version:  1.0
 *        Created:  10.03.2011 21:58:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Przemysław Liszka (mistix), mistix@op.pl
 *        Company:  
 *
 * =====================================================================================
 */
#include "taskcontainer.h"
#include <iostream>

using std::string;

TaskContainer::TaskContainer(const string& Typ, int Typ_id, bool completed,
		const string& Task, const Data& task_begin, const Data& task_end)
{
	typ = Typ;
	typ_id = Typ_id;
	done = completed;
	task = Task;
	d_begin = task_begin;
	d_end = task_end;
}

int operator<(const TaskContainer& left, const TaskContainer& right)
{
	return (left.d_end < right.d_end);
}

string& TaskContainer::getType()
{
	return typ;
}

string& TaskContainer::getTask()
{
	return task;
}

int TaskContainer::getTypeID()
{
	return typ_id;
}

bool TaskContainer::isCompleted()
{
	return done;
}

Data& TaskContainer::getTaskBegin()
{
	return d_begin;
}

Data& TaskContainer::getTaskEnd()
{
	return d_end;
}
