#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "inf_int.h"

bool operator==(const inf_int& a, const inf_int& b) {

	// 1. ��ȣ ��
	if (a.thesign != b.thesign) return false; // a�� b�� ��ȣ�� �ٸ� ��� false ���

	// 2. �ڸ��� ��
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
