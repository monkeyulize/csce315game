#include "database.h"
#include <algorithm>
table database::set_union(string view_name, string table_one_name, string table_two_name)		//: compute the union of two relations; the relations must be union-compatible.
{
	table union_table;
	table t1 = tables[find_table(table_one_name)];
	table t2 = tables[find_table(table_two_name)];
	//int bigger_table_size = max(t1.entity_table.size(), t2.entity_table.size());
	table bigger_table;
	table smaller_table;
	if (t1.entity_table.size() > t2.entity_table.size()) {
		bigger_table = t1;
		smaller_table = t2;
	}
	else {
		bigger_table = t2;
		smaller_table = t1;
	}
	union_table = bigger_table;
	//for (int i = 0; i < bigger_table.entity_table.size(); i++) { 
	//	union_table.entity_table.push_back(bigger_table.entity_table[i]);
	//}
	for (int i = 0; i < smaller_table.entity_table.size(); i++) {
		for (int j = 0; j < bigger_table.entity_table.size(); j++) {
			if (smaller_table.entity_table[i] == bigger_table.entity_table[j]) {
				//do nothing
				;
			}
			else {
				union_table.entity_table.push_back(smaller_table.entity_table[i]);
			}

		}

	}
	return union_table;
}
table database::set_differnce(string view_name, string table_one_name, string table_two_name)	//: compute the set difference of two relations; the relations must be union-compatible.
{
	//defining tables
	table diff_table;
	table bigger_table;
	table smaller_table;
	table t1 = tables[find_table(table_one_name)];
	table t2 = tables[find_table(table_two_name)];
	
	if (t1.entity_table.size() > t2.entity_table.size()) {
		bigger_table = t1;
		smaller_table = t2;
	}
	else {
		bigger_table = t2;
		smaller_table = t1;
	}
	int check=0;
	
	//finding differences between both tables using smaller one as outer limit
	for (int i = 0; i < smaller_table.entity_table.size(); i++) {
		for (int j = 0; j < bigger_table.entity_table.size(); j++) {
			if (!(smaller_table.entity_table[i] == bigger_table.entity_table[j])) {
				check++;
			}
		}
		//push only if didnt find this element
		if(check==bigger_table.entity_table.size()) diff_table.push_back(smaller_table.entity_table[i])
		check=0;
	}
	//finding reverse differnce between both tables
	for (int i = 0; i < bigger_table.entity_table.size(); i++) {
		for (int j = 0; j < smaller_table.entity_table.size(); j++) {
			if (!(bigger_table.entity_table[i] == smaller_table.entity_table[j])) {
				check++;
			}
		}
		//push only if didnt find this element
		if(check==smaller_table.entity_table.size()) diff_table.push_back(bigger_table.entity_table[i])
		check=0;
	}
	
	return diff_table;
}
table database::set_selection(string view_name, string table_name, int tuple_index)	//: select the tuples in a relation that satisfy a particular condition.
{
	return table();
}
table database::set_projection(string view_name, string table_name, vector<string> attributes)	//: select a subset of the attributes in a relation.
{
	return table();
}
table database::set_renaming(string view_name, string table_name, vector<string> attributes)	//: rename the attributes in a relation.
{
	return table();
}
table database::set_cross_product(string view_name, string table_one_name, string table_two_name)//: compute the Cartesian product of two relations.
{
	return table();
}
table database::set_natural_join(string view_name, string attribute_name, string table_one_name, string table_two_name)//: compute the Cartesian product of two relations.
{
	return table();
}