#include "table.h"
#include <iostream>
#include <string>
using namespace std;
//table::table(string _name, vector<string> _attrib_names, vector<string> _primary_key) {
//	name = _name;
//	attribute_names = _attrib_names;
//	primary_key = _primary_key;
//
//
//
//}



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