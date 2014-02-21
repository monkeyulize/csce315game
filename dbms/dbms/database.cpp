#include "database.h"
#include <algorithm>
table database::set_union(string view_name, string table_one_name, string table_two_name)		//: compute the union of two relations; the relations must be union-compatible.
{
	table union_table;		//the final table view
	table t1 = tables[find_table(table_one_name)];		//get a handle on both tables by their passed name arguments
	table t2 = tables[find_table(table_two_name)];
	union_table = t1;

	int can_push = 0;
	for (int i = 0; i < t2.entity_table.size(); i++) {			//check for unique entities in t2, add those to t1
		for (int j = 0; j < t1.entity_table.size(); j++) {
			if (t2.entity_table[i] == t1.entity_table[j]) {
				can_push = 0;
				break;
			}
			else {
				can_push = 1;
			}
		}
		if (can_push == 1) {
			union_table.entity_table.push_back(t2.entity_table[i]);
		}
	}
	union_table.set_name(view_name);
	return union_table;
}
table database::set_difference(string view_name, string table_one_name, string table_two_name)	//: compute the set difference of two relations; the relations must be union-compatible.
{
	//defining tables
	
	table t1 = tables[find_table(table_one_name)];
	table t2 = tables[find_table(table_two_name)];
	table diff_table(view_name, t1.attribute_names,t1.primary_key);
	int check=0;
	
	//finding differences between both tables using smaller one as outer limit
	for (int i = 0; i < t1.entity_table.size(); i++) {
		for (int j = 0; j < t2.entity_table.size(); j++) {
			if (!(t1.entity_table[i] == t2.entity_table[j])) {
				check++;
			}
		}
		//push only if didnt find this element
		if(check==t2.entity_table.size()) {
			diff_table.entity_table.push_back(t1.entity_table[i]);
		}
		check=0;
	}
	//finding reverse difference between both tables
	for (int i = 0; i < t2.entity_table.size(); i++) {
		for (int j = 0; j < t1.entity_table.size(); j++) {
			if (!(t2.entity_table[i] == t1.entity_table[j])) {
				check++;
			}
		}
		//push only if didnt find this element
		if(check==t1.entity_table.size()) {
			diff_table.entity_table.push_back(t2.entity_table[i]);
		}
		check=0;
	}
	diff_table.set_name(view_name);
	cout<<diff_table.entity_table.size();
	return diff_table;
}

table database::set_selection(string view_name, table tble, condition_obj condit)	//: select the tuples in a relation that satisfy a particular condition.
{
	table sel_table(view_name, tble.attribute_names, tble.primary_key);	
	vector<int> selected_indices = tble.eval_condition(condit);

	for (int i = 0; i < selected_indices.size(); i++) {
		int index = selected_indices[i];
		sel_table.insert(tble.entity_table[index]);
	}
	return sel_table;
}
table database::set_projection(string view_name, string table_name, vector<string> attributes)	//: select a subset of the attributes in a relation.
{
	table t1 = tables[find_table(table_name)];
	table proj_table(view_name, attributes,t1.primary_key);
	vector<string> tuple;
	for(int i = 0; i< t1.entity_table.size(); i++){		//go through the whole entity table
		for(int j = 0; j < t1.attribute_names.size(); j++){	//go through all the attributes
			for(int k = 0; k<attributes.size(); k++)
				if(t1.attribute_names[j]==attributes[k])
					tuple.push_back(t1.entity_table[i].get_attribute(t1.attribute_names[j]));
		}
		proj_table.insert(tuple);
		tuple.clear();
	}
	
	return proj_table;
}
table database::set_renaming(string view_name, table tble, vector<string> attributes)	//: rename the attributes in a relation.
{
	table t1 = tble;
	
	for(int i = 0; i < t1.entity_table.size(); i++)
		for(int j = 0; j < t1.attribute_names.size(); j++)
			t1.entity_table[i].set_attribute(attributes[j],t1.entity_table[i].get_attribute(t1.attribute_names[j]));
	
	for(int i = 0; i < t1.attribute_names.size(); i++){		//go through all attributes
		t1.attribute_names[i] = attributes[i];
	}
	t1.set_name(view_name);
	return t1;
}
table database::set_cross_product(string view_name, string table_one_name, string table_two_name)//: compute the Cartesian product of two relations.
{
	//defining tables
	table cp_table;
	table t1 = tables[find_table(table_one_name)];
	table t2 = tables[find_table(table_two_name)];
	
	//defining starting
	vector<string> attr_names;
	attr_names = t1.attribute_names;
	
	for (int i = 0; i < t2.attribute_names.size(); i++) {
		string temp = t2.attribute_names[i];
		int multiple_attr_counter = 1;
		for (int j = 0; j < attr_names.size(); j++) {			//add other terms + special character due to map data structure
			if (temp == attr_names[j]) {
				multiple_attr_counter++;
				temp = temp+ to_string(multiple_attr_counter);
			}
		}
		attr_names.push_back(temp);
	}
	//defining final attirbute names
	cp_table.set_attr_names(attr_names);
	vector<string> field_values;
	for (int i = 0; i < t1.entity_table.size(); i++) {
		for (int j = 0; j < t2.entity_table.size(); j++) {
			for (int x = 0; x < t1.attribute_names.size(); x++) {
				field_values.push_back(t1.entity_table[i].get_attribute(t1.attribute_names[x]));

			}
			for (int x = 0; x < t2.attribute_names.size(); x++) {

				field_values.push_back(t2.entity_table[j].get_attribute(t2.attribute_names[x]));
			}
			cp_table.insert(field_values);
			field_values.clear();
		}
	}
	cp_table.set_name(view_name);
	return cp_table;
}
table database::set_natural_join(string view_name, string table_one_name, string table_two_name)
{
	//defining tables
	table nj_table;
	table t1 = tables[find_table(table_one_name)];
	table t2 = tables[find_table(table_two_name)];
	
	//define attribute names as t1's they must be union compatable
	vector<string> attr_names;
	attr_names = t1.attribute_names;
	nj_table.set_attr_names(attr_names);

	//go through and see which entities are in both tables, push into natural join
	for (int i = 0; i < t1.entity_table.size(); i++) {
		for (int j = 0; j < t2.entity_table.size(); j++) {
			if (t1.entity_table[i] == t2.entity_table[j]) {
				nj_table.insert(t1.entity_table[i]);
			}
		}
	}
	nj_table.set_name(view_name);
	return nj_table;
}