#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <emmintrin.h>
#include "inf_int.h"


inf_int& inf_int::operator=(const inf_int& rhs) {
	if (this->digits) delete this->digits;
	this->digits = new char[rhs.length + 1];
	memcpy(this->digits, rhs.digits, sizeof(char)*rhs.length + 1);

	this->length = rhs.length;
	this->thesign = rhs.thesign;

	return *this;
}

bool operator==(const inf_int& lhs, const inf_int& rhs) {

	if (lhs.thesign != rhs.thesign || lhs.length != rhs.length)
		return false;

	size_t idx = 0;
	for (; idx + 16 < rhs.length; idx += 16) {
		int mask = _mm_movemask_epi8(_mm_cmpeq_epi32(*(__m128i*)(lhs.digits + idx), *(__m128i*)(rhs.digits + idx)));
		if (mask != 0xffff)
			return false;
	}

	for (; idx < rhs.length; ++idx) {
		if(lhs.digits[idx] != rhs.digits[idx])
			return false;
	}

	return true;
}

bool operator!=(const inf_int& lhs, const inf_int& rhs) {
	return !operator==(lhs, rhs);
}

bool operator>(const inf_int& lhs, const inf_int& rhs) {
	if (lhs.thesign != rhs.thesign) return lhs.thesign;
	if (lhs.length > rhs.length) return lhs.thesign;
	else if (lhs.length < rhs.length) return !lhs.thesign;

	for (std::size_t i = lhs.length; i > 0; i--) {
		if (*(lhs.digits + i - 1) > *(rhs.digits + i - 1)) return lhs.thesign;
		else if (*(lhs.digits + i - 1) < *(rhs.digits + i - 1)) return !lhs.thesign;
		else continue;
	}

	return false;
}

bool operator<(const inf_int& lhs, const inf_int& rhs) {

	if (lhs.thesign != rhs.thesign) return rhs.thesign;

	if (lhs.length > rhs.length) return !lhs.thesign;
	else if (lhs.length < rhs.length) return lhs.thesign;

	for (std::size_t i = lhs.length; i > 0; i--) {
		if (*(lhs.digits + i - 1) > *(rhs.digits + i - 1)) return !lhs.thesign;
		else if (*(lhs.digits + i - 1) < *(rhs.digits + i - 1)) return lhs.thesign;
		else continue;
	}

	return false;
}
