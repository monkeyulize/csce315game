#include "table.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


void table::insert(vector<string> _field_values) {
	entity e;
	

	for(int i = 0; i < _field_values.size(); i++)
	{

		e.set_attribute(attribute_names[i], _field_values[i]);

	}
	entity_table.push_back(e);


}

void table::display_table() {
	cout << name << endl;
	for(int i = 0; i < attribute_names.size(); i++)
	{
		cout << attribute_names[i] << '\t';
	}

	cout << endl;


	for(int i = 0; i < entity_table.size(); i++)
	{
		
		entity_table[i].show_attributes(attribute_names);
		cout << endl;


	}





}

vector<string> table::split_on_spaces(string str) {
	istringstream iss(str);
	string s;
	vector<string> result;

	while (getline(iss, s, ' ')) {
		result.push_back(s.c_str());
	}

	return result;
}

void table::update(string _set_argument, string _where_argument) {
	vector<string> set_args = split_on_spaces(_set_argument);
	vector<string> where_args = split_on_spaces(_where_argument);

	for (int i = 0; i < entity_table.size(); i++)
	{
		//parse through set_args vector to determine which attribute to change (and to what)
		
		//then parse where_args vector to find the condition on which entities need
		//to be updated


		
		if (where_args[1] == "=") {
			if (entity_table[i].attributes[where_args[0]] == where_args[2]) {	//hack that should work with an argument like "x1 < 0"
				entity_table[i].attributes[set_args[0]] = set_args[2];	//hack that should work with an argument like "x1 = 0"
			}
		}
		else if (where_args[1] == "<") {
			if (entity_table[i].attributes[where_args[0]] < where_args[2]) {	
				entity_table[i].attributes[set_args[0]] = set_args[2];	
			}
		}
		else if (where_args[1] == ">") {
			if (entity_table[i].attributes[where_args[0]] > where_args[2]) {
				entity_table[i].attributes[set_args[0]] = set_args[2];	
			}
		}
		else if (where_args[1] == "!=") {
			if (entity_table[i].attributes[where_args[0]] != where_args[2]) {
				entity_table[i].attributes[set_args[0]] = set_args[2];
			}
		}
	}
}


void table::set_attr_names(vector<string> _attribute_names) {
	attribute_names = _attribute_names;


}