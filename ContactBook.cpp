#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

class Address {
private:
	string house;
	string street;
	string city;
	string country;

public:
	Address()
	{
		house = "";
		street = "";
		city = "";
		country = "";
	}
	Address(string h, string s, string ci, string c)
	{
		house = h;
		street = s;
		city = ci;
		country = c;
	}


	string getHouse() { return house; }
	string getStreet() { return street; }
	string getCity() { return city; }
	string getCountry() { return country; }
	void setHouse(string h) { house = h; }
	void setStreet(string s) { street = s; }
	void setCity(string ci) { city = ci; }
	void setCountry(string c) { country = c; }

	bool equals(const Address& address)
	{
		if (this->house == address.house &&
			this->street == address.street &&
			this->city == address.city &&
			this->country == address.country)
		{
			return true;
		}
		return false;
	}

	void print_address()
	{
		cout << "House No. " << house << ", Street " << street << ", " << city << ", " << country;
	}

	Address copy_address()
	{
		Address* temp = new Address;

		temp->house = this->house;
		temp->street = this->street;
		temp->city = this->city;
		temp->country = this->country;
		return *temp;
	}
};

class Contact {
private:
	string first_name;
	string last_name;
	string mobile_number;
	string email_address;
	Address* address;

public:
	Contact()
	{
		first_name = "";
		last_name = "";
		mobile_number = "";
		email_address = "";
		address = nullptr;
	}
	Contact(string first, string last, string mobile, string email, Address* add)
	{
		if (!first.empty()) {
			first_name = first;
		}
		if (!last.empty()) {
			last_name = last;
		}
		if (mobile.size() == 11) {
			mobile_number = mobile;
		}
		email_address = email;
		address->setHouse(add->getHouse());
		address->setStreet(add->getStreet());
		address->setCity(add->getCity());
		address->setCountry(add->getCountry());
	}
	Contact(const Contact& other)
	{
		this->first_name = other.first_name;
		this->last_name = other.last_name;
		this->mobile_number = other.mobile_number;
		this->email_address = other.email_address;
		this->address = new Address;
		/*this->address = other.address;*/
		this->address->setCity(other.address->getCity());
		this->address->setCountry(other.address->getCountry());
		this->address->setHouse(other.address->getHouse());
		this->address->setStreet(other.address->getStreet());

	}

	string getFirstName() { return first_name; }
	string getLastName() { return last_name; }
	string getMobileNumber() { return mobile_number; }
	string getEmailAddress() { return email_address; }
	Address* getAddress() { return address; }

	void setFirstName(string first) {
		if (!first.empty()) {
			first_name = first;
		}
	}

	void setLastName(string last) {
		if (!last.empty()) {
			last_name = last;
		}
	}

	void setMobileNumber(string mobile) {
		if (mobile.size() == 11) {
			mobile_number = mobile;
		}
	}

	void setEmail(string email) {
		email_address = email;
	}

	void setAddress(Address* add) {
		address = add;
	}

	bool equals(Contact contact) {
		if (this->first_name == contact.first_name &&
			this->last_name == contact.last_name &&
			this->mobile_number == contact.mobile_number &&
			this->email_address == contact.email_address &&
			this->address->equals(*(contact.address)))
		{
			return true;
		}
		return false;
	}

	Contact* copy_contact() {

		Contact* newContact = new Contact;
		newContact->first_name = this->first_name;
		newContact->last_name = this->last_name;
		newContact->mobile_number = this->mobile_number;
		newContact->email_address = this->email_address;
		newContact->address = this->address;

		return newContact;
	}

	void printContactInfo()
	{
		cout << "Name: " << first_name << " " << last_name << endl;
		cout << "Mobile Number: " << mobile_number << endl;
		cout << "Email Address: " << email_address << endl;
		cout << "Address: ";
		address->print_address();
		cout << endl;

	}

};

class Group {
private:
	string groupName;
	Contact** groupContacts;
	int capacity;
	int size;

public:
	Group(string name, int capacity = 20) : capacity(capacity) {
		groupName = name;
		groupContacts = new Contact * [capacity];
	}

	~Group() {
		for (int i = 0; i < size; ++i) {
			delete groupContacts[i];
			groupContacts[i] = nullptr; // Set pointer to nullptr after deletion
		}
		delete[] groupContacts;
	}

