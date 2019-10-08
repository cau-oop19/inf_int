/**
	@file   main.cpp
	@date   2019/10/06
	@author 김명승(mskim9967@gmail.com) 중앙대학교 소프트웨어학부 20186274
	@brief  122줄부터 교수님 main함수
*/

#include "inf_int.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <chrono>

int main()
{

	auto start = std::chrono::high_resolution_clock::now();

	/////////////////////////////
	/*            +            */
	/////////////////////////////
	assert((inf_int(100) + inf_int(200)) == inf_int(300));	//양수 + 양수

	assert((inf_int(100) + inf_int(-200)) == inf_int(-100)); //양수 + 음수

	assert((inf_int(-200) + inf_int(-300)) == inf_int(-500)); //음수 + 음수

	assert((inf_int("80000000000") + inf_int("-30000000000")) == inf_int("50000000000")); //큰양수 + 큰음수

	assert((inf_int("-9999999998") + inf_int("-9999999999")) == inf_int("-19999999997")); //큰음수 + 큰음수 올림수테스트

	/////////////////////////////
	/*            -            */
	/////////////////////////////
	assert((inf_int(100) - inf_int(200)) == inf_int(-100));	//양수 - 양수

	assert((inf_int(100) - inf_int(-200)) == inf_int(300));	//양수 - 음수

	assert((inf_int(-200) - inf_int(-300)) == inf_int(100)); //음수 - 음수

	assert((inf_int("80000000000") - inf_int("-30000000000")) == inf_int("110000000000")); //큰양수 - 큰음수

	assert((inf_int("-9999999998") - inf_int("-9999999999")) == inf_int(1)); // 큰음수 - 큰음수 올림수테스트

	/////////////////////////////
	/*            *            */
	/////////////////////////////
	assert((inf_int(100)* inf_int(200)) == inf_int(20000));	//양수 * 양수

	assert((inf_int(100) * inf_int(-200)) == inf_int(-20000)); //양수 * 음수

	assert(inf_int(-200) * inf_int(-300) == inf_int(60000)); //음수 * 음수

	assert((inf_int("80000000000")*inf_int("-30000000000")) == inf_int("-2400000000000000000000"));	//큰양수 * 큰음수

	assert((inf_int("-9999999998")*inf_int("9999999999")) == inf_int("-99999999970000000002")); //큰음수 * 큰음수 올림수테스트
	
	//////////////////////////////
	/*            ==            */
	//////////////////////////////
	assert((inf_int(100) == inf_int(200)) == false);

	assert((inf_int("-30000000000") == inf_int("-30000000000")) == true);

	assert((inf_int("30000000000") == inf_int("-30000000000")) == false);

	//////////////////////////////
	/*            !=            */
	//////////////////////////////
	assert((inf_int(100) != inf_int(200)) == true);

	assert((inf_int("-30000000000") != inf_int("-30000000000")) == false);

	assert((inf_int("30000000000") != inf_int("-30000000000")) == true);

	/////////////////////////////
	/*            >            */
	/////////////////////////////
	assert((inf_int(100) > inf_int(200)) == false); // 양수 > 양수

	assert((inf_int(100) > inf_int(-200)) == true); // 양수 > 음수

	assert((inf_int(-100) > inf_int(200)) == false); // 음수 > 양수

	assert((inf_int(-100) > inf_int(-200)) == true); // 음수 > 음수

	assert((inf_int(10000) > inf_int(200)) == true); // 양수 > 양수 (다른 자릿수)

	assert((inf_int(100) > inf_int(20000)) == false); // 양수 > 양수 (다른 자릿수)

	assert((inf_int("-30000000000") > inf_int("-30000000000")) == false);

	assert((inf_int("30000000000") > inf_int("-30000000000")) == true);

	/////////////////////////////
	/*            <            */
	/////////////////////////////
	assert((inf_int(100) < inf_int(200)) == true); // 양수 < 양수

	assert((inf_int(100) < inf_int(-200)) == false); // 양수 < 음수

	assert((inf_int(-100) < inf_int(200)) == true); // 음수 < 양수

	assert((inf_int(-100) < inf_int(-200)) == false); // 음수 < 음수

	assert((inf_int(10000) < inf_int(200)) == false); // 양수 < 양수 (다른 자릿수)

	assert((inf_int(100) < inf_int(20000)) == true); // 양수 < 양수 (다른 자릿수)

	assert((inf_int("-30000000000") < inf_int("-30000000000")) == false);

	assert((inf_int("30000000000") < inf_int("-30000000000")) == false);


	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////GIVEN TESTCASE////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	std::cout << "---------------------Given TestCase---------------------" << std::endl;

	inf_int a, e;
	inf_int b(100);
	inf_int c("321111111111122222222222233333333333444444444445555555555");
	inf_int d("123451987651234572749499923455022211");
	inf_int f = d;
	inf_int g(f);

	// cin >> g; // not required

	a = b * c;
	// e=g/f; // not required

	b = c - d;

	if (f == d) {
		std::cout << "a : " << a << std::endl;
		std::cout << "b : " << b << std::endl;
		std::cout << "c : " << c << std::endl;
		std::cout << "d : " << d << std::endl;
		// cout << "e : " << e << endl;
		std::cout << "f : " << f << std::endl;
		// cout << "g : " << g << endl;
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns" << std::endl;
	return 0;
}
