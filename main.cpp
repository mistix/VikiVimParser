/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09.03.2011 19:43:15
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
#include <cstring>

using namespace std;

int main(int argc, const char *argv[])
{
	Calendar c("/home/mistix/GTD");

	if(argc == 3) {
		switch(*(argv[1]+1)) {
			case 'T':
				cout << c.getTagsName(argv[2]);
				break;
			case 'M':
				cout << c.getMarkersName(argv[2]);
				break;
			default:
				cout << c.Tasks();
				break;
		}
	} else if(argc == 2) {
		switch(*(argv[1]+1)) {
			case 'W':
				cout << c.Tasks('W');
				break;
			case 's':
				cout << c.simpleTask();
				break;
			case 'A':
				cout << c.Tasks('A');
				break;
			case 'P':
				cout << c.Tasks('P');
				break;
			case 'R':
				cout << c.Tasks('R');
				break;
			case 't':
				cout << c.getTagsName();
				break;
			case 'm':
				cout << c.getMarkersName();
				break;
			case 'h':
				cout << "    ==== Help ====    " << endl
					<< "without options show sorted tasks" << endl
					<< "-W shows only tasks that must wait" << endl
					<< "-A shows all actions" << endl
					<< "-P shows all projects" << endl
					<< "-R shows only referential material" << endl
					<< "-t shows all tags names from your tasks" << endl
					<< "-m shows all names from your tasks";
				break;
			default:	
				cout << c.Tasks();
				break;
		}				
	} else {
		cout << c.Tasks();
	}
	return 0;
}
