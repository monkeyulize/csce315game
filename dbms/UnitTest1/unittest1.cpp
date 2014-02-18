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

	};
}