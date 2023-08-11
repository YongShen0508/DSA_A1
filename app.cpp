#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"
#include<windows.h>
#include <iomanip>

using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();
bool Redundant(List*, LibStudent);
int JulianDate(LibStudent, Date);
int JulianDate(LibBook, Date);
void splitDel(string, Date*);

int main() {
	bool decision = true;
	List* StuList = new List();
	string stuFile, bookFile;
	do {
		system("cls");
		switch (menu()) {
		case(1): {
			system("cls");
			cout << "\n\n\n" << endl;
			cout << string(50, '=') << endl;
			cout << "||\t\tRead File\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			if (!ReadFile("student.txt", StuList)) {
				cout << "\033[1;31m Unable to read the file... \033[0m" << endl;
			}
			system("pause");
			break;
		}
		case(2): {
			system("cls");
			cout << "\n\n\n" << endl;
			cout << string(50, '=') << endl;
			cout << "||\t\tDelete Record\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			bool decision = true;
			char id[10];
			do {
				cout << "\033[0;34m Please input the Student ID <E>xit >>>";
				cin.getline(id, 10);
				cout << "\033[0m";
				if (strlen(id) == 7)
					decision = false;
				else if (strcmp(id, "E") == 0 || strcmp(id, "e") == 0) {
					decision = false;
					cout << "\033[1;31m Exit to main menu \033[0m" << endl;
					Sleep(1500);
				}
				else {
					cout << "\033[1;31m Please input a valid Student ID \033[0m" << endl;
					Sleep(1500);
				}
			} while (decision);
			if (strcmp(id, "E") != 0) {
				LibStudent FoundStudent;
				if (!DeleteRecord(StuList, &id[0])) {
					cout << "\033[1;31m Unable to find the student... \033[0m" << endl;
				}
				else
					cout << "\033[1;33m Student successfully deleted from system... \033[0m" << endl;
			}
			system("pause");
			break;
		}
		case(3): {
			system("cls");
			cout << "\n\n\n" << endl;
			cout << string(50, '=') << endl;
			cout << "||\t\tSearch Record\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			bool decision = true;
			char id[10];
			do {
				cout << "\033[0;34m Please input the Student ID <E>xit >>>";
				cin.getline(id, 10);
				cout << "\033[0m";
				if (strlen(id) == 7)
					decision = false;
				else if (strcmp(id, "E") == 0 || strcmp(id, "e") == 0) {
					decision = false;
					cout << "\033[1;31m Exit to main menu \033[0m" << endl;
					Sleep(1500);
				}
				else {
					cout << "\033[1;31m Please input a valid Student ID \033[0m" << endl;
					Sleep(1500);
				}
			} while (decision);
			if (strcmp(id, "E") != 0) {
				LibStudent FoundStudent;
				if (SearchStudent(StuList, &id[0], FoundStudent)) {
					cout << string(50, '=') << endl;
					cout << "||\t\tStudent Information\t\t||" << endl;
					cout << string(50, '=') << endl;
					FoundStudent.print(cout);
					cout << "\n\n";
				}
				else {
					cout << "\033[1;33m Student not found inside the system... \033[0m" << endl;

				}
			}
			system("pause");
			break;
		}
		case(4): {
			system("cls");
			cout << "\n\n\n" << endl;
			cout << string(50, '=') << endl;
			cout << "||\t\tInsert Book\t\t\t||" << endl;
			cout << string(50, '=') << endl;
			if (!InsertBook("book.txt", StuList))
				cout << "\033[1;31m Unable to insert book...\033[0m" << endl;
			system("pause");
			break;
		}
		case(5): {
			int Fchoice, Schoice;
			int source, detail;
			system("cls");
			bool validInput = false;
			do {
				cout << "\n\n\n" << endl;
				cout << string(70, '=') << endl;
				cout << "||                         Display Output                           ||" << endl;
				cout << "======================================================================" << endl;
				cout << "||                                                                  ||" << endl;
				cout << "||        Where would you like the output to be displayed?          ||" << endl;
				cout << "||                                                                  ||" << endl;
				cout << "======================================================================" << endl;

				cout << "\t ===================             ===================" << endl;
				cout << "\t ||               ||             ||               ||" << endl;
				cout << "\t ||    1.FILE     ||             ||   2.SCREEN    ||" << endl;
				cout << "\t ||               ||             ||               ||" << endl;
				cout << "\t ===================             ===================" << endl;
				cout << endl;

				cout << "\033[0;34m Please Enter Your Choice (1/2) :";
				cin >> Fchoice;
				cout << "\033[0m";
				if (Fchoice == 1)
					source = 1;
				else if (Fchoice == 2)
					source = 2;

				cout << "======================================================================" << endl;
				cout << "||                                                                  ||" << endl;
				cout << "||                   !~ Information Required ~!                     ||" << endl;
				cout << "||                                                                  ||" << endl;
				cout << "||                 1. Student Info and Book Info                    ||" << endl;
				cout << "||                 2. Student Info                                  ||" << endl;
				cout << "||                                                                  ||" << endl;
				cout << "======================================================================" << endl;
				cout << endl;
				cout << "\033[0;34m Please Enter Your Choice (1/2): ";
				cin >> Schoice;
				cout << "\033[0m";
				if (Schoice == 1)
					detail = 1;
				else if (Schoice == 2)
					detail = 2;

				if (Fchoice < 1 || Fchoice > 2 || Schoice < 1 || Schoice > 2) {
					cout << "\033[1;31m Invalid Input found! Please try again!\033[0m" << endl;
					validInput = false;
				}
			} while (validInput == true);
			Display(StuList, Fchoice, Schoice);
			cin.ignore();
			system("pause");
			break;
		}
		case(6): {
			system("cls");
			cout << "\n\n\n" << endl;
			cout << string(115, '=') << endl;
			cout << "||\t\t\t\t\t\t Compute Statistics \t\t\t\t\t\t " "||" << endl;
			cout << string(115, '=') << endl;
			if (!computeAndDisplayStatistics(StuList)) {
				cout << "\033[1;31m Fail to compute statistics.\033[0m" << endl;
				Sleep(500);
			}
			system("pause");
			break;
		}
		case(7): {
			system("cls");
			cout << "\n\n\n" << endl;
			cout << string(58, '=') << endl;
			cout << "||\t\t    Student With Same Book(s)  \t\t||" << endl;
			cout << string(58, '=') << endl;
			bool decision = true;
			char CallNum[30];
			do {
				cout << "\033[0;34m Please input the Call Number of Book <E>xit >>>";
				cin.getline(CallNum, 30);
				cout << "\033[0m";
				if (strlen(CallNum) < 20)
					decision = false;
				else if (strcmp(CallNum, "E") == 0) {
					decision = false;
					cout << "\033[1;31m Exit to main menu \033[0m" << endl;
					Sleep(1500);
				}
				else {
					cout << "\033[1;31m Please input a valid Call Num of book \033[0m" << endl;
					Sleep(1500);
				}
			} while (decision);
			if (strcmp(CallNum, "E") != 0) {
				LibStudent FoundStudent;
				if (!printStuWithSameBook(StuList, CallNum)) {
					cout << "\033[1;31m Unable access to the file... \033[0m" << endl;
				}
			}
			system("pause");
			break;
		}
		case(8): {
			List* WarnedList1 = new List();
			List* WarnedList2 = new List();
			system("cls");
			cout << "\n\n\n" << endl;
			cout << string(82, '=') << endl;
			cout << "||\t\t\t\t Warned Student  \t\t\t\t||" << endl;
			cout << string(82, '=') << endl;
			if (!displayWarnedStudent(StuList, WarnedList1, WarnedList2)) {
				cout << "\033[1;31m Unable to display the list..\033[0m" << endl;
				Sleep(500);
			}
			system("pause");
			break;
		}
		case(9): {
			decision = false;
			break;
		}
		default: {
			cout << "\033[1;31m Invalid input found in the system...\033[0m" << endl;
			Sleep(1000);
			break;
		}
		}
	} while (decision);
	system("pause");
	return 0;
}

