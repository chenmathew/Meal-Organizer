//Mathew Chen, Program 4, header.h
//INPUT: Nothing
//OUTPUT: Data structures
//Creates the data structures
//This program allows the user to organize meals and stores the restaurant, rating, etc.

#include <iostream>
#include <cstring>
#include <fstream>

//Hash table size
const int tablesize = 101;



//Meal Structure
struct meal
{
	meal (); //Constructor
	~meal (); //Destructor
	int copy (meal * tocopy); //Copies 
	char * mealname;
	char * placename;
	char * review;
	char * placetype;
	double price;
	int rating;
};



//Node structure
struct node
{
	node (); //Constructor
	~node (); //Destructor
	meal * details;
	node * left;
	node * right;
};


//Table functions
class table
{
	public:
		table (); //Default constructor
		int removeall (); //Destructor wrapper
		int removeall (node * root); //Destructor
		~table (); //Default destructor
		int insert (char newmealname [], char newplacename [], char newreview [], char newplacetype [], double price, int rating); //Inserts user data
		node * insert (node * root, node * temp); //Insert function
		int removebymeal (char newmealname []); //Removes by meal
		int displaymatch (char mealname []); //Displays the matching data
		int displayall (); //Displays all
		int getheight (); //gets height
		int removepartmeal (char mealname [], char placename []); //Removes particu;lar meal
		bool isefficient (); //Is it efficient
		int searchformeal (char * mealname, meal matches [], int size); //Searches for meal
	private:
		int searchformeal (node * root, char * mealname, meal matches [], int counter, int size); //Searches for meal
		int removepartmeal (node *& root, char mealname [], char placename []); //Removes part. meal
		node * mintocopy (node *& root); //Copies IOS
		int getheight (node * root); //Gets height
		int displaymatch (node * root, char mealname []); //Displays match
		int displayall (node * root); //DIsplays all
		node * root; //names root for class
};
