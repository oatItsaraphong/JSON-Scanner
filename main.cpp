//Reza Mansouri - rmansouri@csu.fullerton.edu
//Itsaraphong Sawangsri - itsaraphong@csu.fullerton.edu
//Assignment 2

//#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include "ast.h"
#include "parser.h"


using namespace std;

int main(int argc, char* argv[])
{
    /*JsonObject* o = new JsonObject();
    o->Add("str", new JsonString("foo"));
    o->Add("num", new JsonNumber(123));
    o->Add("bool", new JsonBoolean(true));
    o->Add("nul", new JsonNull());

    JsonArray *a = new JsonArray();
    a->Add(new JsonString("bar"));
    a->Add(new JsonNumber(456));
    a->Add(new JsonBoolean(false));
    o->Add("arr", a);

    o->Print();
    */

    if (argc != 2) 
    {
        cout << "Not enough arguments, please include JSON file" << endl;
        return 0;
    }
    ifstream ifs(argv[1]);
    Parser parser(&ifs);
    
    //should be in try catch but error catching is having problems
    JsonValue *val = parser.jVal();
    val->Print();    
    /*
    try {
        JsonValue *val = parser.jVal();
        val->Print();    
    } catch (ParseError e) {
        cerr << "The JSON file contains an error: " << endl;
        cerr << e.err() << endl;
    }*/
    
    return 0;
}//end main
