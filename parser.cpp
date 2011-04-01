/*
 * =====================================================================================
 *
 *       Filename:  parser.cpp
 *
 *    Description:  Parser
 *
 *        Version:  1.0
 *        Created:  09.03.2011 19:21:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Przemysław Liszka (mistix), mistix@op.pl
 *        Company:  
 *
 * =====================================================================================
 */
#include "parser.h"
#include <iostream>
#include <string>
#include <dirent.h>
#include <fstream>

using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::getline;

Parser::Parser(const std::string& path_)
{
	vdir.push_back(path_);
}

void Parser::add_dir(const string& path)
{
	vdir.push_back(path);
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Parser
 *      Method:  Parser :: parseFilesFromDir
 * Description:  Extract only file with .viki extension
 *--------------------------------------------------------------------------------------
 */
int Parser::parseFilesFromDir(const char* str)
{
	string tmp(str);
	string ff(".viki");
	size_t found;

	if(tmp.length() > 2) {
		found = tmp.find(ff);
		if(found == string::npos) {
			return -1; //bad file type
		}
	} else {
		return -2; //this is not, a file
	}

	return 0;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Parser
 *      Method:  Parser :: getFilesFromDir
 * Description:  Make list of file contained in directory 
 *--------------------------------------------------------------------------------------
 */
void Parser::getFilesFromDir()
{
	struct dirent* dir;
	DIR *dp;

	for(it=vdir.begin(); it != vdir.end(); it++) {
		dp = opendir((*it).c_str());
		if(dp == NULL)
			cerr << "Can't open directory !" << endl;

		while((dir = readdir(dp))) {
			if(parseFilesFromDir(dir->d_name) == 0)
				vfile.push_back(dir->d_name);
		}
		closedir(dp);
	}
}

vector<string>& Parser::getRawTasks()
{
	getFilesFromDir();
	parseTaskFile();
	return vtask;
}

void Parser::parseTaskFile()
{
	string line;
	vector<string>::iterator dit;
	size_t found;

	for(dit=vdir.begin(); dit != vdir.end(); dit++) {
		for(it=vfile.begin(); it != vfile.end(); it++) {
			string path = *dit + "/" + *it;
			ifstream in(path.c_str());
			while(getline(in,line)) {
				found = line.find("#");
				if(found != string::npos) {
					/* TODO dodać zadania w wielu liniach */
					line = line.substr(found);
					vtask.push_back(line);
				}
			}
		}
	}
}
