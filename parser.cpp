//Reza Mansouri - rmansouri@csu.fullerton.edu
//Itsaraphong Sawangsri - itsaraphong@csu.fullerton.edu
//Assignment 2

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cerrno>
#include "parser.h"
#include "ast.h"


void Parser::skipspace() {
	char c;
	while(isspace(c = stream_->get())) {
		//do nothing
		if(c == '\n'){
		m_line++;
		}
		
	}
	//put back non whitespace char 
	stream_->unget();
}

char Parser::readChar() {
	skipspace();
	char c = stream_->get();
	if(c == '\n'){
		m_line++;
	}
	return c;
}

//JSON Object: {members*}
JsonObject *Parser::jObj() {
	skipspace();
	char c;
	if ((c = readChar()) != '{') {
		string errorMessage = "Expected '{' but got ";
		errorMessage.push_back(c);
		parseError(errorMessage);
	}
	JsonObject *o = new JsonObject();
	if ((c = readChar()) == '}') { 
		//empty object
		
	} else { // should contain string value pair
		stream_->unget();
		
		jMembers(o);
		stream_->unget();
		
		if ((c = readChar()) != '}') {
			string errorMessage = "Expected '}' but got ";
			errorMessage.push_back(c);
			parseError(errorMessage);
		}
		
	}
	return o;
}

//JSON Members: string:value, members*
void Parser::jMembers(JsonObject *o) {
	skipspace();
	char c;
	
	string str = jStr();
	//string and value should be separated by :
	if ((c = readChar()) != ':') {
		string errorMessage = "Expected ':' but got " + c;
		parseError(errorMessage);
	} 
	//jVal(str, *o);
	o->Add(str, jVal());
	//if comma, more string:value pairs 
	if ((c = readChar()) == ',') {
		jMembers(o);
	}
}

//JSON Array: [Elements*]
JsonArray *Parser::jArr() {
	skipspace();
	char c;
	if ((c = readChar()) != '[') {
		string errorMessage = "Expected '[' but got ";
		errorMessage.push_back(c);
		parseError(errorMessage);
	}
	JsonArray *a = new JsonArray();
	
	if ((c = readChar()) == ']') {
		//empty array
		
	} else {
		stream_->unget();
		jElements(a);
		stream_->unget();
		if ((c = readChar()) != ']') {
			string errorMessage = "Expected ']' but got ";
			errorMessage.push_back(c);
			parseError(errorMessage);
		}
	}
	return a;
}

//JSON Elements: list of JSON values
void Parser::jElements(JsonArray *a) {
	skipspace();
	char c;
	
	a->Add(jVal());
	//if comma, more values
	if ((c = readChar()) == ',') {
		jElements(a);
	}
}

string Parser::jStr() {
	string str;
	char c;
	//string should be enclosed in quotes
	if ((c = stream_->get()) != '"') {
		string errorMessage = "Expected '\"' but got ";
		errorMessage.push_back(c);
		parseError(errorMessage);
	}
	//read string until end quote
	while((c = stream_->get()) != '"') {
		if (c == '\\') {
			string errorMessage = "String cannot contain control characters.";
			parseError(errorMessage);
		}
		else if(c == '\n'){
			string errorMessage = "String need to be terminated";
			parseError(errorMessage);
		}
		str.push_back(c);
	}
	return str;
}

//JSON Number: int, int followed by fraction part, int followed by exponent, or both
JsonNumber *Parser::jNum() {
	skipspace();
	//atof(str);
	string str;
	char c = stream_->get();
	while( isdigit(c) 
				|| c == '-' 
				|| c == 'e' 
				|| c == 'E' 
				|| c == '+' 
				|| c == '.') {
		str.push_back(c);
		c = stream_->get();
	}
	stream_->unget();
	errno = 0;
	double dbl = atof(str.c_str());
	if (errno) {
		string errorMessage = "Expected JSON Number but got " + str;
		parseError(errorMessage);
	}
	return new JsonNumber(dbl);
}

//JSON Value is JSON Object, JSON Array, JSON String, JSON number, or true/false/null
JsonValue *Parser::jVal() {
	skipspace();
	char c = readChar();
	string tr, fa, nu;
	JsonValue *ret;
	switch(c) {
		case '"':
			stream_->unget();
			ret = new JsonString(jStr());
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-':
			stream_->unget();
			ret = jNum();
			break;
		case '{':
			stream_->unget();
			ret = jObj();
			break;
		case '[':
			stream_->unget();
			ret = jArr();
			break;
		case 't':
			stream_->unget();
			for(int i=0; i < 4; i++) {
				c = stream_->get();
				tr.push_back(c);
			}
			if (tr != "true") {
				string errorMessage = "Expected 'true' but got " + tr;
				parseError(errorMessage);
			}
			ret = new JsonBoolean(true);
			break;
		case 'f':
			stream_->unget();
			for(int i=0; i < 5; i++) {
				c = stream_->get();
				fa.push_back(c);
			}
			if (fa != "false") {
				string errorMessage = "Expected 'false' but got " + fa;
				parseError(errorMessage);
			}
			ret = new JsonBoolean(false);
			break;
		case 'n':
			stream_->unget();
			for(int i=0; i < 4; i++) {
				c = stream_->get();
				nu.push_back(c);
			}
			if (nu != "null") {
				string errorMessage = "Expected 'null' but got " + nu;
				parseError(errorMessage);
			}
			ret = new JsonNull();
			break;
		default:
			string errorMessage = "Expected JSON Value but got " + c;
			parseError(errorMessage);
			break;
	}
	return ret;
}
//needs to be fixed
void Parser::parseError(const string &message) {
	//cout << message << " at Line: " << m_line << endl;
	string newMess = message;
	newMess.append("  - at Line: ");
	newMess.append(to_string(m_line));
	//newMess.push_back
	try{
		throw ParseError(newMess);
	}
	catch(ParseError& k)
	{
		cout << k.err() << endl;
	}
	
}