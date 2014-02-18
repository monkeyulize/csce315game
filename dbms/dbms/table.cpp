#include "table.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//mutator function
void table::set_attr_names(vector<string> _attribute_names) {
	attribute_names = _attribute_names;
}

//Helper functions
//inserts an entity into table
void table::insert(vector<string> _field_values) {
	entity e;
	vector<bool> found;
	bool present = true;
	
	for (int i = 0; i < _field_values.size(); i++){
		e.set_attribute(attribute_names[i], _field_values[i]);
	}

	for (int i = 0; i < primary_key.size(); i++){
		found.push_back(false);
		for (int j = 0; j < entity_table.size(); j++){
			if (e.attributes[primary_key[i]] == entity_table[j].attributes[primary_key[i]]){
				found[i] = true;
			}
		}
	}

	for (int k = 0; k < found.size(); k++){
		if (found[k] == false){
			present = false;
		}
	}

	if (present == false){
		entity_table.push_back(e);
	}
	
	if (present){
		cout << "Duplicate entity detected. Insert FAILED." << endl;
	}
	
	
	
}

//prints table for user
void table::display_table() {
	cout << name << endl;
	for(int i = 0; i < attribute_names.size(); i++){
		cout << attribute_names[i] << '\t';
	}
	
	cout << endl;
	
	for(int i = 0; i < entity_table.size(); i++){		
		entity_table[i].show_attributes(attribute_names);
		cout << endl;
	}
}

//chuncks a string by spaces and returns a vector with inputs
vector<string> table::split_on_spaces(string str) {
	istringstream iss(str);
	string s;
	vector<string> result;

	while (getline(iss, s, ' ')){
		result.push_back(s.c_str());
	}
	
	return result;
}

//goes through table andfinds which arguements meet set arguments and updates though values
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

//goes through table and deletes arguements that meet set arguments
void table::delete_from(string _where_argument) {
	vector<string> where_args = split_on_spaces(_where_argument);

	for (int i = 0; i < entity_table.size(); i++)
	{
		if (where_args[1] == "=") {
			if (entity_table[i].attributes[where_args[0]] == where_args[2]) {	//hack that should work with an argument like "x1 < 0"
				entity_table.erase(entity_table.begin() + i);
			}
		}
		else if (where_args[1] == "<") {
			if (entity_table[i].attributes[where_args[0]] < where_args[2]) {
				entity_table.erase(entity_table.begin() + i);
			}
		}
		else if (where_args[1] == ">") {
			if (entity_table[i].attributes[where_args[0]] > where_args[2]) {
				entity_table.erase(entity_table.begin() + i);
			}
		}
		else if (where_args[1] == "!=") {
			if (entity_table[i].attributes[where_args[0]] != where_args[2]) {
				entity_table.erase(entity_table.begin() + i);
			}
		}
	}
}
