/**
	@file   constructor.cpp
	@date   2019/10/02
	@author 김명승(mskim9967@gmail.com) 중앙대학교 소프트웨어학부 20186274
	@brief  생성자 소멸자
*/

#include "inf_int.h"

inf_int::inf_int() {
	length = 1;

	thesign = true;

	digits = (char *)malloc(sizeof(char));
	*digits = '0';
}

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
	_itoa_s(arg_int, digits, sizeof(char)*length + 1, 10);	//int to char 변환과정에서 null붙음
	//memcpy(digits, (char *)&arg_int, sizeof(char)*length);
}

inf_int::inf_int(const char* arg_str) {
	char* temp_str;

	//문자열이 음수일 시 부호를 음수로 지정하고
	//문자열에서 -를 제거
	if (arg_str[0] == '-') {
		//부호 한자리 빼서 -1
		temp_str = (char *)malloc(sizeof(char)*(strlen(arg_str) - 1));

		thesign = false;

		length = strlen(arg_str) - 1;

		for (int i = 0; i < length; i++)
			temp_str[i] = arg_str[i + 1];
	}
	else {
		temp_str = (char *)malloc(sizeof(char)*strlen(arg_str));

		thesign = true;

		length = strlen(arg_str);

		memcpy(temp_str, arg_str, sizeof(char)*strlen(arg_str));
	}

	digits = (char *)malloc(sizeof(char)*length);
	memcpy(digits, temp_str, sizeof(char)*length);	//NULL 제외
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
/*
void inf_int::print() {
	for (int i = 0; i < length; i++)
		std::cout << digits[i];
	std::cout<< std::endl;
	std::cout << length << std::endl;
	std::cout << thesign << std::endl;
	std::cout << std::endl;
}


int main(){
	inf_int a;
	inf_int b(-100),c(50000);
	inf_int d("321111111111122222222222233333333333444444444445555555555");
	inf_int e("-123451987651234572749499923455022211");
	inf_int f = c;

	inf_int g(f);

	a.print();
	b.print();
	c.print();
	d.print();
	e.print();
	f.print();
}
*/