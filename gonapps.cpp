#include <algorithm>
#include <utility>
#include <string>
#include <cstdint>
#include "inf_int.h"

void inf_int::calcCarries() {
	for(size_t i = 0; i != length - 1; ++i) {
		while(digits[i] >= 10) {
			digits[i] -= 10;
			digits[i + 1] += 1;
		}
		while(digits[i] <= -10) {
			digits[i] += 10;
			digits[i + 1] -= 1;
		}
	}

	if(digits[length - 1] >= 10 || digits[length - 1] <= -10)
		extend(1);

	while(digits[length - 1 - 1] >= 10) {
		digits[length - 1 - 1] -= 10;
		digits[length - 1] += 1;
	}

	while(digits[length - 1 - 1] <= -10) {
		digits[length - 1 - 1] += 10;
		digits[length - 1] -= 1;
	}
}

void inf_int::calcPartialSum() {
	for(size_t i = length - 1 - 1; i != -1; --i) {
		if(digits[i + 1] * digits[i] < 0) {
			if(digits[i + 1] > 0) {
				++digits[i + 1];
				if(digits[i] > 0)
					digits[i] = 10 - digits[i];
				else
					digits[i] = -10 - digits[i];

			} else {
				--digits[i + 1];
				if(digits[i] > 0)
					digits[i] = 10 - digits[i];
				else
					digits[i] = -10 - digits[i];
			}
		}
	}
}

void inf_int::normalize() {
	thesign = digits[length - 1] >= 0;
	for(size_t i = 0; i != length; ++i) {
		if(digits[i] < 0)
			digits *= -1;
	}
}

inf_int operator+(const inf_int& lhs, const inf_int& rhs) {
	// + +: len == longer_len || len == longer_len + 1
	// - -: len == longer_len || len == longer_len + 1
	// + -: 1 <= len <= longer_len
	const auto& longer = lhs.length > rhs.length ? lhs : rhs;
	const auto& shorter = lhs.length < rhs.length ? lhs : rhs;
	const auto longer_sign = static_cast<uint8_t>(longer.thesign ? 1 : -1);
	const auto shorter_sign = static_cast<uint8_t>(shorter.thesign ? 1 : -1);
	inf_int res{longer.length};
	for(size_t i = 0; i != shorter.length - 1; ++i) {
		res.digits[i]
		= longer_sign * longer.digits[i]
		+ shorter_sign * shorter.digits[i];
	}
	if(longer_sign == shorter_sign)
		res.calcCarries();
	else
		res.calcPartialSum();
	res.normalize();
	return res;
}

inf_int operator-(const inf_int& lhs, const inf_int& rhs) {
	auto tmp = rhs;
	tmp.thesign = !rhs.thesign;
	return operator+(lhs, tmp);
}

inf_int operator*(const inf_int& lhs, const inf_int& rhs) {
	//  len == len1 + len2 - 1 || len == len1 + len2
	const auto& longer = lhs.length > rhs.length ? lhs : rhs;
	const auto& shorter = lhs.length < rhs.length ? lhs : rhs;
	auto res = longer;
	for(size_t i = 0; i != shorter.length - 1; ++i) {
		for(size_t j = 0; j != longer.length - 1; ++j) {
			res.digits[j] *= shorter.digits[i];
			res.calcCarries();
		}
	}
	return res;
}

std::ostream& operator<<(std::ostream& ostr, const inf_int& self) {
	std::string str{self.digits, self.length};
	std::reverse(str.begin(), str.end());
	if(self.thesign == false)
	ostr << "-";
	ostr << std::move(str);
	return ostr;
}
