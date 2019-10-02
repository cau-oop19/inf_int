#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

class inf_int
{
private:
	char* digits;
	unsigned int length;
	bool thesign;   // true if positive , false if negative.
	// ex) 15311111111111111 -> digits="11111111111111351", length=17, thesign=true;
	// ex) -12345555555555 -> digits="55555555554321", length=14, thesign=false
	// you may insert additional private members here.

public:

	inf_int();
	inf_int(int);

	friend bool operator==(const inf_int&, const inf_int&);
	friend bool operator!=(const inf_int&, const inf_int&);
	friend bool operator>(const inf_int&, const inf_int&);
	friend bool operator<(const inf_int&, const inf_int&);

};

inf_int::inf_int()
{
	this->digits = new char[2];	// 동적할당

	this->digits[0] = '0';		// default 값 0 설정
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}
inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) {		// 음수 처리
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0) {			// 숫자를 문자열로 변환하는 과정
		buf[i] = n % 10 + '0';

		n /= 10;
		i++;
	}

	if (i == 0) {	// 숫자의 절댓값이 0일 경우
		new (this) inf_int();	// 생성자 재호출...gcc에서 컴파일에러가 있다고 함. inf_int()의 경우 별개의 인스턴스가 생성됨. 
	}
	else {
		buf[i] = '\0';

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buf);
	}
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