	bool checkGroup(const Group& others)
	{
		if (this->groupName == others.groupName)
		{
			return true;
		}

	}

	string getGroupName() { return groupName; }

	void addContact(Contact* contact) {
		if (contact != nullptr) {
			if (size < capacity) {
				groupContacts[size++] = new Contact(*contact);
				cout << "Contact added to group '" << groupName << "' successfully." << endl;
			}
			else {
				cout << "Group capacity reached. Cannot add more contacts." << endl;
			}
		}
		else {
			cout << "Invalid contact. Cannot add to group." << endl;
		}
	}

	void removeContact(int num) {
		if (num >= 1 && num <= capacity && groupContacts[num - 1] != nullptr) {
			delete groupContacts[num - 1];

			for (int i = num - 1; i < size - 1; i++) {
				groupContacts[i] = groupContacts[i + 1];
			}
			groupContacts[size - 1] = nullptr; // Update the last element to nullptr
			size--;

			cout << "Contact removed from group '" << groupName << "' successfully." << endl;
		}
		else {
			cout << "Invalid contact number or contact not found." << endl;
		}
	}

	int findContactIndex(string contactName) {
		for (int i = 0; i < size; ++i) {
			if (groupContacts[i]->getFirstName() == contactName) {
				return i;
			}
		}
		return -1; // Return -1 if contact not found
	}

	void displayContacts() const {
		cout << "Contacts in group '" << groupName << "':" << endl;
		for (int i = 0; i < size; i++) {
			cout << "\nContact " << i + 1 << ":\n";
			groupContacts[i]->printContactInfo();
			cout << endl;
		}
	}
};

class ContactsBook {
private:
	static const int size_of_contacts = 100;
	Contact* contacts_list[size_of_contacts];
	static int contacts_count;
	Group* groups[100];
	int groups_count = 0;

	bool full()
	{
		if (contacts_count == size_of_contacts) {
			return true;
		}
		else
		{
			return false;
		}
	}

	void resize_list() {

		//double the size of array
		int newSize = size_of_contacts * 2;
		Contact* new_contacts_list = new Contact[newSize];

		//copy existing contacts to the new array
		for (int i = 0; i < contacts_count; i++) {
			new_contacts_list[i] = *contacts_list[i];
		}

		// Free memory allocated for the old contacts list
		*contacts_list = new_contacts_list;
		delete[] contacts_list;

	}

	void sort_contacts_list(int choice)
	{
		for (int i = 0; i < contacts_count - 1; ++i)
		{
			for (int j = 0; j < contacts_count - i - 1; ++j)
			{
				// if sort by first name
				if (choice == 1)
				{
					if (contacts_list[j]->getFirstName() > contacts_list[j + 1]->getFirstName())
					{
						//swap contacts
						Contact* temp = contacts_list[j];
						contacts_list[j] = contacts_list[j + 1];
						contacts_list[j + 1] = temp;
					}
				}
				// if sort by last name
				else if (choice == 2)
				{
					if (contacts_list[j]->getLastName() > contacts_list[j + 1]->getLastName())
					{
						// swap contacts
						Contact* temp = contacts_list[j];
						contacts_list[j] = contacts_list[j + 1];
						contacts_list[j + 1] = temp;
					}
				}
			}
		}
	}

public:
	ContactsBook()
	{
		for (int i = 0; i < 100; ++i) {
			groups[i] = nullptr;
		}
		for (int i = 0; i < size_of_contacts; i++)
		{

			contacts_list[i] = nullptr;
		}
	}

	void add_contact(const Contact& contact) {
		if (full()) {
			resize_list();
		}

		contacts_list[contacts_count] = new Contact(contact);
		cout << "\nContact has been added successfully\n";
		contacts_count++;
	}

	int total_contacts() {
		return contacts_count;
	}

