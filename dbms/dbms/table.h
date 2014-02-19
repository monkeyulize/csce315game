#ifndef TABLE_H
#define TABLE_H

#include "entity.h"
#include "condition_obj.h"
#include <vector>


class table {
private:
	string name;	//stores name of table
public:
	//storage variables
	vector<entity> entity_table;				//stores tuples
	vector<string> attribute_names;				//stores column titles
	vector<string> primary_key;					//stores significant columns, blocks redundant entries
	
	table() {};
	table(string _name, vector<string> _attribute_names, vector<string> _primary_key){
		name = _name;
		attribute_names = _attribute_names;
		primary_key = _primary_key;
	};
	
	//mutator function
	void set_name(string _name) {
		name = _name;
	}
	void set_attr_names(vector<string> _attribute_names);
	
	//accessor function
	string get_name() {
		return name;
	}
	
	//Helper functions
	void insert(vector<string> _field_values);
	
	//inserts an entity into the entity table
	void insert(entity _e) {
		entity_table.push_back(_e);
	}
	
	//updates all values that meet a specific condition
	void update(vector<pair<string, string>> _set_argument, condition_obj condit);
	
	//parses an input into table to return a vector with inputs at each index
	vector<string> split_on_spaces(string _str);
	
	//print function
	void display_table();
	
	//removes an entity from table
	void delete_from(condition_obj condit);

	vector<int> eval_condition(condition_obj condit);



	//overwritten boolean operator to compare two tables equality
	bool operator == (const table &Ref) const {
        bool found;
		if(entity_table.size() != Ref.entity_table.size()){ 	//unequal size means unequal tables
			return false;
		}	

		for(int i = 0; i < entity_table.size(); i++){
			found = false;
			for(int j = 0; j < Ref.entity_table.size(); j++){
				if(entity_table[i] == Ref.entity_table[j]){			//check if each entry is in other table
					found = true;
				}
			}	
			if (found == false){ 								//if even one is not found return false
				return false; 
			}
		}
		return true;
    }

};

#endif