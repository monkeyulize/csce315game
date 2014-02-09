#include "table.h"
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

	//creating tuples
	vector<string> joe;
	joe.push_back("joe");
	joe.push_back("dog");
	joe.push_back("4");

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

	cout<<t.entity_table[1]==t.entity_table[2];
	
	cout << "\n\n";

	t.update("years = 6", "years < 5");

	t.display_table();
	
	database.insert(t);
	
	cin.get();
	return 0;
}