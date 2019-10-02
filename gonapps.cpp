#include <algorithm>
#include <utility>
#include <string>
#include <cstdint>
#include "inf_int.h"

static void calcCarries(inf_int* val) {
	for(size_t i = 0; i != val->length - 1 - 1; ++i) {
		while(val->digits[i] >= 10) {
			val->digits[i] -= 10;
			val->digits[i + 1] += 1;
		}
	}

	if(val->digits[val->length - 1] >= 10)
		val->extend(1);

	while(val->digits[val->length - 1 - 1] >= 10) {
		val->digits[val->length - 1 - 1] -= 10;
		val->digits[val->length - 1] += 1;
	}
}

inf_int operator+(const inf_int& lhs, const inf_int& rhs) {
	// + +: len == longer_len || len == longer_len + 1
	// - -: len == longer_len || len == longer_len + 1
	// + -: 1 <= len <= longer_len
	const auto& longer = lhs.length > rhs.length ? lhs : rhs;
	const auto& shorter = lhs.length < rhs.length ? lhs : rhs;
	const auto longer_sign = static_cast<uint8_t>(longer.thesign ? 1 : -1);
	const auto shorter_sign = static_cast<uint8_t>(longer.thesign ? 1 : -1);
	inf_int res{longer.length};
	for(size_t i = 0; i != shorter.length - 1; ++i) {
		res.digits[i]
		= longer_sign * longer.digits[i]
		+ shorter_sign * shorter.digits[i];
	}

	calcCarries(&res);
	return res;
}

inf_int operator-(const inf_int& lhs, const inf_int& rhs) {
	auto rhsCopy = rhs;
	inf_int res{lhs.length > rhs.length ? lhs.length : rhs.length};
	return res;
}

inf_int operator*(const inf_int& lhs, const inf_int& rhs) {
	//  len == len1 + len2 || len == len1 + len2 + 1
	inf_int res{lhs.length > rhs.length ? lhs.length : rhs.length};
	return res;
}

std::ostream& operator<<(std::ostream& ostr, const inf_int& self) {
	std::string str{self.digits, self.length};
	std::reverse(str.begin(), str.end());
	ostr << self.thesign ? "+" : "-";
	ostr << std::move(str);
	return ostr;
}
