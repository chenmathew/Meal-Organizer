//Mathew Chen, Program 4, functions.cpp
//INPUT: Use input from main
//OUTPUT: Functions into main
//Functions for the program, not accessible by user
//This program allows the user to organize meals and stores the restaurant, rating, etc.

#include "header.h"
using namespace std;


//Default constructor for table
table :: table ()
{
	root = NULL;
}



//Default destructor for table
table :: ~table ()
{
	removeall ();
}



//Wrapper for destructor
int table :: removeall ()
{
	removeall (root);
	return 1;
}



//Destructor
int table :: removeall (node * root)
{
	if (!root)
		return 0;
	removeall (root -> left);
	removeall (root -> right);
	delete root;
	return 1;
}



//Default destructor for node
node :: node ()
{
	details = new meal;
	left = NULL;
	right = NULL;
}



//Default destructor for node
node :: ~node ()
{
	delete details;
}



//Constructor for meal
meal :: meal ()
{
	mealname = NULL;
	placename = NULL;
	review = NULL;
	placetype = NULL;
	price = 0;
	rating = 0;
}



//Destructor for meal
meal :: ~meal ()
{
	if (mealname)
	delete [] mealname;
	if (placename)
	delete [] placename;
	if (review)
	delete [] review;
	if (placetype)
	delete [] placetype;
}



//INPUT: Meal info
//OUTPUT: Node to copy into file
//Copies user into to temp node
int table :: insert (char newmealname [], char newplacename [], char newreview [], char newplacetype [], double price, int rating)
{
	node * temp = new node;
	temp -> details -> mealname = new char [strlen (newmealname) + 1];
	temp -> details -> placename = new char [strlen (newplacename) + 1];
	temp -> details -> review = new char [strlen (newreview) + 1];
	temp -> details -> placetype = new char [strlen (newplacetype) + 1];
	strcpy (temp -> details -> mealname, newmealname);
	strcpy (temp -> details -> placename, newplacename);
	strcpy (temp -> details -> review, newreview);
	strcpy (temp -> details -> placetype, newplacetype);
	temp -> details -> price = price;
	temp -> details -> rating = rating;
	temp -> left = NULL;
	temp -> right = NULL;

	if (!root)
	{
		root = temp;
		return 1;
	}
	root = insert (root, temp);
	return 1;
}



//INPUT: Things copied into temp
//OUTPUT: Inserts to tree
//Inserts to tree using string compare
node * table :: insert (node * root, node * temp)
{
	if (!root)
	{
		root = temp;
	}
	else if (strcmp (root -> details -> mealname, temp -> details -> mealname) >= 0)
	{
		root -> left = insert (root -> left, temp);
	}
	else
	{
		root -> right = insert (root -> right, temp);
	}
	return root;
}



//INPUT: Mealname
//OUTPUT: How many matches there are
//Wrapper for search meal
int table :: searchformeal (char * mealname, meal matches [], int size)
{
	if (!root)
		return 0;
	return searchformeal (root, mealname, matches, 0, size);
}




//INPUT: Mealname
//OUTPUT: How many matches there are
//Searches for matches and 
int table :: searchformeal (node * root, char * mealname, meal matches [], int counter, int size)
{
	if (!root)
		return counter;
	if (!strcmp (mealname, root -> details -> mealname) && counter < size)
	{
		matches [counter].copy (root -> details);
		++counter;
	}
	counter = searchformeal (root -> left, mealname, matches, counter, size);
	counter = searchformeal (root -> right, mealname, matches, counter, size);
	return counter;
}



//INPUT: Data to copy
//OUTPUT: Meal object
//Copies meal
int meal :: copy (meal * tocopy)
{
	if (!tocopy)
		return 0;
	else
	{
		if (mealname)
			delete [] mealname;
		if (tocopy -> mealname)
		{
			mealname = new char [strlen (tocopy -> mealname) + 1];
			strcpy (mealname, tocopy -> mealname);
		}
		else
		{
			mealname = NULL;
		}
		if (placename)
			delete [] placename;
		if (tocopy -> placename)
		{
			placename = new char [strlen (tocopy -> placename) + 1];
			strcpy (placename, tocopy -> placename);
		}
		else
		{
			placename = NULL;
		}
		if (review)
			delete [] review;
		if (tocopy -> review)
		{
			review = new char [strlen (tocopy -> review) + 1];
			strcpy (review, tocopy -> review);
		}
		else
		{
			review = NULL;
		}
		if (placetype)
			delete [] placetype;
		if (tocopy -> placetype)
		{
			placetype = new char [strlen (tocopy -> placetype) + 1];
			strcpy (placetype, tocopy -> placetype);
		}
		else
		{
			placetype = NULL;
		}
		price = tocopy -> price;
		rating = tocopy -> rating;
	}
	return 1;
}



