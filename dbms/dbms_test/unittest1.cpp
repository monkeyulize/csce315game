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



		}

		

	};
}