#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <mysql.h>
#include <iomanip>
#include <ctime>
#include <vector>
#include <limits>
#include <map>
#include <algorithm>
#include <ctime>
using namespace std;

// Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

// Global Variable End

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "", "coffee_shop", 3306, NULL, 0);

	}
};

int userRole;
string AdminID, EmployeeID, CustomerID;

//PUBLIC
//MANAGE ADMIN MENU
void profileAdmin(); 
void listAdmin(); 
void registerAdmin(); 
void deleteAdmin(); 
void updateAdmin(); 

//MANAGE MENU
void manageAdminMenu(); 
void manageEmployeeMenu(); 
void manageCustomerMenu();
void manageMenu(); 


//MANAGE EMPLOYEE MENU
void listEmployee(); 
void registerEmployee(); 
void deleteEmployee(); 
void updateEmployee(); 

//EMPLOYEE MENU
void profileEmployee(); 
void viewCustomerOrders(); 


//CUSTOMER MENU
void registerCustomer(); 
void updateCustomer(); 
void placeorder(); 

//MANAGE CUSTOMER MENU
void profileCustomer(); 
void listCustomer(); 
void deleteCustomer(); 


//MENUU
void mainMenu(); 
void employeeMenu(); 
void customerMenu(); 


//LOGIN MENU
void loginAdmin(); 
void loginEmployee(); 
void loginCustomer(); 
//MANAGE ITEM MENU
void viewMenu(); 
void addMenu(); 
void updateMenu(); 
void deleteMenu(); 
void listMenu(); 

//PAYMENT
void customerPayment(double totalprice); //DONE
void viewPayment();  //ONLY ADMIN CAN SEE

//LOGIN LOGOUT MENU
void logout(); 
void mainlogin(); 

int main()
{

	db_response::ConnectionFunction();
	mainlogin();

	// Call Methods
	// Call Methods End

}






//MANAGE ADMIN MENU
void profileAdmin()
{
	system("cls");
	char choose;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                            ADMIN                                |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	string username;
	cout << "Insert Username : ";
	cin >> username;

	string retrieve_admin_query = "select * from admin where Username = '" + username + "'";
	const char* q = retrieve_admin_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << endl;
			cout << " Admin ID:  " << row[0] << endl;
			cout << " Username:  " << row[1] << endl;
			cout << " PhoneNo:   " << row[2] << endl; // Assuming PhoneNo is the third column in the admin table

		}
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'E' to return to MANAGE ADMIN MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageAdminMenu();
	}
	else
	{
		exit(0);
	}
}
void listAdmin()
{
	system("cls");
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                        LIST OF ADMINS                          |" << endl;
	cout << "------------------------------------------------------------------" << endl;

	string list_admin_query = "SELECT * FROM admin";
	const char* q = list_admin_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (mysql_num_rows(res) > 0)
		{
			cout << left << setw(15) << "Admin ID" << setw(25) << "Username" << setw(15) << "PhoneNo" << endl;
			cout << "---------------------------------------------------------------" << endl;
			while (row = mysql_fetch_row(res))
			{
				cout << left << setw(15) << row[0] << setw(25) << row[1] << setw(15) << row[2] << endl;
			}
		}
		else
		{
			cout << "No admins found in the database." << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
	}

	// Exit Code
	char choose;
	cout << "\nPress 'E' to return to MANAGE ADMIN MENU : ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageAdminMenu();
	}
	else
	{
		exit(0);
	}
}
void registerAdmin() //ONLY FOR ADMIN
{
	system("cls");
	string username, PhoneNo, Password;
	char choose;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                      ADMIN  REGISTRATION                        |" << endl;
	cout << "------------------------------------------------------------------" << endl;

	cin.ignore(1, '\n');

	cout << "Admin Username : ";
	cin >> username;

	// Check if the username already exists
	string checkUsername_query = "SELECT COUNT(*) FROM admin WHERE username = '" + username + "'";
	const char* cu = checkUsername_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		if (atoi(row[0]) > 0)
		{
			cout << "Username already exists. Please choose another name." << endl;
			cout << "Press 'E' to return to MANAGE ADMIN MENU: ";
			cin >> choose;
			if (choose == 'e' || choose == 'E')
			{
				manageAdminMenu();
			}
			else
			{
				exit(0);
			}
			return; // Exit the function early if the username exists
		}
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}

	cout << "PhoneNo : ";
	cin >> PhoneNo;

	cout << "Password : ";
	cin >> Password;

	string insert_query = "INSERT INTO admin (username, PhoneNo, Password) VALUES ('" + username + "', '" + PhoneNo + "', '" + Password + "')";
	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added to database." << endl;
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'E' to return to MANAGE ADMIN MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageAdminMenu();
	}
	else
	{
		exit(0);
	}
}
void deleteAdmin()
{
	system("cls");
	char choose;
	string username;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                         DELETE ADMIN                            |" << endl;
	cout << "------------------------------------------------------------------" << endl;

	cout << "Insert Username : ";
	cin >> username;

	string retrieve_admin_query = "SELECT * FROM admin WHERE username = '" + username + "'";
	const char* q = retrieve_admin_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (mysql_num_rows(res) > 0)
		{
			while (row = mysql_fetch_row(res))
			{
				cout << endl;
				cout << " Admin ID:  " << row[0] << endl;
				cout << " Username:  " << row[1] << endl;
				cout << " PhoneNo:  " << row[2] << endl;
			}

			string delete_admin_query = "DELETE FROM admin WHERE username = '" + username + "'";
			const char* qW = delete_admin_query.c_str();
			qstate = mysql_query(conn, qW);

			if (!qstate)
			{
				cout << "Delete Successful!" << endl;
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
		}
		else
		{
			cout << "Username not found." << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "------------------------------------------------------------------ " << endl;
	cout << "Press 'E' to return to MANAGE ADMIN MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageAdminMenu();
	}
	else
	{
		exit(0);
	}
}
void updateAdmin() {
	system("cls");
	int optreg;
	char choose;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                          UPDATE ADMIN                           |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	string username;
	cout << "Insert Admin Username : ";
	cin >> username;

	string retrieve_admin_query = "select * from admin where username = '" + username + "'";
	const char* q = retrieve_admin_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate) {
		res = mysql_store_result(conn);
		if (mysql_num_rows(res) > 0) {
			while (row = mysql_fetch_row(res)) {
				cout << endl;
				cout << " Username : " << row[1] << endl;
				cout << endl << endl;
			}
		}
		else {
			cout << "Username not found." << endl;
			manageAdminMenu();
			return;
		}
	}
	else {
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}

	bool continueUpdating = true;
	while (continueUpdating) {
		cout << "1. USERNAME. " << endl;
		cout << "2. PASSWORD " << endl;
		cout << "3. BACK " << endl;
		cout << "" << endl;
		cout << "CHOOSE OPTION (1-3) : ";
		cin >> optreg;

		string update_admin_query;
		switch (optreg) {
		case 1: {
			string updateusername;
			cout << "------------------------------------------------------------------ " << endl;
			cout << "USERNAME.: ";
			cin >> updateusername;
			update_admin_query = "update admin set username = '" + updateusername + "' where username = '" + username + "'";
			break;
		}
		case 2: {
			string updatepassword;
			cout << "------------------------------------------------------------------ " << endl;
			cout << "PASSWORD: ";
			cin >> updatepassword;
			update_admin_query = "update admin set password = '" + updatepassword + "' where username = '" + username + "'";
			break;
		}
		case 3: {
			manageAdminMenu();
			return;
		}
		default: {
			cout << "Invalid option. Please choose again." << endl;
			continue;
		}
		}

		const char* q = update_admin_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate) {
			cout << "Update Successful!" << endl;
		}
		else {
			cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
		}

		cout << "Do you want to update anything else? (Y/N): ";
		cin >> choose;
		if (choose == 'N' || choose == 'n') {
			continueUpdating = false;
		}
	}

	// Exit Code
	cout << "------------------------------------------------------------------ " << endl;
	cout << "Press 'E' to return to MANAGE ADMIN MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E') {
		manageAdminMenu();
	}
	else {
		exit(0);
	}
}


