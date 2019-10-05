#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cstdlib>
#include <thread>
#include <future>
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
	/*
	for (std::size_t i = lhs.length; i > 0; i--) { // 자릿수 순회, 숫자가 거꾸로 저장되기 때문에 -- 사용
		if (*(lhs.digits + i - 1) != *(rhs.digits + i - 1)) return false; // 현재 자릿수가 lhs와 rhs가 다른 경우 false 출력
		else continue;
	}
	*/



	///////////////////////////////////////////
	////////// 멀티스레딩 테스트 시작 /////////
	///////////////////////////////////////////


	/*
		스레드를 만들기 전에, 먼저 논리 코어 수만큼 promise, future, thread를 선언합니다.
		그 후 lhs와 rhs의 digits를 논리 코어 수만큼 분할하고, 분할한 string을 char*의 형태로 각 스레드에 할당합니다.
		각 스레드에서는 할당된 분량의 두 string이 같은지 확인한 후 promise에 bool 값을 리턴합니다.
		모든 스레드가 종료된 후, future로부터 bool 값을 확인하여 분할했던 string들이 모두 같은지 최종 확인합니다.
	*/


	// 프로그램을 실행하는 컴퓨터의 논리 코어 수 저장
	const std::size_t coreNum = std::thread::hardware_concurrency();

	// 스레드의 promise, future, thread를 논리 코어 수만큼 선언
	std::promise<bool> *threadPromise = new std::promise<bool>[coreNum];
	std::future<bool> *threadFuture = new std::future<bool>[coreNum];
	std::thread *thread = new std::thread[coreNum];

	// 스레드 생성 및 실행
	std::size_t digits_offset = 0; // 스레드에 할당될 string의 시작 지점
	for (std::size_t i = 0; i < coreNum; i++) {

		std::size_t offset_jump_length = ((lhs.length % coreNum) > i) ? ((lhs.length / coreNum) + 1) : (lhs.length / coreNum); // 스레드에 할당될 string의 길이
		
		threadFuture[i] = threadPromise[i].get_future(); // future에 promise의 반환 예정 값 지정

		// 스레드 생성 (람다 함수 사용)
		thread[i] = std::thread([](std::promise<bool>* result, char* lhs, char* rhs, std::size_t jumpLength)
		{
			for (std::size_t k = 0; k < jumpLength; k++) {
				//std::cout << *(lhs + k) << ", " << *(rhs + k) << "\n";
				if (*(lhs + k) != *(rhs + k)) {
					result->set_value(false); // 이 스레드에 할당된 부분에서 lhs와 rhs가 다름, false 출력
					return;
				}
			}
			result->set_value(true); // 이 스레드에 할당된 부분에서 lhs와 rhs가 같음, true 출력
			return;
		}, &threadPromise[i], lhs.digits + (digits_offset * sizeof(char)), rhs.digits + (digits_offset * sizeof(char)), offset_jump_length);

		digits_offset += offset_jump_length; // digits_offset 갱신
	}

	// 모든 결과가 나올 때까지 대기
	for (std::size_t i = 0; i < coreNum; i++) thread[i].join();

	// 최종 결과 출력
	for (std::size_t i = 0; i < coreNum; i++) {
		if (threadFuture[i].get() == false)
		{
			// 선언했던 promise, future, thread를 제거
			delete threadPromise;
			delete threadFuture;
			delete thread;
			return false; // 최종 확인 결과 lhs와 rhs가 다름, false 출력
		}
	}

	// 선언했던 promise, future, thread를 제거
	delete threadPromise;
	delete threadFuture;
	delete thread;

	///////////////////////////////////////////
	////////// 멀티스레딩 테스트 종료 /////////
	///////////////////////////////////////////


	return true; // lhs와 rhs가 완전히 같음, true 출력
}

bool operator!=(const inf_int& lhs, const inf_int& rhs) {
	return !operator==(lhs, rhs);
}

bool operator>(const inf_int& lhs, const inf_int& rhs) {

	// 1. 부호 비교
	if (lhs.thesign != rhs.thesign) { // lhs와 rhs의 부호가 서로 다를 경우
		return lhs.thesign; // lhs가 양수일 경우 true, lhs가 음수일 경우 false 반환
	}

	// 2. 길이 비교
	else { // lhs와 rhs의 부호가 서로 같을 경우
		if (lhs.length > rhs.length) return lhs.thesign; // lhs의 길이가 더 길 경우 lhs가 양수이면 true, lhs가 음수이면 false 반환
		else if (lhs.length < rhs.length) return rhs.thesign; // rhs의 길이가 더 길 경우 rhs가 양수이면 true, rhs가 음수이면 false 반환
		else { // lhs와 rhs의 길이 또한 같을 경우
			for (std::size_t i = lhs.length; i > 0; i--) { // 자릿수 순회, 숫자가 거꾸로 저장되기 때문에 -- 사용
				if (*(lhs.digits + i - 1) > *(rhs.digits + i - 1)) return lhs.thesign; // 현재 자릿수가 lhs가 rhs보다 더 클 경우
				else if (*(lhs.digits + i - 1) < *(rhs.digits + i - 1)) return rhs.thesign; // 현재 자릿수가 lhs가 rhs보다 더 작을 경우
				else continue;
			}
		}
	}

	return false; // lhs와 rhs가 완전히 같음, false 출력
}

bool operator<(const inf_int& lhs, const inf_int& rhs) {

	// 1. 부호 비교
	if (lhs.thesign != rhs.thesign) { // lhs와 rhs의 부호가 서로 다를 경우
		return rhs.thesign; // rhs가 양수일 경우 true, rhs가 음수일 경우 false 반환
	}

	// 2. 길이 비교
	else { // lhs와 rhs의 부호가 서로 같을 경우
		if (lhs.length < rhs.length) return rhs.thesign; // rhs의 길이가 더 길 경우 rhs가 양수이면 true, rhs가 음수이면 false 반환
		else if (lhs.length > rhs.length) return lhs.thesign; // lhs의 길이가 더 길 경우 rhs가 양수이면 true, rhs가 음수이면 false 반환
		else { // lhs와 rhs의 길이 또한 같을 경우
			for (std::size_t i = lhs.length; i > 0; i--) { // 자릿수 순회, 숫자가 거꾸로 저장되기 때문에 -- 사용
				if (*(lhs.digits + i - 1) < *(rhs.digits + i - 1)) return rhs.thesign; // 현재 자릿수가 lhs가 rhs보다 더 작을 경우
				else if (*(lhs.digits + i - 1) > *(rhs.digits + i - 1)) return lhs.thesign; // 현재 자릿수가 lhs가 rhs보다 더 클 경우
				else continue;
			}
		}
	}

	return false; // lhs와 rhs가 완전히 같음, false 출력
}
