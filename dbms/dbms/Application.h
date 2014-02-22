#include "parser.h"

class Application{
	private:
		database db;
		parser p;
	public:
		void display_menu(){
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "                                    Commands and Queries                              	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "                                         Add<FILL>                      				" << endl;
			cout << "                                       Remove<FILL>									" << endl;
			cout << "                               Combine(add, subtract, cross)                           " << endl;
			cout << "                                       Diplay<FILL>									" << endl;
			cout << "                                   New<FILL>Collection                  				" << endl;
			cout << "                                        Save<FILL>										" << endl;
			cout << "                                        Open<FILL>               						" << endl;
			cout << "                                     SaveAndCLose<FILL>								" << endl;
			cout << "                                     Help(For testing)									" << endl;
			cout << "                                     Exit(To terminate)								" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
		}
		void display_detailed_menu(){
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "                                    Commands and Queries                              	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Add<FILL>    : Add a <Fill> to a specific collection.             				" << endl;
			cout << "        Remove<FILL> : Remove a specific or collection of <Fills> that meet a condition." << endl;
			cout << "        Combine	  : Perform an operation on collections of <Fills>; Add, Cross, Difference." << endl;
			cout << "        Display<FILL> : Display the contents of a collection with specified name.		" << endl;
			cout << "        New<FILL>Collection :                  										" << endl;
			cout << "        Save<FILL>	  :																	" << endl;
			cout << "        Open<FILL>   :            														" << endl;
			cout << "        SaveAndCLose<FILL> :															" << endl;
			cout << "        Help		  :																	" << endl;
			cout << "        Exit(To terminate)	:															" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
		}
		void prompt_add(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			for (int i = 0; i < db.get_tables_vector.size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector[i].get_name();
			}
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void prompt_combine(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			for (int i = 0; i < db.get_tables_vector.size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector[i].get_name();
			}
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void prompt_remove(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			for (int i = 0; i < db.get_tables_vector.size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector[i].get_name();
			}
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void prompt_display(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			for (int i = 0; i < db.get_tables_vector.size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector[i].get_name();
			}
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void prompt_new_table(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			for (int i = 0; i < db.get_tables_vector.size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector[i].get_name();
			}
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void prompt_save(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			for (int i = 0; i < db.get_tables_vector.size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector[i].get_name();
			}
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void prompt_open(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			for (int i = 0; i < db.get_tables_vector.size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector[i].get_name();
			}
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void prompt_close(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			for (int i = 0; i < db.get_tables_vector.size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector[i].get_name();
			}
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void initialize(){
			string parsed_name;						//used for achievement, player, and game names
			string command;							//used to keep track of switch case
			bool exit = false;

			display_menu();

			while (!exit){
				cout << "What would you like to do=>" << endl;
				cin >> command;

				if (command == "Add<FILL>"){
					prompt_add();
				}
				else if (command == "Remove<FILL>"){
					prompt_remove();
				}
				else if (command == "Combine"){
					prompt_combine();
				}
				else if (command == "Diplay<FILL>"){
					prompt_display();
				}
				else if (command == "New<FILL>Collection"){
					prompt_new_table();
				}
				else if (command == "Save<FILL>"){
					prompt_save();
				}
				else if (command == "Open<FILL>"){
					prompt_open();
				}
				else if (command == "SaveAndCLose<FILL>"){
					prompt_close();
				}
				else if (command == "Help"){
					cout << "Type In The Keyword Of The Action You Would Like To Perform." << endl;
					display_detail_menu();
				}
				else if (command == "Exit"){
					p.exit_cmd();
				}
				else if (command == "Help"){
					display_detailed_menu();
				}
				else{
					exit = true;
				}

			}
		}
}