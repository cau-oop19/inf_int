#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <cstdint>
#include "inf_int.h"


inf_int::inf_int() {
	length = 1;

	thesign = true;

	digits = (char *)malloc(sizeof(char));
	*digits = '0';
}
/*
inf_int::inf_int() {
	length = 1;

	thesign = true;

	digits = (char *)malloc(sizeof(char));
	*digits = '0';
}
*/

inf_int::inf_int(int arg_int) {
	int temp = arg_int;	//arg_int 자릿수 계산을 위한 임시공간
	length = 0;

	if (arg_int < 0) {
		thesign = false;
		arg_int = 0 - temp;	//양수로 변환
	}
	else
		thesign = true;

	//자릿수 계산
	while (temp) {
		length++;
		temp /= 10;
	}

	digits = (char *)malloc(sizeof(char)*length + 1);
	//sprintf_s(digits, sizeof(char)*length, "%d", arg_int);
	itoa(arg_int, digits, sizeof(char)*length + 1, 10);	//int to char 변환과정에서 null붙음
	//memcpy(digits, (char *)&arg_int, sizeof(char)*length);
}

/*

inf_int::inf_int(int arg_int) {
	length = 0;

	if (arg_int < 0) {
		thesign = false;
		arg_int = 0 - arg_int;	//양수로 변환
	}
	else
		thesign = true;

	int temp = arg_int;	//arg_int 자릿수 계산을 위한 임시공간
	while (temp) {
		length++;
		temp /= 10;
	}

	digits = (char *)malloc(sizeof(char)*(length + 1));
	for (int i = 0; arg_int != 0; i++) {
		digits[i] = (arg_int % 10) + '0';
		arg_int /= 10;
	}
	//sprintf_s(digits, sizeof(char)*length, "%d", arg_int);
	<<<<<< < HEAD
		//_itoa_s(arg_int, digits, sizeof(char)*length + 1, 10);
		====== =
		itoa(arg_int, digits, sizeof(char)*length + 1, 10);	//int to char 변환과정에서 null붙음
	>>>>>> > 524a2da7a7b6bf341b027570ee71db8e60301381
		//memcpy(digits, (char *)&arg_int, sizeof(char)*length);
}
*/

inf_int::inf_int(const char* arg_str) {

	//문자열이 음수일 시 부호를 음수로 지정하고 문자열에서 -를 제거
	if (arg_str[0] == '-') {
		//문자열 크기는 부호 한자리를 빼서 -1
		digits = (char *)malloc(sizeof(char)*(strlen(arg_str) - 1));

		thesign = false;

		length = strlen(arg_str) - 1;

		for (int i = 1; (unsigned int)i <= length; i++)
			digits[length - i] = arg_str[i];
	}
	else {
		digits = (char *)malloc(sizeof(char)*strlen(arg_str));

		thesign = true;

		length = strlen(arg_str);

		for (int i = 0; (unsigned int) i < length; i++)
			digits[length - 1 - i] = arg_str[i];
	}
}

inf_int::inf_int(const inf_int& arg_int) {
	digits = (char *)malloc(sizeof(char)*arg_int.length);
	memcpy(this->digits, arg_int.digits, sizeof(char)*arg_int.length);
	this->length = arg_int.length;
	this->thesign = arg_int.thesign;
}

inf_int::~inf_int() {
	free(digits);
}

bool operator==(const inf_int& a, const inf_int& b) {
	for (unsigned int i = a.length; i > 0; i--) { // 자릿수 순회, 숫자가 거꾸로 저장되기 때문에 -- 사용
		if (*(a.digits + i - 1) != *(b.digits + i - 1)) return false; // 현재 자릿수가 a와 b가 다른 경우 false 출력
		else continue;
	}
	return true; // a와 b가 완전히 같음, true 출력
}

bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {
	if (a.thesign != b.thesign) { // a와 b의 부호가 서로 다를 경우
		return a.thesign; // a가 양수일 경우 true, b가 양수일 경우 false 반환
	}
	else { // a와 b의 부호가 서로 같을 경우
		 //a와 b의 길이 비교
		if (a.length > b.length) return a.thesign; // a의 길이가 더 길 경우 a가 양수이면 true, a가 음수이면 false 반환
		else if (a.length < b.length) return b.thesign; // a의 길이가 더 길 경우 a가 양수이면 true, a가 음수이면 false 반환
		else { // a와 b의 길이 또한 같을 경우
			for (unsigned int i = a.length; i > 0; i--) { // 자릿수 순회, 숫자가 거꾸로 저장되기 때문에 -- 사용
				if (*(a.digits + i - 1) > *(b.digits + i - 1)) return a.thesign; // 현재 자릿수가 a가 b보다 더 클 경우
				else if (*(a.digits + i - 1) < *(b.digits + i - 1)) return b.thesign; // 현재 자릿수가 a가 b보다 더 작을 경우
				else continue;
			}
			return false; // a와 b가 완전히 같음, false 출력
		}
	}
}

bool operator<(const inf_int& a, const inf_int& b) {
	return !operator>(a, b);
}


void inf_int::calcCarries() {
	for (size_t i = 0; i != length - 1 - 1; ++i) {
		while (digits[i] >= 10) {
			digits[i] -= 10;
			digits[i + 1] += 1;
		}
	}

	if (digits[length - 1] >= 10)
		extend(1);

	while (digits[length - 1 - 1] >= 10) {
		digits[length - 1 - 1] -= 10;
		digits[length - 1] += 1;
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
	inf_int res{ longer.length };
	for (size_t i = 0; i != shorter.length - 1; ++i) {
		res.digits[i]
			= longer_sign * longer.digits[i]
			+ shorter_sign * shorter.digits[i];
	}

	res.calcCarries();
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
	for (size_t i = 0; i != shorter.length - 1; ++i) {
		for (size_t j = 0; j != longer.length - 1; ++j) {
			res.digits[j] *= shorter.digits[i];
			res.calcCarries();
		}
	}
	return res;
}

std::ostream& operator<<(std::ostream& ostr, const inf_int& self) {
	std::string str{ self.digits, self.length };
	std::reverse(str.begin(), str.end());
	if (self.thesign == false)
		ostr << "-";
	ostr << std::move(str);
	return ostr;
}