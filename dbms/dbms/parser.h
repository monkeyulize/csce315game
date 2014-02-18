#ifndef PARSER_H
#define PARSER_H

#include "database.h"
#include "tokenizer.h"
#include <string>
#include "table.h"
#include "typed_attribute.h"
#include "update_obj.h"

using namespace std;
class parser {
public:

	char alpha();
	std::string identifier();
	std::string keyword();
	std::string relation_name();
	std::string attribute_name();
	condition_obj condition();
	conjunction_obj conjunction();
	comparison_obj comparison();
	int type();
	std::pair<int, int> attr_type();
	typed_attribute typed_attribute_list();
	std::vector<string> attribute_list();
	std::vector<string> literal_list();
	
	//commands	
	table create_cmd();
	std::string close_cmd();
	std::string show_cmd();
	void insert_cmd();
	update_obj update_cmd();
	void write_cmd();		//drops table writes to a file, name+.db
	void delete_cmd();		//deletes entry
	void open_cmd();		//loads table form a text file
	void exit_cmd();		//exit(0)

	//queries
	void projection_qry();
	void attribute_qry();
	void renaming_qry();
	void union_qry();
	void difference_qry();
	void product_qry();
	void natural_join_qry();
};

#endif

