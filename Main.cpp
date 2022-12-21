#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

// ********** Global Variables  ********** 
const int FACULTY_MEMBERS = 56;
const int MAX_NAME_CHAR = 50;
const int NUMBER_ITEMS = 10;


// ********** Structures  ********** 
struct Allocated_to
{
	int allocated_items = 0;
	char name[MAX_NAME_CHAR];
};

struct InventoryItem
{
	bool isFilled = 0;
	char Name[MAX_NAME_CHAR];
	int Item_ID;
	char category[15];
	int Item_count = 0;
	int allocatedItems = 0;
	Allocated_to assigned_to[FACULTY_MEMBERS];
};


// ********** Functions Prototypes  ********** 
void Name_valid(char arr[MAX_NAME_CHAR]);
void Item_valid(char arr[MAX_NAME_CHAR]);
void Category_valid(char arr[15]);
void File();
void File_read(InventoryItem item[NUMBER_ITEMS]);
void File_write(InventoryItem item[NUMBER_ITEMS]);


//System's functions
void Menu();
void Add_Item(InventoryItem item[NUMBER_ITEMS]);
void View_Item(InventoryItem item[NUMBER_ITEMS]);
void Search_Item(InventoryItem item[NUMBER_ITEMS]);
void Edit_Item(InventoryItem item[NUMBER_ITEMS]);
void Delete_Item(InventoryItem item[NUMBER_ITEMS]);
void Assign_Item(InventoryItem item[NUMBER_ITEMS]);
void Retrieve_Item(InventoryItem item[NUMBER_ITEMS]);
void List_Assigned_Item(InventoryItem item[NUMBER_ITEMS]);

int main()
{
	bool list_isFilled[NUMBER_ITEMS] = { 0 };
	InventoryItem* item = new InventoryItem[NUMBER_ITEMS];
	int choice = 0;

	File();
	File_read(item);

	cout << "****** Inventory Management System *******" << endl;
	Menu();

	while (1)
	{
		cout << "Your choice: ";
		cin >> choice;
		cout << endl;

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
			Search_Item(item);
			break;
		}
		case 4:
		{
			Edit_Item(item);
			break;
		}

		case 5:
		{
			Delete_Item(item);
			break;
		}
		case 6:
		{
			Assign_Item(item);
			break;

		}
		case 7:
		{
			Retrieve_Item(item);
			break;
		}
		case 8:
		{
			List_Assigned_Item(item);
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

		if(choice != 2 && choice != 3 && choice != 8)
			File_write(item);
	}
}


//****************************************  Functions  ****************************************

//For number validation - Do not accept a character
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

//String Validations
void Item_valid(char arr[MAX_NAME_CHAR])
{
	while (1)
	{
		cout << "Enter Item: ";
		cin.getline(arr, MAX_NAME_CHAR);

		//If the first character is Alphanum - break
		if (isalnum(arr[0]))
		{
			break;
		}
		else
		{
			cout << "Invalid input. Please re-enter a valid name." << endl;
		}
	}
}

void Name_valid(char arr[MAX_NAME_CHAR])
{
	while (1)
	{
		cout << "Enter name: ";
		cin.getline(arr, MAX_NAME_CHAR);

		//If the first character is Alphanum - break
		if (isalnum(arr[0]))
		{
			break;
		}
		else
		{
			cout << "Invalid input. Please re-enter a valid name." << endl;
		}
	}
}

void Category_valid(char arr[15])
{
	while (1)
	{
		cout << "Enter category: ";
		cin.getline(arr, 15);

		//If the first character is Alphanum - break
		if (isalnum(arr[0]))
		{
			break;
		}
		else
		{
			cout << "Invalid input. Please re-enter a valid category name." << endl;
		}
	}
}


//File creation or (if exist) do nothing
void File()
{
	ofstream fout("Inventory_item_data.bin", ios::binary | ios::app);
	if (fout)
	{
		fout.close();
	}
	else
	{
		cout << "File was not opened." << endl;
	}

}

//File Reading
void File_read(InventoryItem item[NUMBER_ITEMS])
{
	ifstream fin("Inventory_item_data.bin", ios::binary);
	if (fin)
	{

		fin.seekg(0, ios::end);
		int size = fin.tellg();
		fin.seekg(0, ios::beg);
		for (int i = 0; i <= size / sizeof(item[0]); i++)
		{
			fin.read(reinterpret_cast<char*>(&item[i]), sizeof(item[0]));
		}
		fin.clear();
		fin.close();
	}
	else
	{
		cout << "File was not opened. Couldn't read it." << endl;
	}

}

