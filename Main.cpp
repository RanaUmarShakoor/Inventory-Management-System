#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

const int FACULTY_MEMBERS = 56;
const int MAX_NAME_CHAR = 50;
const int NUMBER_ITEMS = 50;

struct Allocated_to
{
	int allocated_items = 0;
	char name[MAX_NAME_CHAR];
};

struct InventoryItem
{
	char Name[MAX_NAME_CHAR];
	int Item_ID;
	char category[15];
	int Item_count=0;
	int allocatedItems=0;
	Allocated_to assigned_to[FACULTY_MEMBERS];
};


void Menu();
void Add_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void View_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void Edit_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void Delete_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void Assign_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void Retrieve_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void List_Assigned_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);



int main()
{
	bool list_isFilled[NUMBER_ITEMS] = { 0 };
	InventoryItem* item = new InventoryItem[NUMBER_ITEMS];
	int choice = 0;


	cout << "****** Inventory Management System *******" << endl;
	Menu();

	while (choice != 9)
	{
		cout << "Your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
		{
			Add_Item(item, list_isFilled);
			break;
		}
		case 2:
		{
			View_Item(item, list_isFilled);
			break;
		}
		case 3:
		{
			Edit_Item(item, list_isFilled);
			break;
		}
		case 4:
		{

			break;
		}

		case 5:
		{
			Delete_Item(item, list_isFilled);
			break;
		}
		case 6:
		{
			Assign_Item(item, list_isFilled);
			break;

		}
		case 7:
		{
			Retrieve_Item(item, list_isFilled);
			break;
		}
		case 8:
		{
			List_Assigned_Item(item, list_isFilled);
			break;
		}
		case 9:
		{
			cout << "Exiting..." << endl;
			return 0;
		}

		default:
		{
			cout << "Invalid choice entered. Please re-enter a valid choice." << endl;
		}

		}

	}

}

int Number_valid()
{
	char Number[8];
	int num = 0;

	cin.getline(Number, 8);
	bool isTrue = 1;

	for (int i = 0; i < strlen(Number); i++)
	{
		if (!isdigit(Number[i]))
		{
			isTrue = 0;
			break;
		}
	}

	if (isTrue)
	{
		num = atoi(Number);
		return num;
	}
	else
		return -1;

}

int Search_ID(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	int userID = 0, index = 0;
	bool isFound = 0;
	cin.ignore();

	while (1)
	{
		//Taking ID from user
		cout << "Enter item ID: ";
		userID = Number_valid();

		//Checking if the item of entered ID exist
		for (int i = 0; i < NUMBER_ITEMS; i++)
		{
			if (list_isFilled[i] == 1)
			{
				if (item[i].Item_ID == userID)
				{
					index = i;
					isFound = 1;
					break;
				}
			}
		}

		if (isFound)
		{
			return index;
			break;
		}
		else
		{
			cout << "Any item with the entered ID doesn't exist. Please enter a valid ID." << endl;
		}
	}
}




//Display the menu
void Menu()
{
	;
	cout << endl;
	cout << "1) Add inventory items " << endl
		<< "2) View all inventory items" << endl
		<< "3) Search inventory items" << endl
		<< "4) Edit inventory item" << endl
		<< "5) Delete inventory item" << endl
		<< "6) Assign inventory item" << endl
		<< "7) Retrieve inventory item" << endl
		<< "8) View list of faculty members who have borrowed a specific item" << endl
		<< "9) Exit" << endl;
}

//Add inventory item
void Add_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	int count = 0;
	char username[50];

	//Checks the list to find an empty node in the array
	for (int i = 0; i < FACULTY_MEMBERS; i++)
	{
		if (list_isFilled[i] == 0)
		{
			count = i;
			break;
		}
	}


	cin.ignore();
	//Taking input info for the date
	while (1)
	{
		cout << "Enter item: ";
		cin.getline(username, MAX_NAME_CHAR);

		if (isalpha(username[0]))
		{
			strcpy_s(item[count].Name, MAX_NAME_CHAR, username);
			break;
		}
		else
			cout << "Please enter a valid name." << endl;
	}
	

	//Taking valid input for Item ID
	while (1)
	{
		cout << "Enter item_ID: ";
		item[count].Item_ID = Number_valid();
		if (item[count].Item_ID > 0)
		{
			break;
		}
		cout << "Invalid item_ID entered. Please re-enter." << endl;
	}
	

	//Taking input for item_count
	while (1)
	{
		cout << "Enter Number of items: ";
		item[count].Item_count = Number_valid();
		if (item[count].Item_count >= 0)
		{
			break;
		}
		cout << "Invalid number of items entered. Please re-enter." << endl;
	}

	//Taking input for item_category
	while (1)
	{
		cout << "Enter category: ";
		cin.getline(username, MAX_NAME_CHAR);

		if (isalpha(username[0]))
		{
			strcpy_s(item[count].category, MAX_NAME_CHAR, username);
			break;
		}
		else
			cout << "Please enter a valid category." << endl;
	}

	//Updating the items list
	list_isFilled[count] = 1;
	cout << "Item added." << endl << endl;
}

//View inventory items
void View_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	cout << setw(7) << "ID" << setw(15) << "Category" << '\t' << left << setw(50) << "Item Name" << right << setw(15) << "Count" << endl;
	cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;
	for (int i = 0; i < NUMBER_ITEMS; i++)
	{
		//CHecking the list to find filled space and displaying that item
		if (list_isFilled[i] == 1)
		{
			cout << setw(7) << item[i].Item_ID << setw(15) << item[i].category << '\t' << left << setw(50) << item[i].Name << right << setw(15) << item[i].Item_count << endl;
		}
	}

	cout << endl << endl;
}

