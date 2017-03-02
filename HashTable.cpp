/*
"Tavi" Ioane Tenari
2/21/17
Program 3

This is the implmentation for all HashTable objects.
Functions are detailed above each implementation.

*/
#include "HashTable.h"

/*
DEFAULT CONSTRUCTOR
	Sets all elements of queue and hash table to empty listings.
*/
HashTable::HashTable()
{
	Listing emptyListing("", "", "", "");
	for (int i = 0; i < processQueue.size(); i++)
	{
		processQueue.push(emptyListing);
	}
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		table[i].push_back(emptyListing);
	}
}

/*
OVERLOADED CONSTRUCTOR
	Takes a txt filename as a parameter, and create a HashTable object
	by hashing the contents of the file and storing the data in a hash table.
*/
HashTable::HashTable(string fileName)
{
	FillQueue(fileName);
	ProcessQueue();
}

/*
DESTRUCTOR
*/
HashTable::~HashTable()
{
}

//-----------------------------------FUNCTION IMPLEMENTATION---------------------------------------------------------------------------------------------------------------------------

/*
Hash1
	This hash function takes a listing object as a parameter, and returns an
	integer which represents the index of the hash table where the listing will
	be stored. 

	The hash is determined by the alpha-numeric value of the sum of the data members
	first, last, areaCode, and number of the listing parameter.
*/
int HashTable::Hash1(Listing listing)
{
	int index = 0;

	//-----------------HASHING ALGORITHM----------------------------------------------------------------------------------------------------
	string line = listing.getFirstName() + listing.getLastName() +			// alpha-numeric sum of first name, last name, and phone number.
				  listing.getAreaCode() + listing.getNumber();
	//--------------------------------------------------------------------------------------------------------------------------------------

	for (int i = 0; i < line.length(); i++)
	{
		index += line[i];
	}

	return (index % TABLE_SIZE);		//The hash is returned mod TABLE_SIZE
}

/*
Hash2
	This hash function takes a listing object as a parameter, and returns an
	integer which represents the index of the hash table where the listing will
	be stored. 

	The hash is determined by the following algorithm:

	(18 * the first initial of the first name) +
	(468 * the sequence position of the first initial of the last name) +
	(the sequence position of the third digit of the phone number) +
	(the sequence position of the first digit of the area code)

	The sequence position is determined by the STRING-LEGENDS, which emulate the sequence in which 
	the information reads if the phonebook entries are sorted.

	The result is a hash which fills the table HORIZONTALLY based on the alpha-numeric value of the first and last names.
*/
int HashTable::Hash2(Listing listing)
{
	//------------------------STRING-LEGENDS---------------------------------------------------------------------------
	const string numSequence = "78-0123456";								// sequence for third digit of phone number
	const string areaSequence = "--0-9";									// sequence for first digit of area code
	const string nameSequence = "01--2-3--4-5------67-----8";				// sequence for first digit of last name
	//-----------------------------------------------------------------------------------------------------------------

	//-----------------------HASHING-VARIABLE DEFINITIONS-----------------------------------------------------------------------------------------
	const int subBlock = 18;												// (9 numbers) * (2 area codes)
	const int mainBlock = 468;												// (9 numbers) * (26 different letters of last names) * (2 area codes)
	
	int firstInit = listing.getFirstName()[0] - ALPHA_OFFSET;				// first-initial-of-first-name's alpha-numeric value
	int lastInit = listing.getLastName()[0] - ALPHA_OFFSET;					// last-initial-of-last-name's alpha-numeric value
	int thirdDigit_num = listing.getNumber()[2] - NUM_OFFSET;				// third digit of phone number
	int firstDigit_area = listing.getAreaCode()[1] - NUM_OFFSET;			// first digit of area code
	
	int lastInit_order = nameSequence[lastInit] - NUM_OFFSET;				// sequence according to first digit of last name
	int thirdDigit_num_order = numSequence[thirdDigit_num] - NUM_OFFSET;	// sequence according to third digit of phone number
	int firstDigit_area_order = areaSequence[firstDigit_area] - NUM_OFFSET;	// sequence according to first digit of area code
	//--------------------------------------------------------------------------------------------------------------------------------------------

	//-----------------------HASHING ALGORITHM--------------------------------------------------------------------------------------------
	int index = ( ((subBlock * firstInit) + (mainBlock * lastInit_order)) + (thirdDigit_num_order + firstDigit_area_order) ) % TABLE_SIZE;
	//------------------------------------------------------------------------------------------------------------------------------------

	return index;
}

