#include "parser.h"
#include <iostream>
#include <fstream>

using namespace std;

Token_stream ts;

char parser::alpha() {
	Token t = ts.get();
	switch (t.kind) {
	case '9': case '7':
		return t.letter;
	default:
		return '\0';


	}

}


string parser::identifier() {
	int quote_counter = 0;
	string id = "";
	Token t = ts.get();
	if (t.kind != '"') {
		ts.putback(t);
	}	
	while (1) {
		switch (t.kind) {
		case '9':
			id += alpha();
			t = ts.get();
			ts.putback(t);
			break;
		case '"':
			quote_counter++;
			if (quote_counter == 2) {
				ts.get();
				return id;
			}
			t = ts.get();
			if (t.kind != '"') {
				ts.putback(t);
			}
			
			break;
		case '8':
			ts.putback(t);
			id = t.value;
		case '_':
			id += t.kind;
			ts.get();
			t = ts.get();
			ts.putback(t);
			break;
		default:
			return id;
		}
	}
}




comparison_obj parser::comparison() {
	comparison_obj comp;
	Token t = ts.get();
	string _oper1, _oper2 = "";
	string _op = "";
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '8':
			_oper2 = to_string(t.value);
			keep_going = 0;
			break;
		
		case '9':
			ts.putback(t);
			_oper1 = identifier();

			t = ts.get();
			break;
		case '"':
			ts.putback(t);
			_oper2 = identifier();

			t = ts.get();
			break;
		case '<':
			_op += t.kind;
			t = ts.get();
			
			if (t.kind == '=') {
				_op += t.kind;
				t = ts.get();
			}
			else if (t.kind == '9') {
				_oper2 = identifier();
				keep_going = 0;
			}
			break;
		case '>':
			_op += t.kind;
			t = ts.get();
			
			if (t.kind == '=') {
				_op += t.kind;
				t = ts.get();
			}
			else if (t.kind == '9') {
				_oper2 = identifier();
				keep_going = 0;
			}
			break;
		case '=':
			_op += t.kind;
			t = ts.get();
			
			if (t.kind == '=') {
				_op += t.kind;
				t = ts.get();
			}
			else if (t.kind == '9') {
				_oper2 = identifier();
				keep_going = 0;
			}
			break;
		case '!':
			_op += t.kind;
			t = ts.get();
			
			if (t.kind == '=') {
				_op += t.kind;
				t = ts.get();
			}
			else if (t.kind == '9' || t.kind == '"') {
				_oper2 = identifier();
				keep_going = 0;
			}
			break;
		case ';': //end of line
			ts.putback(t);
			keep_going = 0;
		default:
			keep_going = 0;
		}
	}
	comp.oper1 = _oper1;
	comp.op = _op;
	comp.oper2 = _oper2;
	return comp;
}


conjunction_obj parser::conjunction() {
	conjunction_obj conjun;
	Token t = ts.get();
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			ts.putback(t);
			conjun.comparisons.push_back(comparison());
			t = ts.get();
			break;
		case '&':
			ts.get();
			conjun.comparisons.push_back(comparison());
			t = ts.get();
			break;		
		case ';':
			ts.putback(t);
			return conjun;
		default:
			ts.putback(t);
			keep_going = 0;
			return conjun;
		}
	}
}

condition_obj parser::condition() {
	condition_obj condit;
	Token t = ts.get();
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			ts.putback(t);
			condit.conjunctions.push_back(conjunction());
			t = ts.get();
			break;
		case '|':
			ts.get();
			condit.conjunctions.push_back(conjunction());
			t = ts.get();
			break;
		case ';':
			ts.putback(t);
			return condit;
		case ')':
			ts.putback(t);
			return condit;
		default:
			ts.putback(t);
			keep_going = 0;
		}
	}
}



string parser::keyword() {

	string id = "";
	Token t = ts.get();
	ts.putback(t);
	while (1) {
		switch (t.kind) {
		case '7':
			id += alpha();
			t = ts.get();
			ts.putback(t);
			break;
		default:
			return id;
		}
	}
}

