#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"
#include<windows.h>



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
bool Redundant(List*, LibStudent);
int JulianDate(LibStudent, Date);


int main() {
	bool decision = true;
	List list;
	do {
		system("cls");
		int number = menu();
		switch (number){
		case(1):{
			if (ReadFile("student.txt", &list)) {
				cout << "Congrats..successfully read the file..." << endl;
			}
			system("pause");
			break;
		}
		case(2):{
			char id[10];
			cout << "please input the ID of student >>>";
			cin.getline(id, 10);
			//DeleteRecord(list, id);
			break;
		}
		case(3):{
			bool decision = true;
			char id[10];
			do {
				cout << "Please input the ID of student >>>";
				cin.getline(id, 10);
				if (strlen(id) >= 10 || strlen(id) ==0)
				{
					cout << "please ensure the id within the range" << endl;
					decision = false;
				}
			} while (decision);
			LibStudent FoundStudent;
			if (SearchStudent(&list, &id[0], FoundStudent))
			{
				FoundStudent.print(cout);
			}
			break;
		}
		case(4):{

			break;
		}
		case(5):{

			break;
		}
		case(6):{

			break;
		}
		case(7):{

			break;
		}
		case(8):{
			bool displayWarnedStudent(List*, List*, List*);

			break;
		}
		case(9):{
			decision = false;
			break;
		}
		default:{
			cout << "\tInvalid input found in the system..." << endl;
			Sleep(1000);
			break;
		}
		}
	} while (decision);
	system("pause");
	return 0;
}

int menu(){
	string selection, decision;
	int record;
	cout << "\n\n\n"<<string( 50, '=') << endl;
	cout << "\t1. Read file." << endl;
	cout << "\t2. Delete record." << endl;
	cout << "\t3. Search student." << endl;
	cout << "\t4. Insert book." << endl;
	cout << "\t5. Display output" << endl;
	cout << "\t6. Compute and Display Statistics" << endl;
	cout << "\t7. Student with Same Book" << endl;
	cout << "\t8. Display Warned Student" << endl;
	cout << "\t9. Exit." << endl;
	cout << string(50, '=') << endl;
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

bool ReadFile(string filename, List* list){
	int index = 0,count=0;
	string value;
	LibStudent NewStudent;
	ifstream StudRecord;
	StudRecord.open(filename);
	if (StudRecord.fail()){
		cout << "unsuccessfully read the record" << endl;
		return false;
	}
	else {
		while (!StudRecord.eof()) {
			index = 0;
			do {
				StudRecord >> value;
				if (value == "=") {
					if (index == 0) {
						StudRecord >> NewStudent.id;
					}
					else if (index == 1) {
						StudRecord.ignore();
						StudRecord.getline(NewStudent.name, 30);
					}
					else if (index == 2) {
						StudRecord >> NewStudent.course;
					}
					else if (index == 3) {
						StudRecord >> NewStudent.phone_no;
						if (!Redundant(list, NewStudent)) {
							list->insert(NewStudent);
							count++;
						}
					}
					index++;
				}
			} while (index != 4);
		}
	}
	return true;
}
bool Redundant(List* list, LibStudent NewStudent) {
	LibStudent TempStudent;
	for (int i = 1; i <= list->size(); i++) {
		if (list->get(i, TempStudent)) {
			if (TempStudent.compareName2(NewStudent))  //compare with exist linked list
				return true;
		}
	}
	return false;
}

bool DeleteRecord(List* list, char* id) {
	cout << "id found" << endl;
	return true;
}

//type1 >2 books (overdue>=10 days)
//type2 total fine>50 , all books overdues

bool displayWarnedStudent(List* list, List* type1, List* type2) {
	if (list->empty()) {
		cout << "no student found in the system" << endl;
		return false;
	}
	Date Current;
	Current.day = 29;
	Current.month = 3;
	Current.year = 2020;
	//type1//int OverDueBook > 2;//int OverDueDate >= 10;
	//type2//double TotalFine = 50,all book due;
	struct LibStudent TempStudent;
	Node* TempPtr = list->head;
	while (TempPtr != NULL) {
		int NoOfBook = 0;
		TempStudent = TempPtr->item;
		for (int i = 0; i < 15; i++) {
			if (TempStudent.book[i].title == NULL) {
				break;
			}
			else if (TempStudent.book[i].fine != 0 && JulianDate(TempStudent, Current) >= 10) {
				NoOfBook++;
			}
		}
		if (NoOfBook > 2) {
			type1->insert(TempStudent);
		}
		if (TempStudent.total_fine > 50 && NoOfBook == TempStudent.totalbook) {
			type2->insert(TempStudent);
		}
		TempPtr = TempPtr->next;
	}
	int StudNum;
	if (!type1->empty()) {
		cout << string(80, '=') << endl;
		cout << "Type 1 Warning List" << endl;
		cout << string(80, '=') << endl;
		Node* TempPtr = type1->head;
		StudNum = 1;
		while (TempPtr != NULL) {
			int BookNum = 0;
			cout << "<<<  Student" << StudNum++ << " >>>" << endl;
			cout << string(80, '=') << endl;
			cout << "Overdue Book List(s) " << endl;
			for (int i = 0; i < 15; i++) {
				if (TempPtr->item.book[i].title == NULL) {
					break;
				}
				else if (TempPtr->item.book[i].fine > 0) {
					cout << "\nBook " << ++BookNum << endl;
					cout << string(80, '-') << endl;
					TempPtr->item.book[i].print(cout);
					cout << string(80, '-') << endl;
				}
			}
			cout << string(80, '*') << endl;
			TempPtr = TempPtr->next;
		}
	}
	if (!type2->empty()) {
		Node* TempPtr2 = type2->head;
		StudNum = 1;
		cout << "\n\nType 2 Warning List\n\n";
		while (TempPtr2 != NULL) {
			int BookNum = 0;
			cout << "<<<  Student" << StudNum++ << " >>>";
			TempPtr2->item.print(cout);
			cout << endl << string(80, '=') << endl;
			cout << "\n\nOverdue Book List(s) " << endl;
			for (int i = 0; i < 15; i++) {
				if (TempPtr->item.book[i].title == NULL) {
					break;
				}
				else if (TempPtr2->item.book[i].fine > 0) {
					cout << string(80, '-') << endl;
					cout << "<<<< Book " << ++BookNum << ">>>\n";
					cout << string(80, '-') << endl;
					TempPtr2->item.book[i].print(cout);
					cout << string(80, '-') << endl;
				}
			}
			cout << string(80, '*') << endl;
			TempPtr2 = TempPtr2->next;
		}
		return true;
	}

}
int JulianDate(LibStudent student, Date date) {
	int ReturnValue;
	double dueday = 0, currentday = 0;
	for (int i = 1; i < 12; i++) {
		if (i < student.book->due.month)
			dueday += 30;
		else if (i < date.month)
			currentday += 30;
	}
	dueday = student.book->due.year * 365.25 + student.book->due.day;
	currentday = date.year * 365.25 + date.day;
	ReturnValue = int(currentday - dueday);
	return ReturnValue;
}
