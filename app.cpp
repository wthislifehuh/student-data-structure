#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include	<cstring>
#include	"List.h"
#include	"Student.h"

using namespace std;

/* 9 functions */
bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
bool InsertExamResult(const char*, List*);
bool PrintStatistic(List);
bool FilterStudent(List, List*, char*, int, int);
bool UpdateIDandPhone(List*);
bool FindPotentialFirstClass(List, List*, char*);
int menu();

/* Extra functions and variable */
bool CheckFile(string);
bool CheckID(Student*);
bool ExamResult = false;	// To check if the exam result has been inserted into list1

int main() {
	// Declaration
	List list1, list2;
	bool next = true, validInput = false;
	char course[40], deleteid[10];
	int year = 0, totalcredit = 0, choice = 0;

	cout << endl << endl << "\tWelcome to Student Record Program !" << endl << endl;

	// Main function
	do {
		system("Pause");
		switch (menu())
		{
		case 1:
			system("cls");
			cout << "=====================================================" << endl;
			cout << right << setw(34) << "CREATE STUDENT LIST" << endl;
			cout << "=====================================================" << endl;
			cout << endl << "Creating student list and removing all the duplicated records..." << endl << endl;

			if (!CreateStuList("student.txt", &list1))
				cout << "The student list cannot be created!" << endl << endl;
			else {
				cout << "The student list has been successfully created!" << endl << endl;
			}
			break;


		case 2:
			system("cls");
			cout << "=====================================================" << endl;
			cout << right << setw(35) << "DELETE STUDENT RECORD" << endl;
			cout << "=====================================================" << endl;
			cout << "Example of student ID: 1200233" << endl;
			cout << "(Tips: Enter the basic ID before it has been updated)" << endl << endl;
			cout << "Please enter the student ID to be deleted: ";
			cin >> deleteid;

			if (DeleteStudent(&list1, deleteid)) {
				cout << endl << "Deleting student record..." << endl;
				cout << "The student information is successfully deleted from the list." << endl << endl;
			}
			else
				cout << "The Student ID entered is not found ..." << endl << endl;
			break;


		case 3:
			system("cls");
			cout << "=====================================================" << endl;
			cout << right << setw(35) << "PRINT STUDENT LIST" << endl;
			cout << "=====================================================" << endl;
			cout << right << setw(30) << "Sources" << endl;
			cout << "-----------------------------------------------------" << endl;
			cout << right << setw(38) << "(1): Display to screen" << endl;
			cout << right << setw(37) << "(2): Print it to file" << endl;
			cout << "-----------------------------------------------------" << endl;

			// Input validation
			do {
				cout << "Please enter your choice of source: ";
				cin >> choice;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input! Please enter again." << endl << endl;
					break;
				}
				else if (choice == 1 || choice == 2) {
					if (!PrintList(list1, choice))
						cout << "The student list fails to be printed!" << endl << endl;
				}
				else {
					cout << "Invalid input! Please enter again!" << endl << endl;
					break;
				}
			} while (choice < 1 || choice > 2);

			break;

		case 4:
			system("cls");
			cout << "=====================================================" << endl;
			cout << right << setw(35) << "INSERT EXAM RESULT" << endl;
			cout << "=====================================================" << endl << endl;
			if (InsertExamResult("exam.txt", &list1)) {
				ExamResult = true;
				cout << "Inserting student exam result..." << endl << endl;
				cout << "All the exam results have been successfully inserted!" << endl << endl;
			}
			break;


		case 5:
			system("cls");
			cout << "=====================================================" << endl;
			cout << right << setw(35) << "PRINT STATISTIC" << endl;
			cout << "=====================================================" << endl;
			PrintStatistic(list1);
			cout << endl;
			break;


		case 6:
			system("cls");
			cout << "=====================================================" << endl;
			cout << right << setw(35) << "FILTER STUDENT LIST" << endl;
			cout << "=====================================================" << endl;
			if (!ExamResult) {
				cout << "Please note that the exam results haven't been inserted yet..." << endl << endl;
				break;
			}
			cout << "Enter the filter conditions: " << endl;
			do {
				cout << "Course\t\t = ";
				if (!(cin >> course) || strlen(course) > 2)
				{
					cout << "Invalid input! Please enter again." << endl << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}

				// Accept both uppercase and lowercase input
				course[0] = toupper(course[0]);
				course[1] = toupper(course[1]);

				cout << "Year\t\t = ";
				if (!(cin >> year) || year < 2001 || year > 2099)
				{
					cout << "Invalid input! Please enter again." << endl << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}

				cout << "Total Credit\t>= ";
				if (!(cin >> totalcredit) || totalcredit < 0)
				{
					cout << "Invalid input! Please enter again." << endl << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				validInput = true;
			} while (!validInput);

			if (FilterStudent(list1, &list2, course, year, totalcredit))
				if (!(&list2)->empty())
					PrintList(list2, 1);
				else
					cout << "No result matched." << endl << endl;
			while (!list2.empty()) list2.remove(1);
			break;


		case 7:
			system("cls");
			cout << "=====================================================" << endl;
			cout << right << setw(40) << "UPDATE STUDENT ID AND PHONE NO" << endl;
			cout << "=====================================================" << endl << endl;
			cout << "Updating student id and their phone no..." << endl << endl;
			if (UpdateIDandPhone(&list1))
			{
				cout << "All the student id and phone number have been successfully updated!" << endl << endl;
				system("PAUSE");
				if (!PrintList(list1, 1))
					cout << "The student list fail to be printed..." << endl;
			}
			else
				cout << "The student id and phone number cannot be updated..." << endl << endl;
			break;


		case 8:
			system("cls");
			cout << "=====================================================" << endl;
			cout << right << setw(43) << "FIND POTENTIAL FIRST CLASS STUDENT" << endl;
			cout << "=====================================================" << endl;
			cout << right << setw(30) << "Courses" << endl;
			cout << "-----------------------------------------------------" << endl;
			cout << right << setw(28) << "CS" << endl;
			cout << right << setw(28) << "CN" << endl;
			cout << right << setw(28) << "CT" << endl;
			cout << right << setw(28) << "IA" << endl;
			cout << right << setw(28) << "IB" << endl;
			cout << "-----------------------------------------------------" << endl;

			cout << "Please enter your choice of course: ";
			cin >> course;
			// Accept both lowercase and uppercase input
			course[0] = toupper(course[0]);
			course[1] = toupper(course[1]);

			if (strcmp(course, "CS") == 0 || strcmp(course, "CN") == 0 ||
				strcmp(course, "CT") == 0 || strcmp(course, "IA") == 0 || strcmp(course, "IB") == 0)
			{
				// Check if the exam record has been inserted
				if (!ExamResult)
				{
					cout << endl << "Please note that the students' exam results haven't been inserted!" << endl;
					cout << "Kindly proceed with (4) Insert exam result..." << endl << endl;
				}
				else {
					if (FindPotentialFirstClass(list1, &list2, course)) {
						if (!list2.empty())
							PrintList(list2, 1);
					}
				}
			}
			else
				cout << "Invalid Input! Please enter again. " << endl << endl;
			while (!list2.empty()) list2.remove(1);
			break;


		case 9:
			cout << endl << "You are quitting..." << endl;
			system("Pause");
			next = false;
			break;
		}
	} while (next);

	system("cls");
	cout << endl << endl << "\t" << "Thanks for using the program.\n\t\tHave a nice day!" << endl << endl;

	system("pause");
	return 0;
}