//MANAGE ITEM MENU
void listMenu()
{
	system("cls");
	char choose;
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                              VIEW MENU                                                    |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n";

	qstate = mysql_query(conn, "select * from menu");

	if (!qstate)
	{

		cout << setw(20) << "Menu ID" << setw(40) << "Drink" << setw(20) << "Price" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(40) << row[1] << setw(20) << row[2] << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
	cout << "Press 'E' to return to MANAGE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageMenu();
	}
	else
	{
		exit(0);
	}
}
void addMenu()
{
	system("cls");
	string drink, price;
	char choose;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                             ADD MENU                            |" << endl;
	cout << "------------------------------------------------------------------" << endl;

	cin.ignore(1, '\n');

	cout << "Drink :";
	getline(cin, drink);

	cout << "Price : ";
	getline(cin, price);
	cout << endl;

	string insert_query = "insert into menu (drink, price) values('" + drink + "','" + price + "')";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added to the database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'E' to return to MANAGE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageMenu();
	}
	else
	{
		exit(0);
	}
}
void updateMenu()
{
	system("cls");
	int optreg;
	char choose;
	string MenuID;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                       UPDATE MENU                             |" << endl;
	cout << "------------------------------------------------------------------ " << endl;

	cout << "Current Menu:" << endl;
	cout << setw(20) << "Menu ID" << setw(40) << "Drink" << setw(20) << "Price" << endl;
	qstate = mysql_query(conn, "SELECT * FROM menu");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(40) << row[1] << setw(20) << row[2] << endl;
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
		exit(1);
	}

	cout << "------------------------------------------------------------------ " << endl;
	cout << "Choose the Menu ID to update: ";
	cin >> MenuID;

	string retrieve_menu_query = "SELECT * FROM menu WHERE MenuID = '" + MenuID + "'";
	const char* q = retrieve_menu_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (mysql_num_rows(res) > 0)
		{
			while (row = mysql_fetch_row(res))
			{
				cout << endl;
				cout << " Drink : " << row[1] << endl;
				cout << " Price : " << row[2] << endl;
				cout << endl << endl;
			}

			bool continueUpdating = true;
			while (continueUpdating)
			{
				cout << "1. DRINK " << endl;
				cout << "2. PRICE " << endl;
				cout << "3. BACK " << endl;
				cout << "" << endl;
				cout << "CHOOSE OPTION (1-3) : ";
				cin >> optreg;

				string update_menu_query;
				switch (optreg)
				{
				case 1:
				{
					string updatedrink;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "DRINK: ";
					cin.ignore(); // Consume newline character
					getline(cin, updatedrink);
					update_menu_query = "UPDATE menu SET drink = '" + updatedrink + "' WHERE MenuID = '" + MenuID + "'";
					break;
				}
				case 2:
				{
					string updateprice;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "PRICE: ";
					cin >> updateprice;
					update_menu_query = "UPDATE menu SET price = '" + updateprice + "' WHERE MenuID = '" + MenuID + "'";
					break;
				}
				case 3:
				{
					manageMenu();
					return;
				}
				default:
				{
					cout << "Invalid option. Please choose again." << endl;
					continue;
				}
				}

				const char* q = update_menu_query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					cout << "Update Successful!" << endl;
				}
				else
				{
					cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
				}

				cout << "Do you want to update another menu item? (Y/N): ";
				cin >> choose;
				if (choose == 'N' || choose == 'n')
				{
					continueUpdating = false;
				}
			}
		}
		else
		{
			cout << "Menu ID not found." << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "------------------------------------------------------------------ " << endl;
	cout << "Press 'E' to return to MANAGE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageMenu();
	}
	else
	{
		exit(0);
	}
}
void deleteMenu()
{
	system("cls");
	char choose;
	string MenuID;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                        DELETE DRINK                     |" << endl;
	cout << "------------------------------------------------------------------" << endl;

	// Display menu items
	string retrieve_menu_query = "SELECT * FROM menu";
	const char* q = retrieve_menu_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res)
		{
			cout << "Menu ID" << setw(20) << "Drink" << setw(20) << "Price" << endl;
			while ((row = mysql_fetch_row(res)))
			{
				cout << setw(7) << row[0] << setw(20) << row[1] << setw(20) << row[2] << endl;
			}
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "Query Execution Problem! Error: " << mysql_error(conn) << endl;
		return;
	}

	// Prompt user to enter the Menu ID to delete
	cout << "Insert Menu ID to delete: ";
	cin >> MenuID;

	// Delete the menu item
	string delete_menu_query = "DELETE FROM menu WHERE MenuID = '" + MenuID + "'";
	const char* qW = delete_menu_query.c_str();
	qstate = mysql_query(conn, qW);

	if (!qstate)
	{
		cout << "Delete Successful!" << endl;
	}
	else
	{
		cout << "Query Execution Problem! Error: " << mysql_error(conn) << endl;
	}

	// Exit Code
	cout << "------------------------------------------------------------------ " << endl;
	cout << "Press 'E' to return to MANAGE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageMenu();
	}
	else
	{
		exit(0);
	}
}


	
//MANAGE MENU
void manageAdminMenu()
{
	system("cls");
	int optreg;

	cout << "------------------------------------------------------------------" << endl;
	cout << "|                             MANAGE ADMIN                             |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "1. PROFILE ADMIN " << endl;
	cout << "2. REGISTER ADMIN " << endl;
	cout << "3. UPDATE ADMIN " << endl;
	cout << "4. DELETE ADMIN " << endl;
	cout << "5. LIST ADMIN" << endl;
	cout << "6. BACK" << endl;
	cout << "" << endl;
	cout << "INSERT NUMBER : ";
	cin >> optreg;

	switch (optreg)
	{
	case 1:
		profileAdmin();
		break;
	case 2:
		registerAdmin();
		break;
	case 3:
		updateAdmin();
		break;
	case 4:
		deleteAdmin();
		break;
	case 5:
		listAdmin();
		break;
	case 6:
		mainMenu();
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
		manageAdminMenu();
		break;
	}
}
void manageEmployeeMenu()
{
	system("cls");
	int optreg;

	cout << "------------------------------------------------------------------" << endl;
	cout << "|                             MANAGE EMPLOYEE                             |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "1. REGISTER EMPLOYEE " << endl;
	cout << "2. UPDATE EMPLOYEE " << endl;
	cout << "3. DELETE EMPLOYEE " << endl;
	cout << "4. LIST EMPLOYEE" << endl;
	cout << "5. BACK" << endl;
	cout << "" << endl;
	cout << "INSERT NUMBER : ";
	cin >> optreg;

	switch (optreg)
	{
	case 1:
		registerEmployee();
		break;
	case 2:
		updateEmployee();
		break;
	case 3:
		deleteEmployee();
		break;
	case 4:
		listEmployee();
		break;
	case 5:
		mainMenu();
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
		manageEmployeeMenu();
		break;
	}
}
void manageCustomerMenu()
{
	system("cls");
	int optreg;

	cout << "------------------------------------------------------------------" << endl;
	cout << "|                              MANAGE CUSTOMER                               |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "1. LIST CUSTOMER " << endl;
	cout << "2. DELETE CUSTOMER " << endl;
	cout << "3. BACK" << endl;
	cout << "" << endl;
	cout << "INSERT NUMBER : ";
	cin >> optreg;

	switch (optreg)
	{
	case 1:
		listCustomer();
		break;
	case 2:
		deleteCustomer();
		break;
	case 3:
		mainMenu();
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
		manageCustomerMenu();
		break;
	}
}
void manageMenu()
{
	system("cls");
	int optreg;

	cout << "------------------------------------------------------------------" << endl;
	cout << "|                         DRINK MENU                             |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "1. ADD DRINK " << endl;
	cout << "2. UPDATE DRINK " << endl;
	cout << "3. DELETE DRINK " << endl;
	cout << "4. VIEW DRINK " << endl;
	cout << "5. BACK " << endl;
	cout << "" << endl;
	cout << "INSERT NUMBER : ";
	cin >> optreg;

	switch (optreg)
	{
	case 1:
		addMenu();
		break;
	case 2:
		updateMenu();
		break;
	case 3:
		deleteMenu();
		break;
	case 4:
		listMenu();
		break;
	case 5:
		mainMenu();
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
		manageMenu();
		break;
	}
}

