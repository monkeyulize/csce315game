#include "database.h"
#include <algorithm>
table database::set_union(string view_name, string table_one_name, string table_two_name)		//: compute the union of two relations; the relations must be union-compatible.
{
	table union_table;
	table t1 = tables[find_table(table_one_name)];
	table t2 = tables[find_table(table_two_name)];
	union_table = t1;

	int can_push = 0;
	for (int i = 0; i < t2.entity_table.size(); i++) {
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
				//t1.entity_table[i].show_attributes(t1.attribute_names);
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
entity database::set_selection(string view_name, string table_name, int tuple_index)	//: select the tuples in a relation that satisfy a particular condition.
{
	table t1 = tables[find_table(table_name)];
	return t1.entity_table[tuple_index];
}
table database::set_projection(string view_name, string table_name, vector<string> attributes)	//: select a subset of the attributes in a relation.
{
	table t1 = tables[find_table(table_name)];
	
	for(int i = 0; i < t1.entity_table.size(); i++)
		for(int j = 0; j < t1.attribute_names.size(); j++)
			t1.entity_table[i].set_attribute(attributes[j],t1.entity_table[i].get_attribute(t1.attribute_names[j]));
	
	for(int i = 0; i < t1.attribute_names.size(); i++){		//go through all attributes
		t1.attribute_names[i] = attributes[i];
	}
	t1.set_name(view_name);
	return t1;
}
table database::set_renaming(string view_name, string table_name, vector<string> attributes)	//: rename the attributes in a relation.
{
	table t1 = tables[find_table(table_name)];
	
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
	table cp_table;
	table t1 = tables[find_table(table_one_name)];
	table t2 = tables[find_table(table_two_name)];
	vector<string> attr_names;
	attr_names = t1.attribute_names;
	for (int i = 0; i < t2.attribute_names.size(); i++) {
		attr_names.push_back(t2.attribute_names[i]);
	}
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
table database::set_natural_join(string view_name, string attribute_name, string table_one_name, string table_two_name)//: compute the Cartesian product of two relations.
{
	return table();
}