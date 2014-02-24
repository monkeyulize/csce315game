#include "parser.h"
#include <cctype>

class Application{
	private:
		database * db;
		parser * p;
	public:
		Application(database& _db, parser& _p) { db = &_db; p = &_p; }
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//											Display Functions
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		void print_tables();
		void print_size();
		void display_menu();
		void display_detailed_menu();

		vector<string> split_on_spaces(string str) {
			istringstream iss(str);
			string s;
			vector<string> result;

			while (getline(iss, s, ' ')){
				result.push_back(s.c_str());
			}

			return result;
		}
		string prompt_tuple(string name);
		string prompt_add();
		string prompt_combine(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name-------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name------------------------------------------" << endl;
			cin >> table2;
			return "test";
		}
		string prompt_remove(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        From which <Fill> would you like to remove?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name-----------------------------------------" << endl;
			cin >> table1;
			return table1;
		}
		string prompt_rename(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        From which <Fill> would you like to remove?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name-----------------------------------------" << endl;
			cin >> table1;
			return table1;
		}
		string prompt_update(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        From which <Fill> would you like to remove?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name-----------------------------------------" << endl;
			cin >> table1;
			return table1;
		}
		string prompt_select(string name){
			
			vector<string> split_list;		//full command split into a vector of attributes names
			vector<string> literals;		//strings containing &&, or, or ==, each pairing with a key specified
			vector<string> conj;		//strings containing &&, or, or ==, each pairing with a key specified
			string attr_list;			//full command of space delimited attributes
			string conjugate;					//value contianing equals, not equals, greater than, or less than
			string value;				//value to compare a attribute to
			stringstream ss;		//used for final return including braces and brackets
			vector <string> table_attr_list = db->get_table(name).attribute_names;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "What descriptors do you want to filter your collection by?" << endl;
			cout << "i.e. name age color statistics	  	" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');			
			getline(cin, attr_list); //delimited by spaces					//grabs whole line to split up
			split_list = split_on_spaces(attr_list);				//now has a vector of strings


			cout << "-------------------------------------------------------------------------------		" << endl;
			
			for (int i = 0; i < split_list.size(); i++){
				cout << "For " << split_list[i] << ", what value do you want to compare to?" << endl;
				cin >> value;
				literals.push_back(value);
				cout <<"For " << split_list[i] << ", Do want want values lower, equal to, not equal, or greater?" << endl;
				cout << "Enter \"less\", \"equal\",\"nequal\", or \"greater\".	  	" << endl;
				cin >> conjugate;
				conj.push_back(conjugate);
			}


			ss << " (";
			for (int i = 0; i < split_list.size(); i++){
				ss << split_list[i];
				if (conj[i] == "equal"){
					ss << "==";
				}
				else if (conj[i] == "nequal"){
					ss << "!=";
				}
				else if (conj[i] == "greater"){
					ss << ">";
				}
				else if (conj[i] == "less"){
					ss << "<";
				}
				ss << literals[i];
				
				if (i < split_list.size() - 1){
					ss << " && ";
				}

			}
			ss << ") ";
			return ss.str();
		}
		string prompt_project(string name){
			string attr_list;			//full command of space delimited attributes
			vector<string> split_list;		//full command split into a vector of attributes names
			stringstream ss;		//used for final return including braces and brackets
			vector <string> table_attr_list = db->get_table(name).attribute_names;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "What descriptors in " << name << " would you like to filter by?  " << endl;
			cout << "Enter all to filter by seperated by spaces i.e. \"name age color\" without quotes." << endl;
			
			for (int i = 0; i < table_attr_list.size(); i++){				//print out the attribute list
				cout << table_attr_list[i]<<" ";
			}
			cout << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, attr_list); 							//delimited by spaces
			split_list = split_on_spaces(attr_list);
			
			ss << " (";
			for (int i = 0; i < split_list.size(); i++){
				ss << split_list[i];
				if (i < split_list.size() - 1){
					ss << ", ";
				}
			}
			ss << ") ";
			return ss.str();
		}
		string prompt_filter(){
			string table1, view;	//name of both tables, table1 for existing, view for new name
			string filter;		//the value entered by user to define project or select
			string elements;		//can be attributes or a tuple
			stringstream ss;
			
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        From which <Fill> would you like to filter?                          			" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			
			cout << "----------Enter the tables name------------------------------------------------		" << endl;
			cin >> table1;
			
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        What would you like to call this filtered collection?                         	" << endl;
			cin >> view;
			
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        How would you like to filter "<<table1 <<"                         			" << endl;
			cout << "Filter by description(name, age) or by values (name is bob)                        	" << endl;
			cout << "Enter \"Description\" or \"Value\" without the parentheses                      		" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cin >> filter;
			
			if (filter == "Description"){
				filter = "project";
				elements = prompt_project(table1);
			}
			else if (filter == "Value"){
				filter = "select";
				elements = prompt_select(table1);
			}
			ss << view <<" <- " << filter << elements << table1;
			cout << ss.str();
			return ss.str();
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//											Command Functions
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		string prompt_primary();
		string prompt_type(string attr);
		string prompt_attributes();
		string prompt_new_table();
		string prompt_save();
		string prompt_open();
		string prompt_close();
		string prompt_display();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//									MAIN INITIALIZATION FUNCTION
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		void initialize();
};