//MAIN MENU
void mainMenu()
{
	system("cls");
	int menu;

	cout << "------------------------------------------------------------------" << endl;
	cout << "|                           MAIN MENU                             |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "1. MANAGE ADMIN " << endl;
	cout << "2. MANAGE EMPLOYEE " << endl;
	cout << "3. MANAGE CUSTOMER " << endl;
	cout << "4. MANAGE MENU " << endl;
	cout << "5. VIEW TRANSACTION " << endl;
	cout << "6. LOG OUT " << endl;
	cout << "" << endl;
	cout << "INSERT NUMBER : ";
	cin >> menu;

	switch (menu)
	{
	case 1:
		manageAdminMenu();
		break;
	case 2:
		manageEmployeeMenu();
		break;
	case 3:
		manageCustomerMenu();
		break;
	case 4:
		manageMenu();
		break;
	case 5:
		viewPayment();
		break;
	case 6:
		logout();
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
		mainMenu();
		break;
	}
}
void employeeMenu() {
	char choice;
	do
	{
		system("cls");
		cout << "------------------------------------------------------------------" << endl;
		cout << "|                         EMPLOYEE MENU                           |" << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "1. View Employee Profile" << endl;
		cout << "2. View Customer Orders" << endl;
		cout << "3. Logout" << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "Choose an option: ";
		cin >> choice;

		switch (choice)
		{
		case '1':
			profileEmployee();
			break;
		case '2':
			viewCustomerOrders();
			break;
		case '3':
			cout << "Logging Out....." << endl;
			mainlogin();
			break;
		default:
			cout << "Invalid option! Please try again." << endl;
			break;
		}
		cout << "\nPress any key to return to the menu...";
		cin.ignore();
		cin.get();

	} while (choice != '3');
}
void customerMenu()
{
	system("cls");
	int menu, optreg = 0;

	cout << "------------------------------------------------------------------" << endl;
	cout << "|                       CUSTOMER MENU                        |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "1. REGISTER CUSTOMER " << endl;
	cout << "2. LOGIN & PLACE ORDER " << endl;
	cout << "3. UPDATE CUSTOMER " << endl;
	cout << "4. PROFILE CUSTOMER " << endl;
	cout << "5. BACK " << endl;
	cout << "" << endl;
	cout << "INSERT NUMBER : ";
	cin >> menu;

	switch (menu)
	{
	case 1:
		registerCustomer();
		break;

	case 2:
		loginCustomer();
		break;

	case 3:
		updateCustomer();
		break;

	case 4:
		profileCustomer();
		break;
	case 5:
		mainlogin();
		break;
	}

}