	Contact* search_contact(string first_name, string last_name) {
		bool flag = false;
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i]->getFirstName() == first_name && contacts_list[i]->getLastName() == last_name) {
				flag = true;
				//return a copy of the found contact
				return new Contact(*(contacts_list[i]));
			}
		}
		if (!flag)
		{
			cout << "\nNo Contact found with such name\n";
			return nullptr; //contact not found
		}
	}

	Contact* search_contact(string mobile) {
		bool flag = false;
		for (int i = 0; i < contacts_count; ++i) {
			if (contacts_list[i]->getMobileNumber() == mobile) {
				flag = true;
				//return a copy of the found contact
				return new Contact(*(contacts_list[i]));
			}
		}
		if (!flag)
		{
			cout << "\nNo Contact found with such number\n";
			//no cont found
			return nullptr;
		}
	}

	Contact* search_contact(Address* add) {
		bool flag = false;
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i]->getAddress()->equals(*add)) {
				flag = true;
				//return a copy of the found contact
				return new Contact(*(contacts_list[i]));
			}
		}
		if (!flag) {
			cout << "\nNo Contact found with such address\n";
			return nullptr; // Contact not found
		}
	}

	Contact* general_search(string general)
	{
		for (int i = 0; i < contacts_count; i++)
		{
			if (contacts_list[i]->getFirstName() == general || contacts_list[i]->getLastName() == general || contacts_list[i]->getEmailAddress() == general || contacts_list[i]->getMobileNumber() == general)
			{
				return new Contact(*(contacts_list[i]));
			}
			else if (contacts_list[i]->getAddress()->getHouse() == general || contacts_list[i]->getAddress()->getStreet() == general || contacts_list[i]->getAddress()->getCity() == general || contacts_list[i]->getAddress()->getCountry() == general)
			{
				return new Contact(*(contacts_list[i]));
			}
		}
		cout << "\nNo Contact found with such detail\n";
		return nullptr;
	}

	void printAllContacts()
	{
		for (int i = 0; i < contacts_count; i++)
		{
			cout << "\nContact " << i + 1 << ":\n";
			contacts_list[i]->printContactInfo();
			cout << endl;
		}
	}

	void printSpecificContact(int num)
	{
		if (contacts_list[num - 1] == nullptr)
		{
			cout << "\nNo contact found at " << num << endl;
			return;
		}
		cout << "\nContact: " << num << ":\n";
		contacts_list[num - 1]->printContactInfo();
	}

	void print_contacts_sorted(int choice) {
		sort_contacts_list(choice);

		for (int i = 0; i < contacts_count; i++)
		{
			cout << "\nContact " << i + 1 << ":\n";
			contacts_list[i]->printContactInfo();
			cout << endl;
		}
	}

	void deleteContact(int num)
	{
		cout << "\nContact number " << num << " has been deleted successfully\n";
		delete contacts_list[num - 1];

		//tp fill the space
		for (int i = num - 1; i < contacts_count - 1; i++) {
			contacts_list[i] = contacts_list[i + 1];
		}
		contacts_count--;
	}

	void updateContact(int num, Contact contact)
	{
		delete contacts_list[num - 1];
		contacts_list[num - 1] = new Contact(contact);

		cout << "\nContact " << num << " has been updated\n";
	}

	void merge_duplicates()
	{
		bool flag = false;
		for (int i = 0; i < contacts_count; i++)
		{
			for (int j = i + 1; j < contacts_count; j++)
			{
				if (contacts_list[i]->equals(*contacts_list[j]))
				{
					cout << "\nA duplicate contact has been found and both are merged\n";
					delete contacts_list[j];
					flag = true;


					//to fill up the space
					for (int k = j; k < contacts_count - 1; k++) {
						contacts_list[k] = contacts_list[k + 1];
					}

					contacts_count--;
					j--;
				}
			}
		}

		if (!flag)
		{
			cout << "\nNo duplicate contact found!\n";
		}
	}

	void save_to_file() {
		ofstream outfile("outfile.txt");


		if (!outfile.is_open()) {
			cout << "\nError! File can not be openned" << endl;
			return;
		}

		for (int i = 0; i < contacts_count; i++) {
			outfile << "Contact " << i + 1 << ":\n";
			outfile << "Name: " << contacts_list[i]->getFirstName() << " " << contacts_list[i]->getLastName() << endl;
			outfile << "Mobile Number: " << contacts_list[i]->getMobileNumber() << endl;
			outfile << "Address: House No. " << contacts_list[i]->getAddress()->getHouse() << ", Street ";
			outfile << contacts_list[i]->getAddress()->getStreet() << ", " << contacts_list[i]->getAddress()->getCity();
			outfile << ", " << contacts_list[i]->getAddress()->getCountry() << endl << endl;
		}

		outfile.close();
		cout << "\nContacts saved to file successfully\n";
	}

	void input_from_file() {
		ifstream infile("infile.txt");
		string line;

		if (!infile.is_open()) {
			cout << "\nError! File can not be openned" << endl;
			return;
		}

		cout << "\nContacts from file:" << endl;
		while (getline(infile, line)) {
			cout << line << endl;
		}

		infile.close();
	}

	void advance_search() {
		string advance_string, store_string;
		int count = 0, k = 0, x = 0, contact_count = 0;
		cout << "Enter your input (without space): ";
		cin >> advance_string;
		for (int n = 0; n < contacts_count; n++)
		{
			store_string = contacts_list[n]->getFirstName();
			for (int i = 0; i < strlen(advance_string.c_str()); i++)
			{
				for (int j = 0; j < strlen(store_string.c_str()); j++)
				{
					if (store_string[j] == advance_string[i] && k < j) {
						count++;
						k = j;
						x = i;
					}
				}

			}
			store_string = contacts_list[n]->getLastName();
			k = 0;
			for (int i = x; i < strlen(advance_string.c_str()); i++)
			{
				for (int j = 0; j < strlen(store_string.c_str()); j++)
				{
					if (store_string[j] == advance_string[i] && k < j) {
						count++;
						k = j;
					}
				}

			}
			if (count == strlen(advance_string.c_str()))
			{
				cout << "\nFirst Name: " << contacts_list[n]->getFirstName() << endl;
				cout << "Last Name: " << contacts_list[n]->getLastName() << endl;
				cout << "Mobile no.: " << contacts_list[n]->getMobileNumber() << endl;
				cout << "Email: " << contacts_list[n]->getEmailAddress() << endl;
				cout << "Address: " << endl;
				cout << "House: " << contacts_list[n]->getAddress()->getHouse() << endl;
				cout << "Street: " << contacts_list[n]->getAddress()->getStreet() << endl;
				cout << "City: " << contacts_list[n]->getAddress()->getCity() << endl;
				cout << "Country: " << contacts_list[n]->getAddress()->getCountry() << endl;
				//	cout << "Group: " << contacts_list[n]->getGroup() << endl << endl;
				cout << endl;
				contact_count++;
			}
		}
		count = 0;
		for (int n = 0; n < contacts_count; n++)
		{
			store_string = contacts_list[n]->getMobileNumber();
			for (int i = 0; i < strlen(advance_string.c_str()); i++)
			{
				for (int j = 0; j < strlen(store_string.c_str()); j++)
				{
					if (store_string[j] == advance_string[i] && k < j) {
						count++;
						k = j;
						x = i;
					}
				}

			}

			if (count == strlen(advance_string.c_str()))
			{
				cout << "\nFirst Name: " << contacts_list[n]->getFirstName() << endl;
				cout << "Last Name: " << contacts_list[n]->getLastName() << endl;
				cout << "Mobile no.: " << contacts_list[n]->getMobileNumber() << endl;
				cout << "Email: " << contacts_list[n]->getEmailAddress() << endl;
				cout << "Address: " << endl;
				cout << "House: " << contacts_list[n]->getAddress()->getHouse() << endl;
				cout << "Street: " << contacts_list[n]->getAddress()->getStreet() << endl;
				cout << "City: " << contacts_list[n]->getAddress()->getCity() << endl;
				cout << "Country: " << contacts_list[n]->getAddress()->getCountry() << endl;
				//	cout << "Group: " << contacts_list[n]->getGroup() << endl << endl;
				cout << endl;
				contact_count++;
			}
		}
		count = 0;
		for (int n = 0; n < contacts_count; n++)
		{
			store_string = contacts_list[n]->getEmailAddress();
			for (int i = 0; i < strlen(advance_string.c_str()); i++)
			{
				for (int j = 0; j < strlen(store_string.c_str()); j++)
				{
					if (store_string[j] == advance_string[i] && k < j) {
						count++;
						k = j;
						x = i;
					}
				}

			}
			store_string = contacts_list[n]->getLastName();
			k = 0;

			if (count == strlen(advance_string.c_str()))
			{
				cout << "\nFirst Name: " << contacts_list[n]->getFirstName() << endl;
				cout << "Last Name: " << contacts_list[n]->getLastName() << endl;
				cout << "Mobile no.: " << contacts_list[n]->getMobileNumber() << endl;
				cout << "Email: " << contacts_list[n]->getEmailAddress() << endl;
				cout << "Address: " << endl;
				cout << "House: " << contacts_list[n]->getAddress()->getHouse() << endl;
				cout << "Street: " << contacts_list[n]->getAddress()->getStreet() << endl;
				cout << "City: " << contacts_list[n]->getAddress()->getCity() << endl;
				cout << "Country: " << contacts_list[n]->getAddress()->getCountry() << endl;
				//	cout << "Group: " << contacts_list[n]->getGroup() << endl << endl;
				cout << endl;
				contact_count++;
			}
		}


		cout << contact_count << " Contacts Found!" << endl;

	}

	void createGroup(string groupName) {
		if (groups_count < 100) {
			groups[groups_count] = new Group(groupName);
			groups_count++;
			cout << "\nGroup '" << groupName << "' created successfully." << endl;
		}
		else {
			cout << "\nMaximum number of groups reached. Cannot create more groups." << endl;
		}
	}

	void addContactToGroup(Contact contact, string groupName) {
		for (int i = 0; i < groups_count; i++) {
			if (groups[i]->checkGroup(groupName)) {
				groups[i]->addContact(&contact);
				return;
			}
		}
		cout << "Group '" << groupName << "' not found." << endl;
	}

	void removeContactfromGroup()
	{
		string name;
		int num;
		bool flag = false;

		cout << "Enter name of group you want to remove contacts from: ";
		cin.ignore();
		getline(cin, name);


		for (int i = 0; i < groups_count; i++)
		{
			if (groups[i]->getGroupName() == name) {
				system("cls");
				groups[i]->displayContacts();
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "\nNo gorup found with name " << name << endl;
			return;
		}

		cout << "\nEnter number of contact you want to delete in the group: ";
		cin >> num;

		for (int i = 0; i < groups_count; i++)
		{

			if (groups[i]->checkGroup(name)) {
				groups[i]->removeContact(num);
				return;
			}
		}
		cout << "Group '" << name << "' not found." << endl;
	}

	void printGroupContacts()
	{
		for (int i = 0; i < groups_count; i++)
		{
			cout << "Group " << i + 1 << ":\n";
			groups[i]->displayContacts();
		}
	}

	void deleteGroup(string groupName) {
		int index = -1;
		for (int i = 0; i < groups_count; i++) {
			if (groups[i]->getGroupName() == groupName) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			delete groups[index];

			for (int i = index; i < groups_count - 1; ++i) {
				groups[i] = groups[i + 1];
			}
			groups_count--;
			cout << "Group '" << groupName << "' deleted successfully." << endl;
		}
		else {
			cout << "Group '" << groupName << "' not found." << endl;
		}
	}


};

