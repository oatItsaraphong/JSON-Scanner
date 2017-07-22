//Reza Mansouri - rmansouri@csu.fullerton.edu
//Itsaraphong Sawangsri - itsaraphong@csu.fullerton.edu
//Assignment 2

#ifndef AST_H_
#define AST_H_

#ifdef USEDEBUG
#define Debug(x) cout << x
#else 
#define Debug(x)
#endif

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <map>
#include <list>
using namespace std;


class JsonValue
{
    public:
        virtual void Print() = 0;
};

class JsonObject : public JsonValue
{
    private:
        map<string, JsonValue*> pairs;

    public:
        virtual void Print();
        void Add(string name, JsonValue* value);
};

class JsonString : public JsonValue
{
    private:
        string value;

    public:
        JsonString(string s) : value(s) { };
        virtual void Print();
};

class JsonNumber : public JsonValue
{
    private:
        double value;

    public:
        JsonNumber(double d) : value(d) { };
        virtual void Print();
};

class JsonBoolean : public JsonValue
{
    private:
        bool value;

    public:
        JsonBoolean(bool b) : value(b) { };
        virtual void Print();
};

class JsonNull : public JsonValue
{
    public:
        virtual void Print();
};



class JsonArray : public JsonValue
{
    private:
        list<JsonValue*> values;

    public:
        virtual void Print();
        void Add(JsonValue *v);
};



#endif // AST_H_
