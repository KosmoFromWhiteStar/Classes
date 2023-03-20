#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

#define LINE std::cout << "--------------" << std::endl;
#pragma warning(disable: 4996)

void letter_writer(std::string* letter)
{
	std::time_t ti = std::time(nullptr);
	std::tm* now_time = std::localtime(&ti);;


	std::stringstream ss;
	std::string temp = "";

	ss << std::put_time(now_time, "%d.%m.%Y %H:%M:%S");
	ss >> temp;
	*letter += temp + ' ';
	ss >> temp;
	*letter += temp;
	*letter += '\n';
}

bool compare(std::string inP_word, std::string command)
{
	if (inP_word.length() <= 0 || command.length() <= 0 || inP_word.length() != command.length())return false;
	for (int i = 0; i < inP_word.length() && i < command.length(); i++)
	{
		if (inP_word[i] != command[i] && (inP_word[i] + 32) != command[i] && (inP_word[i] - 32) != command[i])
		{
			return false;
		}
	}
	return true;
}

struct phonebook
{
	std::string num = "";
	std::string name = "";

	void write_num()
	{
		std::ofstream book("res\\phonebook.txt",std::ios::app);
		if (!book.is_open()) std::cerr << "Invalid path" << std::endl;

		book << name << ' ' << num << std::endl;

		book.close();
	}
};

class Phone
{
	std::vector <phonebook> peoples;
	bool status = true;
	void read_num()
	{
		
		std::ifstream book("res\\phonebook.txt");
		while (!book.eof())
		{
			phonebook add_num;
			if (!book.is_open()) std::cerr << "Invalid path" << std::endl;

			book >> add_num.name >> add_num.num;

			if (add_num.name != "" && add_num.num != "")
			{
				peoples.push_back(add_num);
			}
		}
		book.close();
	}
	void display(int* i)
	{
		LINE
			std::cout << "#" << *i << std::endl;
			std::cout << "Name: " << peoples[*i].name << std::endl;
			std::cout << "Num: " << peoples[*i].num << std::endl;
	}
	int find_person()
	{
		if (peoples.size() == 0)
		{
			read_num();
		}
		std::cout << "Input name or num" <<std::endl;
		std::string find;
		std::cin >> find;
		for (int i = 0; i < peoples.size(); i++)
		{
			if (compare(find, peoples[i].name) || compare(find, peoples[i].num))
			{
				return i;
				break;
			}
		}
		return -1;
	}
	void non_finded(int* find_num)
	{
		std::string ans = "";
		std::cout << "Can't find. Maybe add?[y/n]" << std::endl;
		std::cin >> ans;
		if (compare(ans, "y"))
		{
			add();
			*find_num = peoples.size() - 1;
		}
		else if (compare(ans, "n")) return;
	}

public:
	void add()
	{
		phonebook adress;

		std::cout << "Name: ";
		std::cin >> adress.name;

		x:
		std::cout << "Num: +7";
		std::string* temp = new std::string;
		std::cin >> *temp;
		adress.num += "+7" + *temp;
		delete temp;
		temp = nullptr;


		if (adress.num.length() != 12)
		{
			std::cerr << "Invalid num" << std::endl;
			goto x;
			return;
		}
		// write on file after all verification
		adress.write_num();
		peoples.push_back(adress);
	}
	void call()
	{
		int find_num = find_person();
		if (find_num < 0) non_finded(&find_num);
		if(find_num >= 0) std::cout << "CALL " << peoples[find_num].name << " num: " << peoples[find_num].num << std::endl;
	}
	void sms()
	{
		int find_num = find_person();
		if (find_num < 0) non_finded(&find_num);
		if (find_num >= 0) 
		{
			std::cout << "SMS to " << peoples[find_num].name << " num: " << peoples[find_num].num << std::endl;
			
			std::string path = "sms\\";

			path += peoples[find_num].name ;
			path += ".txt";
			std::cout << path;
			std::ofstream smska(path, std::ios::app);
			std::string sms = "";
			letter_writer(&sms);
			smska << sms;

			std::getline(std::cin, sms); // ZAEBAL NE RABOTAT

			smska << sms << std::endl;
			smska << "===================" << std::endl;
			smska.close();
		}
	}
	void exit()
	{
		status = false;
	}
	void list_num()
	{
		if (peoples.size() <= 0)
		{
			std::cout << "You haven't frinds at that moment" << std::endl;
			LINE
		}
		for (int i = 0; i < peoples.size(); i++)
		{
			display(&i);
		}
	}
	bool end() { return status; }
};

int main()
{
	std::string comm = "";
	Phone samsa;
	do
	{
		std::cout << "Input command : ";
		std::cin >> comm;
		if (compare(comm, "add"))samsa.add();
		else if (compare(comm, "call"))samsa.call();     // absolutly worked. DONT TOUCH
		else if (compare(comm, "list"))samsa.list_num(); // absolutly worked. DONT TOUCH
		else if (compare(comm, "sms"))samsa.sms();		 // DONT worked. Error when i close.
		else if (compare(comm, "exit"))samsa.exit();
		else std::cout << "Invalid command." << std::endl;

	} while(samsa.end());
}