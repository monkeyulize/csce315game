#ifndef CONJUNCTION_OBJ_H
#define CONJUNCTION_OBJ_H
#include "comparison_obj.h"

class conjunction_obj {
public:
	std::vector<comparison_obj> comparisons; //&& between elements
	bool operator==(const conjunction_obj& c);
};

inline bool conjunction_obj::operator == (const conjunction_obj& c) {
	bool is_equal = false;
	if (comparisons.size() != c.comparisons.size()) {
		return false;
	}
	for (int i = 0; i < comparisons.size(); i++) {
		if (comparisons[i] == c.comparisons[i]) {
			is_equal = true;
		}
		else {
			return false;
		}
	}
	return is_equal;
}

#endif // !CONJUNCTION_OBJ_H
