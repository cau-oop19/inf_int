/**
	@file   constructor.cpp
	@date   2019/10/04
	@author 김명승(mskim9967@gmail.com) 중앙대학교 소프트웨어학부 20186274
	@brief  생성자 소멸자
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include "inf_int.h"

inf_int::inf_int() {
	new (this) inf_int("0");
}

inf_int::inf_int(int arg_int) {
	int intTemp = arg_int;
	size_t intLen = 0;

	do {
		intLen++;
	} while (intTemp /= 10);

	char* intToStr = (char *)malloc(sizeof(char)*(intLen + 1));	//NULL 자리 포함해서 +1
	sprintf_s(intToStr, sizeof(char)*(intLen + 2), "%d", arg_int);	//NULL, 앞의 부호 자리 포함해서 +2 

	new (this) inf_int((const char*)intToStr);

	//free(intToStr);
}


inf_int::inf_int(const char* arg_str) {
	//-0이 입력되면 0으로 바꿈
	if (!memcmp(arg_str, "-0", strlen(arg_str))) {
		new (this) inf_int("0");
		return;
	}

	size_t start_i;
	for (size_t i = 0; i < strlen(arg_str); i++) {
		if (arg_str[i] >= '1'&&arg_str[i] <= '9') {
			thesign = arg_str[0] == '-' ? false : true;

			start_i = i;
			break;
		}
		//위 if문을 한번도 실행 못한 문자열은 0으로만 이루어진 문자열이므로 부호는 항상 +
		start_i = i;
		thesign = true;
	}

	length = strlen(arg_str) - start_i;

	digits = (char *)malloc(sizeof(char)*length);

	for (size_t i = 1; i <= length; i++)
		digits[length - i] = arg_str[start_i++];
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


inf_int::inf_int(unsigned int size) {
	length = size;
	thesign = true;

	digits = (char *)malloc(sizeof(char)*length);

	for (size_t i = 0; i < length; i++)
		digits[i] = '0';
}

/*
////////////////for debugging///////////////////

void inf_int::print() {
	for (int i = 0; i < length; i++)
		std::cout << digits[i];
	std::cout << std::endl;
	std::cout << length << std::endl;
	std::cout << thesign << std::endl;
	std::cout << std::endl;
}


int main() {

	inf_int a;
	inf_int b(-10000), c(500), d(0), e(-0);
	inf_int f("321111111111122222222222233333333333444444444445555555555");
	inf_int g("-00000001234519876512345727494999234550222110000");
	inf_int h = c;

	inf_int i(f);

	inf_int j("-0"), k("0"),l("000000000000"),m("-00000000");

	a.print();
	b.print();
	c.print();
	d.print();
	e.print();
	f.print();
	g.print();
	h.print();
	i.print();
	j.print();
	k.print();
	l.print();
	m.print();

}

*/