int ContactsBook::contacts_count = 0;

class SearchHistory
{
	string history[100];
	static int historyCount;
public:

	void SearchBox(string hist)
	{
		if (historyCount < 100)
		{
			history[historyCount] = hist;
			historyCount++;
		}
		if (historyCount >= 6)
		{
			for (int i = 0; i < 5; i++) {
				history[i] = history[i + 1];
			}
			historyCount--;
		}

	}

	void displayHistory()
	{
		int n, count = 1;
		if (historyCount < 6)
		{
			n = historyCount - 1;
		}
		else if (historyCount >= 5)
		{
			n = 4;
		}

		cout << "\nSearch history:\n";
		for (int i = n; i >= 0; i--)
		{
			cout << count << ". ";
			cout << history[i] << endl;
			count++;
		}
		count = 1;
	}
};

int SearchHistory::historyCount = 0;

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GroupMenu()
{
	setColor(2);
	for (int i = 0; i < 45; i++)
	{
		cout << static_cast<char>(220);
	}
	cout << "\n\t\tGROUP MENU\n";
	for (int i = 0; i < 45; i++)
	{
		cout << static_cast<char>(223);
	}
	setColor(14);
	cout << "\n\n1. Create a new Group\n";
	cout << "2. Add a Contact to a Group\n";
	cout << "3. Remove a Contact from a Group\n";
	cout << "4. Display All Contacts in a Group\n";
	cout << "5. Delete a Group\n";
	cout << "6. Return to Main Menu\n";
	setColor(15);
	cout << "\nEnter choice: ";
}

