#include <map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//template <class T>
class entity {
private:
	map<string, string> attributes;


public:
	entity() {}
	void set_attribute(string _field_name, string _field_value);
	void add_column(string _field_name, string _field_value);
	void show_attributes(vector<string> _ordering);








};