string parser::relation_name() {
	return identifier();
}
string parser::attribute_name() {
	return identifier();
}
string parser::atomic_expr() {
	Token t = ts.get();
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			ts.putback(t);
			return relation_name();
			t = ts.get();
			break;
		case '(':
			;



		}



	}



}
string parser::expr() {
	Token t = ts.get();
	string result;
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			ts.putback(t);
			result = identifier();
			t = ts.get();
			keep_going = 0;
			break;
		default:
			keep_going = 0;
		}
	}
	if (result == "selection") {

	}
	else if (result == "projection") {

	}
	else if (result == "renaming") {

	}
	else if (result == "union") {

	}
	else if (result == "difference") {

	}
	else if (result == "product") {

	}
	else if (result == "natural-join") {

	}
	else {
		return result;
	}
}


int parser::type() {
	Token t = ts.get();
	ts.putback(t);
	string temp;
	while (1) {
		switch (t.kind) {
		case '7':
			temp = keyword();
			if (temp == "VARCHAR") {
				return 1; //varchar type
			}
			else if (temp == "INTEGER"){
				return 2; //integer type
			}
		}
	}
}
pair<int, int> parser::attr_type() {
	pair<int, int> pair;
	int which_type = type();
	Token t = ts.get();
	switch (which_type) {
	case 1:
		pair.first = 1;
		t = ts.get();
		if (t.kind == '8') {
			pair.second = t.value;
		}
		ts.get();
		break;
	case 2:
		pair.first = 2;
		pair.second = 0;
		ts.putback(t);

		break;
	}
	return pair;
}

typed_attribute parser::typed_attribute_list() {
	typed_attribute ta_list;

	string attr;
	pair<int, int> type;
	Token t = ts.get();
	ts.putback(t);
	while (1) {
		switch (t.kind) {
		case '9':
			attr = attribute_name();
			type = attr_type();
			t = ts.get();
			break;
		case ',':
			ta_list.list.push_back(attr);
			ta_list.types.push_back(type);
			t = ts.get();
			ts.putback(t);
			break;
		case ')':
			ta_list.list.push_back(attr);
			ta_list.types.push_back(type);
			return ta_list;
		}
	}
}
vector<string> parser::attribute_list() {
	vector<string> list;
	string attr;
	Token t = ts.get();
	ts.putback(t);
	while (1) {
		switch (t.kind) {
		case '9':
			attr = attribute_name();
			t = ts.get();
			break;
		case ',':
			list.push_back(attr);
			t = ts.get();
			ts.putback(t);
			break;
		case ')':
			list.push_back(attr);
			return list;
		}
	}
}
vector<string> parser::literal_list() {
	vector<string> list;
	string id;
	Token t = ts.get();
	while (1) {
		switch (t.kind) {
		case '"':
			id = identifier();
			list.push_back(id);
			t = ts.get();
			break;
		case ',':
			t = ts.get();
			break;
		case '8':
			list.push_back(to_string(t.value));
		case ')':
			return list;




		}


	}


}

insert_obj parser::insert_cmd()  {
	insert_obj io;
	Token t = ts.get();
	string name;
	vector<string> literals;
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			ts.putback(t);
			name = relation_name();
			t = ts.get();
			break;
		case '7':
			ts.putback(t);
			if (keyword() == "VALUESFROM") {
				t = ts.get();
				literals = literal_list();

			}
			keep_going = 0;
			break;
		}
	}
	io.name = name;
	io.values = literals;
	return io;
}

update_obj parser::update_cmd() {
	update_obj uo;
	Token t = ts.get();
	condition_obj condits;
	string name;
	string attr_name;
	vector<pair<string, string>> sets; //pair<string, string> is <attribute, new-value>
	//string condition;

	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			ts.putback(t);
			name = relation_name();
			t = ts.get();
			break;
		case '7':
			ts.putback(t);
			string temp_keyword = keyword();
			if (temp_keyword == "SET") {
				int keep_going2 = 1;
				pair<string, string> temp;
				t = ts.get();
				while (keep_going2) {
									
					switch (t.kind) {
					case '9':
						ts.putback(t);
						temp.first = attribute_name();
						t = ts.get();
						break;
					case '=':
						temp.second = identifier();
						t = ts.get();
						break;
					case ',':
						sets.push_back(temp);
						t = ts.get();
						break;
					case '7':
						sets.push_back(temp);
						ts.putback(t);
						keep_going2 = 0;
						break;
					}
				}
			}
			else if (temp_keyword == "WHERE") {
				condits = condition();
				keep_going = 0;
			}
			break;
		}
	}
	uo.rel_name = name;
	uo.attribute_values = sets;
	uo.condition = condits;
	return uo;
}