void Menu()
{
	setColor(10);
	for (int i = 0; i < 45; i++)
	{
		cout << static_cast<char>(220);
	}
	cout << "\n\t\tCONTACT MENU\n";
	for (int i = 0; i < 45; i++)
	{
		cout << static_cast<char>(223);
	}
	setColor(14);
	cout << "\n\n1.  Add Contact\n2.  Merge Duplicates\n";
	cout << "3.  Store to file\n4.  Load from file\n";
	cout << "5.  Print Contacts Sorted\n6.  Print / delete / update contacts\n";
	cout << "7.  Search contacts\n8.  Display count of contacts\n";
	cout << "9.  Manage Groups\n10. Search History\n11. Exit Program\n";

	setColor(15);
	cout << "\nEnter choice: ";
}

void WelcomeScreen()
{
	setColor(8);
	cout << "\n\n\n";
	cout << "\t\t     * * *       * * *     *      *  * * * * *    *         * * *   * * * * *  " << endl;
	cout << "\t\t   *      *    *       *   * *    *      *       * *      *      *      *       " << endl;
	cout << "\t\t   *          *         *  *  *   *      *      *   *     *             *       " << endl;
	cout << "\t\t   *          *         *  *   *  *      *     * * * *    *             *       " << endl;
	cout << "\t\t   *       *   *       *   *    * *      *    *       *   *       *     *       " << endl;
	cout << "\t\t     * * *       * * *     *      *      *   *         *    * * *       *       " << endl;

	cout << "\n\n";
	cout << "\t\t\t\t * * * *       * * *         * * *      *     *    " << endl;
	cout << "\t\t\t\t *      *    *       *     *       *    *   *      " << endl;
	cout << "\t\t\t\t * * * *    *         *   *         *   ** *       " << endl;
	cout << "\t\t\t\t *      *   *         *   *         *   * *        " << endl;
	cout << "\t\t\t\t *       *   *       *     *       *    *   *      " << endl;
	cout << "\t\t\t\t * * * *       * * *         * * *      *     *    " << endl;


	cout << "\n\n\n\t\t\t\t\t";
	system("pause");
	system("cls");
}