/*
Hash3
	This hash function takes a listing object as a parameter, and returns an
	integer which represents the index of the hash table where the listing will
	be stored.

	The hash is determined by the following algorithm:

	(the sequence position of the first initial of the last name * 5148) +
	(the first initial of the first name * 198) +
	(the sequence position of the first digit of the area code * 99) +
	(the sequence position of the third digit of the phone number * 11) +
	(the sequence position of the sum of the last two digits of the phone number)

	The sequence position is determined by the STRING-LEGENDS, which emulate the sequence in which
	the information reads if the phonebook entries are sorted.

	The result is a hash which fills the table VERTICALLY based on the alpha-numeric value of the first and last names.
*/
int HashTable::Hash3(Listing listing)
{
	//------------------------STRING-LEGENDS--------------------------------------------------------------------------------------
	const string numSequence = "78-0123456";								// sequence for third digit of phone number
	const string sumSequence = "6-7-8-90:1-2-3-4-5";						// sequence for sum of last two digits of phone number
	 const string areaSequence = "--0-1";									// sequence used for first digit of area code
	 const string nameSequence = "01--2-3--4-5------67-----8";				// sequence used for first digit of last name
	//----------------------------------------------------------------------------------------------------------------------------

	//-----------------------HASHING-VARIABLE DEFINITIONS---------------------------------------------------------------------------------
	const int subBlock = 11;												// 11 numbers per 3rd digit of phone number
	const int mainBlock = 99;												// 99 numbers per area code
	const int firstNameBlock = 198;											// 198 numbers per first name
	const int lastNameBlock = 5148;											// 5148 numbers per last name

	int firstInit = listing.getFirstName()[0] - ALPHA_OFFSET;				// first-initial-of-first-name's alpha-numeric value
	int lastInit = listing.getLastName()[0] - ALPHA_OFFSET;					// first-initial-of-last-name's alpha-numeric value
	int thirdDigit_num = listing.getNumber()[2] - NUM_OFFSET;				// third digit of phone number
	int last2_num = (listing.getNumber()[6] - NUM_OFFSET) +					// sum of last two digits of phone number
					(listing.getNumber()[7] - NUM_OFFSET);					
	int firstDigit_area = listing.getAreaCode()[1] - NUM_OFFSET;			// first digit of area code

	int lastInit_order = nameSequence[lastInit] - NUM_OFFSET;				// sequence according to first digit of last name
	int thirdDigit_num_order = numSequence[thirdDigit_num] - NUM_OFFSET;	// sequence according to third digit of phone number
	int last2_sum_order = sumSequence[last2_num] - NUM_OFFSET;				// sequence according to sum of last two digits of phone number
	int firstDigit_area_order = areaSequence[firstDigit_area] - NUM_OFFSET;	// sequence according to first digit of area code
	//-------------------------------------------------------------------------------------------------------------------------------------
	
	//-----------------------HASHING ALGORITHM-------------------------------------------------------------------------------------------------------------------------------------------
	int index = ( (lastInit_order * lastNameBlock) + (firstInit * firstNameBlock) + (firstDigit_area_order * mainBlock) + (thirdDigit_num_order * subBlock) + (last2_sum_order) ) % 4177;
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	return index;
}

