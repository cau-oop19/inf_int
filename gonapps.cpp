#include <utility>
#include "inf_int.h"

friend inf_int operator+(const inf_int& lhs, const inf_int& rhs) {
	
}

friend inf_int operator-(const inf_int& lhs, const inf_int& rhs) {
	
}

friend inf_int operator*(const inf_int& lhs, const inf_int& rhs) {
	
}

friend inf_int operator/(const inf_int& lhs, const inf_int& rhs) {
}

friend std::ostream& operator<<(std::ostream& ostr, const inf_int& self) {
	std::string str{digits, length};
	ostr << std::move((thesign ? "+", "-") + str);
	return ostr;
}

