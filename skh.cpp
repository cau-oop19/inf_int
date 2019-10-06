#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <cstddef>
#include "inf_int.h"


inf_int& inf_int::operator=(const inf_int& rhs) {
	if (this->digits) delete this->digits; // ������ ���ڸ� ����
	this->digits = new char[rhs.length + 1]; // ���ο� digits ����
	memcpy(this->digits, rhs.digits, sizeof(char)*rhs.length + 1); // ���� ����

	this->length = rhs.length; // ���� ����
	this->thesign = rhs.thesign; // ��ȣ ����

	return *this;
}

bool operator==(const inf_int& lhs, const inf_int& rhs) {

	// 1. ��ȣ ��
	if (lhs.thesign != rhs.thesign) return false; // lhs�� rhs�� ��ȣ�� �ٸ� ��� false ���

	// 2. ���� ��
	if (lhs.length != rhs.length) return false; // lhs�� rhs�� ���̰� �ٸ� ��� false ���

	// 3. �ڸ��� ��
	/*
	for (std::size_t i = lhs.length; i > 0; i--) { // �ڸ��� ��ȸ, ���ڰ� �Ųٷ� ����Ǳ� ������ -- ���
		if (*(lhs.digits + i - 1) != *(rhs.digits + i - 1)) return false; // ���� �ڸ����� lhs�� rhs�� �ٸ� ��� false ���
		else continue;
	}
	*/



	///////////////////////////////////////////
	////////// ��Ƽ������ �׽�Ʈ ���� /////////
	///////////////////////////////////////////


	/*
		���� �ʿ��� �������� ������ ���ϰ�, ��� �����忡�� ������ �� �ִ� atomic ���� result�� �����մϴ�.
		�� �� lhs�� rhs�� digits�� ������ ����ŭ �����ϰ�, ������ string�� char*�� ���·� �� �����忡 �Ҵ��մϴ�.
		�� �����忡���� �Ҵ�� �з��� �� string�� ������ Ȯ���ϸ�, �ٸ� �κ��� �߰ߵ� ��� result�� false�� ��ȯ�մϴ�.
		�� �ϳ��� �����忡���� �ٸ� �κ��� �߰����� ���, result�� false�� �ǰ� ��� ������� ����˴ϴ�.
		��� �����尡 ����� ��, result�� bool���� ����, ������ �����ߴ� string���� ��� ������ ���� Ȯ���մϴ�.
	*/


	// �ʿ��� �������� ���� ����
	// ���� ������ ���̰� CPU�� �ھ� ������ ���� ��� �ھ� ����, �׷��� ���� ��� ���� ������ ���̸� ����
	const std::size_t number_of_threads = (lhs.length >= std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : lhs.length);

	//// �����带 �� �ھ� ����ŭ ����
	std::atomic<bool> result { true }; // ����� ����, �⺻������ true ����
	std::thread *thread = new std::thread[number_of_threads]; // ������ ����

	// ������ ���� �� ����
	std::size_t digits_offset = 0; // �����忡 �Ҵ�� string�� ���� ������ ��������� ������
	for (std::size_t i = 0; i < number_of_threads; i++) {

		std::size_t offset_jump_length = ((lhs.length % number_of_threads) > i) ? ((lhs.length / number_of_threads) + 1) : (lhs.length / number_of_threads); // �����忡 �Ҵ�� string�� ����

		// ������ ���� (���� �Լ� ���)
		thread[i] = std::thread([](std::atomic< bool >& result, char* lhs, char* rhs, std::size_t offset_jump_length)
		{
			for (std::size_t k = 0; k < offset_jump_length; k++) {
				// std::cout << *(lhs + k) << ", " << *(rhs + k) << "\n";
				if (*(lhs + k) != *(rhs + k)) result = false; // �� �����忡 �Ҵ�� �κп��� lhs�� rhs�� �ٸ�, false ���
				if (result == false) return; // �� �����带 �����Ͽ�, �� �ϳ��� �����忡���� false�� ��µǾ��� ��� ��� �����带 ����
			}
			return; // result�� true�� ���� ä �� ������ ����

		}, std::ref(result), lhs.digits + (digits_offset * sizeof(char)), rhs.digits + (digits_offset * sizeof(char)), offset_jump_length);

		digits_offset += offset_jump_length; // digits_offset ����
	}

	for (std::size_t i = 0; i < number_of_threads; i++) thread[i].join(); // ��� ����� ���� ������ ���

	// ���� ��� ���
	if (result == false)
	{
		delete[] thread; // �����ߴ� �����带 ����
		return false; // ���� Ȯ�� ��� lhs�� rhs�� �ٸ�, false ���
	}

	// �����ߴ� �����带 ����
	delete[] thread;

	///////////////////////////////////////////
	////////// ��Ƽ������ �׽�Ʈ ���� /////////
	///////////////////////////////////////////


	return true; // lhs�� rhs�� ������ ����, true ���
}

