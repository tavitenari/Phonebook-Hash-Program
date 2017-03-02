/*
"Tavi" Ioane Tenari
2/21/17
Program 3

This is the implementation code for all Listing objects.
Functions are detailed above each implementation.

*/
#include "Listing.h"

/*
DEFAULT CONSTRUCTOR
	Sets all data members to empty strings.
*/
Listing::Listing()
{
	first = "";
	last = "";
	areaCode = "";
	number = "";
}

/*
OVERLOADED CONSTRUCTOR
	takes 4 strings which set the first name, last name, area code, and 
	phone number data members respectively.
*/
Listing::Listing(string first, string last, string areaCode, string number)
{
	this->first = first;
	this->last = last;
	this->areaCode = areaCode;
	this->number = number;
}

/*
DESTRUCTOR
*/
Listing::~Listing()
{
}

//-------FUNCTION IMPLEMENTATION---------

/*
getFirstName
	This is a getter function which
	returns the data member "first",
	which represents the first name
	of the owner of the phone number.
*/
string Listing::getFirstName()
{
	return first;
}

/*
getLastName
	This is a getter function which
	returns the data member "last",
	which represents the last name
	of the owner of the phone number.
*/
string Listing::getLastName()
{
	return last;
}

/*
getAreaCode
	This is a getter function which 
	returns the data member "areaCode",
	which represents the 3-digit area code
	of the phone number.
*/
string Listing::getAreaCode()
{
	return areaCode;
}

/*
getNumber
	This is a getter function which
	returns the data member "number",
	which represents the 7-digit
	phone number in the listing.
*/
string Listing::getNumber()
{
	return number;
}