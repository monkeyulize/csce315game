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
vector<string> parser::literal_list() {
	vector<string> list;
	string id;
	Token t = ts.get();
	while (1) {
		switch (t.kind) {
		case '"':
			id = identifier();
			list.push_back(id);
			ts.get();
			t = ts.get();
			break;
		case ',':
			t = ts.get();
			break;
		case ')':
			return list;




		}


	}


}

void parser::insert_cmd()  {
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
}

void parser::update_cmd() {
	Token t = ts.get();
	string name;
	string attr_name;
	vector<pair<string, string>> sets; //pair<string, string> is <attribute, new-value>
	string condition;

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
						ts.putback(t);
						keep_going2 = 0;
						break;
					}
				}
			}
			else if (temp_keyword == "WHERE") {

			}
			break;

		}




	}





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
		}
	}
	return name;
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