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
	this->digits = new char[2];	// �����Ҵ�

	this->digits[0] = '0';		// default �� 0 ����
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}
inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) {		// ���� ó��
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0) {			// ���ڸ� ���ڿ��� ��ȯ�ϴ� ����
		buf[i] = n % 10 + '0';

		n /= 10;
		i++;
	}

	if (i == 0) {	// ������ ������ 0�� ���
		new (this) inf_int();	// ������ ��ȣ��...gcc���� �����Ͽ����� �ִٰ� ��. inf_int()�� ��� ������ �ν��Ͻ��� ������. 
	}
	else {
		buf[i] = '\0';

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buf);
	}
}


bool operator==(const inf_int& a, const inf_int& b) {
	for (unsigned int i = a.length; i > 0; i--) { // �ڸ��� ��ȸ, ���ڰ� �Ųٷ� ����Ǳ� ������ -- ���
		if (*(a.digits + i - 1) != *(b.digits + i - 1)) return false; // ���� �ڸ����� a�� b�� �ٸ� ��� false ���
		else continue;
	}
	return true; // a�� b�� ������ ����, true ���
}

bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {
	if (a.thesign != b.thesign) { // a�� b�� ��ȣ�� ���� �ٸ� ���
		return a.thesign; // a�� ����� ��� true, b�� ����� ��� false ��ȯ
	}
	else { // a�� b�� ��ȣ�� ���� ���� ���
		 //a�� b�� ���� ��
		if (a.length > b.length) return a.thesign; // a�� ���̰� �� �� ��� a�� ����̸� true, a�� �����̸� false ��ȯ
		else if (a.length < b.length) return b.thesign; // a�� ���̰� �� �� ��� a�� ����̸� true, a�� �����̸� false ��ȯ
		else { // a�� b�� ���� ���� ���� ���
			for (unsigned int i = a.length; i > 0; i--) { // �ڸ��� ��ȸ, ���ڰ� �Ųٷ� ����Ǳ� ������ -- ���
				if (*(a.digits + i - 1) > *(b.digits + i - 1)) return a.thesign; // ���� �ڸ����� a�� b���� �� Ŭ ���
				else if (*(a.digits + i - 1) < *(b.digits + i - 1)) return b.thesign; // ���� �ڸ����� a�� b���� �� ���� ���
				else continue;
			}
			return false; // a�� b�� ������ ����, false ���
		}
	}
}

bool operator<(const inf_int& a, const inf_int& b) {
	return !operator>(a, b);
}
