#include "parser.h"
#include <cctype>

class Application{
	private:
		database * db;
		parser * p;
	public:
		Application(database& _db, parser& _p) { db = &_db; p = &_p; }
		void print_tables(){
			for (int i = 0; i < db->get_tables_vector().size(); i++){
				cout << "Table " << i+1 << ": " << db->get_tables_vector()[i].get_name() << endl;
			}
		}
		void print_size(){
			cout<<db->get_tables_vector().size();
		}
		void display_menu(){
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "                                    Commands and Queries                              	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "                                         Add<FILL>                      				" << endl;
			cout << "                                       Remove<FILL>									" << endl;
			cout << "                               Combine(add, subtract, cross)                           " << endl;
			cout << "                                       Display<FILL>									" << endl;
			cout << "                                   New<FILL>Collection                  				" << endl;
			cout << "                                        Save<FILL>										" << endl;
			cout << "                                        Open<FILL>               						" << endl;
			cout << "                                     SaveAndClose<FILL>								" << endl;
			cout << "                                     Help(For testing)									" << endl;
			cout << "                                     Exit(To terminate)								" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
		}
		void display_detailed_menu(){
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "                                    Commands and Queries                              	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Add<FILL>     : Add a <Fill> to a specific collection.             				" << endl;
			cout << "        Remove<FILL>  : Remove a specific or collection of <Fills> that 				" << endl;
			cout << "		                meet a condition." 												  << endl;
			cout << "        Combine       : Perform an operation on collections of <Fills>					" << endl;
			cout<<  "                       Add, Cross, Difference."							              << endl;
			cout << "        Display<FILL> : Display the contents of a collection with specified 			" << endl;
			cout << "		                 name.		"                                                     << endl;
			cout << "        New<FILL>Collection : Creates a new collection of <Fills> 						" << endl;
			cout << "        Save<FILL> : Saves values to a file for future reading						" << endl;
			cout << "        Open<FILL> : Opens and reads from a file a <Fill>       						" << endl;
			cout << "        SaveAndClose<FILL> : Closes and saves values to a file 						" << endl;
			cout << "        Help          :	You should know you are here, but it prints						" << endl;
			cout << "    					detailed description of each instruction						" << endl;
			cout << "        Exit(To terminate)	: Terminates Application    								" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
		}
		vector<string> split_on_spaces(string str) {
			istringstream iss(str);
			string s;
			vector<string> result;

			while (getline(iss, s, ' ')){
				result.push_back(s.c_str());
			}

			return result;
		}
		string prompt_tuple(string name){
			string attribute;			//full command of space delimited attributes
			vector<string> split_list;		//full command split into a vector of attributes names
			stringstream ss;		//used for final return including braces and brackets
			vector <string> table_attr_list = db->get_table(name).attribute_names;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "What values would you like for ";
			for (int i = 0; i < table_attr_list.size(); i++){
				cout << table_attr_list[i]<<"?"<<endl;
				cin >> attribute;
				split_list.push_back(attribute);
			}
			
			ss << " (";
			for (int i = 0; i < split_list.size(); i++){
				if (isalpha(split_list[i][0])){		//value is a varchar
					split_list[i] = '"' + split_list[i] + '"';
				}
				ss << split_list[i];
				if (i < split_list.size() - 1){
					ss << ", ";
				}

			}
			ss << ")";
			return ss.str();
		}
		string prompt_add(){
			string table1;
			stringstream ss;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <FILL> would you like to add to?      	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the tables name------------------------------------------------" << endl;
			cin >> table1;
			string attributes = prompt_tuple(table1);
			ss << "INSERT INTO " << table1 << " VALUES FROM " << attributes;
			return ss.str();
		}
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
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        From which <Fill> would you like to remove?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name-----------------------------------------" << endl;
			cin >> table1;
			return table1;
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
			ss << ")";
			cout << ss.str();
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
			cout << "Enter \"Description\" or \"value\" without the parentheses                      		" << endl;
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
			return ss.str();
		}
		string prompt_display(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> do you want to display				                        	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the tables name------------------------------------------------" << endl;
			cin >> table1;
			return "SHOW "+ table1;
		}
		string prompt_primary(){
			string attr_list;			//full command of space delimited primary keys
			vector<string> split_list;		//full command of primary keys in vector
			stringstream ss;		//used for final return including braces and brackets
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "What key values would you like to use to specify unique entries? " << endl;
			cout << "i.e. two entries cannot have the same name and age	  	" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, attr_list); //delimited by spaces
			split_list = split_on_spaces(attr_list);
			
			ss <<"PRIMARY KEY (";
			for (int i = 0; i < split_list.size(); i++){
				ss << split_list[i];
				if (i < split_list.size() - 1){
					ss << ", ";
				}

			}
			ss << ")";
			return ss.str();
		}
		string prompt_type(string attr){
			string type;			//stores users input of string or int
			stringstream ss;		//used for final return including braces and brackets
			int length;					//each string will have a length
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "Is " << attr << " a number or a word? "<< endl;
			cout << "enter \"number\" or \"word\" without the quotes "<< endl;
			cout << "i.e. color is a word such as blue or green, age would be a number like 3" << endl;
			cin >> type;
			if (type == "word"){
				cout << "---------------------------------------------------------------------------		" << endl;
				cout << "What is the maximum length " << attr << " can have?" << endl; 
				cout << "i.e. name can only be 8 letters long" << endl;
				cin >> length;
				type = "VARCHAR";
			}
			else if (type == "number"){
				type = "INTEGER";
			}

			//store the attribute and the type into final return
			ss << attr <<" "<< type;
			
			//if its a word will have a length parameter too
			if (type == "VARCHAR"){
				ss << "(" << length << ")";
			}
			return ss.str();
		}
		string prompt_attributes(){
			string attr_list;			//full command of space delimited attributes
			vector<string> split_list;		//full command split into a vector of attributes names
			stringstream ss;		//used for final return including braces and brackets
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "What descriptions do you want in your collection?" << endl;
			cout << "i.e. name age color statistics	  	" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, attr_list); //delimited by spaces
			split_list = split_on_spaces(attr_list);

			ss << " (";
			for (int i = 0; i < split_list.size(); i++){
				ss<<prompt_type(split_list[i]);
				if (i < split_list.size() - 1){
					ss << ", ";
				}

			}
			ss<< ")";
			return ss.str();
		}
		string prompt_new_table(){
			string table1;
			stringstream ss;
			string attributes="";
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        What is the name of the new <Fill> Collection		                         	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cin >> table1;
			attributes = prompt_attributes();
			string primary = prompt_primary();
			ss << "CREATE TABLE " << table1 << attributes << primary;
			cout << ss.str()<<endl;
			return ss.str();
		}
		string prompt_save(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "				 Which <Fill> would you like to save?                  					" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the Tables name -----------------------------------------------" << endl;
			cin >> table1;
			return "WRITE " + table1;
		}
		string prompt_open(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        What is the name of the <Fill> you would like to open?                       	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cin >> table1;
			return "OPEN " + table1;
		}
		string prompt_close(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to save and close?                          					" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the Tables name -----------------------------------------------" << endl;
			cin >> table1;
			return "CLOSE " + table1;
		}
		void initialize(){	
			streambuf * buf = cin.rdbuf();
			string parsed_inst;						//used for achievement, player, and game names
			string command;							//used to keep track of switch case
			bool exit = false;
			display_menu();
			while (1){
				command = "test3";
				cout << "What would you like to do=>" << endl;
				cin.clear();
				cin.rdbuf(buf);
				cin >> command;
				stringstream eval_input;
				eval_input.clear();
				eval_input.str(string());
				
				
				if (command == "Add<FILL>"){
					parsed_inst = prompt_add();
				}
				else if (command == "Remove<FILL>"){
					parsed_inst = prompt_remove();
				}
				else if (command == "Combine"){
					parsed_inst = prompt_combine();
				}
				else if (command == "Display<FILL>"){
					parsed_inst = prompt_display();
				}
				else if (command == "New<FILL>Collection"){
					parsed_inst = prompt_new_table();
				}
				else if (command == "Save<FILL>"){
					parsed_inst = prompt_save();
				}
				else if (command == "Open<FILL>"){
					parsed_inst = prompt_open();
				}
				else if (command == "SaveAndClose<FILL>"){
					parsed_inst = prompt_close();
				}
				else if (command == "Filter<FILL>"){
					parsed_inst = prompt_filter();
				}
				else if (command == "Help"){	
					cout << "Type In The Keyword Of The Action You Would Like To Perform." << endl;
					display_detailed_menu();
					continue;
				}
				else if (command == "Exit"){
					parsed_inst = "EXIT";
				}
				else{
					cout << "Type In The Keyword Of The Action You Would Like To Perform." << endl;
					display_detailed_menu();
					continue;
				}
				eval_input << parsed_inst;
				cin.rdbuf(eval_input.rdbuf());
				p->evaluate_statement();
			}
		}
};