void loadingScreen() {
	cout << "\n\n\n\n\n\n\n";
	cout << "\t\t\t   *      " << "    * *    " << "     *     " << "  * * *    " << " * * * " << "  *    * " << "     * *    " << endl;
	cout << "\t\t\t   *      " << "  *     *  " << "    * *    " << "  *     *  " << "   *   " << "  **   * " << "   *     *  " << endl;
	cout << "\t\t\t   *      " << " *       * " << "   *   *   " << "  *      * " << "   *   " << "  * *  * " << "  *         " << endl;
	cout << "\t\t\t   *      " << " *       * " << "  * * * *  " << "  *      * " << "   *   " << "  *  * * " << "  *    * *  " << endl;
	cout << "\t\t\t   *      " << "  *     *  " << " *       * " << "  *     *  " << "   *   " << "  *   ** " << "   *     *  " << endl;
	cout << "\t\t\t   * * * *" << "    * *    " << "*         *" << "  * * *    " << " * * * " << "  *    * " << "     * * *  " << endl;
	cout << "\n\n\n\t\t\t  ";
	for (int i = 0; i < 70; i++)
	{
		cout << static_cast<char>(178);
	}
	cout << "\r\t\t\t ";
	setColor(10);
	for (int i = 0; i < 70; ++i) {
		cout << static_cast<char>(219);
		Sleep(69);
	}
	setColor(14);
	system("cls");
}

