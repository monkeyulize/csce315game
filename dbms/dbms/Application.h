#include "parser.h"

class Application{
	private:
	public:
		parser p;
		void initialize(){
			int player_one, player_two;				//always uses player_one as default for player ID
			int game_id, achievement_id;
			int points;
			string parsed_name;						//used for achievement, player, and game names
			string command;							//used to keep track of switch case
			bool exit = false;

			display_menu();

			while (!exit){
				cout << "What would you like to do=>" << endl;
				cin >> command;

				if (command == "Add<FILL>"){
					cin >> player_one;
					parsed_name = Parser();
					add_Player(player_one, parsed_name);
				}
				else if (command == "Remove<FILL>"){
					cin >> game_id;
					parsed_name = Parser();
					add_Game(game_id, parsed_name);
				}
				else if (command == "Combine"){
					cin >> game_id >> achievement_id;
					parsed_name = Parser();
					cin >> points;
					add_Achieve_Entry(game_id, achievement_id, parsed_name, points);
				}
				else if (command == "Diplay<FILL>"){
					cin >> player_one >> game_id;
					parsed_name = Parser();
					add_Player_Plays(player_one, game_id, parsed_name);
				}
				else if (command == "New<FILL>Collection"){
					cin >> player_one >> player_two;
					add_Friends(player_one, player_two);
				}
				else if (command == "Save<FILL>"){
					cin >> player_one >> game_id >> achievement_id;
					add_Achieve_Earned(player_one, game_id, achievement_id);
				}
				else if (command == "Open<FILL>"){
					cin >> player_one >> game_id;
					print_Friends_Playing(player_one, game_id);
				}
				else if (command == "SaveAndCLose<FILL>"){
					cin >> player_one >> player_two >> game_id;
					print_Compare_Achievements(player_one, player_two, game_id);
				}
				else if (command == "Help"){
					cin >> player_one;
					print_Player_Summary(player_one);
				}
				else if (command == "Exit"){
					cin >> game_id;
					print_Game_Summary(game_id);
				}
				else if (command == "SummarizeAchievement"){
					cin >> game_id >> achievement_id;
					print_Achieve_Summary(game_id, achievement_id);
				}
				else if (command == "Help"){
					display_menu();
				}
				else{
					exit = true;
				}

		}
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
			void prompt_combine(){
				string table1, table2;
				cout << "-------------------------------------------------------------------------------		" << endl;
				cout << "        While tables would you like to perform a combine on?                          	" << endl;
				cout << "-------------------------------------------------------------------------------		" << endl;
				for (int i = 0; i < db.tables.size(); i++){
					cout << "Table " << i << ": " << db.tables[i].get_name();
				}
				cout << "----------Enter the first tables name----------------------------------------------------------" << endl;
				cin >> table1;
				cout << "----------Enter the second tables name----------------------------------------------------------" << endl;
				cin >> table2;
			}
};