//MANAGE EMPLOYEE MENU
void listEmployee()
{
	system("cls");
	char choose;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                  LIST EMPLOYEE                                         |" << endl;
	cout << " ---------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n";

	qstate = mysql_query(conn, "select * from employee");

	if (!qstate)
	{
		cout << setw(10) << "EmployeeID" << setw(20) << "username" << setw(20) << "Position" << setw(20) << "SalaryPerMonth" << setw(20) << "PhoneNo" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{

			cout << setw(10) << row[0] << setw(20) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[5] << endl;
			//cout << "\nEmployeeID: " << row[0] << "\tName: " << row[1] << "\tPhone No.: " << row[5];
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << endl;
	cout << endl;
	cout << "Press 'E to return to MANAGE EMPLOYEE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageEmployeeMenu();
	}
	else
	{
		exit(0);
	}
}
void registerEmployee()
{
	system("cls");
	string username, Position,SalaryPerMonth, Password, PhoneNo;
	char choose;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                      EMPLOYEE  REGISTRATION                    |" << endl;
	cout << "------------------------------------------------------------------" << endl;

	cin.ignore(1, '\n');

	cout << "Employee Username : ";
	cin >> username;

	cout << "Position. : ";
	cin >> Position;

	cout << "SalaryPerMonth : ";
	cin >> SalaryPerMonth;

	cout << "Password : ";
	cin >> Password;

	cout << "Phone No. : ";
	cin >> PhoneNo;

	string insert_query = "INSERT INTO employee (username, Position, SalaryPerMonth, Password, PhoneNo) VALUES ('" + username + "', '" + Position + "','" + SalaryPerMonth + "', '" + Password + "', '" + PhoneNo + "')";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added to database." << endl;
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'E' to return to MANAGE EMPLOYEE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageEmployeeMenu();
	}
	else
	{
		exit(0);
	}
}
void deleteEmployee()
{
	system("cls");
	char choose;
	string username;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                         DELETE EMPLOYEE                         |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	//string I;
	cout << "Insert Employee Username : ";
	cin >> username;

	string retrieve_employee_query = "SELECT * FROM employee WHERE username = '" + username + "'";
	const char* q = retrieve_employee_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (mysql_num_rows(res) > 0)
		{
			while (row = mysql_fetch_row(res))
			{
				cout << endl;
				cout << " Username : " << row[1] << endl;
				cout << " Position : " << row[2] << endl;
				cout << " SalaryPerMonth : " << row[3] << endl;
				cout << " Phone No : " << row[5] << endl;
			}

			string delete_employee_query = "DELETE FROM employee WHERE username = '" + username + "'";
			const char* qW = delete_employee_query.c_str();
			qstate = mysql_query(conn, qW);

			if (!qstate)
			{
				cout << "Delete Successful!" << endl;
			}
			else
			{
				cout << "Delete Unsuccessful!" << mysql_errno(conn) << endl;
			}
		}
		else
		{
			cout << "Username not found." << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "------------------------------------------------------------------ " << endl;
	cout << "Press 'E' to return MANAGE EMPLOYEE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageEmployeeMenu();
	}
	else
	{
		exit(0);
	}
}
void updateEmployee()
{
	system("cls");
	int optreg;
	char choose;
	string username;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                          UPDATE EMPLOYEE                       |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Insert Employee Username : ";
	cin >> username;

	string retrieve_employee_query = "SELECT * FROM employee WHERE username = '" + username + "'";
	const char* q = retrieve_employee_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (mysql_num_rows(res) > 0)
		{
			while (row = mysql_fetch_row(res))
			{
				cout << endl;
				cout << " Name : " << row[1] << endl;
				cout << " Position : " << row[2] << endl;
				cout << " SalaryPerMonth : " << row[3] << endl;
				cout << " Phone No. : " << row[5] << endl;
				cout << endl << endl;
			}

			bool continueUpdating = true;
			while (continueUpdating)
			{
				cout << "1. NAME. " << endl;
				cout << "2. POSITION. " << endl;
				cout << "3. SALARYPERMONTH. " << endl;
				cout << "4. PHONE NO. " << endl;
				cout << "5. PASSWORD " << endl;
				cout << "6. BACK " << endl;
				cout << "" << endl;
				cout << "CHOOSE OPTION (1-6) : ";
				cin >> optreg;

				string update_employee_query;
				switch (optreg)
				{
				case 1:
				{
					string updatename;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "NAME.: ";
					cin >> updatename;
					update_employee_query = "UPDATE employee SET username = '" + updatename + "' WHERE username = '" + username + "'";
					break;
				}
				case 2:
				{
					string updateposition;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "POSITION.: ";
					cin >> updateposition;
					update_employee_query = "UPDATE employee SET Position = '" + updateposition + "' WHERE username = '" + username + "'";
					break;
				}
				case 3:
				{
					string updatesalary;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "SALARYPERMONTH .: ";
					cin >> updatesalary;
					update_employee_query = "UPDATE employee SET SalaryPerMonth = '" + updatesalary + "' WHERE username = '" + username + "'";
					break;
				}
				case 4:
				{
					string updatephoneno;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "PHONE NO.: ";
					cin >> updatephoneno;
					update_employee_query = "UPDATE employee SET PhoneNo = '" + updatephoneno + "' WHERE username = '" + username + "'";
					break;
				}
				case 5:
				{
					string updatepassword;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "PASSWORD: ";
					cin >> updatepassword;
					update_employee_query = "UPDATE employee SET Password = '" + updatepassword + "' WHERE username = '" + username + "'";
					break;
				}
				case 6:
				{
					manageEmployeeMenu();
					return;
				}
				default:
				{
					cout << "Invalid option. Please choose again." << endl;
					continue;
				}
				}

				const char* q = update_employee_query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					cout << "Update Successful!" << endl;
				}
				else
				{
					cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
				}

				cout << "Do you want to update anything else? (Y/N): ";
				cin >> choose;
				if (choose == 'N' || choose == 'n')
				{
					continueUpdating = false;
				}
			}
		}
		else
		{
			cout << "Username not found." << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "------------------------------------------------------------------ " << endl;
	cout << "Press 'E' to return to MANAGE EMPLOYEE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageEmployeeMenu();
	}
	else
	{
		exit(0);
	}
}


