#include "parser.h"

class Application{
	private:
		database db;
		parser p;
	public:
		void print_tables(){
			for (int i = 0; i < db.get_tables_vector().size(); i++){
				cout << "Table " << i << ": " << db.get_tables_vector()[i].get_name() << endl;
			}
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
			cout << "                                     SaveAndCLose<FILL>								" << endl;
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
			cout << "        Save<FILL>    :	Saves values to a file for future reading						" << endl;
			cout << "        Open<FILL>    : Opens and reads from a file a <Fill>       						" << endl;
			cout << "        SaveAndCLose<FILL> : Closes and saves values to a file 						" << endl;
			cout << "        Help          :	You should know you are here, but it prints						" << endl;
			cout << "    					detailed description of each instruction						" << endl;
			cout << "        Exit(To terminate)	: Terminates Application    								" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
		}
		void prompt_add(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to add to?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
		}
		void prompt_combine(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to perform a combine on?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
			cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
			cin >> table2;
		}
		void prompt_remove(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to remove from?                          	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
		}
		void prompt_display(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> do you want to display				                        	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
			cin >> table1;
		}
		void prompt_new_table(){
			string table1, table2;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        What is the name of the new <Fill> Collection		                         	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cin >> table1;
		}
		void prompt_save(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "				 Which <Fill> would you like to save?                  					" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the Tables name -------------------------------------------------------" << endl;
			cin >> table1;
		}
		void prompt_open(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        What is the name of the <Fill> you would like to open?                       	" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cin >> table1;
		}
		void prompt_close(){
			string table1;
			cout << "-------------------------------------------------------------------------------		" << endl;
			cout << "        Which <Fill> would you like to save and close?                          					" << endl;
			cout << "-------------------------------------------------------------------------------		" << endl;
			print_tables();
			cout << "----------Enter the Tables name -------------------------------------------------------" << endl;
			cin >> table1;
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
				else if (command == "Display<FILL>"){
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
				else if (command == "Help"){		//works
					cout << "Type In The Keyword Of The Action You Would Like To Perform." << endl;
					display_detailed_menu();
				}
				else if (command == "Exit"){
					p.exit_cmd();
				}
				else{
					cout << "Type In The Keyword Of The Action You Would Like To Perform." << endl;
					display_detailed_menu();
				}

			}
		}
};