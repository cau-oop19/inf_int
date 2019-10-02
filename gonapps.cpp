#include <utility>
#include <string>
#include "inf_int.h"

inf_int operator+(const inf_int& lhs, const inf_int& rhs) {
	// + +: len == longer_len || len == longer_len + 1
	// - -: len == longer_len || len == longer_len + 1
	// + -: 1 <= len <= longer_len
	const inf_int* const longer = lhs.length > rhs.length ? &lhs : &rhs;
	const inf_int* const shorter = lhs.length < rhs.length ? &lhs : &rhs;
/*
        inf_int res{longer.length};
	for(size_t i = 0; i != shorter.length - 1; ++i) {
		res.digits[longer.length - i]
		= longer.digits[longer.length - i]
		+ shorter.digits[shorter.length - i];
	}
	return res;

*/
}

inf_int operator-(const inf_int& lhs, const inf_int& rhs) {
        inf_int res{lhs.length > rhs.length ? lhs.length : rhs.length};
	return res;
}

inf_int operator*(const inf_int& lhs, const inf_int& rhs) {
	// len == len1 + len2 || len == len1 + len2 + 1
        inf_int res{lhs.length > rhs.length ? lhs.length : rhs.length};
	return res;
}

std::ostream& operator<<(std::ostream& ostr, const inf_int& self) {
	std::string str{self.digits, self.length};
	ostr << self.thesign ? "+" : "-";
        ostr << std::move(str);
	return ostr;
}