//File Writing
void File_write(InventoryItem item[NUMBER_ITEMS])
{
	ofstream fout("Inventory_item_data.bin", ios::binary);
	if (fout)
	{

		fout.seekp(0, ios::end);
		int size = fout.tellp();
		for (int i = 0; i < NUMBER_ITEMS; i++)
		{
			fout.write(reinterpret_cast<char*>(&item[i]), sizeof(item[0]));
		}
		fout.close();
	}
	else
	{
		cout << "File was not opened. Couldn't write in it." << endl;
	}
}

//To search an item using item_ID
int Search_ID(InventoryItem item[NUMBER_ITEMS])
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
			if (item[i].isFilled == 1)
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

//******************************************************************************************************************

//Display the menu
void Menu()
{
	cout << "1) Add inventory items " << endl
		<< "2) View all inventory items" << endl
		<< "3) Search inventory items" << endl
		<< "4) Edit inventory item" << endl
		<< "5) Delete inventory item" << endl
		<< "6) Assign inventory item" << endl
		<< "7) Retrieve inventory item" << endl
		<< "8) View list of faculty members who have borrowed a specific item" << endl
		<< "9) Exit" << endl << endl;
}

//Add inventory item
void Add_Item(InventoryItem item[NUMBER_ITEMS])
{
	int index = 0;
	//Checks the list to find an empty node in the array
	for (int i = 0; i < FACULTY_MEMBERS; i++)
	{
		if (item[i].isFilled == 0)
		{
			index = i;
			break;
		}
	}

	cin.ignore(10000, '\n');

	//Taking input info for the date
	Item_valid(item[index].Name);

	//Taking valid input for Item ID if it is's a number above 0
	while (1)
	{
		int user_ID;
		cout << "Enter item_ID: ";
		user_ID = Number_valid();

		bool isDuplicate = 0;
		for (int i = 0; i < NUMBER_ITEMS; i++)
		{
			if (user_ID == item[i].Item_ID)
			{
				isDuplicate = 1;
				break;
			}
		}

		if (isDuplicate)
		{
			cout << "Item with entered ID already exist. Please enter a new ID." << endl;
		}
		else if (user_ID > 0)
		{
			item[index].Item_ID = user_ID;
			break;
		}
		else
		{
			cout << "Invalid item_ID entered. Please re-enter." << endl;
		}

	}

	//Taking input for item_count only if it's not negative number
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
	Category_valid(item[index].category);

	//Updating the items list
	item[index].isFilled = 1;
	cout << "Item Added. " << endl << endl;
}

//View inventory items
void View_Item(InventoryItem item[NUMBER_ITEMS])
{
	cout << setw(7) << "ID" << ' ' << setw(15) << "Category" << '\t' << ' '
		<< left << setw(50) << "Item Name" << right << " " << setw(15) << "Count" << endl
		<< setfill('-') << setw(90) << "-" << setfill(' ') << endl;
	for (int i = 0; i < NUMBER_ITEMS; i++)
	{
		//CHecking the list to find filled space and displaying that item
		if (item[i].isFilled == 1)
		{
			cout << setw(7) << item[i].Item_ID << '|' << setw(15) << item[i].category << '\t' << '|'
				<< left << setw(50) << item[i].Name << right << '|' << setw(15) << item[i].Item_count << endl;
		}
	}

	cout << endl << endl;
}

//Search inventory items
void Search_Item(InventoryItem item[NUMBER_ITEMS])
{
	char user_name[MAX_NAME_CHAR];
	cin.ignore();
	//Taking input for item name
	Item_valid(user_name);

	for (int i = 0; i < NUMBER_ITEMS; i++)
	{
		//Checking if the node is Filled
		if (item[i].isFilled)
		{
			//Checking if the Item exist and displaying it
			if (strcmp(user_name, item[i].Name) == 0)
			{
				cout << setw(7) << "ID" << ' ' << setw(15) << "Category" << '\t'  << ' ' 
					<< left << setw(50) << "Item Name" << right << " " << setw(15) << "Count" << endl
					<< setfill('-') << setw(90) << "-" << setfill(' ') << endl;
				
				cout << setw(7) << item[i].Item_ID  << '|' << setw(15) << item[i].category << '\t' << '|' 
					<< left << setw(50) << item[i].Name << right << '|' << setw(15) << item[i].Item_count << endl << endl;
				return;
			}
		}
	}
	cout << "No Item found." << endl << endl;
}

//Edit inventory items
void Edit_Item(InventoryItem item[NUMBER_ITEMS])
{
	//GEtting input for ID from the user and validating  it
	int index = Search_ID(item);

	cout << endl << "Enter NEW data" << endl;
	Item_valid(item[index].Name);

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
	Category_valid(item[index].category);

	cout << "Item is Edited." << endl << endl;
}

//Delete inventory items
void Delete_Item(InventoryItem item[NUMBER_ITEMS])
{
	int index = 0;
	//Getting ID from the user and validating it
	index = Search_ID(item);

	//DELETING
	item[index].isFilled = 0;
	item[index].Item_ID = 0;
	item[index].allocatedItems = 0;

	cout << "Item deleted successfully..." << endl;
}