//(1) To read student List from file and store in list
bool CreateStuList(const char* filename, List* list) {

	ifstream inFile(filename);
	if (!CheckFile(filename)) return false;		// Check if the file exist or is empty

	char discard[30];
	bool duplicate;
	Student student, stud;


	// Read value from student.txt and store in list1
	while (inFile >> discard >> discard >> discard >> student.id)
	{
		inFile >> discard >> discard;
		inFile.ignore();
		inFile.getline(student.name, 256);
		inFile >> discard >> discard >> student.course;
		inFile >> discard >> discard >> discard >> student.phone_no;

		// Check duplicated ID which is not to be stored in list1
		duplicate = false;
		if (!list->empty()) {
			for (int i = 1; i <= list->size(); i++) {
				list->get(i, stud);

				CheckID(&stud); // Check if the ID in list is 10 characters (after updated)

				// Compare the student ID to find duplicated record
				if (student.compareID(stud)) {
					duplicate = true;
					break;
				}
			}
		}

		if (!duplicate) 	// if ID is not duplicated, insert student
			list->insert(student);
	}
	inFile.close();
	return true;
}


// (2) Delete student from the list 
bool DeleteStudent(List* list, char* id) {

	Student stud;

	// Check if the list is empty
	if (list->empty()) {
		cout << "The list is empty! Please create student list first." << endl << endl;
		return false;
	}
	// Search for every student in the list
	for (int i = 1; i <= list->size(); ++i) {
		list->get(i, stud);

		CheckID(&stud); // Check if the ID in list is 10 characters (after updated)

		// Remove the student with matched ID
		if (strcmp(id, stud.id) == 0) {
			list->remove(i);
			return true;
		}
	}
	return false;
}