int menu() {
	string selection, decision;
	int record;
	cout << "\n\n\n" << string(50, '=') << endl;
	cout << "||\t\t\t\t\t\t||" << endl;
	cout << "||\t\t   MAIN MENU        \t\t||" << endl;
	cout << "||\t\t\t\t\t\t||" << endl;
	cout << string(50, '=') << endl;
	cout << "||\t\t\t\t\t\t||" << endl;
	cout << "||\t\033[1;36m1. Read file.\033[0m\t\t\t\t||" << endl;
	cout << "||\t\033[1;36m2. Delete record.\033[0m\t\t\t||" << endl;
	cout << "||\t\033[1;36m3. Search student.\033[0m\t\t\t||" << endl;
	cout << "||\t\033[1;36m4. Insert book.\033[0m\t\t\t\t||" << endl;
	cout << "||\t\033[1;36m5. Display output\033[0m\t\t\t||" << endl;
	cout << "||\t\033[1;36m6. Compute and Display Statistics\033[0m\t||" << endl;
	cout << "||\t\033[1;36m7. Student with Same Book\033[0m\t\t||" << endl;
	cout << "||\t\033[1;36m8. Display Warned Student\033[0m\t\t||" << endl;
	cout << "||\t\033[1;36m9. Exit.\033[0m\t\t\t\t||" << endl;
	cout << "||\t\t\t\t\t\t||" << endl;
	cout << string(50, '=') << endl;
	cin.clear();
	cout << "\033[0;34mEnter your choice : ";
	getline(cin, selection);
	cout << "\033[0m";
	record = 0;
	for (int i = 0; i < selection.size(); i++) {
		if (isdigit(selection[i]))
			record++;
	}
	if (record == selection.size())
		return stoi(selection);
	return NULL;
}

