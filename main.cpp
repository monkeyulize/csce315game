#include "table.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string name = "animals";
	vector<string> attribute_names;
	attribute_names.push_back("name");
	attribute_names.push_back("kind");
	attribute_names.push_back("years");

	vector<string> primary_key;
	primary_key.push_back("name");
	primary_key.push_back("kind");

	table t (name, attribute_names, primary_key); //create table

	vector<string> joe;
	joe.push_back("joe");
	joe.push_back("dog");
	joe.push_back("4");

	t.insert(joe);

	vector<string> bob;
	bob.push_back("bob");
	bob.push_back("cat");
	bob.push_back("4");

	t.insert(bob);

	t.display_table();

	cout << "\n\n";

	t.update("years = 6", "years < 5");

	t.display_table();



	cin.get();
	return 0;
}