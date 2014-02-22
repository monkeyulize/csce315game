#include "database.h"
#include "parser.h"
#include "tokenizer.h"
#include <iostream>
#include <sstream>
#include "Application.h"

using namespace std;

int main(){
	database db;
	parser p;

	stringstream eval_input;
	eval_input <<	"CREATE TABLE cats (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);\n" <<
					"INSERT INTO cats VALUES FROM(\"joe\", \"cat\", 4);\n" <<
					"INSERT INTO cats VALUES FROM (\"tabitha\", \"cat\", 1);\n";
	cin.rdbuf(eval_input.rdbuf());

	p.evaluate_statement(db);

	eval_input <<	"CREATE TABLE dogs (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);\n" <<
					"INSERT INTO dogs VALUES FROM (\"spot\", \"dog\", 10);\n" <<
					"INSERT INTO dogs VALUES FROM (\"snoopy\", \"dog\", 3);\n";
	cin.rdbuf(eval_input.rdbuf());

	p.evaluate_statement(db);

	eval_input.clear();
	eval_input.str(string());
	eval_input <<	"SHOW cats;" <<
					"SHOW dogs;";
	cin.rdbuf(eval_input.rdbuf());

	p.evaluate_statement(db);


	eval_input.clear();
	eval_input.str(string());
	eval_input << "youngpets <- select (years < 5) (cats + dogs);" <<
		"SHOW youngpets;";
	cin.rdbuf(eval_input.rdbuf());

	p.evaluate_statement(db);

	eval_input.clear();
	eval_input.str(string());
	eval_input << "UPDATE  youngpets SET name = \"bingo\" WHERE kind == \"dog\" && years < 5;" <<
		"SHOW youngpets;";
	cin.rdbuf(eval_input.rdbuf());
	

	p.evaluate_statement(db);	
	
	eval_input.clear();
	eval_input.str(string());
	eval_input << "DELETE FROM youngpets WHERE name == \"joe\";" <<
		"SHOW youngpets;";
	cin.rdbuf(eval_input.rdbuf());

	p.evaluate_statement(db);
	
	eval_input.clear();
	eval_input.str(string());
	eval_input << "WRITE cats;";
	cin.rdbuf(eval_input.rdbuf());

	p.evaluate_statement(db);

	eval_input.clear();
	eval_input.str(string());
	eval_input << "CLOSE youngpets;";
	cin.rdbuf(eval_input.rdbuf());

	p.evaluate_statement(db);
	
	/*
	eval_input.clear();
	eval_input.str(string());
	eval_input << "EXIT;";
	cin.rdbuf(eval_input.rdbuf());

	p.evaluate_statement(db);*/

	Application A;
	A.initialize();

	system("pause");
	return 0;
}
