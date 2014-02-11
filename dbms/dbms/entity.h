#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//template <class T>
class entity {
public:
	entity() {}
	map<string, string> attributes;
	void set_attribute(string _field_name, string _field_value);
	void add_column(string _field_name, string _field_value);
	void show_attributes(vector<string> _ordering);
	string get_attribute(string _attribute_name);
	
	bool operator == (const entity &Ref) const {
        return attributes==Ref.attributes;
    }	
};

#endif