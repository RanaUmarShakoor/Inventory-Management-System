#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int FACULTY_MEMBERS = 56;
const int MAX_NAME_CHAR = 50;
const int NUMBER_ITEMS = 50;

struct Allocated_to
{
	char name[MAX_NAME_CHAR];
};


struct InventoryItem
{
	bool isFilled = 0;
	char Name[MAX_NAME_CHAR];
	int Item_ID;
	char category[15];
	int Item_count;
	Allocated_to assigned_to[FACULTY_MEMBERS];
};

void Menu();
void Add_Item(InventoryItem item[NUMBER_ITEMS]);
void View_Item(InventoryItem item[NUMBER_ITEMS]);




int main()
{

	InventoryItem* item = new InventoryItem[NUMBER_ITEMS];
	int choice = 0;

	cout << "****** Inventory Management System *******" << endl;
	Menu();

	while (choice != 9)
	{
		cout << "Your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			Add_Item(item);
			break;
		}
		case 2:
		{
			View_Item(item);
			break;
		}
		case 3:
		{

		}
		case 4:
		{

		}

		case 5:
		{

		}
		case 6:
		{

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

void Add_Item(InventoryItem item[NUMBER_ITEMS])
{
	static int count = 0;

	cout << "Enter item: ";
	cin.ignore();
	cin.getline(item[count].Name, MAX_NAME_CHAR);

	while (1)
	{
		cout << "Enter item_ID: ";
		cin >> item[count].Item_ID;

		if (item[count].Item_ID > 0)
		{
			break;
		}

		cout << "Invalid item_ID entered. Please re-enter." << endl;
	}


	while (1)
	{
		cout << "Enter Number of items: ";
		cin >> item[count].Item_count;

		if (item[count].Item_count >= 0)
		{
			break;
		}

		cout << "Invalid number of items entered. Please re-enter." << endl;
	}


	cout << "Enter category: ";
	cin.ignore();
	cin.getline(item[count].category, 15);

	item[count].isFilled = 1;
	cout << "Item added." << endl;
}

void View_Item(InventoryItem item[NUMBER_ITEMS])
{
	cout << setw(7) << "ID" << setw(15) << "Category" << '\t' << left << setw(50) << "Item Name" << right << setw(15) << "Count" << endl;
	for (int i = 0; i < NUMBER_ITEMS; i++)
	{
		if (item[i].isFilled == 1)
		{
			cout << setw(7) << item[i].Item_ID << setw(15) << item[i].category << '\t' << left << setw(50) << item[i].Name << right << setw(15) << item[i].Item_count << endl;
		}
	}
}