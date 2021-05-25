#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Display menu
int display_menu() {
	int choice = 0;

	do {
		cout << "\tMenu Option\n\n";
		cout << "\t1. Insert new part\n";
		cout << "\t2. Search for part information\n";
		cout << "\t3. Update part information\n";
		cout << "\t4. Export to a text file\n";
		cout << "\t5. Exit.\n";
		cout << "\tYour Choice: ";

		cin >> choice;
	} while (choice < 1 and choice > 5);

	return choice;
}

//Define variables
class part {
	public:
		int part_number, quantity;
		float price;
};
part Inventory[100];
part a_part;
char continue_to_insert;

//Insert part
void insert_inventory() {
	for (int i = 0; i < 100; i++) {
		do {
			cout << "\tEnter the part information below:\n";
			cout << "\tPart number: ";
			cin >> Inventory[i].part_number;
			cout << "\tQuantity: ";
			cin >> Inventory[i].quantity;
			cout << "\tPrice: $";
			cin >> Inventory[i].price;

			cout << "\tContinue to insert? (Y/N): ";
			cin >> continue_to_insert;
		} while (continue_to_insert == 'Y');

		if (continue_to_insert == 'N') {
			break;
		}
	}
}

//Search for part
int search_part() {
	int num;
	cout << "\tEnter the part number to search: ";
	cin >> num;
	for (int i = 0; i < 100; i++) {
		if (num == Inventory[i].part_number) {
			cout << "\tPart number: " << Inventory[i].part_number;
			cout << "\tQuantity: " << Inventory[i].quantity;
			cout << "\tPrice: " << Inventory[i].price;
			return Inventory[i].part_number;
		}
		else {
			return 0;
		}
	}
}

//Update part
part update_part() {
	int num;
	cout << "Enter the part number to update: ";
	cin >> num;
	for (int i = 0; i < 100; i++) {
		if (num == Inventory[i].part_number) {
			cout << "\tFound the part. Ready to update!\n";

			cout << "\tEnter the new quantity: ";
			cin >> Inventory[i].quantity;

			cout << "\tEnter the new price: ";
			cin >> Inventory[i].price;
			
			cout << "\tDone";

			return Inventory[i];
		}
	}
}

//Write to text file
int write_to_text(){
	ofstream inventory;
	inventory.open("Inventory.txt");

	inventory << "Part Number\tQuantity\tPrice\n";

	for (int i = 0; i < 100; i++) {
		if (Inventory[i].part_number != NULL) {
			inventory << Inventory[i].part_number << "\t" << Inventory[i].quantity << "\t" << Inventory[i].price << endl;
		}
		else {
			break;
		}
	}

	inventory.close();

	cout << "\tDone\n";

	return 0;
}

int main() {

	cout << "\t/***************************************************************************************/";
	cout << "\n\t/**This program ask user to enter Inventory information and stores them in a text file**/\n" << endl;
	cout << "\t/***************************************************************************************/\n\n";
	
	int choice;
	
	do {
		choice = display_menu();
		
		switch (choice) {
		case 1:
			insert_inventory();
			break;
		case 2:
			search_part();
			break;
		case 3:
			update_part();
			break;
		case 4:
			write_to_text();
			break;
		}
	} while (choice != 5);
}