//MANAGE CUSTOMER MENU
void profileCustomer()
{
	system("cls");
	char choose;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                           CUSTOMER                             |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	string username;
	cout << "Insert Customer Username : ";
	cin >> username;

	string retrieve_customer_query = "SELECT * FROM customer WHERE username = '" + username + "'";
	const char* q = retrieve_customer_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (mysql_num_rows(res) > 0)
		{
			while (row = mysql_fetch_row(res))
			{
				cout << endl;
				cout << " Customer ID : " << row[0] << endl;
				cout << " username : " << row[1] << endl;
				cout << " Phone No. : " << row[3] << endl;
			}
		}
		else
		{
			cout << "Username does not exist." << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << "Press 'E' to return to MANAGE CUSTOMER MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		customerMenu();
	}
	else
	{
		exit(0);
	}
}
void listCustomer()
{
	system("cls");
	char choose;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                  LIST CUSTOMER                                         |" << endl;
	cout << " ---------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n";

	qstate = mysql_query(conn, "select * from customer");

	if (!qstate)
	{
		cout << setw(10) << "CustomerID" << setw(20) << "username" << setw(20) << "PhoneNo" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{

			cout << setw(10) << row[0] << setw(20) << row[1] << setw(20) << row[3] << endl;
			//cout << "\nEmployeeID: " << row[0] << "\tName: " << row[1] << "\tPhone No.: " << row[5];
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << endl;
	cout << endl;
	cout << "Press 'E to return to MANAGE CUSTOMER MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageCustomerMenu();
	}
	else
	{
		exit(0);
	}
}
void deleteCustomer()
{
	system("cls");
	char choose;
	string username;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                         DELETE CUSTOMER                           |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Insert Customer Username : ";
	cin >> username;

	string retrieve_customer_query = "SELECT * FROM customer WHERE username = '" + username + "'";
	const char* q = retrieve_customer_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res)
		{
			if ((row = mysql_fetch_row(res)))
			{
				cout << endl;
				cout << " Username : " << row[1] << endl;
				cout << " Phone No. : " << row[3] << endl;
			}
			else
			{
				cout << "No customer found with the given username." << endl;
				mysql_free_result(res);
				return;
			}
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "Query Execution Problem! Error: " << mysql_error(conn) << endl;
		return;
	}

	string delete_customer_query = "DELETE FROM customer WHERE username = '" + username + "'";
	const char* qW = delete_customer_query.c_str();
	qstate = mysql_query(conn, qW);

	if (!qstate)
	{
		cout << "Delete Successful!" << endl;
	}
	else
	{
		cout << "Delete Unsuccessful! Error: " << mysql_error(conn) << endl;
	}

	// Exit Code
	cout << "------------------------------------------------------------------ " << endl;
	cout << "Press 'E' to return to MANAGE CUSTOMER MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		manageCustomerMenu();
	}
	else
	{
		exit(0);
	}
}



//CUSTOMER MENU
void registerCustomer()
{
	system("cls");
	string username, Password, PhoneNo;
	char choose;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                   CUSTOMER REGISTRATION                        |" << endl;
	cout << "------------------------------------------------------------------" << endl;

	cin.ignore(1, '\n');

	cout << "Customer Username : ";
	cin >> username;

	cout << "Password : ";
	cin >> Password;

	cout << "Phone No : ";
	cin >> PhoneNo;

	cin.ignore(1, '\n');

	string insert_query = "insert into customer (username, Password, PhoneNo) values('" + username + "','" + Password + "','" + PhoneNo + "')";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << " ";
	cout << "Press 'E' to return CUSTOMER MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		customerMenu();
	}
	else
	{
		exit(0);
	}
}