bool ReadFile(string filename, List* list) {
	ifstream StudRecord;
	StudRecord.open(filename);
	int index = 0, numstud = 0;
	string value;
	LibStudent NewStudent;
	if (StudRecord.fail())
		return false;
	else {
		while (!StudRecord.eof()) {
			index = 0;
			do {
				StudRecord >> value;
				if (value == "=") {//if found = sign
					if (index == 0) {
						StudRecord >> NewStudent.id;
					}
					else if (index == 1) {
						StudRecord.ignore();
						StudRecord.getline(NewStudent.name, 40);
					}
					else if (index == 2) {
						StudRecord >> NewStudent.course;
					}
					else if (index == 3) {
						StudRecord >> NewStudent.phone_no;
						if (!Redundant(list, NewStudent)) {//no student found in linked list
							list->insert(NewStudent);
							numstud++;
						}
					}
					index++;
				}
			} while (index != 4);
		}
		StudRecord.close();
		cout << "\n\t\tLoading...\n" << endl;
		Sleep(3000);
		cout << "\033[0;33m" << numstud << " record(s) have been successfully read... \033[0m" << endl;
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
	if (list->empty())//empty list
		return false;
	Node* cur = list->head;
	for (int i = 1; i <= list->size(); i++) //find the student
	{
		if (strcmp(cur->item.id, id) == 0)//match 
		{
			cout << string(50, '=') << endl;
			cout << "||\t\tStudent Information\t\t||" << endl;
			cout << string(50, '=') << endl;
			cur->item.print(cout);
			cout << endl;
			list->remove(i);
			return true;
		}
		cur = cur->next;
	}
	return false;  // if student not found
}
bool SearchStudent(List* list, char* id, LibStudent& stu) {
	if (list->empty()) {
		cout << "\033[1;31m Unable to find the student...\033[0m" << endl;
		Sleep(2000);
		return false;
	}
	Node* TempPtr = list->head;
	for (int i = 0; i < list->size(); i++) {
		if (strcmp(TempPtr->item.id, id) == 0) {
			cout << "\033[0;33m Successfully search the student...\033[0m \n" << endl;
			stu = TempPtr->item;
			return true;
		}
		TempPtr = TempPtr->next;
	}
	return false;
}

bool InsertBook(string filename, List* list) {
	if (list->empty()) {
		cout << "\033[1;31m Cannot find the book inside the record...\033[0m" << endl;
		return false;
	}
	char stuId[10];
	string author, title, ISBN, publisher, callNum, dateborrow, datedue;
	double fine;
	LibStudent tempStud;
	ifstream bookfile;
	bookfile.open(filename);
	if (bookfile.fail()) {
		cout << "\033[1;31m Unable to open the file...\033[0m" << endl;
		return false;
	}
	else {
		string text;
		while (bookfile >> text) {
			LibBook tempBook;
			//update fine=0 for every book
			fine = 0;
			//track position of book
			int count = 1;
			//read every information from book.txt file
			strncpy(stuId, &text[0], 9);
			stuId[9] = 0;
			bookfile >> author;
			bookfile >> tempBook.title;
			bookfile >> tempBook.publisher;
			bookfile >> tempBook.ISBN;
			bookfile >> tempBook.yearPublished;
			bookfile >> tempBook.callNum;
			bookfile >> dateborrow;
			bookfile >> datedue;
			//split '/' from author 
			int start = 0, end = 0, authorNum = 0;
			string Splitauthor;  //store author name after split '/'
			while (end != author.length()) {
				if (author[end] == '/') {
					Splitauthor = author.substr(start, end - start);
					tempBook.author[authorNum] = new char[50];  //allocate new memory for author[authorNum]
					strcpy(tempBook.author[authorNum], &Splitauthor[0]);
					start = end + 1;
					authorNum++;
				}
				else if (end == (author.length() - 1)) {  //reach to the end of element in anthor
					Splitauthor = author.substr(start, (end + 1) - start);
					tempBook.author[authorNum] = new char[50];
					strcpy(tempBook.author[authorNum], &Splitauthor[0]);
					authorNum++;
				}
				end++;
			}
			//Current Date= "29/3/2020";
			Date BorrowDate;
			Date DueDate;
			Date CurrentDate;
			CurrentDate.day = 29;
			CurrentDate.month = 3;
			CurrentDate.year = 2020;
			splitDel(dateborrow, &BorrowDate);
			splitDel(datedue, &DueDate);

			tempBook.borrow.day = BorrowDate.day;
			tempBook.borrow.month = BorrowDate.month;
			tempBook.borrow.year = BorrowDate.year;
			tempBook.due.day = DueDate.day;
			tempBook.due.month = DueDate.month;
			tempBook.due.year = DueDate.year;
			int numdue = JulianDate(tempBook, CurrentDate);
			if (numdue > 0) {
				fine = 0.5 * numdue;
			}
			tempBook.fine = fine;
			Node* TempPtr = list->head;
			while (TempPtr != NULL) {   //find a student
				if (strcmp(TempPtr->item.id, stuId) == 0) {
					bool redundant = false;
					for (int i = 0; i < 15; i++) {//max borrow book = 15
						if (strlen(TempPtr->item.book[i].title) == 1) { //detect empty book
							break;
						}
						else {
							if (strcmp(TempPtr->item.book[i].title, tempBook.title) == 0) {
								redundant = true;
								break;
							}
						}
					}
					if (!redundant) {
						TempPtr->item.totalbook++;
						TempPtr->item.book[TempPtr->item.totalbook - 1] = tempBook;
						TempPtr->item.calculateTotalFine();
					}
				}
				TempPtr = TempPtr->next;
			}
		}
		bookfile.close();
	}
	cout << "\n\t\tLoading...\n" << endl;
	Sleep(3000);
	cout << "\033[0;33m Book inserted successfully to student list. \033[0m \n";
	return true;
}
void splitDel(string date, Date* StructDate) {
	int begin = 0, end = 0;
	bool decision = false;
	//10/5/2022
	for (int j = 0; j < date.length(); j++) {
		if (date[j] == '/' && !decision) {
			StructDate->day = stoi(date.substr(begin, j));
			begin = j + 1;
			decision = true;
		}
		else if (date[j] == '/' && decision) {
			StructDate->month = stoi(date.substr(begin, j));
			StructDate->year = stoi(date.substr(++j, date.length() - 1));
		}
	}
}

bool Display(List* list, int source, int detail) {
	// Special Case
	if (list->empty()) {
		cout << "\033[1;31mOops! The student list is EMPTY.\033[0m" << endl;
		return false;
	}
	// Check if the input ranges are within [1,2]
	if (source < 1 || source > 2 || detail < 1 || detail > 2) {
		return false;
	}
	// Normal Case
	int stuNum = 1;
	ofstream file;
	ostream* output;
	LibBook bookInfo;
	Node* cur = list->head;
	// Display on File
	if (source == 1) {
		file.open("Output.txt");
		output = &file;
	}
	// Display on Screen
	else {
		output = &cout;
	}
	if (detail == 1) {
		// Display student info and book info
		while (cur != NULL) {
			*output << "--------------------" << endl;
			*output << "Student " << stuNum << endl;
			*output << "--------------------";
			cur->item.print(*output);
			// Loop through the borrowed books
			for (int i = 0; i < cur->item.totalbook; i++) {
				bookInfo = cur->item.book[i];
				*output << endl;
				*output << "< Book " << i + 1 << " >" << endl << endl;
				*output << "Title: " << bookInfo.title << endl;
				*output << "Author(s): ";
				//	Considering multiple authors
				int counter = 0;
				while (bookInfo.author[counter] != NULL) {
					*output << bookInfo.author[counter];
					if (bookInfo.author[counter + 1] != NULL)
						*output << ", ";
					counter++;
				}
				*output << endl;
				*output << "Publisher: " << bookInfo.publisher << endl;
				*output << "Year Published: " << bookInfo.yearPublished << endl;
				*output << "ISBN: " << bookInfo.ISBN << endl;
				*output << "Call Number: " << bookInfo.callNum << endl;
				*output << "Borrow Date: " << bookInfo.borrow.day << "/" << bookInfo.borrow.month << "/" << bookInfo.borrow.year << endl;
				*output << "Due Date: " << bookInfo.due.day << "/" << bookInfo.due.month << "/" << bookInfo.due.year << endl;
				*output << "Fine: RM " << bookInfo.fine << endl;

			}
			*output << "*************************************************************************" << endl;
			cur = cur->next;
			stuNum++;
		}
	}
	else
	{	// Display student info 
		stuNum = 1;
		while (cur != NULL) {
			*output << endl << endl;
			*output << "--------------------" << endl;
			*output << "STUDENT " << stuNum << endl;
			*output << "--------------------";
			cur->item.print(*output);
			*output << "*************************************************************************" << endl;
			cur = cur->next;
			stuNum++;
		}
	}
	file.close();

	if (source == 1)
	{
		cout << "\033[0;33m" << " Information has been successfully written to 'Output.txt'. \033[0m" << endl;
	}

	return true;
}
bool computeAndDisplayStatistics(List* list) {
	// Check if List is empty
	if (list->empty()) {
		cout << "\033[1;31m Oops! The student list is EMPTY.\033[0m" << endl;
		return false;
	}
	else {
		// Initialize variables
		char course[10][3];
		int num_course = 0;
		int num_stu = 0;
		int num_books = 0;
		int overdue_books = 0;
		double fine = 0;
		bool repeat = false;

		Node* cur = list->head;

		//	All unique courses are recorded into array
		while (cur != NULL) {
			repeat = false;
			// Check if the course is already in the array
			for (int i = 0; i < 10; i++) {
				if (strcmp(course[i], cur->item.course) == 0) {
					repeat = true;
					break;
				}
			}
			// If the course is not repeated, add it into array
			if (repeat == false) {
				strcpy(course[num_course], cur->item.course);
				num_course++;
			}
			cur = cur->next;
		}
		// Display header
		cout << left << setw(15) << "Course";
		cout << setw(25) << "Number of Students";
		cout << setw(25) << "Total Books Borrowed";
		cout << setw(25) << "Total Overdue Books";
		cout << setw(25) << "Total Overdue Fine(RM)" << endl;
		for (int i = 0; i < num_course; i++) {
			cur = list->head;
			// Reinitialize to 0
			int num_stu = 0;
			int num_books = 0;
			int overdue_books = 0;
			double fine = 0;
			while (cur != NULL) {
				if (strcmp(cur->item.course, course[i]) == 0) {   //	Increase if item.course is same as current array element
					num_stu++;
					num_books += cur->item.totalbook;
					fine += cur->item.total_fine;

					for (int j = 0; j < cur->item.totalbook; j++) { // Check if a book is overdue
						if (cur->item.book[j].fine > 0) {
							overdue_books++;
						}
					}
				}
				cur = cur->next;
			}
			//	Display Statistic
			cout << setprecision(2) << fixed;
			cout << left << setw(20) << course[i];
			cout << "\t" << setw(20) << num_stu;
			cout << "\t" << setw(20) << num_books;
			cout << "\t" << setw(20) << overdue_books;
			cout << "\t" << setw(20) << fine << endl;

		}
		cout << endl << endl;
		return true;
	}
}

bool printStuWithSameBook(List* list, char* callNum) {
	if (list->empty())
		return false;
	int TotalNum = 0;
	List StudWithSameBook;
	LibStudent StudInfo;
	Node* CurPtr = list->head;
	while (CurPtr != NULL) {
		StudInfo = CurPtr->item;
		for (int i = 0; i < 15; i++) {
			if (StudInfo.book[i].callNum == NULL) {
				break;
			}
			else {
				if (strcmp(StudInfo.book[i].callNum, callNum) == 0) {
					TotalNum++;
					StudWithSameBook.insert(StudInfo);
					break;
				}
			}
		}
		CurPtr = CurPtr->next;
	}
	system("cls");
	cout << string(58, '=') << endl;
	cout << "||\t\t    Student With Same Book(s)  \t\t||" << endl;
	cout << string(58, '=') << endl;
	cout << "\n\n\033[0;33m Call Number of Book : " << callNum << "\033[0m" << endl;
	cout << "\033[0;33m There are " << TotalNum << " student(s) borrow this book\033[0m\n\n";
	int NumOfStudent = 0;
	if (TotalNum > 0) {
		Node* TempPtr = StudWithSameBook.head;
		cout << string(58, '=') << endl;
		while (TempPtr != NULL) {  	//print student info that borrow the same book
			cout << string(58, '=') << endl;
			cout << "\t\tStudent" << ++NumOfStudent << endl;
			cout << string(58, '=') << endl;
			cout << "Student Id : " << TempPtr->item.id << endl;
			cout << "Name : " << TempPtr->item.name << endl;
			cout << "Course : " << TempPtr->item.course << endl;
			cout << "Phone Number : " << TempPtr->item.phone_no << endl;
			cout << "Borrow Date : ";
			TempPtr->item.book[0].borrow.print(cout);
			cout << "\nDue Date : ";
			TempPtr->item.book[0].due.print(cout);
			cout << "\n\n";
			TempPtr = TempPtr->next;
		}
	}
	cout << string(60, '=') << endl;
	return true;
}
//type1 >2 books (overdue>=10 days)
//type2 total fine>50 , all books overdues
bool displayWarnedStudent(List* list, List* type1, List* type2) {
	if (list->empty()) {
		cout << "\033[1;31m No student found inside the record...\033[0m" << endl;
		return false;
	}
	Date Current;
	Current.day = 29;
	Current.month = 3;
	Current.year = 2020;
	//type1//int OverDueBook > 2;//int OverDueDate >= 10;
	//type2//double TotalFine = 50,all book due;
	LibStudent TempStudent;
	Node* TempPtr = list->head;
	bool decision = false;
	while (TempPtr != NULL) {
		int NoOfBook = 0;
		TempStudent = TempPtr->item;
		for (int i = 0; i < 15; i++) {
			if (strcmp(TempStudent.book[i].title, " ") == 0) {
				if (NoOfBook == i)
					decision = true;
				break;
			}
			else if (JulianDate(TempStudent.book[i], Current) >= 10) {
				NoOfBook++;
			}
		}
		if (NoOfBook > 2) {
			type1->insert(TempStudent);
		}
		if (TempStudent.total_fine > 50 && TempStudent.totalbook == NoOfBook) {
			type2->insert(TempStudent);
		}
		TempPtr = TempPtr->next;
	}
	int StudNum;
	if (type1->empty() && type2->empty()) {
		cout << "\033[1;31m No student inside the warning list...\033[0m" << endl;
		return true;
	}
	if (!type1->empty()) { //student in type1 list
		cout << string(80, '=') << endl;
		cout << "\t\t\t\033[1;31m Type 1 Warning List\033[0m" << endl;
		cout << string(80, '=') << endl;
		Node* TempPtr = type1->head;
		StudNum = 1;
		while (TempPtr != NULL) {
			int BookNum = 0;
			cout << "<<<  Student" << StudNum++ << " >>>" << endl;
			TempPtr->item.print(cout);
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
	if (!type2->empty()) {//student in type2 list
		Node* TempPtr2 = type2->head;
		StudNum = 1;
		cout << "\t\t\t\033[1;31m Type 2 Warning List\033[0m" << endl;
		while (TempPtr2 != NULL) {
			int BookNum = 0;
			cout << "<<<  Student" << StudNum++ << " >>>";
			TempPtr2->item.print(cout);
			cout << endl << string(80, '=') << endl;
			cout << "\n\nOverdue Book List(s) " << endl;
			for (int i = 0; i < 15; i++) {  //print overdue book
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
	}
	return true;
}

//Function overloading calculate Julian Date
int JulianDate(LibStudent student, Date date) {
	int ReturnValue;
	double dueday = 0, currentday = 0;
	for (int i = 1; i < 12; i++) {
		if (i <= student.book->due.month)
			dueday += 30;
		if (i <= date.month)
			currentday += 30;
	}
	dueday += student.book->due.year * 365.25 + student.book->due.day;
	currentday += date.year * 365.25 + date.day;
	ReturnValue = int(currentday - dueday);//calculate the difference between current date and due date
	return ReturnValue;
}
int JulianDate(LibBook Book, Date date) {
	int ReturnValue;
	double dueday = 0, currentday = 0;
	for (int i = 1; i < 12; i++) {
		if (i <= Book.due.month)
			dueday += 30;
		if (i <= date.month)
			currentday += 30;
	}
	dueday += Book.due.year * 365.25 + Book.due.day;
	currentday += date.year * 365.25 + date.day;
	ReturnValue = int(currentday - dueday);
	return ReturnValue;
}
