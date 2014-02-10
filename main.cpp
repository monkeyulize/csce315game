#include "table.h"
#include "database.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	database database();
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
	bob.push_back("4");
	//third
	vector<string> marty;
	bob.push_back("marty");
	bob.push_back("tiger");
	bob.push_back("5");
	//inserting first tuple
	t.insert(joe);

	//creating tuples
	vector<string> bob;
	bob.push_back("bob");
	bob.push_back("cat");
	bob.push_back("4");

	//inserting second tuple
	t.insert(bob);

	t.display_table();
	
	
	
	cout << "\n\n";

	t.update("years = 6", "years < 5");	

	t.display_table();
	
	cout<<endl<<endl;
	
	database.create_table("pets",attribute_names;,primary_key)
	database.create_table("felines",attribute_names;,primary_key)
	database.get_table("pets").insert(joe);
	database.get_table("pets").insert(bob);
	database.get_table("felies").insert(bob);
	database.get_table("felies").insert(marty);
	table temp = database.get_table("pets").set_union("felines");
	temp.display_table();
	
	
	cin.get();
	return 0;
}