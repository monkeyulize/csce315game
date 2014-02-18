#ifndef CONDITION_OBJ_H
#define CONDITION_OBJ_H
#include "conjunction_obj.h"

class condition_obj {
public:
	std::vector<conjunction_obj> conjunctions; //|| between elements

	bool operator==(const condition_obj &c);

};

inline bool condition_obj::operator==(const condition_obj& c) {
	bool is_equal = false;
	if (conjunctions.size() != c.conjunctions.size()) {
		return false;
	}
	for (int i = 0; i < conjunctions.size(); i++) {
		if (conjunctions[i] == c.conjunctions[i]) {
			is_equal = true;
		}
		else {
			return false;
		}
	}
	return is_equal;
}

#endif