//Assign inventory item
void Assign_Item(InventoryItem item[NUMBER_ITEMS])
{
	bool isAssignee_Available = 0;
	int index = 0, assignee = -1, allocatedItems = 0;

	//Getting ID from the user and validating it
	index = Search_ID(item);

	//Checking if any item is in STOCK (if no: exiting)
	if (item[index].Item_count <= 0)
	{
		cout << "No item in STOCK. Can't assign." << endl;
		return;
	}

	//Looking for an empty node to store the data about NEW Assignee
	for (int i = 0; i < FACULTY_MEMBERS; i++)
	{
		if (item[index].assigned_to[i].allocated_items == 0)
		{
			assignee = i;
			break;
		}
	}

	//If there is node available
	if (assignee >= 0)
	{
		char username[MAX_NAME_CHAR];
		Name_valid(username);

		//Checking if the Assignee's name entered already exist
		for (int i = 0; i < FACULTY_MEMBERS; i++)
		{
			//If Assignee already exist. Assigning him items instead of creating new instance
			if (strcmp(username, item[index].assigned_to[i].name) == 0)
			{
				strcpy_s(item[index].assigned_to[i].name, MAX_NAME_CHAR, username);
				isAssignee_Available = 1;
				assignee = i;
				break;
			}
		}

		if (isAssignee_Available == 0)
		{
			strcpy_s(item[index].assigned_to[assignee].name, MAX_NAME_CHAR, username);
		}


		while (1)
		{
			//Taking input for item to be allocated
			cout << "Enter the number of items you want to assign (in stock: " << item[index].Item_count << ") : ";
			allocatedItems = Number_valid();

			//Validation if the items entered by the user are in stock and Assigning item (updating records
			if (allocatedItems <= item[index].Item_count && allocatedItems >= 0)
			{
				item[index].Item_count -= allocatedItems;
				item[index].allocatedItems += allocatedItems;
				item[index].assigned_to[assignee].allocated_items += allocatedItems;
				break;
			}
			cout << "Invalid number of items entered. Please re-enter." << endl;
		}

		cout << "(" << (allocatedItems) << ')' << item[index].Name << " is assigned to " << item[index].assigned_to[assignee].name << endl << endl;
	}
	else
	{
		cout << "Max Limit is reached!" << endl;
	}

	
}

//Retrieving items from the Assignees
void Retrieve_Item(InventoryItem item[NUMBER_ITEMS])
{
	int index = 0, assignee = 0, returnedItems = 0;
	char userName[MAX_NAME_CHAR];
	bool isFound = 0;

	//Getting ID from the user and validating it
	index = Search_ID(item);

	//Checking if the item is assigned or not
	if (item[index].allocatedItems <= 0)
	{
		cout << "No item is ASSIGNED. Can't retrieve." << endl;
		return;
	}

	while (1)
	{
		//Taking input for the name of the assignee from whom you want to retrieve
		Name_valid(userName);

		//Checking if the name entered exist in the system (borrowed item)
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
		//Taking input for the number of item to be retrieved
		cout << "Enter the number of items retrieved (in stock: " << item[index].assigned_to[assignee].allocated_items << ") : ";
		returnedItems = Number_valid();

		//Validation & Retrieving items
		if (returnedItems <= item[index].assigned_to[assignee].allocated_items && returnedItems >= 0)
		{
			item[index].Item_count += returnedItems;
			item[index].allocatedItems -= returnedItems;
			item[index].assigned_to[assignee].allocated_items -= returnedItems;
			break;
		}
		cout << "Invalid number of items entered. Please re-enter." << endl;
	}

	//Displaying message.
	cout << "(" << (returnedItems) << ") items retrieved from " << item[index].assigned_to[assignee].name << endl << endl;
}

//Displaying the list of Assignees of a Specific item
void List_Assigned_Item(InventoryItem item[NUMBER_ITEMS])
{
	int index = 0;
	//Getting ID from the user and validating it
	index = Search_ID(item);

	//Checking if any item is assigned
	if (item[index].allocatedItems <= 0)
	{
		cout  << endl << "No item is ASSIGNED." << endl;
		return;
	}

	//Displaying the list of persons who borrowed the item
	cout  << endl << left << setw(50) << "Name" << setw(8) << "Number of Items" << endl;
	cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
	for (int i = 0; i < FACULTY_MEMBERS; i++)
	{
		if (item[index].assigned_to[i].allocated_items > 0)
		{
			cout << setw(50) << item[index].assigned_to[i].name << setw(8) << item[index].assigned_to[i].allocated_items << endl;
		}
	}
	cout << endl;
}
