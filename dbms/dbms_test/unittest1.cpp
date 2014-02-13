#include "stdafx.h"
#include "CppUnitTest.h"

#include "database.h"

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

			//bool equal = false;
			//if(unioned == db.get_table("Correct Union")) { equal = true; }
			
			Assert::IsTrue(unioned == db.get_table("Correct Union"));
			//Assert::AreEqual(unioned, db.get_table("Correct Union"));
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

		TEST_METHOD(SelectionTest)
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
						
			vector<string> spot;
			spot.push_back("spot");
			spot.push_back("dog");
			spot.push_back("6");

			db.create_table("dogs", attribute_names, primary_key);
			db.get_table("dogs").insert(joe);
			db.get_table("dogs").insert(spot);


	/*	
		felines.push_back("cat");
		table selection = db.set_selection("sell", "cats", felines);
		selection = db.set_selection("sell", "cats", felines);
		selection.display_table();
		felines.push_back("6");
		table temp6 = db.set_selection("sell", "dogs", felines);
		temp6.display_table();*/
			vector<string> felines;
			felines.push_back("dog");

			table selection = db.set_selection("sell", "dog", felines);
			/*table selection = db.set_selection("bob", "cat", bob);
			table selection = db.set_selection("marty", "cat", marty);
			table selection = db.set_selection("spot", "dog", spot);*/
			
			db.create_table("Correct Selection", attribute_names, primary_key);
			db.get_table("Correct Selection").insert(joe);
			db.get_table("Correct Selection").insert(spot);

			//bool equal = false;
			//if(unioned == db.get_table("Correct Union")) { equal = true; }
			
			Assert::IsTrue(selection == db.get_table("Correct Selection"));
			//Assert::AreEqual(unioned, db.get_table("Correct Union"));
		}

		

	};
}