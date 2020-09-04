// Guan Ce Looa
// CS 301 Summer 2020
// Assignment 1: Employee Tracker

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct employee
{
	string name;
	int rank;
	int salary;
	employee* next;
};

void join(string name, employee* &list, ofstream &employ);
void quit(string name, employee* &list, ofstream &employ);
void promote(string name, employee* &list, ofstream &employ);
void demote(string name, employee* &list, ofstream &employ);
void salary(employee* list, ofstream &employ);
void employees(employee* list, ofstream &employ);
void parse(string command, employee* &list, int &run, ofstream &employ);
int end();

int main()
{
	employee* list = nullptr; // Initialize empty list with head pointer as "list"
	string command;

	ofstream employ;
	employ.open("employ.txt");

	cout << "Welcome to employee tracker. By GCLOOA 2020." << endl;
	employ << "Welcome to employee tracker. By GCLOOA 2020." << endl; // Duplicate lines are for writing to employ.txt
	int run = 1;
	while (run == 1)
	{
		cout << "Please select a command:" << endl;
		employ << "Please select a command:" << endl;
		cout << "join <person> | quit <person> | promote <person> | demote <person> | salary | employees | end" << endl;
		employ << "join <person> | quit <person> | promote <person> | demote <person> | salary | employees | end" << endl;
		cout << "Input: ";
		getline(cin, command);
		employ << "Input: " << command << endl;
		parse(command, list, run, employ); // Custom parser, explained in function definition below
		cout << endl;
		employ << endl;
	}

	cout << "Final employee list:" << endl;
	employ << "Final employee list:" << endl;
	salary(list, employ);
	
	cout << "Press any key to end program." << endl;
	employ << "End of activity log." << endl;
	cin.get();
	return 0;
}

void join(string name, employee* &list, ofstream &employ)
{
	employee* newbie = new employee;
	newbie->name = name;
	newbie->rank = 1;
	newbie->salary = newbie->rank * 2000;
	newbie->next = nullptr;

	if (list == nullptr)
	{
		list = newbie;
	}
	else
	{
		employee* ptr = list; // Node selection pointer
		while (ptr->next != nullptr)
		{
			ptr->rank = ptr->rank + 1; // Modify existing employee rank
			ptr->salary = ptr->rank * 2000; // Modify existing employee salary
			ptr = ptr->next;
		}
		ptr->rank = ptr->rank + 1; // Modify existing employee rank
		ptr->salary = ptr->rank * 2000; // Modify existing employee salary
		ptr->next = newbie;
	}
	cout << name << " joined." << endl;
	employ << name << " joined." << endl;
}

void quit(string name, employee* &list, ofstream &employ)
{
	employee* ptr = list; // Node selection pointer
	employee* qtr = nullptr; // Previous node selection pointer
	while (ptr != nullptr && ptr->name != name) // Search list
	{
		qtr = ptr;
		ptr = ptr->next;
	}
	if (ptr == nullptr) // Employee not found
	{
		cout << "Employee does not exist." << endl;
		employ << "Employee does not exist." << endl;
	}
	else if (qtr == nullptr) // Employee is found, and is the first node of the list
	{
		list = list->next;
	}
	else // Employee is found
	{
		ptr = list; // Reset selection pointer to update ranks
		while (ptr != nullptr && ptr->name != name) // Search list
		{
			ptr->rank = ptr->rank - 1; // Modify existing employee rank
			ptr->salary = ptr->rank * 2000; // Modify existing employee salary
			qtr = ptr;
			ptr = ptr->next;
		}
		qtr->next = ptr->next;
	}
	delete ptr; // Delete selected node
	cout << name << " quit." << endl;
	employ << name << " quit." << endl;
}

void promote(string name, employee* &list, ofstream &employ)
{
	employee* ptr = list; // Node selection pointer
	employee* qtr = nullptr; // Previous node selection pointer
	while (ptr != nullptr && ptr->name != name) // Search list
	{
		qtr = ptr;
		ptr = ptr->next;
	}
	if (ptr == nullptr) // Employee not found
	{
		cout << "Employee does not exist." << endl;
		employ << "Employee does not exist." << endl;
	}
	else if (qtr == nullptr) // Employee is found, and is the first node of the list
	{
		cout << "Employee has the highest rank." << endl;
		employ << "Employee has the highest rank." << endl;
	}
	else // Employee is found
	{
		string temp = qtr->name; // Swap employee rank
		qtr->name = ptr->name;
		ptr->name = temp;
		cout << name << " promoted." << endl;
		employ << name << " promoted." << endl;
	}
}

