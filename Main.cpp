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
	int Item_count;
	int AssignedItems = 0;
	Allocated_to assigned_to[FACULTY_MEMBERS];
};



void Menu();
void Add_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void View_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void Edit_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void Delete_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);
void Assign_item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS]);





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
			Assign_item(item, list_isFilled);
			break;

		}
		case 7:
		{

		}
		case 8:
		{

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

	//Checks the list to find an empty node in the array
	for (int i = 0; i < FACULTY_MEMBERS; i++)
	{
		if (list_isFilled[i] == 0)
		{
			count = i;
			break;
		}
	}

	//Taking input info for the date
	cout << "Enter item: ";
	cin.ignore();
	cin.getline(item[count].Name, MAX_NAME_CHAR);

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
	cout << "Enter category: ";
	cin.getline(item[count].category, 15);

	//Updating the items list
	list_isFilled[count] = 1;
	cout << "Item added." << endl << endl;
}

//View inventory items
void View_Item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	cout << setw(7) << "ID" << setw(15) << "Category" << '\t' << left << setw(50) << "Item Name" << right << setw(15) << "Count" << endl;
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
	//GEtting input for ID from the user and validating  it
	int index = Search_ID(item, list_isFilled);

	cout << endl << "Enter new item: ";
	cin.getline(item[index].Name, MAX_NAME_CHAR);

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
	cout << "Enter category: ";
	cin.getline(item[index].category, 15);

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
	item[index].AssignedItems = 0;

	cout << "Item deleted successfully..." << endl;
}

void Assign_item(InventoryItem item[NUMBER_ITEMS], bool list_isFilled[NUMBER_ITEMS])
{
	int index = 0, assignee = 0, allocatedItems = 0;
	//Getting ID from the user and validating it
	index = Search_ID(item, list_isFilled);
	
	for (int i = 0; i < FACULTY_MEMBERS; i++)
	{
		if (item[index].assigned_to[i].allocated_items == 0)
		{
			assignee = i;
			break;
		}
	}


	cout << "Enter the person's name: ";
	cin.getline(item[index].assigned_to[assignee].name, MAX_NAME_CHAR);

	while (1)
	{
		cout << "Enter the number of items you want to assign (in stock: " << item[index].Item_count << ") : ";
		cin >> allocatedItems;

		if (allocatedItems <= item[index].Item_count)
		{
			item[index].Item_count -= allocatedItems;
			item[index].assigned_to[assignee].allocated_items = allocatedItems;
			break;
		}
		cout << "Invalid number of items entered. Please re-enter." << endl;
	}

	cout <<"(" << (allocatedItems) << ") items assigned to " << item[index].assigned_to[assignee].name << endl << endl;
}