/*
"Tavi" Ioane Tenari
2/21/17
Program 3

Lab3 - Driver

main() is the driver program of the assignment.
It details the information associated with
the hashing of the provided txt file "phonebook.txt"
and displays the contents of the table.

*/
#include "HashTable.h"
using namespace std;

int main()
{
	HashTable hTable("phonebook.txt");
	hTable.DisplayTable();
	system("pause");
	return 0;
}

