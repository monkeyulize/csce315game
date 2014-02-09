#include <map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//template <class T>
class entity {
private:
	//map<string, string> attributes;


public:
	entity() {}
	map<string, string> attributes;
	void set_attribute(string _field_name, string _field_value);
	void add_column(string _field_name, string _field_value);
	void show_attributes(vector<string> _ordering);
	string get_attribute(string _attribute_name);
	
	bool operator == (const entity &Ref) const {
        return attributes==Ref.attributes;
		/*if(attributes.size() != Ref.attributes.size())	//if they have differnt sizes they are not equal
				return 0;								//may  need to change for specifics
		
		map<string, string>::iterator iter_one;
		map<string, string>::iterator iter_two;
		
		for(iter = attributes.begin(), iter_two = Ref.attributes.begin(); iter_one != iter_one.end(); ++iter_one, ++iter_two)
		{
			if(*iter_one != *iter_two)
				return 0;
		}

	  return 1;*/
    }

	
};