Contact takeInputs(Contact& tempContact)
{
	string first, last, mobile, email;
	string house, street, city, country;
	Address tempAddress;

	cout << "First Name: ";
	cin.ignore();
	getline(cin, first);
	tempContact.setFirstName(first);

	cout << "Last Name: ";
	getline(cin, last);
	tempContact.setLastName(last);

	cout << "Mobile Number: ";
	getline(cin, mobile);
	if (mobile.size() > 11 || mobile.size() < 11)
	{
		do
		{
			cout << "\nInvalid Number!\nEnter a valid Number: ";
			getline(cin, mobile);
		} while (mobile.size() != 11);
	}

	tempContact.setMobileNumber(mobile);

	cout << "Email Address: ";
	getline(cin, email);
	tempContact.setEmail(email);

	cout << "House Number: ";
	getline(cin, house);
	tempAddress.setHouse(house);

	cout << "Street: ";
	getline(cin, street);
	tempAddress.setStreet(street);

	cout << "City: ";
	getline(cin, city);
	tempAddress.setCity(city);

	cout << "Country: ";
	getline(cin, country);
	tempAddress.setCountry(country);

	tempContact.setAddress(&tempAddress);

	return tempContact;

}

int main()
{
	bool ProgramEnd = false;
	int menuChoice, searchChoice, delContChoice;
	int groupChoice;

	string first, last, mobile, email;
	string house, street, city, country;

	SearchHistory history;
	ContactsBook contactbook;
	Address tempAddress, findAddress;
	Contact tempContact;

	WelcomeScreen();
	loadingScreen();

	while (!ProgramEnd)
	{
		Menu();
		cin >> menuChoice;

		if (menuChoice == 1)
		{

			cout << "\nEnter details of contact you want to add:\n";
			contactbook.add_contact(takeInputs(tempContact));

			cout << endl;
			system("pause");
			system("cls");

		}

		else if (menuChoice == 2)
		{
			contactbook.merge_duplicates();
			cout << endl;
			system("pause");
			system("cls");
		}

		else if (menuChoice == 3)
		{
			contactbook.save_to_file();
			cout << endl;
			system("pause");
			system("cls");

		}

		else if (menuChoice == 4)
		{
			contactbook.input_from_file();

			cout << endl;
			system("pause");
			system("cls");

		}

		else if (menuChoice == 5)
		{
			cout << "\n1. Sort All by first names\n2. Sort All by last name\n";
			cout << "\nEnter your chocie: ";
			cin >> searchChoice;

			contactbook.print_contacts_sorted(searchChoice);

			cout << endl;
			system("pause");
			system("cls");
		}

		else if (menuChoice == 6)
		{
			contactbook.printAllContacts();

			setColor(10);
			cout << "\n1. To view/update/delete a specific contact\n";
			setColor(1);
			cout << "2. Continue";
			setColor(15);
			cout << "\n\nEnter choice : ";
			cin >> searchChoice;

			if (searchChoice == 1)
			{
				cout << "Enter contact number you want the details of: ";
				cin >> delContChoice;
				contactbook.printSpecificContact(delContChoice);

				setColor(4);
				cout << "\n1. To delete contact";
				setColor(10);
				cout << "\n2. To update contact";
				setColor(1);
				cout << "\n3. Continue\n\n";
				setColor(15);
				cout << "Enter your choice: ";
				cin >> menuChoice;

				if (menuChoice == 1)
				{
					contactbook.deleteContact(delContChoice);
					cout << endl;
					system("pause");
					system("cls");
					continue;
				}
				else if (menuChoice == 2)
				{
					cout << "\nEnter the new updated info:\n";

					contactbook.updateContact(delContChoice, takeInputs(tempContact));

					cout << endl;
					system("pause");
					system("cls");
					continue;
				}
				else if (menuChoice == 3)
				{
					system("cls");
					continue;
				}
				else
				{
					cout << "\nInvalid input\n";
				}


			}
			else if (searchChoice == 2)
			{
				system("cls");
				continue;

			}
			else
			{
				cout << "Invalid input\n";
			}

			cout << endl;
			system("pause");
			system("cls");
		}

		else if (menuChoice == 7)
		{
			system("cls");
			cout << "\n1. Search by Name\n2. Search by Mobile number";
			cout << "\n3. Search by Address\n4. General Search\n5. Advance Search\n\nEnter your choice: ";
			cin >> searchChoice;

			if (searchChoice == 1)
			{

				cout << "\nEnter the name of person you want to find:\n";
				cout << "First Name: ";
				cin >> first;
				cout << "Last Name: ";
				cin >> last;

				string combinedName = first + " " + last;

				history.SearchBox(combinedName);

				cout << endl;
				if (contactbook.search_contact(first, last) != nullptr)
				{
					contactbook.search_contact(first, last)->printContactInfo();
				}

				cout << endl;

				system("pause");
				system("cls");

			}

			else if (searchChoice == 2)
			{

				cout << "Enter mobile number of the person you want to find: ";
				cin.ignore();
				getline(cin, mobile);

				history.SearchBox(mobile);

				cout << endl;
				if (contactbook.search_contact(mobile) != nullptr)
				{
					contactbook.search_contact(mobile)->printContactInfo();
				}

				cout << endl;

				system("pause");
				system("cls");

			}

			else if (searchChoice == 3)
			{
				cout << "Enter the address of person you want to find:\n";
				cout << "House Number: ";
				cin >> house;
				findAddress.setHouse(house);

				cout << "Street: ";
				cin >> street;
				findAddress.setStreet(street);

				cout << "City: ";
				cin >> city;
				findAddress.setCity(city);

				cout << "Country: ";
				cin >> country;
				findAddress.setCountry(country);

				string combineAddress = "House No. " + house + ", Street " + street + ", " + city + ", " + country;
				history.SearchBox(combineAddress);


				cout << endl;
				if (contactbook.search_contact(&findAddress) != nullptr)
				{
					contactbook.search_contact(&findAddress)->printContactInfo();
				}

				cout << endl;

				system("pause");
				system("cls");

			}
			else if (searchChoice == 4)
			{
				cout << "Enter any info of contact to find: ";
				cin.ignore();
				getline(cin, first);

				history.SearchBox(first);

				if (contactbook.general_search(first) != nullptr)
				{
					contactbook.general_search(first)->printContactInfo();
				}

				cout << endl;

				system("pause");
				system("cls");
			}
			else if (searchChoice == 5)
			{
				contactbook.advance_search();

				cout << endl;

				system("pause");
				system("cls");
			}


			else
			{
				cout << "\nInvalid Input\n";
				system("pause");
				system("cls");
			}
		}

		else if (menuChoice == 8)
		{
			cout << "\nTotal number of contacts saved in contact book = " << contactbook.total_contacts() << endl;

			cout << endl;
			system("pause");
			system("cls");
		}

		else if (menuChoice == 9)
		{
			while (true)
			{
				system("cls");
				GroupMenu();
				cin >> groupChoice;
				if (groupChoice == 1)
				{
					cout << "\nEnter name of your group: ";
					cin.ignore();
					getline(cin, first);

					contactbook.createGroup(first);

					cout << endl;
					system("pause");
					system("cls");

				}
				else if (groupChoice == 2)
				{
					cout << "Enter name of group you want to add contacts in: ";
					cin.ignore();
					getline(cin, first);


					cout << "\nEnter details of contact you want to add:\n";
					contactbook.addContactToGroup((takeInputs(tempContact)), first);

					cout << endl;
					system("pause");
					system("cls");
				}
				else if (groupChoice == 3)
				{


					contactbook.removeContactfromGroup();

					cout << endl;
					system("pause");
					system("cls");
				}
				else if (groupChoice == 4)
				{
					system("cls");
					contactbook.printGroupContacts();

					cout << endl;
					system("pause");
					system("cls");
				}

				else if (groupChoice == 5)
				{
					cout << "Enter name of group you want to delete: ";
					cin.ignore();
					getline(cin, first);

					contactbook.deleteGroup(first);

					cout << endl;
					system("pause");
					system("cls");
				}

				else if (groupChoice == 6)
				{
					system("cls");
					break;
				}

				else
				{
					cout << "\nInvalid Input\n";

					system("pause");
					system("cls");
				}
				system("cls");
			}
		}

		else if (menuChoice == 10)
		{
			history.displayHistory();

			cout << endl;
			system("pause");
			system("cls");
		}

		else if (menuChoice == 11)
		{
			ProgramEnd = true;
		}

		else
		{
			cout << "\nInvalid Input\n";

			system("pause");
			system("cls");
		}

	}

	cout << "\nProgram Ended\n";
	cout << endl;
	system("pause");
	return 0;
}