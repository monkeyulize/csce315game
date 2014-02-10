#include "table.h"
#include "database.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	database db;
	//attributes list
	string name = "animals";
	vector<string> attribute_names;
	attribute_names.push_back("name");
	attribute_names.push_back("kind");
	attribute_names.push_back("years");

	//primary keys list
	vector<string> primary_key;
	primary_key.push_back("name");
	primary_key.push_back("kind");

	//creation of table using above
	table t (name, attribute_names, primary_key); 
	//database.create_table(name, attribute_names, primary_key); 
	
	//creating tuples
	//first
	vector<string> joe;
	joe.push_back("joe");
	joe.push_back("dog");
	joe.push_back("4");
	//second
	vector<string> bob;
	bob.push_back("bob");
	bob.push_back("cat");
	bob.push_back("3");
	//third
	vector<string> marty;
	marty.push_back("marty");
	marty.push_back("cat");
	marty.push_back("5");
	//forth
	vector<string> spot;
	spot.push_back("spot");
	spot.push_back("dog");
	spot.push_back("6");
	
	
	
	
	cout<<endl<<endl;
	
	db.create_table("dogs", attribute_names, primary_key);
	db.create_table("cats", attribute_names, primary_key);
	db.get_table("dogs").insert(joe);
	db.get_table("dogs").insert(spot);
	db.get_table("dogs").insert(bob);
	db.get_table("cats").insert(bob);
	db.get_table("cats").insert(marty);
	table temp = db.set_union("pets", "cats", "dogs");
	temp.display_table();
	
	
	cin.get();
	return 0;
}