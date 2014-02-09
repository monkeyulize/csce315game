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

	void insert(vector<string> _field_values);
	void update(string _set_argument, string _where_argument);
	vector<string> split_on_spaces(string str);
	void display_table();
};