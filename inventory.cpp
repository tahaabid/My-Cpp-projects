#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

/*this function takes an int argument which is the number of different reminders
if the reminders are 0, then it simply displays the menu
otherwise it will also display that there are n number of reminders the user should address.
the input of this function is the action that the user will choose to do
the function returns the int that specifies what action the user wants to do*/
int menu(int reminders) {
  int action;
  Sleep(350);
  cout << endl;
  if(reminders != 0) {
  	if(reminders == 1) {
  		cout << "##There is 1 important reminder you should look into##" << endl;
	  }
	else {
		cout << "##There are  " << reminders << " important reminders you should look into##" << endl;
	}
  }
  cout << "***********************************************************************" << endl;
  cout << "****************** Taha's  Inventory Management System ****************" << endl;
  cout << "******---             What would you like to do?             ---*******" << endl;
  cout << "*******              Choose an option from below                *******" << endl;
  cout << "*1. Check reminders                                                   *" << endl;
  cout << "*2. Add a new product                                                 *" << endl;
  cout << "*3. Update Existing Product                                           *" << endl;
  cout << "*4. View Products                                                     *" << endl;
  cout << "*5. Quit                                                              *" << endl;
  cout << "***********************************************************************" << endl;
  cin >> action;
  return action;
}

std::string to_string(int x) {
	stringstream ss;
	ss << x;
	string s;
	ss >> s;
	return s;
}



struct Product {
	string name;
	string type;
	double price;
	int quantity;
	int days_left;
	string batch;
};

/*function to dynamically double size of array.*/
void increase_size(Product *&current, int &len) {
	Product *ptr_to_delete_prev = current;  //to free up this memory later
	Product *biggerarray = new Product[2 * len];  //creating the new bigger array
	for (int i = 0; i < len; i++) {  //to copy all the elements from older to newer
		biggerarray[i] = current[i];
	}
	current = biggerarray;  //updating the ptr of the older (smaller) array to the newer (bigger) array
	delete[] ptr_to_delete_prev;  //releasing memory taken up by smaller array
	len = len * 2; //updating the size of our array by reference
}

/*Function to add a product into the database. Take parameters of the original database, num of products inside and the size of the array
After asking for relevant info from the user, Adds the product into the database*/
void addproduct( Product goodsarray[], int &size, int &size_of_array) {
	if (size == size_of_array) {
	    increase_size(goodsarray, size);
	}
	cout << "Please enter the product name: " << endl;
	cin >> goodsarray[size].name;
	cout << "Please enter the product type: " << endl;
	cin >> goodsarray[size].type;
	cout << "Please enter " << goodsarray[size].name << "'s price : " << endl;
	cin >> goodsarray[size].price;
	cout << "What quantity of " << goodsarray[size].name << "(s) would you like to add this time? " << endl;
	cin >> goodsarray[size].quantity;
	cout << "How many days can " << goodsarray[size].name << " last before it expires? " << endl;
	cin >> goodsarray[size].days_left;
	cout << "Please enter the batch number for this batch of " << goodsarray[size].name << ": " << endl;
	cin >> goodsarray[size].batch;
	cout << "\nPlease hang on a minute " << goodsarray[size].name << " is being added";
	int repeat = 0;
	while (repeat != 5) {
		Sleep(350);
		cout << ".";
		repeat++;
	}
	cout << "\nProduct added Successfully! ^_^ " << endl;
	size += 1;
	return;
}

