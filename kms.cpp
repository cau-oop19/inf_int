/**
	@file   constructor.cpp
	@date   2019/10/03
	@author ����(mskim9967@gmail.com) �߾Ӵ��б� ����Ʈ�����к� 20186274
	@brief  ������ �Ҹ���
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include "inf_int.h"

inf_int::inf_int() {
	length = 1;

	thesign = true;

	digits = (char *)malloc(sizeof(char));
	*digits = '0';
}

inf_int::inf_int(int arg_int) {
	length = 0;

	if (arg_int < 0) {
		thesign = false;
		arg_int = 0 - arg_int;	//����� ��ȯ
	}
	else
		thesign = true;

	int temp = arg_int;	//arg_int �ڸ��� ����� ���� �ӽð���
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
	//_itoa_s(arg_int, digits, sizeof(char)*length + 1, 10);
	//itoa(arg_int, digits, sizeof(char)*length + 1, 10);	//int to char ��ȯ�������� null����
	//memcpy(digits, (char *)&arg_int, sizeof(char)*length);
}

inf_int::inf_int(const char* arg_str) {

	//���ڿ��� ������ �� ��ȣ�� ������ �����ϰ� ���ڿ����� -�� ����
	if (arg_str[0] == '-') {
		//���ڿ� ũ��� ��ȣ ���ڸ��� ���� -1
		digits = (char *)malloc(sizeof(char)*(strlen(arg_str) - 1));

		thesign = false;

		length = strlen(arg_str) - 1;

		for (int i = 1; i <= length; i++)
			digits[length - i] = arg_str[i];
	}
	else {
		digits = (char *)malloc(sizeof(char)*strlen(arg_str));

		thesign = true;

		length = strlen(arg_str);

		for (int i = 0; i < length; i++)
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

/*	
////////////////for debugging///////////////////

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