//Edit inventory items
void Edit_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	char username[50];
	//GEtting input for ID from the user and validating  it
	int index = Search_ID(item, list_isFilled);

	cout << endl << "Enter new item: ";
	while (1)
	{
		cout << "Enter new item: ";
		cin.getline(username, MAX_NAME_CHAR);

		if (isalpha(username[0]))
		{
			strcpy_s(item[index].Name, MAX_NAME_CHAR, username);
			break;
		}
		else
			cout << "Please enter a valid name." << endl;
	}

	//Taking valid input for Item ID
	while (1)
	{
		cout << "Enter new item_ID: ";
		item[index].Item_ID = Number_valid();
		if (item[index].Item_ID > 0)
		{
			break;
		}
		cout << "Invalid item_ID entered. Please re-enter." << endl;
	}


	//Taking input for item_count
	while (1)
	{
		cout << "Enter Number of items: ";
		item[index].Item_count = Number_valid();
		if (item[index].Item_count >= 0)
		{
			break;
		}
		cout << "Invalid number of items entered. Please re-enter." << endl;
	}

	//Taking input for item_category
	while (1)
	{
		cout << "Enter category: ";
		cin.getline(username, MAX_NAME_CHAR);

		if (isalpha(username[0]))
		{
			strcpy_s(item[index].category, MAX_NAME_CHAR, username);
			break;
		}
		else
			cout << "Please enter a valid category." << endl;
	}

	cout << "Item is Edited." << endl << endl;
}

//Delete inventory items
void Delete_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	int index = 0;
	//Getting ID from the user and validating it
	index = Search_ID(item, list_isFilled);

	//DELETING
	list_isFilled[index] = 0;
	item[index].Item_ID = 0;
	item[index].allocatedItems = 0;

	cout << "Item deleted successfully..." << endl;
}

//Assign inventory item
void Assign_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	char username[50];
	int index = 0, assignee = 0, allocatedItems = 0;
	//Getting ID from the user and validating it
	index = Search_ID(item, list_isFilled);

	//Checking if any item is in STOCK (if no: exiting)
	if (item[index].Item_count <= 0)
	{
		cout << "No item in STOCK. Can't assign." << endl;
		return;
	}


	for (int i = 0; i < FACULTY_MEMBERS; i++)
	{
		if (item[index].assigned_to[i].allocated_items == 0)
		{
			assignee = i;
			break;
		}
	}


	while (1)
	{
		cout << "Enter the person's name: ";
		cin.getline(username, MAX_NAME_CHAR);

		if (isalpha(username[0]))
		{
			strcpy_s(item[index].assigned_to[assignee].name, MAX_NAME_CHAR, username);
			break;
		}
		else
			cout << "Please enter a valid name." << endl;
	}

	while (1)
	{
		cout << "Enter the number of items you want to assign (in stock: " << item[index].Item_count << ") : ";
		cin >> allocatedItems;

		if (allocatedItems <= item[index].Item_count && allocatedItems>=0)
		{
			item[index].Item_count -= allocatedItems;
			item[index].allocatedItems += allocatedItems;
			item[index].assigned_to[assignee].allocated_items = allocatedItems;
			break;
		}
		cout << "Invalid number of items entered. Please re-enter." << endl;
	}

	cout <<"(" << (allocatedItems) << ") items assigned to " << item[index].assigned_to[assignee].name << endl << endl;
}

void Retrieve_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	int index = 0, assignee = 0, returnedItems = 0;
	char userName[MAX_NAME_CHAR];
	bool isFound = 0;

	//Getting ID from the user and validating it
	index = Search_ID(item, list_isFilled);

	if (item[index].allocatedItems <= 0)
	{
		cout << "No item is ASSIGNED. Can't retrieve." << endl;
		return;
	}

	while (1)
	{
		cout << "Enter the person's name: ";
		cin.getline(userName, MAX_NAME_CHAR);

		for (int i = 0; i < FACULTY_MEMBERS; i++)
		{
			if (item[index].assigned_to[i].allocated_items > 0)
			{
				if (strcmp(userName, item[index].assigned_to[i].name) == 0)
				{
					isFound = 1;
					assignee = i;
					break;
				}

			}
		}

		if (isFound == 1)
		{
			break;
		}
		else
			cout << "Person not found. Please re-enter." << endl;

	}
	


	while (1)
	{
		cout << "Enter the number of items retrieved (in stock: " << item[index].assigned_to[assignee].allocated_items << ") : ";
		cin >> returnedItems;

		if (returnedItems <= item[index].assigned_to[assignee].allocated_items && returnedItems>=0)
		{
			item[index].Item_count += returnedItems;
			item[index].allocatedItems -= returnedItems;
			item[index].assigned_to[assignee].allocated_items -= returnedItems;
			break;
		}
		cout << "Invalid number of items entered. Please re-enter." << endl;
	}

	cout << "(" << (returnedItems) << ") items retrieved from " << item[index].assigned_to[assignee].name << endl << endl;
}

void List_Assigned_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	int index = 0;
	//Getting ID from the user and validating it
	index = Search_ID(item, list_isFilled);

	//Checking if any item is assigned
	if (item[index].allocatedItems <= 0)
	{
		cout << "No item is ASSIGNED." << endl;
		return;
	}

	//Displaying the list of persons who borrowed the item
	cout  << left << setw(50) << "Name" << setw(8) << "Number of Items" << endl;
	cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
	for (int i = 0; i < FACULTY_MEMBERS; i++)
	{
		if (item[index].assigned_to[i].allocated_items > 0)
		{
			cout << setw(50) << item[index].assigned_to[i].name << setw(8) << item[index].assigned_to[i].allocated_items << endl;
		}
	}
}