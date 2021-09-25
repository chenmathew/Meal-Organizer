//Mathew Chen, Program 4, main.cpp
//INPUT: User input
//OUTPUT: Data into functions
//Client program, menu like.
//This program allows the user to organize meals and stores the restaurant, rating, etc.

#include "header.h"
using namespace std;


int main ()
{
	table t;
	char mealname [100]; char placename [100]; char review [100]; char placetype [100]; double price; int rating;
	meal m;
	meal array [10];
	int choice = 0;

	while (choice != 8)
	{
		cout << "1. New meal" << endl << "2. Search meal" << endl << "3. Remove meal at particular place" << endl << "4. Display matches" << endl << "5. Display all" << endl << "6. Get height" << endl << "7. Is it efficient?" << endl << "8. Quit" << endl;
		cin >> choice;
		cin.ignore (100, '\n');
		if (choice == 1)
		{
			cout << "enter meal name" << endl;
			cin.get (mealname, 100, '\n');
			cin.ignore (100, '\n');
			cout << "enter place name" << endl;
			cin.get (placename, 100, '\n');
			cin.ignore (100, '\n');
			cout << "enter place type" << endl;
			cin.get (review, 100, '\n');
			cin.ignore (100, '\n');
			cout << "enter review" << endl;
			cin.get (placetype, 100, '\n');
			cin.ignore (100, '\n');
			cout << "enter price in numbers)" << endl;
			cin >> price;
			cin.ignore (100, '\n');
			cout << "enter rating (1-10)" << endl;
			cin >> rating;
			cin.ignore (100, '\n');
			t.insert (mealname, placename, review, placetype, price, rating);
		}
		if (choice == 2)
		{
			cout << "enter meal name" << endl;
			cin.get (mealname, 100, '\n');
			int count = t.searchformeal (mealname, array, 10);
			cout << "mealcount: " << count << endl;
			for (int i = 0; i < count; ++i)
			{
				cout << "mealname: " << array [i].mealname << endl;
			}
		}
		if (choice == 3)
		{
			cout << "enter meal name" << endl;
			cin.get (mealname, 100, '\n');
			cin.ignore (100, '\n');
			cout << "enter place name" << endl;
			cin.get (placename, 100, '\n');
			cin.ignore (100, '\n');
			t.removepartmeal (mealname, placename);
		}
		if (choice == 4)
		{
			cout << "enter meal name" << endl;
			cin.get (mealname, 100, '\n');
			cin.ignore (100, '\n');
			t.displaymatch (mealname);
		}
		if (choice == 5)
			t.displayall ();
		if (choice == 6)
		{
			if (t.getheight () == -1)
				cout << "add some meals" << endl;
			else
				cout << "height: " << t.getheight () << endl;
		}
		if (choice == 7)
		{
			if (!t.isefficient ())
				cout << "no" << endl;
			else
				cout << "yes" << endl;
		}
		if (choice == 8)
			choice = 8;

	}
	return 0;
}
