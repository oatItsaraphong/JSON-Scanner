//Reza Mansouri - rmansouri@csu.fullerton.edu
//Itsaraphong Sawangsri - itsaraphong@csu.fullerton.edu
//Assignment 2

#ifndef PARSER_H_
#define PARSER_H_

#include <exception>
#include <fstream>
#include <deque>
#include "ast.h"

using namespace std;

class ParseError : public exception {
public: 
	ParseError(const string &msg) : message_(msg) {}
	virtual const char* err() throw() {
		return message_.c_str();
	}
	virtual ~ParseError() throw() {}
private:
	string message_;
};

class Parser {
public:
	Parser(ifstream *stream): stream_(stream){}
	~Parser() {}

	JsonValue *		jVal();

private:
	ifstream *		stream_;
	int 			m_line = 1;
	string 			errorMessage;
	
	void 			skipspace();
	char 			readChar();

	JsonObject *	jObj();
	void 			jMembers(JsonObject *o);
	JsonArray *		jArr();
	void 			jElements(JsonArray *a);
	string 			jStr();
	JsonNumber *	jNum();

	void 			parseError(const string &message);	
};
#endif