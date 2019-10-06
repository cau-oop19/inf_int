#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cstdlib>
#include <thread>
#include <atomic>
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
		먼저 필요한 스레드의 갯수를 정하고, 모든 스레드에서 접근할 수 있는 atomic 변수 result를 선언합니다.
		그 후 lhs와 rhs의 digits를 스레드 수만큼 분할하고, 분할한 string을 char*의 형태로 각 스레드에 할당합니다.
		각 스레드에서는 할당된 분량의 두 string이 같은지 확인하며, 다른 부분이 발견될 경우 result에 false를 반환합니다.
		단 하나의 스레드에서라도 다른 부분을 발견했을 경우, result는 false가 되고 모든 스레드는 종료됩니다.
		모든 스레드가 종료된 후, result의 bool값을 통해, 이전에 분할했던 string들이 모두 같은지 최종 확인합니다.
	*/


	// 필요한 스레드의 갯수 선언
	// 비교할 숫자의 길이가 CPU의 코어 수보다 많을 경우 코어 수를, 그렇지 않을 경우 비교할 숫자의 길이를 지정
	const std::size_t number_of_threads = (lhs.length >= std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : lhs.length);

	//// 스레드를 논리 코어 수만큼 선언
	std::atomic<bool> result { true }; // 결과값 저장, 기본값으로 true 지정
	std::thread *thread = new std::thread[number_of_threads]; // 스레드 선언

	// 스레드 생성 및 실행
	std::size_t digits_offset = 0; // 스레드에 할당될 string의 시작 지점을 상대적으로 지정함
	for (std::size_t i = 0; i < number_of_threads; i++) {

		std::size_t offset_jump_length = ((lhs.length % number_of_threads) > i) ? ((lhs.length / number_of_threads) + 1) : (lhs.length / number_of_threads); // 스레드에 할당될 string의 길이

		// 스레드 생성 (람다 함수 사용)
		thread[i] = std::thread([](std::atomic< bool >& result, char* lhs, char* rhs, std::size_t offset_jump_length)
		{
			for (std::size_t k = 0; k < offset_jump_length; k++) {
				// std::cout << *(lhs + k) << ", " << *(rhs + k) << "\n";
				if (*(lhs + k) != *(rhs + k)) result = false; // 이 스레드에 할당된 부분에서 lhs와 rhs가 다름, false 출력
				if (result == false) return; // 이 스레드를 포함하여, 단 하나의 스레드에서라도 false가 출력되었을 경우 모든 스레드를 종료
			}
			return; // result를 true로 놔둔 채 이 스레드 종료

		}, std::ref(result), lhs.digits + (digits_offset * sizeof(char)), rhs.digits + (digits_offset * sizeof(char)), offset_jump_length);

		digits_offset += offset_jump_length; // digits_offset 갱신
	}

	for (std::size_t i = 0; i < number_of_threads; i++) thread[i].join(); // 모든 결과가 나올 때까지 대기

	// 최종 결과 출력
	if (result == false)
	{
		delete[] thread; // 선언했던 스레드를 제거
		return false; // 최종 확인 결과 lhs와 rhs가 다름, false 출력
	}

	// 선언했던 스레드를 제거
	delete[] thread;

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