/*This function will update a certain product that the user wishes to modify
it will take the struct array, numbers of products in the array, what product to update and the batch string as its arguments
it will then search for this product in the array and update it according to how the user wishes by taking in input of new price, quantity & expiry
if the product is not found a message as such will be displayed*/
void updateproduct(Product goodsarray[], int size) {
	string update_product, lot;
	cout << "Which product would you like to update: ";
	cin >> update_product;
	cout << "\nPlease enter the batch number for this product: ";
	cin >> lot;
	//need to locate product first
	int loc;
	for(int i = 0; i < size; i++) {
		if(goodsarray[i].name == update_product && goodsarray[i].batch == lot) {
			loc = i;
			break;
		}
		else if(i + 1 == size) {  //incase we reach last iteration and product still not found
			cout <<"\nSorry, the Product you are looking for does not exist in the database. :/" << endl;
			return;
		}
	}
	//updating the product 
	cout << "\nEnter the new Price: ";
	cin >> goodsarray[loc].price; 
	cout << "\nEnter the updated quantity: ";
	cin >> goodsarray[loc].quantity;
	cout << "\nEnter the new Expiry date: ";
	cin >> goodsarray[loc].days_left;
	
	cout << "\nPlease hang on a minute " << goodsarray[loc].name << " is being Updated";
	int repeat = 0;
	while (repeat != 5){
		Sleep(350);
		cout << ".";
		repeat++;
	}
	cout << "\nProduct Updated Successfully! ^_^ " << endl;
}
void bubblesort(Product unsorted_array[], int size, string criteria) {
	if(criteria == "price") {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < (size-1) - i; ++j) {
				if (unsorted_array[j].price > unsorted_array[j+1].price) {
					Product temp;
					temp = unsorted_array[j+1];
					unsorted_array[j+1] = unsorted_array[j];
					unsorted_array[j] = temp;
				}
			}
		}
	}
	else if (criteria == "quantity") {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < (size-1) - i; ++j) {
				if (unsorted_array[j].quantity > unsorted_array[j+1].quantity) {
					Product temp;
					temp = unsorted_array[j+1];
					unsorted_array[j+1] = unsorted_array[j];
					unsorted_array[j] = temp;
				}
			}
		}
	}
	else {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < (size-1) - i; ++j) {
				if (unsorted_array[j].days_left > unsorted_array[j+1].days_left) {
					Product temp;
					temp = unsorted_array[j+1];
					unsorted_array[j+1] = unsorted_array[j];
					unsorted_array[j] = temp;
				}
			}
		}
	}
}

/*This function takes in the database and its size, then print out the entire inventory*/
void display(Product goodsproduct[], int size) {
	for (int i = 0; i < size; i++) {
		cout << goodsproduct[i].name << " " << goodsproduct[i].type << " " << goodsproduct[i].price << " " << goodsproduct[i].quantity << " " 
		<< goodsproduct[i].days_left << " " << goodsproduct[i].batch << endl;
	}
	return;
}

void sortfunction(Product goodsarray[], int option, int size) {
	//3 price
	//4 quantity
	//expiry
	if (option == 3) {
		bubblesort(goodsarray, size, "price");
	}
	else if (option == 4) {
		bubblesort(goodsarray, size, "quantity");
	}
	else  {
		bubblesort(goodsarray, size, "days_left");
	}
	display(goodsarray, size);
}