// (3) Print the student List1
bool PrintList(List list, int source) {

	// Check if the list is empty
	if (list.empty()) {
		cout << "The list is empty! Please create student list first." << endl << endl;
		return false;
	}

	Student stu;

	// Print all the student record onto screen
	if (source == 1) {
		system("cls");
		cout << "The student list will be shown below: " << endl;
		cout << "=====================================================================================================================" << endl << endl << endl;

		for (int stuNo = 1; stuNo <= list.size(); stuNo++) {
			list.get(stuNo, stu);
			cout << "******************************************************" << " STUDENT " << stuNo << " *****************************************************" << endl;
			stu.print(cout);	// Print student info
			cout << "--------------------------------------------------PAST EXAM RESULT:--------------------------------------------------" << endl;
			if (stu.exam_cnt == 0)
				cout << endl << "THIS STUDENT HAS\'T TAKEN ANY EXAM YET" << endl;
			else {
				for (int i = 0; i < stu.exam_cnt; i++)	// Print subject result for every semester or exam & GPA
					stu.exam[i].print(cout);
			}
			cout << endl;
			cout << "******************************************************" << " STUDENT " << stuNo << " *****************************************************" << endl << endl << endl;
		}
		cout << "=====================================================================================================================" << endl;
		cout << "All the record of the students has been successfully displayed. " << endl << endl;
	}

	// Write all the student record into student_result.txt file
	else if (source == 2) {
		cout << "Printing the record of the students to the file \"student_result.txt\"... " << endl << endl;
		ofstream outFile("student_result.txt");
		for (int stuNo = 1; stuNo <= list.size(); stuNo++) {
			list.get(stuNo, stu);
			outFile << "******************************************************" << " STUDENT " << stuNo << " *****************************************************" << endl;
			stu.print(outFile);
			outFile << "--------------------------------------------------PAST EXAM RESULT:--------------------------------------------------" << endl;
			if (stu.exam_cnt == 0)
				outFile << endl << "THIS STUDENT HAVEN\'T TAKEN ANY EXAM YET" << endl;
			else {
				for (int i = 0; i < stu.exam_cnt; i++)
					stu.exam[i].print(outFile);
			}
			outFile << endl;
			outFile << "****************************************************** STUDENT " << stuNo << " *****************************************************" << endl << endl << endl;
		}
		outFile.close();
		cout << "The record of the students has been printed to the file \"student_result.txt\" successfully. " << endl << endl;
	}
	return true;
}


//(4) Read the exam result into exam struct 
bool InsertExamResult(const char* filename, List* list)
{
	Student stud, stud1;
	ifstream readFile(filename);

	// Check if the file exists
	if (!CheckFile(filename)) return false;

	// Check if the list is empty
	if (list->empty())
	{
		cout << "Student list is empty, please create the list first." << endl;
		return false;
	}

	// Read exam record from text file
	while (readFile >> stud1.id) {
		for (int nodeNo = 1; nodeNo <= list->size(); ++nodeNo)
		{
			list->get(nodeNo, stud);// Get student record from the list

			CheckID(&stud); // Check if the ID in list is 10 characters (after updated)

			// Proceed to the next node if the ID is incompatible
			if (!stud1.compareID(stud)) continue;

			++stud.exam_cnt;	// Increment by one for each exam
			readFile >> stud.exam[stud.exam_cnt - 1].trimester
				>> stud.exam[stud.exam_cnt - 1].year
				>> stud.exam[stud.exam_cnt - 1].numOfSubjects;

			for (int subNo = 0; subNo < stud.exam[stud.exam_cnt - 1].numOfSubjects; ++subNo)
				readFile >> stud.exam[stud.exam_cnt - 1].sub[subNo].subject_code
				>> stud.exam[stud.exam_cnt - 1].sub[subNo].subject_name
				>> stud.exam[stud.exam_cnt - 1].sub[subNo].credit_hours
				>> stud.exam[stud.exam_cnt - 1].sub[subNo].marks;

			stud.exam[stud.exam_cnt - 1].calculateGPA();
			stud.calculateCurrentCGPA();

			// Insert the result into linked list
			list->set(nodeNo, stud);
		}
	}
	readFile.close();
	return true;
}

