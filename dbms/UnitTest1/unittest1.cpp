#include "stdafx.h"
#include "CppUnitTest.h"
#include "../dbms/database.h"
#include "../dbms/parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(parser_updateTest)
		{
			update_obj test_obj;
			update_obj set_obj;
			stringstream update_input;
			update_input << "animals SET name = \"bob\" WHERE age < 10;";
			parser p;
			cin.rdbuf(update_input.rdbuf());

			test_obj = p.update_cmd();

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

			set_obj.attribute_values = set_attributes;
			set_obj.condition = condits;
			set_obj.rel_name = relation_name;

			Assert::IsTrue(test_obj == set_obj);
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