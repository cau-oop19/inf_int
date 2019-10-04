#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <cstddef>
#include "inf_int.h"


inf_int& inf_int::operator=(const inf_int& rhs) {
	if (this->digits) delete this->digits; // 기존의 숫자를 지움
	this->digits = new char[rhs.length + 1]; // 새로운 digits 생성
	memcpy(this->digits, rhs.digits, sizeof(char)*rhs.length + 1); // 숫자 복사

	this->length = rhs.length; // 길이 복사
	this->thesign = rhs.thesign; // 부호 복사

	return *this;
}

bool operator==(const inf_int& lhs, const inf_int& rhs) {

	// 1. 부호 비교
	if (lhs.thesign != rhs.thesign) return false; // lhs와 rhs의 부호가 다른 경우 false 출력

	// 2. 길이 비교
	if (lhs.length != rhs.length) return false; // lhs와 rhs의 길이가 다를 경우 false 출력

	// 3. 자릿수 비교
	for (std::size_t i = lhs.length; i > 0; i--) { // 자릿수 순회, 숫자가 거꾸로 저장되기 때문에 -- 사용
		if (*(lhs.digits + i - 1) != *(rhs.digits + i - 1)) return false; // 현재 자릿수가 lhs와 rhs가 다른 경우 false 출력
		else continue;
	}
	return true; // lhs와 rhs가 완전히 같음, true 출력
}

bool operator!=(const inf_int& lhs, const inf_int& rhs) {
	return !operator==(lhs, rhs);
}

bool operator>(const inf_int& lhs, const inf_int& rhs) {
	if (lhs.thesign != rhs.thesign) { // lhs와 rhs의 부호가 서로 다를 경우
		return lhs.thesign; // lhs가 양수일 경우 true, rhs가 양수일 경우 false 반환
	}
	else { // lhs와 rhs의 부호가 서로 같을 경우
		 //lhs와 rhs의 길이 비교
		if (lhs.length > rhs.length) return lhs.thesign; // lhs의 길이가 더 길 경우 lhs가 양수이면 true, lhs가 음수이면 false 반환
		else if (lhs.length < rhs.length) return rhs.thesign; // rhs의 길이가 더 길 경우 rhs가 양수이면 true, rhs가 음수이면 false 반환
		else { // lhs와 rhs의 길이 또한 같을 경우
			for (std::size_t i = lhs.length; i > 0; i--) { // 자릿수 순회, 숫자가 거꾸로 저장되기 때문에 -- 사용
				if (*(lhs.digits + i - 1) > *(rhs.digits + i - 1)) return lhs.thesign; // 현재 자릿수가 lhs가 rhs보다 더 클 경우
				else if (*(lhs.digits + i - 1) < *(rhs.digits + i - 1)) return rhs.thesign; // 현재 자릿수가 lhs가 rhs보다 더 작을 경우
				else continue;
			}
			return false; // lhs와 rhs가 완전히 같음, false 출력
		}
	}
}

bool operator<(const inf_int& lhs, const inf_int& rhs) {
	return !operator>(lhs, rhs);
}