//INPUT: Meal name
//OUTPUT: Success/Failure
//removes the meal name only if it matches the place name
int table :: removepartmeal (char mealname [], char placename [])
{
	if (!root)
		return 0;
	return removepartmeal (root, mealname, placename);
}



//INPUT: Meal name
//OUTPUT: Success/Failure
//removes the meal name only if it matches the place name
int table :: removepartmeal (node *& root, char mealname [], char placename [])
{
	if (!root)
		return 0;
	if (!strcmp (mealname, root -> details -> mealname) && !strcmp (placename, root -> details -> placename))
	{
		if (!root -> right && !root -> left)
		{
			delete root;
			root = NULL;
			return 1;
		}
		if (root -> left && !root -> right)
		{
			node * temp = root;
			root = root -> left;
			delete temp;
			return removepartmeal (root, mealname, placename) + 1;
		}
		if (!root -> left && root -> right)
		{
			node * temp = root;
			root = root -> right;
			delete temp;
			return removepartmeal (root, mealname, placename) + 1;
		}
		node * temp = mintocopy (root -> right);
		temp -> left = root -> left;
		temp -> right = root -> right;
		delete root;
		root = temp;
		return removepartmeal (root, mealname, placename) + 1;
	}
	removepartmeal (root -> left, mealname, placename);
	removepartmeal (root -> right, mealname, placename);
	return 1;
}



//INPUT: Root node
//OUTPUT: Temp node
//Copies the in order successor
node * table :: mintocopy (node *& root)
{
	if (!root)
		return NULL;
	if (root -> left)
		return mintocopy (root -> left);
	node * temp = root;
	root = root -> right;
	return temp;
}



//INPUT: Location and node
//OUTPUT: Success/Failure
//Displays all data under the mealname
int table :: displaymatch (char mealname [])
{
	if (!root)
		return 0;
	return displaymatch (root, mealname);
}



//INPUT: Location and node
//OUTPUT: Success/Failure
//Displays all data under the mealname
int table :: displaymatch (node * root, char mealname [])
{
	if (!root)
		return 0;
	if (!strcmp (mealname, root -> details -> mealname))
	{
		cout << "Mealname: " << root -> details -> mealname << endl;
		cout << "Place name: " << root -> details -> mealname << endl;
		cout << "Review: " << root -> details -> mealname << endl;
		cout << "Place type: " << root -> details -> mealname << endl;
		cout << "Price: " << root -> details -> mealname << endl;
		cout << "Rating: " << root -> details -> mealname << endl;
	}
	displaymatch (root -> left, mealname);
	displaymatch (root -> right, mealname);
	return 1;
}



//INPUT: Nothing
//OUTPUT: Height
//Gets the height
int table :: getheight ()
{
	if (!root)
		return 0;
	return getheight (root);
}



//INPUT: Nothing
//OUTPUT: Height
//Gets the height
int table :: getheight (node * root)
{
	if (!root)
	{
		return 0;
	}
	int ldepth = getheight (root -> left) + 1;
	int rdepth = getheight (root -> right) + 1;
	if (rdepth > ldepth)
		return rdepth;
	else
		return ldepth;
}



//INPUT: Nothing
//OUTPUT: True/False
//Tells if it's efficient
bool table :: isefficient ()
{
	if (!root)
		return 0;
	int ldepth = getheight (root -> left) + 1;
	int rdepth = getheight (root -> right) + 1;
	if (rdepth - ldepth < -1 || rdepth - ldepth > 1)
		return false;
	else
		return true;
}



//INPUT: Nothing
//OUTPUT: Displays all
//Displays tree in order
int table :: displayall ()
{
	if (!root)
		return 0;
	return displayall (root);
}



//INPUT: Nothing
//OUTPUT: Displays all
//Displays tree in order
int table :: displayall (node * root)
{
	if (!root)
		return 0;
	displayall (root -> left);
	cout << "Meal name: " << root -> details -> mealname << endl;
	cout << "Place name: " << root -> details -> mealname << endl;
	cout << "Review: " << root -> details -> mealname << endl;
	cout << "Place type: " << root -> details -> mealname << endl;
	cout << "Price: " << root -> details -> mealname << endl;
	cout << "Rating: " << root -> details -> mealname << endl;
	displayall (root -> right);
	return 1;
}
