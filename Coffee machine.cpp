#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

fstream user_data("user_data.bin", ios::out|ios::in);
fstream drinks_data("drinks.bin", ios::out | ios::in);

struct User
{
	char nickname[15];
	char password[15];
	bool admin = false;
};

struct Drink
{
	char drink[15];
	double price;
	bool deleted = false;
};


void menu_for_user(User* pointer);
void menu_for_admin(User* pointer);
void Entry();
void sign_in();
void sign_up();
void add();
void all_drinks();
void delete_drink();
bool compare(char name[], char nickname[]);
void purchase();
void fill_vector_with_data(vector<Drink> &data);
//void fill_vector_with_data(vector<User> &data);
void update_data(vector<Drink> data);
//void update_data(vector<User> data);

vector<Drink> drinks;
vector<User> users;

int main()
{
	fill_vector_with_data(drinks);
	//fill_vector_with_data(users);
	cout << "Welcome to our coffe shop\n";
	Entry();
}

void sign_in()
{
	cout << "Enter your name: ";
	char name[15], password[15];
	cin.getline(name, 15);
	cout << "Enter password: ";
	cin.getline(password, 15);
	user_data.close();
	user_data.open("user_data.bin", ios::out | ios::in);
	User* temp = new User;
	user_data.read((char*)temp, sizeof(User));
	if (compare(name, temp->nickname) && compare(password,temp->password))
	{
		cout << "Welcome\n";
		if (temp->admin) menu_for_admin(temp);
		else menu_for_user(temp);
		return;
	}
	while(!user_data.eof())
	{
		if (compare(name,temp->nickname) && compare(password,temp->password))
		{
			cout << "Welcome\n";
			if (temp->admin) menu_for_admin(temp);
			else menu_for_user(temp);
			return;
		}
		user_data.read((char*)temp, sizeof(User));
	}
	cout << "Wrong name or password\n";
	Entry();
}

void sign_up()
{
	cout << "Create name (max 15 symbols) : ";
	char name[15];
	cin.getline(name, 15);
	User temp;
	user_data.close();
	user_data.open("user_data.bin", ios::in | ios::out);
	user_data.read((char*)&temp, sizeof(User));
	if (compare(name, temp.nickname))
	{
		cout << "Such name already exists\n";
		sign_up();
		return;
	}
	while (!user_data.eof())
	{
		if (compare(name,temp.nickname))
		{
			cout << "Such name already exists\n";
			sign_up();
			return;
		}
		user_data.read((char*)&temp, sizeof(User));
	}
	User* a = new User;
	for (int i = 0; i<15; ++i)
	{
		a->nickname[i] = name[i];
	}
	cout << "\nCreate password (max 15 symbols) : ";
	cin.getline(a->password, 15);
	cout << "\nEnter 69 if you want to have administration rights\n";
	string choice;
	cin >> choice;
	cin.ignore();
	if (choice == "69")
	{
		a->admin = true;
		cout << "Your admin account was created\n";
	}
	else
	{
		cout << "Your user account was created\n";
	}
	user_data.close();
	user_data.open("user_data.bin", ios::app | ios::out);
	user_data.write((char*)a, sizeof(User));
	user_data.close();
	user_data.open("user_data.bin", ios::in | ios::out);
	if (!a->admin) menu_for_user(a);
	else menu_for_admin(a);
}

void menu_for_user(User* pointer)
{
	cout << "\nSee all drinks and prices [1]\n";
	cout << "Buy drink [2]\n";
	cout << "Change user [3]\n";
	char choice;
	cin >> choice;
	switch (choice)
	{
	case '1':
	{
		all_drinks();
		break;
	}
	case '2':
	{
		purchase();
		break;
	}
	case '3':
	{
		Entry();
		return;
	}
	default:
	{
		menu_for_user(pointer);
		break;
	}
	}
	menu_for_user(pointer);
}

void menu_for_admin(User* pointer)
{
	cout << "\nAdd new drink [1]\n";
	cout << "See all drinks and prices [2]\n";
	cout << "Delete drink [3]\n";
	cout << "Change user [4]\n";
	char choice;
	cin >> choice;
	switch (choice)
	{
	case '1':
	{
		add();
		break;
	}
	case '2':
	{
		all_drinks();
		break;
	}
	case '3':
	{
		delete_drink();
		break;
	}
	case '4':
	{
		Entry();
		return;
	}
	default:
	{
		menu_for_user(pointer);
		break;
	}
	}
	menu_for_admin(pointer);
}

void Entry()
{
	cout << "Sign in [1]\n";
	cout << "Sign up [2]\n";
	cout << "Exit [3]\n";
	char choice;
	cin >> choice;
	cin.ignore();
	switch (choice)
	{
	case '1':
	{
		sign_in();
		break;
	}
	case '2':
	{
		sign_up();
		break;
	}
	case '3':
	{
		return;
	}
	default:
	{
		cout << "Press 1 or 2\n";
		Entry();
		break;
	}
	}
}

void add()
{
	Drink* drink = new Drink;
	cout << "Enter name of the drink: ";
	cin.ignore();
	cin.getline(drink->drink, 15);
	cout << "Enter price of the drink: ";
	cin >> drink->price;
	for (Drink c : drinks)
	{
		if (compare(c.drink, drink->drink) && drink->price == c.price)
		{
			cout << "\nSuch drink already exists!\n";
			return;
		}
	}
	drinks.push_back(*drink);
	delete drink;
	update_data(drinks);
}

void all_drinks()
{
	for (Drink c : drinks)
	{
		cout << c.drink << "	" << c.price << endl;
	}
}

void delete_drink()
{
	Drink* temp = new Drink;
	double price;
	cout << "Enter drink you want to delete: ";
	cin.ignore();
	cin.getline(temp->drink,15);
	cout << "Enter its price: ";
	cin >> price;
	for (int i=0,size=drinks.size();i<size;++i)
	{
		if (compare(temp->drink, drinks[i].drink) && price == drinks[i].price)
		{
			drinks.erase(drinks.begin() + i);
			break;
		}
	}
	delete temp;
	update_data(drinks);
}

bool compare(char name[], char nickname[])
{
	for (int i = 0; nickname[i] != '\0'; ++i)
	{
		if (nickname[i] != name[i])
		{
			return false;
		}
	}
	return true;
}

void purchase()
{
	all_drinks();
	cout << "\nWhat would you like? ";
	char order[15];
	cin.ignore();
	cin.getline(order, 15);
	for (int i = 0, size = drinks.size(); i < size; ++i)
	{
		if (compare(order, drinks[i].drink))
		{
			cout << "\nDrink successfully purchased!\n";
			break;
		}
	}
}

void fill_vector_with_data(vector<Drink> &data)
{
	Drink* temp = new Drink;
	drinks_data.read((char*)temp, sizeof(Drink));
	while (!drinks_data.eof())
	{
		data.push_back(*temp);
		drinks_data.read((char*)temp, sizeof(Drink));
	}
}

void update_data(vector<Drink> data)
{
	drinks_data.close();
	drinks_data.open("drinks.bin", ios::in | ios::out | ios::trunc);
	for (Drink c : data)
	{
			drinks_data.write((char*)& c, sizeof(Drink));
	}
}
