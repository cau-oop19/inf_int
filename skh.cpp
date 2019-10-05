#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cstdlib>
#include <thread>
#include <future>
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
		�����带 ����� ����, ���� �� �ھ� ����ŭ promise, future, thread�� �����մϴ�.
		�� �� lhs�� rhs�� digits�� �� �ھ� ����ŭ �����ϰ�, ������ string�� char*�� ���·� �� �����忡 �Ҵ��մϴ�.
		�� �����忡���� �Ҵ�� �з��� �� string�� ������ Ȯ���� �� promise�� bool ���� �����մϴ�.
		��� �����尡 ����� ��, future�κ��� bool ���� Ȯ���Ͽ� �����ߴ� string���� ��� ������ ���� Ȯ���մϴ�.
	*/


	// ���α׷��� �����ϴ� ��ǻ���� �� �ھ� �� ����
	const std::size_t coreNum = std::thread::hardware_concurrency();

	// �������� promise, future, thread�� �� �ھ� ����ŭ ����
	std::promise<bool> *threadPromise = new std::promise<bool>[coreNum];
	std::future<bool> *threadFuture = new std::future<bool>[coreNum];
	std::thread *thread = new std::thread[coreNum];

	// ������ ���� �� ����
	std::size_t digits_offset = 0; // �����忡 �Ҵ�� string�� ���� ����
	for (std::size_t i = 0; i < coreNum; i++) {

		std::size_t offset_jump_length = ((lhs.length % coreNum) > i) ? ((lhs.length / coreNum) + 1) : (lhs.length / coreNum); // �����忡 �Ҵ�� string�� ����
		
		threadFuture[i] = threadPromise[i].get_future(); // future�� promise�� ��ȯ ���� �� ����

		// ������ ���� (���� �Լ� ���)
		thread[i] = std::thread([](std::promise<bool>* result, char* lhs, char* rhs, std::size_t jumpLength)
		{
			for (std::size_t k = 0; k < jumpLength; k++) {
				//std::cout << *(lhs + k) << ", " << *(rhs + k) << "\n";
				if (*(lhs + k) != *(rhs + k)) {
					result->set_value(false); // �� �����忡 �Ҵ�� �κп��� lhs�� rhs�� �ٸ�, false ���
					return;
				}
			}
			result->set_value(true); // �� �����忡 �Ҵ�� �κп��� lhs�� rhs�� ����, true ���
			return;
		}, &threadPromise[i], lhs.digits + (digits_offset * sizeof(char)), rhs.digits + (digits_offset * sizeof(char)), offset_jump_length);

		digits_offset += offset_jump_length; // digits_offset ����
	}

	// ��� ����� ���� ������ ���
	for (std::size_t i = 0; i < coreNum; i++) thread[i].join();

	// ���� ��� ���
	for (std::size_t i = 0; i < coreNum; i++) {
		if (threadFuture[i].get() == false)
		{
			// �����ߴ� promise, future, thread�� ����
			delete threadPromise;
			delete threadFuture;
			delete thread;
			return false; // ���� Ȯ�� ��� lhs�� rhs�� �ٸ�, false ���
		}
	}

	// �����ߴ� promise, future, thread�� ����
	delete threadPromise;
	delete threadFuture;
	delete thread;

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
