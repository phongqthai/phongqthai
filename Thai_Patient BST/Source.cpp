#include <iostream>
#include <string>
using namespace std;

//Define Node
struct Node {
	string name;
	int ss, age, smoker, HBP, HFD, points;
	Node* left, * right;
};

//Define type name for Node*
typedef Node* node;

//Create a root node
node root = NULL;

//Duplicate check if social security number is already exist or not
bool duplicate(node ptr, int key) {
	if (ptr == NULL) return false;
	if (ptr->ss == key) return true;
	return duplicate(ptr->left, key) || duplicate(ptr->right, key);
}

//Get information for new node created
node get_info(int ssnum)
{
	//Create new node, assign social security number and calculate points
	node ptr = new Node();
	ptr->points = 0;
	ptr->ss = ssnum;
	ptr->left = ptr->right = NULL;

	//Get patient's first name
	cout << "\tEnter first name: ";
	cin >> ptr->name;

	//Get patient's age
	cout << "\tEnter age: ";
	cin >> ptr->age;
	while (ptr->age < 0) {
		cout << "\tAge cannot be smaller than 0!\n";
		cout << "\tEnter age: ";
		cin >> ptr->age;
	}
	if (ptr->age < 20) ptr->points += 1;
	else if (ptr->age < 30) ptr->points += 2;
	else ptr->points += 3;

	// Check if patient smoke or not
	cout << "\tDo you smoke? (Answer 1 for yes, 0 for no) ";
	cin >> ptr->smoker;
	while (ptr->smoker != 1 && ptr->smoker != 0) {
		cout << "\tEnter either 1 for yes or 0 for no: ";
		cin >> ptr->smoker;
	}
	if (ptr->smoker == 1) ptr->points += 4;

	// Check high blood pressure
	cout << "\tDo you have high blood pressure? (Answer 1 for yes, 0 for no) ";
	cin >> ptr->HBP;
	while (ptr->HBP != 1 && ptr->HBP != 0) {
		cout << "\tEnter either 1 for yes or 0 for no: ";
		cin >> ptr->HBP;
	}
	if (ptr->HBP == 1) ptr->points += 2;

	// Check high fat diet
	cout << "\tDo you have high fat diet? (Answer 1 for yes, 0 for no) ";
	cin >> ptr->HFD;
	while (ptr->HFD != 1 && ptr->HFD != 0) {
		cout << "\tEnter either 1 for yes or 0 for no: ";
		cin >> ptr->HFD;
	}
	if (ptr->HFD == 1) ptr->points += 1;
	cout << "\n\n";

	return ptr;
}

//Insert new node to the tree
void insertNode(int key) {
	//Check if social number is exist or not
	while (duplicate(root, key)) {
		cout << "\n\tThis social security is already exist, please enter a new one!\n";
		cout << "\n\tEnter new social security number: ";
		cin >> key;
	}
	node ptr = new Node();
	ptr->left = ptr->right = NULL;
	ptr = get_info(key);
	node position = NULL;
	node rootNode = root;
	while (rootNode != NULL) {
		position = rootNode;
		if (ptr->ss < rootNode->ss) rootNode = rootNode->left;
		else rootNode = rootNode->right;
	}
	if (position == NULL) root = ptr;
	else if (ptr->ss < position->ss) position->left = ptr;
	else position->right = ptr;
}

//Display information of a patient
void display_info(node ptr) {
	//Social Number
	cout << "\tSocial Number: " << ptr->ss << endl;
	//Name
	cout << "\tName: " << ptr->name << endl;
	//Age
	cout << "\tAge: " << ptr->age << endl;
	//Smoke
	if (ptr->smoker == 1) cout << "\tThis patient smokes, ";
	else cout << "\tThis patient doesn't smoke, ";
	//Blood Pressure
	if (ptr->HBP == 1) cout << "has high blood pressure, ";
	else cout << "doesn't have hight blood pressure, ";
	//Fat Diet
	if (ptr->HFD == 1) cout << "and eats high fat diet." << endl;
	else cout << "and doesn't eat high fat diet." << endl;
	//Points
	cout << "\tTotal points of this patient is: " << ptr->points << endl;
	cout << "\n\t---------------\n" << endl;
}

//Display the whole tree of patients
void display_list(node ptr) {
	//inOrder display
	if (ptr != NULL) {
		display_list(ptr->left);
		display_info(ptr);
		display_list(ptr->right);
	}
}