table parser::create_cmd() {

	Token t = ts.get();
	string name;
	typed_attribute ta_list;
	vector<string> primary_key_list;
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			ts.putback(t);
			name = relation_name();
			t = ts.get();
			break;
		case '7':
			ts.putback(t);
			if (keyword() == "PRIMARYKEY") {
				t = ts.get();
				primary_key_list = attribute_list();

			}
			keep_going = 0;
			break;


		case '(':
			ta_list = typed_attribute_list();
			t = ts.get();
			break;
		}
	}
	table temp(name, ta_list.list, primary_key_list);
	return temp;
}
string parser::show_cmd() {
	cout << "in show" << endl;
	Token t = ts.get();
	string name;
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			cout << "case 9" << endl;
			ts.putback(t);//does not continue to have name
			cout << "not pushed back" << endl;
			name = relation_name();
			cout << "have name" << endl;
			t = ts.get();
			keep_going = 0;
			break;
		case '7':
			cout << "case 7" << endl;
			ts.putback(t);
			if (keyword() == "SHOW") {
				t = ts.get();
				cout << "know show" << endl;
			}
			break;
		default:
			return name;
		}
	}
}
string parser::close_cmd() {
	cout << "in close" << endl;
	Token t = ts.get();
	string name;
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			cout << "case 9" << endl;
			ts.putback(t);//does not continue to have name
			cout << "not pushed back" << endl;
			name = relation_name();
			cout << "have name" << endl;
			t = ts.get();
			keep_going = 0;
			break;
		case '7':
			cout << "case 7" << endl;
			ts.putback(t);
			if (keyword() == "CLOSE") {
				t = ts.get();
				cout << "know close" << endl;
			}
			break;
		}
	}
	return name;
}

void parser::selection_qry() {
	Token t = ts.get();
	condition_obj condits;
	string name;
	int keep_going = 1;
	while (keep_going) {
		switch (t.kind) {
		case '(':

			condits = condition();
			t = ts.get();
			break;
		case ')':
			name = atomic_expr();
			break;
		default:
			keep_going = 0;
		}


	}



}

void parser::query() {
	Token t = ts.get();
	int keep_going = 1;
	string name;
	string which_query;
	while (keep_going) {
		switch (t.kind) {
		case '9':
			ts.putback(t);
			name = relation_name();
			t = ts.get();
			break;
		case '<':
			t = ts.get();
			if (t.kind == '-') {
				which_query = identifier();
				keep_going = 0;
			}			
			break;
		default:
			break;
		}
	}

	if (which_query == "select") {
		selection_qry();
	}


}












void parser::delete_cmd() {
	Token t = ts.get();


}
void parser::exit_cmd() {
	Token t = ts.get();


}
void parser::open_cmd() {
	Token t = ts.get();


}
void parser::write_cmd(table tble) {

	

		ofstream myfile;
		myfile.open("display.db");

		myfile << "in write" << endl;
		Token t = ts.get();
		string name;
		int keep_going = 1;
		ts.putback(t);//does not continue to have name

		name = relation_name();

		cout << name << endl;
		name = "animals";
		myfile << name << endl;
		for (int i = 0; i < tble.attribute_names.size(); i++){
			myfile << tble.attribute_names[i] << '\t';
		}

		myfile << endl;

		for (int i = 0; i < tble.entity_table.size(); i++){
			for (int j = 0; j <tble.attribute_names.size(); j++){
				myfile << tble.entity_table[i].attributes[tble.attribute_names[j]] << '\t';
			}
			myfile << endl;
		}


		myfile.close();



}
void parser::evaluate_statement(database& db){
	Token t = ts.get();
	ts.putback(t);
	int keep_going = 1;
	string key_word = keyword();
	while (keep_going) {
		switch (t.kind) {
		case '7':
			if (key_word == "SHOW") {
				show_cmd();
			}
			else if (key_word == "DELETE") {
				delete_cmd();
			}
			else if (key_word == "CREATETABLE") {
				db.add_table(create_cmd());
				t = ts.get();
			}
			else if (key_word == "EXIT") {
				exit_cmd();
			}
			else if (key_word == "CLOSE") {
				close_cmd();
			}
			else if (key_word == "UPDATE") {
				update_cmd();
			}
			else if (key_word == "WRITE") {
				write_cmd();
			}
			else if (key_word == "OPEN") {
				open_cmd();
			}
			else if (key_word == "INSERTINTO") {
				insert_obj io = insert_cmd();
				db.get_table(io.name).insert(io.values);

			}
			break;
		default:
			keep_going = 0;
			break;
		}
	}

			
}