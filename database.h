#include "table.h"

class database{
private:
	vector<table> tables;

public:
	database() {};
	
	void insert(table t)
	{
		tables.push_back(t);
	}
	void update(string _set_argument, string _where_argument);
	vector<string> split_on_spaces(string str);
	void display_table();
	void set_union();		//: compute the union of two relations; the relations must be union-compatible.
	void set_differnce();	//: compute the set difference of two relations; the relations must be union-compatible.
	void set_selection();	//: select the tuples in a relation that satisfy a particular condition.
    void set_projection();	//: select a subset of the attributes in a relation.
	void set_renaming();	//: rename the attributes in a relation.
	void set_cross_product();//: compute the Cartesian product of two relations.
};