/*Function to show the user the sorted products depending on the different options as chosen by the user
it takes the database and num of products as parameters. Then prompts the user, asking how to sort the data, and displays the sorted products on the output window*/
void viewproduct(Product goodsarray[], int size) {
	cout << "How would you like to view your Products?" << endl;
	cout << "1. All Products" << endl;
	cout << "2. Specific Product" << endl;
	cout << "3. By Price" << endl;
	cout << "4. By Quantity" << endl;
	cout << "5. By Expiry days" << endl;
	cout << "So...which is it going to be?" << endl;
	int option;
	cin >> option;

	switch(option) {
		case 1: {
			for(int j = 0; j < size; ++j) {
				cout << goodsarray[j].name << " " << goodsarray[j].type << " " << goodsarray[j].price << " " << goodsarray[j].quantity;
				cout  << " " << goodsarray[j].days_left << " " << goodsarray[j].batch << endl;
			}
			break;
		}
		case 2: {
			cout << "Which product would you like to check?" << endl;
			string product_name;
			cin >> product_name;
			cout << "What is the Batch Number for this product?" << endl;
			string product_batch;
			cin >> product_batch;
			//finding product
			for (int i = 0; i < size; ++i) {
				if ((goodsarray[i].name == product_name) && (goodsarray[i].batch == product_batch)) {
					cout << "These are the details of your request:" << endl;
					cout << "Name:" << goodsarray[i].name << endl;
					cout << "Batch:" << goodsarray[i].batch << endl;
					cout << "Type:" << goodsarray[i].type << endl;
					cout << "Price:" << goodsarray[i].price << endl;
					cout << "Quantity:" << goodsarray[i].quantity << endl;
					cout << "Expiry Days:" << goodsarray[i].days_left << endl;
					break;
				}
				else if (i + 1 == size) {
					cout << "Sorry your product does not exist. Please search again if you are sure the product exists, perhaps there was a typo." << endl;
				}
			}
			break;
		}
		case 3: {
			cout << "So these are all the products in stock with prices in ascending order." << endl;
			sortfunction(goodsarray, 3, size);
			break;
		}
		case 4: {
			cout << "So these are all the products in stock with quantity in ascending order." << endl;
			sortfunction(goodsarray, 4, size);
			break;
		}
		case 5: {
			cout << "So these are all the products in stock with days to expiry in ascending order." << endl;
			sortfunction(goodsarray, 5, size);
			break;
		}
	}
}

/*A function to check for important issues to bring to the user's attention before he makes any decision.
the input is the struct array, number of products, as well as a by reference int value for how many imp reminders there are and 
a char that specifies whether we want to be printing out the reminders as well or just updating the value of how many reminders there are
incase the char is I, only the number of reminders value will be updated, but incase it is different, this function will print out the reminders
*/
void reminder(Product *array, int num_p, int &notices, char demand)
{
	string output;
	notices = 0; //resetting value of notices, to put a fresh calculated value
	//checking expiry
	for(int i = 0; i < num_p; ++i) {
		if(array[i].type != "Perishables" && array[i].days_left < 7) {  //need to treat perishables separately due to their shorter life
			output = output + "--> " + array[i].name + " of Batch " + array[i].batch + " will expire in " + to_string(array[i].days_left) + " day(s).\n";
			++notices;
		}
		else if (array[i].type == "Perishables" && array[i].days_left < 2) {
			output += "--> " + array[i].name + " of Batch " + array[i].batch + " will expire in " + to_string((array[i].days_left)) + " day.\n";
			++notices;
		}
	}
	//checking excess inventory
	for(int j = 0; j < num_p; ++j) {
		if(array[j].quantity > 10000) {
			output = output +  "--> " + "There are " + to_string((array[j].quantity)) + " units of unsold " + array[j].name + " of Batch " + array[j].batch + ".\n";
			++notices;
		}
	}
	if(demand == 'I') {  //no need to print anything, only the count of notices was wanted
		return;
	}
	else if(notices == 0) {  //incase viewer chooses option 1 even when there are no imp reminders
		cout << "Great News! You have no pending issues to take note of. \n";
	}
	else {
		cout << "Your attention is called to the following pending issues you may wish to resolve: \n" << output;
	}
}

/*To check how much money worth of products the user have inside this inventory database.*/
void inventory_worth( Product goodsarray[], int size) {
	string productname;
	cout << "Which product's inventory worth would you like to know? (Type ALL if you want to know the total worth of your inventory)" << endl;
	cin >> productname;
	cout << endl;
	double sum = 0;
	if (productname == "All") {
		for (int i = 0; i < size; i++) {
			sum += goodsarray[i].price * goodsarray[i].quantity;
		}
		if (sum >= 500000) {
			cout << "You have $" << sum << " worth of products in your warehouse! You're Loaded!" << endl;
		}
		else {
			cout << "You have $" << sum << " worth of products in your warehouse! Go out and purchase more!" << endl;
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			if (productname == goodsarray[i].name) {
				sum += goodsarray[i].price * goodsarray[i].quantity;
			}
		}
		cout << "You have $" << sum << " worth of " << productname << " in your warehouse!" << endl;
	}
}

