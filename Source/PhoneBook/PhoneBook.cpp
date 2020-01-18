// PhoneBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>												// Basic input/output
#include <string>												// strings
#include <fstream>												// read/write files
#include <conio.h>												// getche
#include <direct.h>												// for creating system files folder

using namespace std;

const string FilePath = "SystemFiles\\Contacts.txt";

const string SuccessMessage = "Success!\nPress any key to continue . . .";

const string InvalidNumberMessage = "\t\t\t\tInvalid input. Enter a number: ";

const string NoContactMessage = "No contact found.";

const int MAX_LEN = 100;
int TotalContacts = 0;

// Contact class that contain main info of a contact
class Contact
{
public:
	// main info of the contact
	string Name, Phone;

	// Default constructor
	Contact()
	{
		Name = "~No Name~";
		Phone = "~No Data~";
	}

	// Constructor that takes the basic info as arguments and fill it in our class
	Contact(string name, string phone)
	{
		Name = name;
		Phone = phone;
	}
};


// The phone book class that will handle save and edit our file
class Phone_Book
{
public:
	// Array of contacts that will carry our data at running-time
	Contact Contacts[MAX_LEN];

	// Default constructor that will recover running-time data
	Phone_Book()
	{
		// Recovering data
		RecoverData();

		// Make directory
		_mkdir("SystemFiles");
	}

public:
	// fill our array from the text if found
	void RecoverData()
	{
		ifstream contact(FilePath, ios::in);			
		TotalContacts = 0;

		for (int i = 0; i < MAX_LEN; i++)
		{
			contact >> Contacts[i].Name >> Contacts[i].Phone;
			if (Contacts[i].Name != "~No Name~")
				TotalContacts++;
		}
	}

	// Saving data to the file after OP
	void SaveData()
	{	
		// open the file and clear it first
		ofstream old(FilePath); {
			old.clear();		old.close();
		}

		// then get in for loop to save all contacts data to the file.

		for (int i = 0; i < TotalContacts; i++)
		{
			if (Contacts[i].Name != "~No Name~")
			{
				ofstream contact(FilePath, ios::app); {
					contact << Contacts[i].Name << "\t" << Contacts[i].Phone << endl;
				}
			}
		}
	}

	// Display all data on console
	void DisplayData()
	{
		// Clear the screen
		system("CLS");

		// Make sure we have all data
		RecoverData();

		// variable for user input.
		int choice;

		for (int i = 0; i < TotalContacts; i++)
		{
			cout << i + 1 << "- " << Contacts[i].Name << "\t" << Contacts[i].Phone << endl;
		}

		cout << "\n\n1- Add new contact.\t2- Edit a contact.\t3- Delete a contact.\t0- Main menu.\n\n\t\t\t\tChoice: ";
		cin >> choice;
		// checking if user input not a number.
		while (1)
		{
			if (cin.fail() || choice < 0)
			{
				cin.clear();	cin.ignore(256, '\n');
				cout << InvalidNumberMessage;		cin >> choice;
				continue;
			}
			break;
		}

		if (choice == 1)
			AddContact();
		else if (choice == 2)
			EditContact();
		else if (choice == 3)
			DeleteContact();
		else if (choice == 0)
			MainMenu();
		else
		{
			cout << "Invalid choice.\nPress any key to back to main menu . . .";
			_getche();
			MainMenu();
		}
	}

	// Display main menu
	void MainMenu()
	{
		// background color.
		system("color 3F");			

		// clear screen
		system("CLS");

		// variable for user input.
		int choice;					

		cout << "\n\t\t\t\t=======================================\n";
		cout << "\t\t\t\t|| (1) | See list of contacts.       ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||\n";
		cout << "\t\t\t\t|| (2) | Add a contact.              ||\n";
		cout << "\t\t\t\t||-----|-----------------------------||\n";
		cout << "\t\t\t\t|| (0) | Exit the program.           ||\n";
		cout << "\t\t\t\t=======================================\n";
		cout << "\t\t\t\t======= BY: AVA Sharkawy ==============\n";
		cout << "\t\t\t\t\t\tChoice: ";	cin >> choice;	// taking choice from user

		// checking if user input not a number.
		while (1)
		{			
			if (cin.fail() || choice < 0)
			{
				cin.clear();	cin.ignore(256, '\n');
				cout << InvalidNumberMessage;		cin >> choice;
				continue;
			}
			break;
		}

		switch (choice)
		{		// switch cases for user choice.
		case 1:					// case 1 go to print all data function.
			DisplayData();	break;
		case 2:					// case 2 go to add a new contact function.
			AddContact();	break;
		case 0:					// case 0 end the program.
			exit(0);	 break;
		default:
			break;
		}

	}

	// Add a new contact
	void AddContact()
	{
		string name, phone;

		cout << "Enter name: "; cin >> name;
		cout << "\nEnter phone: "; cin >> phone;

		Contacts[TotalContacts].Name = name;
		Contacts[TotalContacts].Phone = phone;
		TotalContacts++;

		// Saving data
		SaveData();

		cout << SuccessMessage;
		_getch();
		DisplayData();
	}

	// Edit contact
	void EditContact()
	{
		// User choice;
		int choice;

		cout << "Enter contact number: ";	cin >> choice;
		// checking if user input not a number.
		while (1)
		{
			if (cin.fail() || choice < 0)
			{
				cin.clear();	cin.ignore(256, '\n');
				cout << InvalidNumberMessage;		cin >> choice;
				continue;
			}
			break;
		}

		if (choice <= TotalContacts)
		{
			int index = choice - 1;
			string name, phone;
			cout << "Current name: " << Contacts[index].Name << endl;
			cout << "Enter new name: "; cin >> name;
			cout << "Current phone: " << Contacts[index].Phone << endl;
			cout << "Enter new phone: "; cin >> phone;

			Contacts[index].Name = name;
			Contacts[index].Phone = phone;

			SaveData();

			cout << SuccessMessage;
			_getche();
			DisplayData();
		}
		else
		{
			cout << NoContactMessage;
			_getche();
			MainMenu();
		}
	}

	// Delete Contact
	void DeleteContact()
	{
		// User choice;
		int choice;

		cout << "Enter contact number: ";	cin >> choice;
		// checking if user input not a number.
		while (1)
		{
			if (cin.fail() || choice < 0)
			{
				cin.clear();	cin.ignore(256, '\n');
				cout << InvalidNumberMessage;		cin >> choice;
				continue;
			}
			break;
		}

		if (choice <= TotalContacts)
		{
			int index = choice - 1;
			sys_DeleteIndex(index);
			cout << SuccessMessage;
			_getche();
			DisplayData();
		}
		else
		{
			cout << NoContactMessage;
			_getche();
			MainMenu();
		}
	}

	void sys_DeleteIndex(int index)
	{
		for (int i = index; i < TotalContacts; i++)
		{
			Contacts[i] = Contacts[i + 1];
		}
		TotalContacts--;
		SaveData();
	}

};


int main()
{
	Phone_Book pb = Phone_Book();
	pb.MainMenu();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
