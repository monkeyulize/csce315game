#include "table.h"

class database{
private:
	vector<table> tables;

public:
	database() {};
	void create_table(string _name, vector<string> _attribute_names, vector<string> _primary_key)
	{
		table t (_name, _attribute_names, _primary_key);
		add_table(t);
	}
	void add_table(table t)
	{
		tables.push_back(t);
	}
	void delete_table(table t)
	{
		int index = find_table(t.get_name());
		tables.erase(tables.begin() + index);
	}
	int find_table(string table_name)
	{
		for(int i = 0; i <tables.size(); i++)
		{
			if(tables[i].get_name()==table_name)
				return i;
		}
		return -1;
	}
	table get_table(string table_name)
	{
		return tables[find_table(table_name)];
	}
	table set_union(string view_name, string table_one_name, string table_two_name);							//: compute the union of two relations; the relations must be union-compatible.
	table set_differnce(string view_name, string table_one_name, string table_two_name);						//: compute the set difference of two relations; the relations must be union-compatible.
	table set_selection( string view_name, string table_name, int tuple_index);									//: select the tuples in a relation that satisfy a particular condition.
    table set_projection(string view_name, string table_name, vector<string> attributes);						//: select a subset of the attributes in a relation.
	table set_renaming(string view_name, string table_name, vector<string> attributes);							//: rename the attributes in a relation.
	table set_cross_product(string view_name, string table_one_name, string table_two_name);					//: compute the Cartesian product of two relations.
	table set_natural_join(string view_name, string attribute_name, string table_one_name, string table_two_name);	//: compute the Cartesian product of two relations.
};