/*This function will load the database from the database file when the program is run
it takes a pointer to the aray, as well as size of the array and the number of products in it currently
it will then insert these products into the array for further processing by the program*/
void load_array(Product *&array, int &sizeofarray, int &num_products) // Taha
{
	cout << "Please wait a moment while the program is loading ";
	int repeat = 0;
	while (repeat != 4){
		Sleep(350);
		cout << ".";
		repeat++;
	}
	cout << endl;
	int idx = 0;
	stringstream ss;
	string lineofdata;
	ifstream fin;
	fin.open("Database.txt");
	if(fin.fail()) {
	    cout << "Failed to open Database.txt" << endl;
		exit(1);
	}
	repeat = 0;
	while(repeat !=3) {
		Sleep(300);
		cout << "." << endl;
		repeat++;
	}
	
	while(getline(fin, lineofdata)) {  //read in each line which contains product info and make a stream to feed these values into array
	    if(idx == sizeofarray) {  //incase our product number reaches max size of the array, then increase the size of array
	    	increase_size(array, sizeofarray);
	    }
	    ss.clear();  //dont forget to clear the stream
	    ss.str(lineofdata);
		ss >> array[idx].name;
		ss >> array[idx].type;
		ss >> array[idx].price;
		ss >> array[idx].quantity;
		ss >> array[idx].days_left;
		ss >> array[idx].batch;
		idx++;
		num_products++;
	}
	if(num_products == 1) {
		cout << num_products << " Product loaded successfully!" << endl;
	}
	else {
		cout << num_products << " Products loaded successfully!" << endl;
	}
	fin.close();
}

/*This function outputs the final list of products which are stored in the memory and writes them to the output file. it will be called before
the program terminates. The input is the struct array as well as how many products there are in the array while the output is a file containing all the
details of each product in separate lines for each product
*/
void write_array(Product *save_myarray, int total_products) {
	ofstream fout;
	fout.open("Database.txt");
	if(fout.fail()) {
		cout << "Failed to save data to Database.txt" << endl;
		exit(1);
	}
	for(int  i = 0; i < total_products; ++i) {
		fout << save_myarray[i].name << " ";
		fout << save_myarray[i].type << " ";
		fout << save_myarray[i].price << " ";
		fout << save_myarray[i].quantity << " ";
		fout << save_myarray[i].days_left << " ";
		fout << save_myarray[i].batch << endl;
	}
	fout.close();
}

int main() {
  int choice, size = 10, num_products = 0, notices = 0;  //initial size of array will be 10
  Product *database = new Product[10]; //struct array to store all our products
  load_array(database, size, num_products);  //initializing program from last saved version
  reminder(database, num_products, notices, 'I');  //I argument so we only get the number of notices, the reminders wont be posted
  choice = menu(notices);
  while (choice != 5) {
	cout << endl;
	switch(choice) {
	  case 1:
	  	reminder(database, num_products, notices, 'P');  //P arg will mean it prints out the reminders instead of only calculating how many reminders there are
		break;
	  case 2:
		addproduct(database, num_products, size);
		break;
	  case 3:
		updateproduct(database, num_products);
		break;
	  case 4:
		viewproduct(database, num_products);
		break;
      default:
	  	cout << "Please choose a number between 1 & 5" << endl;
	  	cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  //for max size of buffer or until newline
    }
    
    reminder (database, num_products, notices, 'I'); //update the value of notices incase any action taken, I so nothing gets printed
    choice = menu(notices);
  }
  write_array(database, num_products);
  cout << "\nThank you for using Taha's Inventory Management System!\nHave a nice day! :)\nBye Bye!" << endl;
}
