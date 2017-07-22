//Reza Mansouri - rmansouri@csu.fullerton.edu
//Itsaraphong Sawangsri - itsaraphong@csu.fullerton.edu
//Assignment 2

#include "ast.h"


void JsonObject::Add(string s, JsonValue* value)
{
    Debug("- JsonObject - Add" << endl);
    pairs[s] = value;

}

void JsonObject::Print()
{
    Debug("- JsonObject - Print" << endl);

    //start object
    cout << "( object ";
    for(map<string,JsonValue*>::iterator itmap=pairs.begin();
                itmap != pairs.end(); itmap++)
    {
        cout << itmap->first << " (";
        itmap->second->Print();
        cout << " ) ";
    }

    //end object
    cout << ") " << endl;
}

//Array
void JsonArray::Print()
{
    Debug("- JsonArray - Print" << endl);

    cout << " array ";
    for(list<JsonValue*>::iterator it=values.begin()
                ; it != values.end(); it++)
    {
        cout << " ( ";
       (*it)->Print();
       cout << " )";
    }
}

void JsonArray::Add(JsonValue *v)
{
	Debug("- JsonArray - Add" << endl);
    values.insert(values.end(), v);
}


//All print not include Array
void JsonString::Print()
{
    cout << "string " << value;
}

void JsonNumber::Print()
{
    cout << "number " << value;
}

void JsonBoolean::Print()
{
    if(value)
        cout << "boolean true";
    else
        cout << "boolean false";
}

void JsonNull::Print()
{
    cout << "null";
}