/*
FillQueue
	This takes a txt file path as a parameter and fills the class queue with Listing objects
	derived from the information in the txt file. The function also displays the time elapsed,
	and the amount of listings in the queue. 
*/
void HashTable::FillQueue(string fileName)
{
	ifstream infile(fileName);
	string line;
	string last;
	string first;
	string areaCode;
	string number;
	clock_t t1, t2;

	cout << "Reading file and adding listings to queue...";
	
	//-----Section parses data from the text file and creates a Listing object------------
	t1 = clock();
	for (int i = 0; i < LISTINGS; i++)
	{
		getline(infile, line);
		stringstream lineStream(line);

		lineStream >> last;
		last.pop_back();

		lineStream >> first;

		lineStream >> areaCode;

		lineStream >> number;

		Listing listing(first, last, areaCode, number);
		
		processQueue.push(listing);				//Adds Listing object to the process queue
	}
	t2 = clock();
	double elapsed = double(t2 - t1) / 1000;	//Time elapsed (in seconds)
	//------------------------------------------------------------------------------------

	cout << "complete" << endl;
	cout << "Queue was filled in " << elapsed << " seconds." << endl;
	cout << "There are " << processQueue.size() << " listings in the queue." << endl << endl;
}

/*
BuildTable
	This function takes a txt file path as a parameter and fills the class hash table
	with the Listing objects from the txt file via helper functions.
*/
void HashTable::BuildTable(string fileName)
{
	FillQueue(fileName);
	ProcessQueue();
}

/*
ProcessQueue
	This function processes all of the listings in the queue one-by-one, and stores them
	in the hash table based on the called hash function.

	*On line 254 below, the index of each listing is determined by which hash function
	is called. This program is set to "Hash3", which is the most efficient hash I found. 

	*If you would like to see the other hashes run, change "Hash3" to "Hash1" or "Hash2".
*/
void HashTable::ProcessQueue()
{
	cout << "Filling table with listings...";
	int index;
	clock_t t1, t2;

	//-----Section hashes each Listing in the queue and stores in hash table-
	t1 = clock();
	for (int i = 0; i < LISTINGS; i++)
	{
		Listing listing = processQueue.front();
		processQueue.pop();
		
		index = Hash3(listing);// <---------Change hash function here if desired 
		table[index].push_back(listing);
	}
	t2 = clock();
	double elapsed = double(t2 - t1) / 1000;
	//-----------------------------------------------------------------------

	cout << "complete." << endl;
	cout << "Table was filled in " << elapsed << " seconds." << endl << endl;
	DisplayChainLengths();
}

/*
DisplayChainLengths
	This function displays the lengths of each chain
	of the has table. 
*/
void HashTable::DisplayChainLengths()
{
	cout << "Counting chain lengths...";
	vector<int> chainLengths;
	vector<int> counts;
	bool contains = false;

	//--Section iterates through table and counts chain lengths-
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		int temp = table[i].size();
		if (chainLengths.size() != 0)
		{
			for (int i = 0; i < chainLengths.size(); i++)
			{
				if (temp == chainLengths[i])
				{
					contains = true;
					counts[i]++;
				}
			}
			if (contains == false)
			{
				chainLengths.push_back(temp);
				counts.push_back(1);
			}
		}
		else
		{
			chainLengths.push_back(temp);
			counts.push_back(1);
		}
		contains = false;
	}
	//----------------------------------------------------------

	cout << "complete." << endl;

	//-----Section displays chain lengths-----------------------------------------------------
	if (chainLengths.size() != 0)
	{
		for (int i = 0; i < chainLengths.size(); i++)
		{
			cout << "Total chains of length " << chainLengths[i] << ": " << counts[i] << endl;
		}
	}
	cout << endl;
	//----------------------------------------------------------------------------------------
}

/*
DisplayTable
	This function displays the contents of the table.
	The listings of the table are represented by the first initials
	of the person's first and last name, so the entire listings are not displayed.
	The purpose of this function is to provide a broad idea of how the listings are
	being distributed to the table. 

	Each chain's length is displayed at the end of the chain.
*/
void HashTable::DisplayTable()
{
	cout << "HASH TABLE CONTENTS:" << endl;
	int count = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		cout << "Index[" << i << "]: ";
		for (int j = 0; j < table[i].size(); j++)
		{
			cout << table[i][j].getLastName()[0] << table[i][j].getFirstName()[0] << " ";
			count++;
		}
		cout << "(chain length: " << table[i].size() << ")" << endl;
	}
}
