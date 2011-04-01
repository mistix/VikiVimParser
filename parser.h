#ifndef  PARSER_H
#define  PARSER_H

#include <vector>
#include <string>

class Parser {
	std::vector<std::string> vdir;
	std::vector<std::string> vfile;
	std::vector<std::string>::iterator it;
	std::vector<std::string> vtask;

	int parseFilesFromDir(const char* str);
	void getFilesFromDir();
	void parseTaskFile();
public:
	Parser() {};
	Parser(const std::string& path);

	void add_dir(const std::string& path);

	std::vector<std::string>& getRawTasks();
};

#endif   /* ----- #ifndef PARSER  ----- */
