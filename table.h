#include "entity.h"
#include <vector>


class table {
private:
	vector<entity> entity_table;
	vector<string> attribute_names;
	vector<string> primary_key;
	string name;
public:
	table() {};
	table(string _name, vector<string> _attribute_names, vector<string> _primary_key) {name = _name; attribute_names = _attribute_names; primary_key = _primary_key;};

	void insert(vector<string> field_values);
	void display_table();








};