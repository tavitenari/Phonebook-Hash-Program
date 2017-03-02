/*
"Tavi" Ioane Tenari
2/21/17
Program 3

Listing

This class creates objects which store phone number listings per the data in phonebook.txt.
The object stores the first name, last name, area code, and 7-digit phone number as strings members.

The Listing objects are created when HashTable objects are created.

*/
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Listing {

public:
	//--------CONSTRUCTORS---------------------------------------------
	Listing();
	Listing(string first, string last, string areaCode, string number);
	~Listing();
	//-----------------------------------------------------------------

	//--CLASS FUNCTIONS---
	string getFirstName();
	string getLastName();
	string getAreaCode();
	string getNumber();
	//--------------------

private:
	//-DATA MEMBERS-
	string first;
	string last;
	string areaCode;
	string number;
	//--------------
};