//(5) Print overall student statistic
bool PrintStatistic(List list)
{
	// Variable declaration
	int CS_count = 0, IA_count = 0, IB_count = 0, CN_count = 0, CT_count = 0;
	double totalCGPA = 0;
	int totalSubject = 0, totalCredits = 0, totalTrimester = 0;
	double aveCGPA = 0.0, aveSubject = 0.0, aveCredits = 0.0;
	Student student;

	// Check if the list exists or is empty
	if (list.empty()) {
		cout << "The list is empty. Please create the list first and insert the exam result" << endl;
		return false;
	}

	// Check if the student exam record has been inserted
	if (!ExamResult) {
		cout << "The exam result has not been inserted for each student" << endl;
		return false;
	}

	// Read information from each node
	for (int nodeNo = 1; nodeNo <= list.size(); ++nodeNo) {
		list.get(nodeNo, student);

		if (strcmp(student.course, "CS") == 0)
			++CS_count;
		else if (strcmp(student.course, "IA") == 0)
			++IA_count;
		else if (strcmp(student.course, "IB") == 0)
			++IB_count;
		else if (strcmp(student.course, "CN") == 0)
			++CN_count;
		else
			++CT_count;

		for (int examNo = 0; examNo < student.exam_cnt; ++examNo)
			totalSubject += student.exam[examNo].numOfSubjects;

		totalCGPA += student.current_cgpa;
		totalCredits += student.totalCreditsEarned;
		totalTrimester += student.exam_cnt;
	}

	aveCGPA = totalCGPA / list.size();
	aveSubject = (double)totalSubject / totalTrimester;
	aveCredits = (double)totalCredits / totalTrimester;

	cout << "Total Students: " << list.size() << endl
		<< "\tCS Students - " << CS_count << endl
		<< "\tIA Students - " << IA_count << endl
		<< "\tIB Students - " << IB_count << endl
		<< "\tCN Students - " << CN_count << endl
		<< "\tCT Students - " << CT_count << endl << endl
		<< "Average CGPA: " << aveCGPA << endl
		<< "Average Subjects Taken Per Semester: " << aveSubject << endl
		<< "Average Credits Earned Per Semester: " << aveCredits << endl;

	return true;
}

//(6) Filter student by course, year, credit hours
bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit)
{
	// Variable declaration
	Student student;
	bool filter;
	char yearID[5];

	// Check if list1 is empty
	if (list1.empty()) {
		cout << "The student list is empty. Please create the list first" << endl;
		return false;
	}

	// Check if list2 is not empty
	if (!list2->empty()) {
		cout << "Error. List2 is not empty" << endl;
		return false;
	}

	// Filter function
	for (int nodeNo = 1; nodeNo <= list1.size(); ++nodeNo)
	{
		// Re-initialise filter flag
		filter = true;

		list1.get(nodeNo, student);

		// Extract year from id
		yearID[0] = '2';
		yearID[1] = '0';
		yearID[2] = student.id[0];
		yearID[3] = student.id[1];
		yearID[4] = '\0';

		if ((strcmp(course, student.course) == 0) &&
			(year == atoi(yearID)) &&
			(student.totalCreditsEarned >= totalcredit))
			filter = true;
		else
			filter = false;

		if (!filter) continue;

		list2->insert(student);
	}
	return true;
}



// (7) Update Student ID and Phone No in list1
bool UpdateIDandPhone(List* list) {
	Student stu, temp;
	int pos;

	// Check if the list is empty
	if (list->empty()) {
		cout << "The list is empty! Please create student list first." << endl << endl;
		return false;
	}

	for (int i = 1; i <= list->size(); ++i) {

		list->get(i, stu);
		// Check if the student ID has already been updated to 10 character
		if (strlen(stu.id) > 7) continue;

		// Update Student ID
		strcpy(temp.id, "B");
		strcat(temp.id, stu.course);
		strcat(temp.id, stu.id);
		strcpy(stu.id, temp.id);

		// Update Phone No
		char new_phoneNo[10];
		pos = 0;
		for (int k = 0; k < strlen(stu.phone_no); k++) {
			if (stu.phone_no[k] != '-') {
				new_phoneNo[pos] = stu.phone_no[k];
				pos++;
			}
		}
		new_phoneNo[pos] = '\0'; // Terminate the new string with a null character

		// Check if the first character of phoneNo is even
		if (new_phoneNo[0] % 2 == 0)
			strcpy(temp.phone_no, "02");
		else
			strcpy(temp.phone_no, "01");

		strcat(temp.phone_no, new_phoneNo);
		strcpy(stu.phone_no, temp.phone_no);
		list->set(i, stu);	// Update the changes to list
	}
	return true;
}



