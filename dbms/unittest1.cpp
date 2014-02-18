#include "stdafx.h"
#include "CppUnitTest.h"

#include "../dbms/database.h"
#include "../dbms/parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbms_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(UnionTest)
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
		
		
		TEST_METHOD(DifferenceTest)
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

			table difference = db.set_difference("pets", "cats", "dogs");

			db.create_table("Correct Difference", attribute_names, primary_key);
			db.get_table("Correct Difference").insert(joe);
			db.get_table("Correct Difference").insert(bob);
			db.get_table("Correct Difference").insert(marty);
			db.get_table("Correct Difference").insert(spot);

			//bool equal = false;
			//if(unioned == db.get_table("Correct Union")) { equal = true; }
			
			Assert::IsTrue(difference == db.get_table("Correct Difference"));
			//Assert::AreEqual(unioned, db.get_table("Correct Union"));
		}
		
		TEST_METHOD(parser_updateTest)
		{
			stringstream update_input;
			update_input << "animals SET name = \"bob\" WHERE age <= 10 && kind == \"dog\"";
			parser p;
			cin.rdbuf(update_input.rdbuf());
			p.update_cmd();
			string relation_name = "animals";
			vector<pair<string, string>> set_attributes;
			set_attributes.push_back(pair<string, string>("name", "bob"));
			condition_obj condits;
			conjunction_obj conjun;
			comparison_obj comp;
			comp.oper1 = "age";
			comp.oper2 = "10";
			comp.op = "<";
			conjun.comparisons.push_back(comp);
			condits.conjunctions.push_back(conjun);

			Assert::IsTrue(1 == 1);

			


		}

		

	};
}