void updateCustomer() {
	system("cls");
	int optreg;
	char choose;
	string username, Password;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                          UPDATE CUSTOMER                       |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Enter your Username : ";
	cin >> username;
	cout << "Enter your Password : ";
	cin >> Password;

	// Check if the Username and Password match
	string checkUser_query = "SELECT CustomerID FROM customer WHERE username='" + username + "' AND Password='" + Password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate) {
		res = mysql_store_result(conn);
		if (res && (row = mysql_fetch_row(res))) {
			// Customer is authenticated, proceed with the update
			cout << "Authentication successful!" << endl;

			string retrieve_customer_query = "SELECT * FROM customer WHERE username = '" + username + "'";
			const char* q = retrieve_customer_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) {
				res = mysql_store_result(conn);
				if (res && (row = mysql_fetch_row(res))) {
					cout << endl;
					cout << " Username : " << row[1] << endl;
					cout << " Phone No. : " << row[3] << endl;
					cout << endl << endl;
				}
				else {
					cout << "Customer not found!" << endl;
					return;
				}
			}
			else {
				cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
				return;
			}

			bool continueUpdating = true;
			while (continueUpdating) {
				cout << "1. USERNAME" << endl;
				cout << "2. PHONE NO." << endl;
				cout << "3. PASSWORD" << endl;
				cout << "4. BACK" << endl;
				cout << "" << endl;
				cout << "CHOOSE OPTION (1-4) : ";
				cin >> optreg;

				string update_customer_query;
				switch (optreg) {
				case 1: {
					string updatename;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "USERNAME: ";
					cin >> updatename;
					update_customer_query = "UPDATE customer SET username = '" + updatename + "' WHERE username = '" + username + "'";
					break;
				}
				case 2: {
					string updatephoneno;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "PHONE NO.: ";
					cin >> updatephoneno;
					update_customer_query = "UPDATE customer SET PhoneNo = '" + updatephoneno + "' WHERE username = '" + username + "'";
					break;
				}
				case 3: {
					string updatepassword;
					cout << "------------------------------------------------------------------ " << endl;
					cout << "PASSWORD: ";
					cin >> updatepassword;
					update_customer_query = "UPDATE customer SET Password = '" + updatepassword + "' WHERE username = '" + username + "'";
					break;
				}
				case 4: {
					customerMenu();
					return;
				}
				default: {
					cout << "Invalid option. Please choose again." << endl;
					continue;
				}
				}

				const char* q = update_customer_query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate) {
					cout << "Update Successful!" << endl;
				}
				else {
					cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
				}

				cout << "Do you want to update anything else? (Y/N): ";
				cin >> choose;
				if (choose == 'N' || choose == 'n') {
					continueUpdating = false;
				}
			}

			// Exit Code
			cout << "------------------------------------------------------------------ " << endl;
			cout << "Press 'E' to return to CUSTOMER MENU: ";
			cin >> choose;
			if (choose == 'e' || choose == 'E') {
				customerMenu();
			}
			else {
				exit(0);
			}
		}
		else {
			char c;
			cout << "\nAuthentication failed. Want to try again? (y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
				updateCustomer();
			else
				logout();
		}
	}
	else {
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
		return;
	}
}

struct CartItem
{
	string MenuID;
	int quantity;
};


void placeorder() {
	system("cls");
	string OrderID;
	string CustomerID;
	string username;
	string MenuID;
	string OrderDate;
	double totalprice = 0.0; // Initialize total price
	int quantity;
	char choose;

	// Display the menu using the viewMenu function
	viewMenu();

	vector<CartItem> cart;  // Vector to store cart items

	int cartChoice;
	do {
		// Input order details
		cout << endl;
		cout << "\n";
		cout << "Enter the ID of the item you want to add to the cart: ";
		cin >> MenuID;
		cout << "Enter the quantity: ";
		cin >> quantity;

		// Add item to cart
		CartItem cartItem = { MenuID, quantity };
		cart.push_back(cartItem);

		cout << "\nItem added to the cart successfully!" << endl;

		// Ask if the customer wants to add more items to the cart
		cout << "\nDo you want to add more items to the cart? (1/0): ";
		cin >> cartChoice;
	} while (cartChoice == 1);

	// Display the items in the cart
	for (const auto& cartItem : cart) {
		string retrieve_menu_query = "SELECT * FROM menu WHERE MenuID = '" + cartItem.MenuID + "'";
		const char* q = retrieve_menu_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (row) {
				cout << "\n\t\t\t-----------CART ITEM DETAILS------------" << endl;

				// Check if the data in row[2] is a valid double
				try {
					double price = stod(row[2]);

					cout << " Menu ID: " << row[0] << endl;
					cout << " Drink Item: " << row[1] << endl;
					cout << " Price: RM " << price << endl;
					cout << " Quantity: " << cartItem.quantity << endl;

					// Calculate total price for each item in the cart
					double itemTotalPrice = cartItem.quantity * price;
					cout << " Total Price: RM " << itemTotalPrice << endl;

					totalprice += itemTotalPrice; // Add item's total price to the overall total price
				}
				catch (const std::invalid_argument& e) {
					cout << "\n\t\t\tInvalid price format for menu ID " << cartItem.MenuID << "." << endl;
				}
			}
			else {
				cout << "\n\t\t\tFailed to fetch menu details for menu ID " << cartItem.MenuID << "." << endl;
			}
		}
		else {
			cout << "\n\t\t\tFailed to fetch menu details for menu ID " << cartItem.MenuID << "." << endl;
		}
	}

	// Input customer details
	cout << "Enter the customer username: ";
	cin.ignore();
	getline(cin, username);

	// Get the CustomerID based on the username
	string get_customer_query = "SELECT CustomerID FROM customer WHERE username = '" + username + "'";
	const char* q_get_customer = get_customer_query.c_str();
	qstate = mysql_query(conn, q_get_customer);

	if (!qstate) {
		res = mysql_store_result(conn);
		if (res && mysql_num_rows(res) > 0) {
			row = mysql_fetch_row(res);
			CustomerID = row[0]; // Ensure that CustomerID is correctly assigned
		}
		else {
			cout << "Customer not found." << endl;
			return; // Handle the case where the customer is not found
		}
	}
	else {
		cout << "Failed to retrieve customer. Error: " << mysql_error(conn) << endl;
		return; // Handle the failure to retrieve customer
	}

	// Get current date and time
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	// Format the date as YYYY-MM-DD HH:MM:SS
	char formattedDate[20];
	strftime(formattedDate, sizeof(formattedDate), "%Y-%m-%d %H:%M:%S", &ltm);
	OrderDate = formattedDate;

	for (const auto& cartItem : cart) {
		// Retrieve the price for the current menu item
		string retrieve_menu_query = "SELECT price FROM menu WHERE MenuID = '" + cartItem.MenuID + "'";
		const char* q = retrieve_menu_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (row) {
				try {
					double price = stod(row[0]);
					double itemTotalPrice = cartItem.quantity * price;

					string orders_query = "INSERT INTO orders(MenuID, OrderDate, quantity, total, CustomerID) VALUES ('" + cartItem.MenuID + "', '" + OrderDate + "'," + to_string(cartItem.quantity) + "," + to_string(itemTotalPrice) + ",'" + CustomerID + "')";
					const char* qorders = orders_query.c_str();

					// Use a different variable for each query result
					int orders_qstate = mysql_query(conn, qorders);

					if (orders_qstate) {
						cout << "\n\t\t\tFailed to place the order for item with menu ID " << cartItem.MenuID << "." << endl;
						system("pause");
						return; // Handle the failure, you may want to return or prompt the user again
					}
				}
				catch (const std::invalid_argument& e) {
					cout << "\n\t\t\tInvalid price format for menu ID " << cartItem.MenuID << "." << endl;
				}
			}
			else {
				cout << "\n\t\t\tFailed to fetch menu details for menu ID " << cartItem.MenuID << "." << endl;
			}
		}
		else {
			cout << "\n\t\t\tFailed to fetch menu details for menu ID " << cartItem.MenuID << "." << endl;
		}
	}

	cout << "\n\t\t\tOrder Placed Successfully!" << endl;
	cout << "Total Price: RM " << totalprice << endl; // Display total price
	system("pause");
	customerPayment(totalprice);
}



