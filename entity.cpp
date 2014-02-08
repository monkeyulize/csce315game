#include "entity.h"

void entity::add_column(string _field_name, string _field_value) {
	attributes[_field_name] = _field_value;





}

void entity::set_attribute(string _field_name, string _field_value) {
	attributes[_field_name] = _field_value;

}

void entity::show_attributes(vector<string> _ordering) {
	for(int i = 0; i < _ordering.size(); i++)
	{
		cout << attributes[_ordering[i]] << '\t';


	}
	



}