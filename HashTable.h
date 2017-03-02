/*
"Tavi" Ioane Tenari
2/21/17
Program 3

HashTable

This class reads in entries from a text file and converts the data into Listing objects.
The Listing objects are created as each line is parsed, and the listings are stored in a queue.
When the queue is processed, each listing is popped and hashed into the hash table one-by-one.

The class features 3 hash functions which I developed. Hash3 is arguably the most efficient function,
and is the function which will run when the driver is run.

*/
#include "Listing.h"
#include "time.h"
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//-------------GLOBAL MEMBERS--------------------------------------------
const int LISTINGS = 46332;			// number of entries in phonebook.txt
const int TABLE_SIZE = 4177;		// size of the hash table
const int ALPHA_OFFSET = 65;		// for ASCII conversion of letters
const int NUM_OFFSET = 48;			// for ASCII conversion of numbers
//-----------------------------------------------------------------------

class HashTable{

public:
	//--------CONSTRUCTORS-----
	HashTable();
	HashTable(string fileName);
	~HashTable();
	//-------------------------

	//-------CLASS FUNCTIONS---------
	int Hash1(Listing listing);
	int Hash2(Listing listing);
	int Hash3(Listing listing);
	
	void BuildTable(string fileName);
	void FillQueue(string fileName);
	void DisplayChainLengths();
	void DisplayTable();
	void ProcessQueue();
	//-------------------------------

private:
	//---------DATA MEMBERS--------------------------------------------------------------------------------
	queue<Listing> processQueue;		//A FIFO queue of all listings that will be added to the hash table	
	vector<Listing> table[TABLE_SIZE];	//A hash table whose structure is an array of vectors
	//-----------------------------------------------------------------------------------------------------
};