void viewMenu()
{
	system("cls");
	char choose;
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                              VIEW MENU                                                    |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n";

	qstate = mysql_query(conn, "select * from menu");

	if (!qstate)
	{
		cout << setw(20) << "Menu ID" << setw(40) << "Drink" << setw(20) << "Price" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(40) << row[1] << setw(20) << row[2] << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}






//EMPLOYEE MENU
void profileEmployee()
{
	system("cls");
	char choose;
	cout << "------------------------------------------------------------------" << endl;
	cout << "|                          PROFILE EMPLOYEE                      |" << endl;
	cout << "------------------------------------------------------------------" << endl;
	string username;
	cout << "Insert Employee Username : ";
	cin >> username;

	string retrieve_employee_query = "SELECT * FROM employee WHERE username = '" + username + "'";
	const char* q = retrieve_employee_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (mysql_num_rows(res) > 0)
		{
			while (row = mysql_fetch_row(res))
			{
				cout << endl;
				cout << " Employee ID:  " << row[0] << endl;
				cout << " Name : " << row[1] << endl;
				cout << " Position : " << row[2] << endl;
				cout << " SalaryPerMonth : " << row[3] << endl;
				cout << " Phone No. : " << row[5] << endl;
			}
		}
		else
		{
			cout << "Username not found." << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Exit Code
	cout << " ";
	cout << "Press 'E' to return to EMPLOYEE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		employeeMenu();
	}
	else
	{
		exit(0);
	}
}
void viewCustomerOrders()
{
	system("cls");
	char choose;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                  CUSTOMERS ORDERS                                       |" << endl;
	cout << " ---------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n";

	qstate = mysql_query(conn, "select * from orders");

	if (!qstate)
	{
		cout << left << setw(10) << "OrderID" << setw(20) << "MenuID" << setw(15) << "quantity" << setw(15) << "Total" << setw(20) << "OrderDate" << setw(15) << "CustomerID" << endl;

		res = mysql_store_result(conn);
		if (res) {
			while ((row = mysql_fetch_row(res))) {
				cout << left << setw(10) << row[0] << setw(20) << row[1] << setw(15) << row[2] << setw(15) << row[3] << setw(20) << row[4] << setw(15) << row[5] << endl;
				//cout << "\nEmployeeID: " << row[0] << "\tName: " << row[1] << "\tPhone No.: " << row[5];
			}
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << endl;
	cout << "Press 'E to return to EMPLOYEE MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E')
	{
		employeeMenu();
	}
	else
	{
		exit(0);
	}
}


//LOGIN SECTION
void loginAdmin()
{
	system("cls");
	string username;
	string password;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "|                    COFFEE SHOP MANAGEMENT SYSTEM                 |" << endl;
	cout << "-------------------------------------------------------------------" << endl;

	cout << "ENTER USERNAME : ";
	cin >> username;

	cout << "ENTER PASSWORD : ";

	char ch;
	while ((ch = _getch()) != 13)
	{
		password += ch;
		cout << '*';
	}

	string checkUser_query = "SELECT Username from admin where Username='" + username + "' AND password = '" + password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			while (row = mysql_fetch_row(res))
				username = row[0];
			mainMenu();
		}
		else
		{
			char c;
			cout << "\nInvalid username or password. Want to try again? (y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
				loginAdmin();
			else
				logout();
		}
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}
}

void loginEmployee()
{
	system("cls");
	string username;
	string password;

	cout << "-------------------------------------------------------------------" << endl;
	cout << "|                    COFFEE SHOP MANAGEMENT SYSTEM                  |" << endl;
	cout << "-------------------------------------------------------------------" << endl;

	cout << "ENTER USERNAME : ";
	cin >> username;

	cout << "ENTER PASSWORD : ";

	char ch;
	while ((ch = _getch()) != 13)
	{
		password += ch;
		cout << '*';
	}

	string checkUser_query = "SELECT EmployeeID from employee where username='" + username + "' AND  password = '" + password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			while (row = mysql_fetch_row(res))
				username = row[0];
			employeeMenu();
		}
		else
		{
			char c;
			cout << "\nInvalid username or password. Want to try again? (y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
				loginEmployee();
			else
				logout();
		}
	}
	else
	{
		cout << " Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void loginCustomer()
{
	system("cls");
	string username;
	string Password;

	cout << "-------------------------------------------------------------------" << endl;
	cout << "|                    COFFEE SHOP ORDERING SYSTEM                   |" << endl;
	cout << "-------------------------------------------------------------------" << endl;

	cout << "ENTER USERNAME : ";
	cin >> username;


	cout << "ENTER PASSWORD : ";

	char ch;
	while ((ch = _getch()) != 13)
	{
		Password += ch;
		cout << '*';
	}

	string checkUser_query = "SELECT CustomerID from customer where username='" + username + "' AND  Password = '" + Password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			while (row = mysql_fetch_row(res))
				username = row[0];
			placeorder();
		}
		else
		{
			char c;
			cout << "\nInvalid username or password. Want to try again? (y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
				loginCustomer();
			else
				logout();
		}
	}
	else

		cout << " Quert Execution Problem!" << mysql_errno(conn) << endl;
}



