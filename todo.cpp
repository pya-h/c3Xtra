#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "include/console.h"

using namespace std;

int main()
{
	int menu = 0;
	while (menu != 3)
	{
		system(CLEAR_SCREEN);
		cout << "1. Set a new reminder  2. View the reminders 3. Quit ";
		cin >> menu;
		system(CLEAR_SCREEN);
		if (menu == 1)
		{
			string task, date;
			cout << "Enter the Date (yyyy-mm-dd) " << endl;
			cin >> date;
			cout << "Enter the name of the task " << endl;
			cin.ignore();
			getline(cin, task);
			fstream list("list.txt", ios::app);
			if (!list)
				fstream list("list.txt", ios::out);
			list << date << " " << task <<endl;
			list.close();
		}
		else if (menu == 2)
		{
			cout << "Enter the date that you want to see its reminders (yyyy-mm-dd) \n \'0\' for show all option" << endl;
			string date;
			cin >> date;
			int i = 1;
			fstream list("list.txt", ios::in);
			if (list)
			{
				while (list.good())
				{
					string s;
					list >> s;
					char temp = 0;
					if (date[0] == '0' || s == date)
					{
						cout << endl << i << ".";
						i++;
					}
					while (list.good() && temp != '\n')
					{
						temp = list.get();
						if (date[0] == '0' || s == date)
							cout << temp;
					}
				}
				cin.ignore();
				cin.get();
			}
			list.close();

		}

	}
}