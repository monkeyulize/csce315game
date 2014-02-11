#ifndef TABLE_H
#define TABLE_H

#include "entity.h"
#include <vector>


class table {
private:

	string name;
public:
	table() {};
	table(string _name, vector<string> _attribute_names, vector<string> _primary_key) {name = _name; attribute_names = _attribute_names; primary_key = _primary_key;};
	void set_name(string _name) {
		name = _name;
	}
	string get_name() {
		return name;
	}
	void set_attr_names(vector<string> _attribute_names);
	void insert(vector<string> _field_values);
	void insert(entity _e) {
		entity_table.push_back(_e);
	}
	void update(string _set_argument, string _where_argument);
	vector<string> split_on_spaces(string _str);
	void display_table();
	void delete_from(string _where_argument);

	bool operator == (const table &Ref) const {
        bool found;
		if(entity_table.size() != Ref.entity_table.size()) {
			return false;
		}

		for(int i = 0; i < entity_table.size(); i++){
			found = false;
			for(int j = 0; i < Ref.entity_table.size(); j++){
				if(entity_table[i] == Ref.entity_table[j]){
					found = true;
				} 
				else {}

			}

			if (found == false) { return false; }

		}

		return true;
    }


	vector<entity> entity_table;
	vector<string> attribute_names;
	vector<string> primary_key;

};

#endif