//LOGIN LOGOUT MENU
void logout()
{
	system("cls");
	cin.ignore(1, '\n');
	mainlogin();
}
void mainlogin()
{
	system("cls");
	system("title workshop_1");
	db_response::ConnectionFunction();
	system("Color 75");

	cout << "\n\t\t\t\t\t\t\t  COFFEE SHOP MANAGEMENT SYSTEM " << endl;
	cout << "\t\t\t\t\t**********************************************************\n" << endl;
	cout << "\t\t\t\t\t\tChoose your role to login -> " << endl;
	cout << "\t\t\t\t\t\t1. Admin" << endl;
	cout << "\t\t\t\t\t\t2. Employee" << endl;
	cout << "\t\t\t\t\t\t3. Customer" << endl;
	cout << "\t\t\t\t\t\tRole: ";
	cin >> userRole;

	switch (userRole)
	{
	case 1:
		loginAdmin();
		break;
	case 2:
		loginEmployee();
		break;
	case 3:
		customerMenu();
		break;
	default:
		cout << "Please choose between 1 - 3. Press Enter To Continue...";

		system("cls");
		main();
		break;
	}
	return;
}



void viewPayment() {
	system("cls");
	char choose;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "|                                                  PAYMENT DETAILS                                       |" << endl;
	cout << " ---------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n";

	qstate = mysql_query(conn, "SELECT * FROM payment");

	if (!qstate) {
		cout << left << setw(15) << "PaymentID" << setw(10) << "CustomerID"  << setw(10) << "total" << setw(20) << "paymentdate" << endl;

		res = mysql_store_result(conn);
		if (res) {
			while ((row = mysql_fetch_row(res))) {
				cout << left << setw(15) << row[0] << setw(10) << row[1] << setw(10) << row[2] << setw(20) << row[3] << endl;
			}
		}
		mysql_free_result(res);
	}
	else {
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
	}

	cout << endl;
	cout << "Press 'E' to return to MAIN MENU: ";
	cin >> choose;
	if (choose == 'e' || choose == 'E') {
		mainMenu();
	}
	else {
		exit(0);
	}
}
void customerPayment(double totalprice) {
	while (true) {
		system("cls");
		string username;
		string CustomerID;  // Assuming CustomerID is obtained from the placed order

		cout << "----------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                       SELECT YOUR PAYMENT TYPE                                         |" << endl;
		cout << " ---------------------------------------------------------------------------------------------------------" << endl;
		cout << "\n";
		cout << "\n\t\t\t\t===============================";
		cout << "\n\n\t\t\t [1] ONLINE BANKING" << endl;
		cout << "\n\n\t\t\t [2] CARD" << endl;
		cout << "\n\t\t\t\t===============================";
		cout << "\n\t\t\t\tPlease Enter Your Choice (1/2): ";
		int m;
		cin >> m;

		if (m < 1 || m > 2) {
			cout << "Please choose between 1 and 2!!!" << endl;
			continue;
		}

		cin.ignore();

		string bankName, bankAccount, cardNumber, cvv;

		if (m == 1) {
			cout << "\n\t\t\t\tEnter your Bank Name: ";
			getline(cin, bankName);
			cout << "\n\t\t\t\tEnter your Bank Account: ";
			getline(cin, bankAccount);
		}
		else if (m == 2) {
			cout << "\n\t\t\t\tEnter your Card Number: ";
			getline(cin, cardNumber);
			cout << "\n\t\t\t\tEnter your CVV: ";
			getline(cin, cvv);
		}

		// Get the username
		cout << "Enter your username: ";
		getline(cin, username);

		// Get the CustomerID based on the username
		string get_customer_query = "SELECT CustomerID FROM customer WHERE username = '" + username + "'";
		qstate = mysql_query(conn, get_customer_query.c_str());
		if (!qstate) {
			res = mysql_store_result(conn);
			if (res && mysql_num_rows(res) > 0) {
				row = mysql_fetch_row(res);
				CustomerID = row[0]; // Ensure that CustomerID is correctly assigned
			}
			else {
				cout << "Customer not found." << endl;
				// Handle the case where the customer is not found
				continue;
			}
		}
		else {
			cout << "Failed to retrieve customer. Error: " << mysql_error(conn) << endl;
			// Handle the failure to retrieve customer
			continue;
		}

		// Display payment details in the receipt
		cout << "\n\t\t\t--------------- RECEIPT ---------------" << endl;
		cout << "\n\t\t\t" << setw(20) << left << "Username:" << username << endl;
		cout << "\n\t\t\t" << setw(20) << left << "CustomerID:" << CustomerID << endl;
		cout << "\n\t\t\t" << setw(20) << left << "Total Payment:" << "RM " << totalprice << endl;
		cout << "\n\t\t\t----------------------------------------" << endl;

		// Insert into the payment table
		string payment_query = "INSERT INTO payment(CustomerID, total, paymentdate) VALUES ('" + CustomerID + "', '" + to_string(totalprice) + "', NOW())";
		qstate = mysql_query(conn, payment_query.c_str());

		if (qstate) {
			cout << "\n\t\t\tPayment Unsuccessful. Please try again." << endl;
			system("pause");
			continue;
		}

		cout << "\n\t\t\t\t YOUR PAYMENT IS SUCCESSFUL!!!" << endl;

		int option;

		cout << "\t\t\t\t[1] Order again" << endl;
		cout << "\t\t\t\t[2] Back to Menu" << endl;
		cout << "\n\t\t\t\tPlease Enter Your Choice (1/2): ";
		cin >> option;

		if (option == 1) {
			placeorder();
			// Loop will continue, allowing the user to make another payment
			continue;
		}
		else if (option == 2) {
			// Call your customerMenu function here
			customerMenu();
			break;
		}
		else {
			cout << "Invalid choice. Please select a valid option." << endl;
			continue;
		}
	}
}


