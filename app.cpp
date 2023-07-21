#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"


using namespace std;

bool ReadFile(string, List *);
bool DeleteRecord(List *, char *);
bool Display(List, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, char *id, LibStudent &);
bool computeAndDisplayStatistics(List *);
bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
int menu();


int main() {
	bool decision = true,result;
	int selection;
	string filename;
	do {
		selection = menu();
		switch (selection)
		{
		case(1):
		{
			filename = "student.txt";
			result = ReadFile(filename, List);
		}
		case(2):
		{
		}
		case(3):
		{
		}
		case(4):
		{
		}
		case(5):
		{
		}
		case(6):
		{
		}
		case(7):
		{
		}
		case(8):
		{
		}
		case(9):
		{
			decision = false;
		}
		default:
		{
			cout << "\tInvalid input found in the system..." << endl;
		}
		}
			
	} while (decision);
	

	cout << "\n\n";
	system("pause");
	return 0;
}

int menu()
{
	string selection, decision;
	int record;
	cout << "\t1. Read file." << endl;
	cout << "\t2. Delete record." << endl;
	cout << "\t3. Search student." << endl;
	cout << "\t4. Insert book." << endl;
	cout << "\t5. Display output" << endl;
	cout << "\t6. Compute and Display Statistics" << endl;
	cout << "\t7. Student with Same Book" << endl;
	cout << "\t8. Display Warned Student" << endl;
	cout << "\t9. Exit." << endl;
	cout << "\tEnter your choice : ";
	getline(cin, selection);
	record = 0;
	for (int i = 0; i < selection.size(); i++){
		if (isdigit(selection[i]))
			record++;
	}
	if (record == selection.size())
		return stoi(selection);
	return NULL;
}

bool ReadFile(string, List*)
{

}