bool operator!=(const inf_int& lhs, const inf_int& rhs) {
	return !operator==(lhs, rhs);
}

bool operator>(const inf_int& lhs, const inf_int& rhs) {

	// 1. ��ȣ ��
	if (lhs.thesign != rhs.thesign) { // lhs�� rhs�� ��ȣ�� ���� �ٸ� ���
		return lhs.thesign; // lhs�� ����� ��� true, lhs�� ������ ��� false ��ȯ
	}

	// 2. ���� ��
	else { // lhs�� rhs�� ��ȣ�� ���� ���� ���
		if (lhs.length > rhs.length) return lhs.thesign; // lhs�� ���̰� �� �� ��� lhs�� ����̸� true, lhs�� �����̸� false ��ȯ
		else if (lhs.length < rhs.length) return rhs.thesign; // rhs�� ���̰� �� �� ��� rhs�� ����̸� true, rhs�� �����̸� false ��ȯ
		else { // lhs�� rhs�� ���� ���� ���� ���
			for (std::size_t i = lhs.length; i > 0; i--) { // �ڸ��� ��ȸ, ���ڰ� �Ųٷ� ����Ǳ� ������ -- ���
				if (*(lhs.digits + i - 1) > *(rhs.digits + i - 1)) return lhs.thesign; // ���� �ڸ����� lhs�� rhs���� �� Ŭ ���
				else if (*(lhs.digits + i - 1) < *(rhs.digits + i - 1)) return rhs.thesign; // ���� �ڸ����� lhs�� rhs���� �� ���� ���
				else continue;
			}
		}
	}

	return false; // lhs�� rhs�� ������ ����, false ���
}

bool operator<(const inf_int& lhs, const inf_int& rhs) {

	// 1. ��ȣ ��
	if (lhs.thesign != rhs.thesign) { // lhs�� rhs�� ��ȣ�� ���� �ٸ� ���
		return rhs.thesign; // rhs�� ����� ��� true, rhs�� ������ ��� false ��ȯ
	}

	// 2. ���� ��
	else { // lhs�� rhs�� ��ȣ�� ���� ���� ���
		if (lhs.length < rhs.length) return rhs.thesign; // rhs�� ���̰� �� �� ��� rhs�� ����̸� true, rhs�� �����̸� false ��ȯ
		else if (lhs.length > rhs.length) return lhs.thesign; // lhs�� ���̰� �� �� ��� rhs�� ����̸� true, rhs�� �����̸� false ��ȯ
		else { // lhs�� rhs�� ���� ���� ���� ���
			for (std::size_t i = lhs.length; i > 0; i--) { // �ڸ��� ��ȸ, ���ڰ� �Ųٷ� ����Ǳ� ������ -- ���
				if (*(lhs.digits + i - 1) < *(rhs.digits + i - 1)) return rhs.thesign; // ���� �ڸ����� lhs�� rhs���� �� ���� ���
				else if (*(lhs.digits + i - 1) > *(rhs.digits + i - 1)) return lhs.thesign; // ���� �ڸ����� lhs�� rhs���� �� Ŭ ���
				else continue;
			}
		}
	}

	return false; // lhs�� rhs�� ������ ����, false ���
}
