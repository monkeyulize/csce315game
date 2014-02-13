#include "stdafx.h"
#include "CppUnitTest.h"

#include "database.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbms_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Union_Test)
		{
			
			database db;
			string name = "animals";
			vector<string> attribute_names;
			attribute_names.push_back("name");
			attribute_names.push_back("kind");
			attribute_names.push_back("years");

			vector<string> primary_key;
			primary_key.push_back("name");
			primary_key.push_back("kind");

			vector<string> joe;
			joe.push_back("joe");
			joe.push_back("dog");
			joe.push_back("4");
			
			vector<string> bob;
			bob.push_back("bob");
			bob.push_back("cat");
			bob.push_back("3");
			
			vector<string> marty;
			marty.push_back("marty");
			marty.push_back("cat");
			marty.push_back("5");
			
			vector<string> spot;
			spot.push_back("spot");
			spot.push_back("dog");
			spot.push_back("6");

			db.create_table("dogs", attribute_names, primary_key);
			db.create_table("cats", attribute_names, primary_key);
			db.get_table("dogs").insert(joe);
			db.get_table("dogs").insert(spot);
			db.get_table("cats").insert(bob);
			db.get_table("cats").insert(marty);

			table unioned = db.set_union("pets", "cats", "dogs");

			db.create_table("Correct Union", attribute_names, primary_key);
			db.get_table("Correct Union").insert(joe);
			db.get_table("Correct Union").insert(bob);
			db.get_table("Correct Union").insert(marty);
			db.get_table("Correct Union").insert(spot);
			
			Assert::IsTrue(unioned == db.get_table("Correct Union"));
			
		}

		TEST_METHOD(Project_Test)
		{

			database db;

			string name = "animals";

			vector<string> attribute_names;
			attribute_names.push_back("name");
			attribute_names.push_back("kind");
			attribute_names.push_back("years");

			vector<string> primary_key;
			primary_key.push_back("name");
			primary_key.push_back("kind");

			vector<string> bob;
			bob.push_back("bob");
			bob.push_back("cat");
			bob.push_back("3");

			vector<string> bob1;
			bob1.push_back("bob");
			bob1.push_back("cat");
			
			vector<string> marty;
			marty.push_back("marty");
			marty.push_back("cat");
			marty.push_back("5");

			vector<string> marty1;
			marty1.push_back("marty");
			marty1.push_back("cat");

			vector<string> species;
			species.push_back("kind");
			species.push_back("name");

			db.create_table("cats", attribute_names, primary_key);
			db.get_table("cats").insert(bob);
			db.get_table("cats").insert(marty);

			db.set_projection("proj", "cats", species);

			db.create_table("Projected", species, primary_key);
			db.get_table("Projected").insert(bob1);
			db.get_table("Projected").insert(marty1);

			Assert::IsTrue(db.get_table("Projected") == db.get_table("proj"));

		}

		/*TEST_METHOD(Parser_Test)
		{
			vector<Token> parsed;
			vector<Token> chopped;

			chopped.push_back(Token(9, "CREATE TABLE"));
			chopped.push_back(Token(9, "animals"));
			chopped.push_back(Token(9, "name"));
			chopped.push_back(Token(9, "VARCHAR"));
			chopped.push_back(Token(8, 20));
			chopped.push_back(Token(9, "kind"));
			chopped.push_back(Token(9, "VARCHAR"));
			chopped.push_back(Token(8, 8));
			chopped.push_back(Token(9, "years"));
			chopped.push_back(Token(9, "INTEGER"));
			chopped.push_back(Token(9, "PRIMARY KEY"));
			chopped.push_back(Token(9, "name"));
			chopped.push_back(Token(9, "kind"));

			parsed = parser("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)");


			Assert::IsTrue(chopped == parsed);



		}*/

		

	};
}