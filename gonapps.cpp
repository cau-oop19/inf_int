#include <utility>
#include "inf_int.h"

friend inf_int operator+(const inf_int& lhs, const inf_int& rhs) {
	// + +: len == longer_len || len == longer_len + 1
	// - -: len == longer_len || len == longer_len + 1
	// + -: 1 <= len <= longer_len

	return res;
}

friend inf_int operator-(const inf_int& lhs, const inf_int& rhs) {
	return res;
}

friend inf_int operator*(const inf_int& lhs, const inf_int& rhs) {
	// len == len1 + len2 || len == len1 + len2 + 1
	return res;
}

friend inf_int operator/(const inf_int& lhs, const inf_int& rhs) {
	return res;
}

friend std::ostream& operator<<(std::ostream& ostr, const inf_int& self) {
	std::string str{digits, length};
	ostr << thesign ? "+", "-";
        ostr << std::move(str);
	return ostr;
}

