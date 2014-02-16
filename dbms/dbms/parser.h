#ifndef PARSER_H
#define PARSER_H

#include "database.h"
#include "tokenizer.h"
#include <string>
#include "table.h"

using namespace std;
class typed_attribute {
public:
	vector<string> list;
	vector<pair<int, int>> types; //<1, int> means type varchar of length int, <2, 0> means type integer
								  //first int specifies type of variable, second specifies length assuming its a string
};

class parser {
public:

	char alpha();
	string identifier();
	string keyword();
	string relation_name();
	string attribute_name();
	int type();
	pair<int, int> attr_type();
	typed_attribute typed_attribute_list();
	vector<string> attribute_list();
	vector<string> literal_list();
	table create_cmd();
	string close_cmd();
	string show_cmd();
	void insert_cmd();
	void update_cmd();
};

#endif