//(8) Find potential student who might get first class & insert into list2
bool FindPotentialFirstClass(List list1, List* list2, char* course) {

	// Check if list1 is empty
	if (list1.empty()) {
		cout << "The student list is empty! \n\nPlease create student list and insert their exam results." << endl << endl;
		return false;
	}
	// Check if list 2 is not empty
	if (!list2->empty()) {	// for safety warning
		cout << "The list is not empty!" << endl << endl;
		return false;
	}

	Student stu;
	int stuNo = 0;
	int cnt1, cnt2, credit;

	// Check condition for every student
	for (int i = 1; i <= list1.size(); ++i) {
		list1.get(i, stu);
		if (strcmp(stu.course, course) == 0) {
			cnt1 = 0;	// to count number of trimester GPA < 3.5
			cnt2 = 0;	// to count number of trimester GPA >= 3.75

			// Only test for students who took at least 3 exams
			if (stu.exam_cnt >= 3) {

				// To test for every semester exam
				for (int j = 0; j < stu.exam_cnt; ++j) {

					// To calculate total credit hours per semester
					credit = 0;
					for (int k = 0; k < stu.exam[j].numOfSubjects; ++k)
						credit += stu.exam[j].sub[k].credit_hours;

					// To test gpa each semester exam
					if (stu.exam[j].gpa < 3.5)
						++cnt1;
					else if (stu.exam[j].gpa >= 3.75 && credit >= 12)
						++cnt2;
				}

				if (cnt1 > 0) continue;
				else if (cnt2 >= 3) {
					stuNo++;
					list2->insert(stuNo, stu);		// Update the firstclass student into list2 for printing
				}
			}
		}
	}
	// Print result message
	if (stuNo == 0)
		cout << endl << endl << "There is no student in " << course << " who has potential to get first class." << endl << endl;
	else if (stuNo == 1) {
		cout << endl << endl << "There is " << stuNo << " number of student in " << course << " who has potential to get first class." << endl << endl;
		system("pause");
	}
	else {
		cout << endl << endl << "There are " << stuNo << " number of students in " << course << " who have potential to get first class." << endl << endl;
		system("pause");
	}
	return true;
}


// (9) Menu for navigation between function
int menu() {

	// Display menu to user
	system("cls");
	cout << endl << endl << "=====================================================" << endl;
	cout << right << setw(40) << "  __  __  ___  _  _  _   _  " << endl;
	cout << right << setw(40) << " |  \\/  || __|| \\| || | | | " << endl;
	cout << right << setw(40) << " | |\\/| || _| | .` || |_| | " << endl;
	cout << right << setw(40) << " |_|  |_||___||_|\\_| \\___/  " << endl;
	cout << "=====================================================" << endl;
	cout << "\t1. Create student List" << endl;
	cout << "\t2. Delete Student" << endl;
	cout << "\t3. Print student list" << endl;
	cout << "\t4. Insert exam result" << endl;
	cout << "\t5. Print Exam Statistic" << endl;
	cout << "\t6. Filter Student" << endl;
	cout << "\t7. Update Student's ID and Phone" << endl;
	cout << "\t8. Find Potential First Class Student" << endl;
	cout << "\t9. Exit" << endl;
	cout << "=====================================================" << endl;

	int choice;
	while (true) // Input Validation
	{
		cout << "Enter your choice: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input! Please enter between 1 - 9." << endl << endl;
			continue;
		}
		else if ((choice < 1) || (choice > 9))
		{
			cout << "Invalid input! Please enter between 1 - 9." << endl << endl;
			continue;
		}
		return choice;
	}
}


// Extra: check file existanace and availability
bool CheckFile(string filename) { // Usage: Check whether the file exists with data inside

	ifstream inFile(filename);
	string line;

	// (1) File does not exist
	if (!inFile) {
		cout << "Sorry, \"" << filename << "\" does not exist ..." << endl;
		return false;
	}

	// (2) : File exists with data inside
	while (inFile >> line) {
		inFile.close();
		return true;
	}

	// (3): File exists but empty
	cout << "Sorry, \"" << filename << "\" is an empty file ..." << endl;
	inFile.close();
	return false;
}


// Extra: Check if the student ID has been updated to 10 characters, then store it in original 7 char for comparing in function
bool CheckID(Student* stud) {
	if (strlen(stud->id) == 10) {
		for (int i = 3; i < 10; i++) {
			stud->id[i - 3] = stud->id[i];
			stud->id[i] = NULL;
		}
		return true;
	}
	return false;
}