//Copy data from 1 node to a temporary node (used in deleteNode)
node copy(node ptr) {
	node temp = new Node();
	//Assign data from ptr to temp
	temp->ss = ptr->ss;
	temp->age = ptr->age;
	temp->HBP = ptr->HBP;
	temp->HFD = ptr->HFD;
	temp->name = ptr->name;
	temp->points = ptr->points;
	temp->smoker = ptr->smoker;

	return temp;
}

//Delete a node from the tree
node deleteNode(node ptr, int key) {
	node temp;
	//Check if ptr is NULL
	if (ptr == NULL) return ptr;
	else if (key < ptr->ss) ptr->left = deleteNode(ptr->left, key);
	else if (key > ptr->ss) ptr->right = deleteNode(ptr->right, key);
	else {
		//Case 1: delete the leaf node
		if (ptr->left == NULL && ptr->right == NULL) {
			delete ptr;
			ptr = NULL;
			cout << "\n\tDeletion Successes!\n\n";
		}
		//Case 2: node has one child
		else if (ptr->left == NULL) {
			node temp = ptr;
			ptr = ptr->right;
			delete temp;
			cout << "\n\tDeletion Successes!\n\n";
		}
		else if (ptr->right == NULL) {
			node temp = ptr;
			ptr = ptr->left;
			delete temp;
			cout << "\n\tDeletion Successes!\n\n";
		}
		//Case 3: node has 2 children
		else if (ptr->left != NULL && ptr->right != NULL) {
			//Find the new root - smallest child of the right node
			node min = ptr->right;
			while (min->left != NULL) {
				min = min->left;
			}
			//Assign mininum data to a temporary node
			temp = min;
			ptr = copy(temp);
			//Delete minimum node found using recursive on right node
			ptr->right = deleteNode(ptr->right, temp->ss);
			cout << "\n\tSuccess!\n\n";
		}
		else cout << "\n\tCan't find the patient\n";
	}
	return ptr;
}

//Search for information
node searchNode(node ptr, int key) {
	//Using recursive to find the key value and return true or false
	if (ptr == NULL) return ptr;
	else if (key < ptr->ss) ptr->left = searchNode(ptr->left, key);
	else if (key > ptr->ss) ptr->right = searchNode(ptr->right, key);
}

//Display menu option for user
int dispMenu() {
	//Get user's input for choice
	int choice;
	cout << "\tMenu Option\n\n";
	cout << "\t1. Insert a patient\n";
	cout << "\t2. Display the list of patients\n";
	cout << "\t3. Search patient by social security number\n";
	cout << "\t4. Delete a patient using social security number\n";
	cout << "\t5. Quit" << endl << endl;
	cout << "\tEnter your choice: ";
	cin >> choice;
	return choice;
}

//Check if user's input is 8 digits
bool is8digit(int num) {
	bool digit = false;
	if (num >= 10000000 && num < 100000000) digit = true;
	return digit;
}

int main()
{
	//Title
	cout << "\t\t\tPROJECT PATIENT LIST USING BINARY SEARCH TREE\n\n\n";

	//User input choice out of the menu and socical security number
	int choice, ssn;
	node ptr = new Node();

	do {
		//Get choice option
		choice = dispMenu();
		//Check if choice is from 1 to 5
		if (choice < 0 && choice > 4) {
			cout << "\tPlease enter choice between 1 and 4 or 5 to quit the program: ";
			cin >> choice;
		}
		//Choice is from 1 to 4
		else if (choice != 5) {
			cout << "\n\n";
			switch (choice)
			{
				//Insert new node 
			case 1:
				cout << "\tPlease enter social security number: ";
				cin >> ssn;
				while (is8digit(ssn) == false) {
					cout << "\tPlease enter 8-digit number: ";
					cin >> ssn;
				}
				insertNode(ssn);
				break;
				//Display patients' list
			case 2:
				cout << "\t-Here are the list of patients:\n\n";
				display_list(root);
				break;
				//Search by socical security number
			case 3:
				cout << "\tPlease enter social security number: ";
				cin >> ssn;
				while (is8digit(ssn) == false) {
					cout << "\tPlease enter 8-digit number: ";
					cin >> ssn;
				}
				ptr = searchNode(root, ssn);
				if (ptr == NULL) {
					cout << "\tCan't find the patient\n";
				}
				else display_info(ptr);
				break;
				//Delete a patient
			case 4:
				cout << "\tPlease enter social security number: ";
				cin >> ssn;
				while (is8digit(ssn) == false) {
					cout << "\tPlease enter 8-digit number: ";
					cin >> ssn;
				}
				ptr = deleteNode(root, ssn);
			}
		}
	} while (choice != 5);

	cout << "\n\tThank you for using the project!\n\n";

	return 0;
}
