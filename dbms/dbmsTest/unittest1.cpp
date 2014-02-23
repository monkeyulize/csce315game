#include "stdafx.h"
#include "CppUnitTest.h"
#include "database.h"
#include "parser.h"
#include "tokenizer.h"
#include <iostream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dbmsTest
{		
	database db;
	parser p(db);
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(createCommandTest)
		{
			

			std::stringstream eval_input;
			eval_input << "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);\n";
			std::cin.rdbuf(eval_input.rdbuf());

			p.evaluate_statement();

			table test;

			//push back test attribute names
			vector<string> attr_names;
			attr_names.push_back("name");
			attr_names.push_back("kind");
			attr_names.push_back("years");
			test.set_attr_names(attr_names);

			//push back test primary key
			vector<string> primary_key;
			primary_key.push_back("name");
			primary_key.push_back("kind");
			test.set_pri_key(primary_key);

			//set test name
			test.set_name("animals");

			Assert::IsTrue(test == db.get_table("animals"));
		}
		TEST_METHOD(insertCommandTest)
		{
			std::stringstream eval_input;
			eval_input << "INSERT INTO animals VALUES FROM(\"Joe\", \"cat\", 4);" <<
				"INSERT INTO animals VALUES FROM(\"Spot\", \"dog\", 10);" <<
				"INSERT INTO animals VALUES FROM(\"Snoopy\", \"dog\", 3);" <<
				"INSERT INTO animals VALUES FROM(\"Tweety\", \"bird\", 1);" <<
				"INSERT INTO animals VALUES FROM(\"Joe\", \"bird\", 2);";
			std::cin.rdbuf(eval_input.rdbuf());

			p.evaluate_statement();

			table test;

			//push back test attribute names
			vector<string> attr_names;
			attr_names.push_back("name");
			attr_names.push_back("kind");
			attr_names.push_back("years");
			test.set_attr_names(attr_names);

			//push back test primary key
			vector<string> primary_key;
			primary_key.push_back("name");
			primary_key.push_back("kind");
			test.set_pri_key(primary_key);

			//set test name
			test.set_name("cats");

			Assert::IsTrue(test == db.get_table("cats"));
		}
		TEST_METHOD(UnionTest)
		{
			database db;
			bool check;

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

			vector<string> fluffy;
			fluffy.push_back("fluffy");
			fluffy.push_back("cat");
			fluffy.push_back("1");

			vector<string> merlin;
			merlin.push_back("merlin");
			merlin.push_back("cat");
			merlin.push_back("3");

			db.create_table("cats", attribute_names, primary_key);
			db.create_table("dogs", attribute_names, primary_key);

			db.get_table("cats").insert(fluffy);
			db.get_table("cats").insert(merlin);

			db.get_table("dogs").insert(joe);
			db.get_table("dogs").insert(spot);

			table test("animals", attribute_names, primary_key);
			test.insert(joe);
			test.insert(spot);
			test.insert(fluffy);
			test.insert(merlin);

			if (test == db.set_union("animals", db.get_table("cats"), db.get_table("dogs")))
			{
				check = true;

			}

			Assert::IsTrue(check);


		}
		TEST_METHOD(DifferenceTest)
		{

			database db;
			bool check;

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

			vector<string> fluffy;
			fluffy.push_back("fluffy");
			fluffy.push_back("cat");
			fluffy.push_back("1");

			vector<string> merlin;
			merlin.push_back("merlin");
			merlin.push_back("cat");
			merlin.push_back("3");

			db.create_table("cats", attribute_names, primary_key);
			db.create_table("dogs", attribute_names, primary_key);

			db.get_table("cats").insert(fluffy);
			db.get_table("cats").insert(joe);

			db.get_table("dogs").insert(joe);
			db.get_table("dogs").insert(spot);

			db.set_difference("animals", db.get_table("dogs"), db.get_table("cats"));

			table test("check", attribute_names, primary_key);
			test.insert(fluffy);
			test.insert(joe);
			test.insert(spot);

			if (db.set_difference("animals", db.get_table("dogs"), db.get_table("cats")) == test)
			{
				check = true;
			}

			Assert::IsTrue(check);

		}
		/*TEST_METHOD(ProductTest)
		{
		database db;
		bool check;

		vector<string> attribute_names;
		attribute_names.push_back("name");
		attribute_names.push_back("kind");
		attribute_names.push_back("years");

		vector<string> attribute_names1;
		attribute_names.push_back("")

		vector<string> primary_key;
		primary_key.push_back("name");
		primary_key.push_back("kind");


		vector<string> joe;
		joe.push_back("joe");
		joe.push_back("dog");
		joe.push_back("4");

		vector<string> fluffy;
		fluffy.push_back("fluffy");
		fluffy.push_back("cat");
		fluffy.push_back("1");

		vector<string> product3;
		product3.push_back("joe");
		product3.push_back("dog");
		product3.push_back("1");

		vector<string> product4;
		product3.push_back("joe");
		product3.push_back("cat");
		product3.push_back("4");

		vector<string> product5;
		product5.push_back("joe");
		product5.push_back("cat");
		product5.push_back("1");

		vector<string> product6;
		product5.push_back("fluffy");
		product5.push_back("cat");
		product5.push_back("4");

		vector<string> product7;
		product5.push_back("fluffy");
		product5.push_back("dog");
		product5.push_back("1");

		vector<string> product8;
		product5.push_back("fluffy");
		product5.push_back("dog");
		product5.push_back("4");


		db.create_table("cats", attribute_names, primary_key);
		db.create_table("dogs", attribute_names, primary_key);

		db.get_table("cats").insert(fluffy);

		db.get_table("dogs").insert(joe);

		table test("animals", attribute_names, primary_key);
		test.insert(joe);
		test.insert(fluffy);

		if (test == db.set_union("animals", db.get_table("cats"), db.get_table("dogs")))
		{
		check = true;

		}

		Assert::IsTrue(check);


		}*/
		TEST_METHOD(NaturalJoinTest)
		{

			database db;
			bool check;

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

			vector<string> parker;
			parker.push_back("parker");
			parker.push_back("dog");
			parker.push_back("5");

			vector<string> fluffy;
			fluffy.push_back("fluffy");
			fluffy.push_back("cat");
			fluffy.push_back("1");

			vector<string> merlin;
			merlin.push_back("merlin");
			merlin.push_back("cat");
			merlin.push_back("3");

			vector<string> rascal;
			rascal.push_back("rascal");
			rascal.push_back("cat");
			rascal.push_back("2");

			db.create_table("cats", attribute_names, primary_key);
			db.create_table("dogs", attribute_names, primary_key);

			db.get_table("cats").insert(fluffy);
			db.get_table("cats").insert(joe);
			db.get_table("cats").insert(merlin);
			db.get_table("cats").insert(rascal);
			db.get_table("cats").insert(parker);

			db.get_table("dogs").insert(joe);
			db.get_table("dogs").insert(spot);
			db.get_table("dogs").insert(parker);
			db.get_table("dogs").insert(fluffy);
			db.get_table("dogs").insert(merlin);


			table test("check", attribute_names, primary_key);
			test.insert(fluffy);
			test.insert(joe);
			test.insert(parker);

			if (db.set_natural_join("animals", db.get_table("dogs"), db.get_table("cats")) == test)
			{
				check = true;
			}

			Assert::IsTrue(check);

		}
		TEST_METHOD(InsertionTest)
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

			vector<string> duplicate;
			duplicate.push_back("joe");
			duplicate.push_back("dog");
			duplicate.push_back("1");

			db.create_table("dogs", attribute_names, primary_key);
			db.get_table("dogs").insert(joe);
			db.get_table("dogs").insert(spot);
			db.get_table("dogs").insert(duplicate);
			db.get_table("dogs").insert(joe);

			Assert::IsTrue(2 == db.get_table("dogs").entity_table.size());
		}


	};
}