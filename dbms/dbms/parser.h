#ifndef PARSER_H
#define PARSER_H

#include "database.h"
#include "tokenizer.h"
#include <string>
#include "table.h"
#include "typed_attribute.h"
#include <sstream>
#include <istream>

using namespace std;
class parser {
public:

	database* db_ptr = new database();
	parser() {};
	parser(database& db) { db_ptr = &db; }

	char alpha();
	std::string identifier();
	std::string keyword();
	std::string relation_name();
	std::string attribute_name();
	table atomic_expr();
	table expr();
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
	void update_cmd();
	void write_cmd();		//drops table writes to a file, name+.db
	void delete_cmd();		//deletes entry
	void open_cmd();		//loads table form a text file
	void exit_cmd();		//exit(0)

	//queries
	void query();
	table selection_qry();
	table projection_qry();
	table attribute_qry();
	table renaming_qry();
	table tables_qry();


	void evaluate_statement();

};

#endif

