#include "parser.h"

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

	string id = "";
	Token t = ts.get();
	ts.putback(t);
	while (1) {
		switch (t.kind) {
		case '9':
			id += alpha();
			t = ts.get();
			ts.putback(t);
			break;
		default:
			return id;
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
void parser::create_cmd() {

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
}