void demote(string name, employee* &list, ofstream &employ)
{
	employee* ptr = list; // Node selection pointer
	employee* qtr = nullptr; // Previous node selection pointer
	while (ptr != nullptr && ptr->name != name) // Search list
	{
		qtr = ptr;
		ptr = ptr->next;
	}
	if (ptr == nullptr) // Employee not found
	{
		cout << "Employee does not exist." << endl;
		employ << "Employee does not exist." << endl;
	}
	else if (ptr->next == nullptr) // Employee is found, and is the last node of the list
	{
		cout << "Employee has the lowest rank." << endl;
		employ << "Employee has the lowest rank." << endl;
	}
	else // Employee is found
	{
		qtr = ptr->next; // Select next node of lower rank
		string temp = qtr->name; // Swap employee rank
		qtr->name = ptr->name;
		ptr->name = temp;
		cout << name << " demoted." << endl;
		employ << name << " demoted." << endl;
	}
}

void salary(employee* list, ofstream &employ)
{
	if (list == nullptr)
	{
		cout << "There are currently no employees in this company." << endl;
		employ << "There are currently no employees in this company." << endl;
	}
	else
	{
		cout << "Employee list and salary:" << endl;
		cout << "[Rank] [Name]     [Salary]" << endl;
		employ << "Employee list and salary:" << endl;
		employ << "[Rank] [Name]     [Salary]" << endl;
		while (list != nullptr)
		{
			cout << " " << left << setw(7) << list->rank << setw(10) << list->name << " $" << list->salary << endl;
			employ << " " << left << setw(7) << list->rank << setw(10) << list->name << " $" << list->salary << endl;
			list = list->next;
		}
	}
}

void employees(employee* list, ofstream &employ)
{
	if (list == nullptr)
	{
		cout << "There are currently no employees in this company." << endl;
		employ << "There are currently no employees in this company." << endl;
	}
	else
	{
		cout << "Employee list:" << endl;
		cout << "[Rank] [Name]" << endl;
		employ << "Employee list:" << endl;
		employ << "[Rank] [Name]" << endl;
		while (list != nullptr)
		{
			cout << " " << left << setw(7) << list->rank << list->name << endl;
			employ << " " << left << setw(7) << list->rank << list->name << endl;
			list = list->next;
		}
	}
}

void parse(string command, employee* &list, int &run, ofstream &employ)
{
	// Below is my own logic written to separate commands that require names (JOIN, QUIT, PROMOTE, & DEMOTE)
	// and the commands that don't (SALARY, EMPLOYEES, & END)
	string cmd;
	string cmd_arg = command;
	for (auto i : command) // Start iterating over input string from getline()
	{
		if (i == ' ') // If there is a space, split it into two strings
		{
			cmd_arg = cmd;
			cmd = "";
		}
		else
		{
			cmd = cmd + i;
		}
	}
	command = cmd; // Swap strings into correct variables
	cmd = cmd_arg; // If the original string has no spaces, this swap is redundant, but required to make this work
	cmd_arg = command;

	// Command list option select 
	if (cmd == "join")
	{
		join(cmd_arg, list, employ);
	}
	else if (cmd == "quit")
	{
		quit(cmd_arg, list, employ);
	}
	else if (cmd == "promote")
	{
		promote(cmd_arg, list, employ);
	}
	else if (cmd == "demote")
	{
		demote(cmd_arg, list, employ);
	}
	else if (cmd == "salary")
	{
		salary(list, employ);
	}
	else if (cmd == "employees")
	{
		employees(list, employ);
	}
	else if (cmd == "end")
	{
		run = end();
	}
	else
	{
		cout << "There is no such command. Type commands according to the options give. Commands are case-sensitive." << endl;
		employ << "There is no such command. Type commands according to the options give. Commands are case-sensitive." << endl;
	}
}

int end()
{
	return 0;
}