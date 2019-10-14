#include "inf_int.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <chrono>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::cout << inf_int{-9098} << " + " << inf_int{99} << " = " << inf_int{-9098} + inf_int{99} << std::endl;
	std::cout << inf_int{-9999} << " + " << inf_int{9000} << " = " << inf_int{-9999} + inf_int{9000} << std::endl;
	std::cout << inf_int{-9998} << " + " << inf_int{9} << " = " << inf_int{-9998} + inf_int{9} << std::endl;
	std::cout << inf_int{-9999} << " + " << inf_int{9000} << " = " << inf_int{-9999} + inf_int{9000} << std::endl;
	std::cout << inf_int{-9998} << " + " << inf_int{89} << " = " << inf_int{-9998} + inf_int{89} << std::endl;
	std::cout << inf_int{-9998} << " + " << inf_int{8999} << " = " << inf_int{-9998} + inf_int{8999} << std::endl;
	std::cout << inf_int{-9} << " - " << inf_int{-9} << " = " << inf_int{-9} - inf_int{-9} << std::endl;
	std::cout << inf_int{-9} << " - " << inf_int{-8} << " = " << inf_int{-9} - inf_int{-8} << std::endl;



	assert(inf_int{-9098} + inf_int{99} == inf_int{-9098 + 99});
	assert(inf_int{-9999} + inf_int{9000} == inf_int{-9999 + 9000});
	assert(inf_int{-9998} + inf_int{9} == inf_int{-9998 + 9});
	assert(inf_int{-9999} + inf_int{9000} == inf_int{-9999 + 9000});
	assert(inf_int{-9998} + inf_int{89} == inf_int{-9998 + 89});
	assert(inf_int{-9998} + inf_int{8999} == inf_int{-9998 + 8999});
	assert(inf_int{-9} - inf_int{-9} == inf_int{-9 - -9});
	assert(inf_int{-9} - inf_int{-8} == inf_int{-9 - -8});



	assert((inf_int("80000000000") + inf_int("-30000000000")) == inf_int("50000000000")); //큰양수 + 큰음수
	assert((inf_int("-9999999998") + inf_int("-9999999999")) == inf_int("-19999999997")); //큰음수 + 큰음수 올림수테스트
	assert((inf_int("80000000000") - inf_int("-30000000000")) == inf_int("110000000000")); //큰양수 - 큰음수
	assert((inf_int("-9999999998") - inf_int("-9999999999")) == inf_int(1)); // 큰음수 - 큰음수 올림수테스트

	assert((inf_int("80000000000")*inf_int("-30000000000")) == inf_int("-2400000000000000000000"));	//큰양수 * 큰음수

	assert((inf_int("-9999999998")*inf_int("9999999999")) == inf_int("-99999999970000000002")); //큰음수 * 큰음수 올림수테스트
	
	assert((inf_int(100) == inf_int(200)) == false);

	assert((inf_int("-30000000000") == inf_int("-30000000000")) == true);

	assert((inf_int("30000000000") == inf_int("-30000000000")) == false);

	assert((inf_int(100) != inf_int(200)) == true);

	assert((inf_int("-30000000000") != inf_int("-30000000000")) == false);

	assert((inf_int("30000000000") != inf_int("-30000000000")) == true);

	assert((inf_int(100) > inf_int(200)) == false); // 양수 > 양수

	assert((inf_int(100) > inf_int(-200)) == true); // 양수 > 음수

	assert((inf_int(-100) > inf_int(200)) == false); // 음수 > 양수

	assert((inf_int(-100) > inf_int(-200)) == true); // 음수 > 음수

	assert((inf_int(10000) > inf_int(200)) == true); // 양수 > 양수 (다른 자릿수)

	assert((inf_int(100) > inf_int(20000)) == false); // 양수 > 양수 (다른 자릿수)

	assert((inf_int("-30000000000") > inf_int("-30000000000")) == false);

	assert((inf_int("30000000000") > inf_int("-30000000000")) == true);

	assert((inf_int(100) < inf_int(200)) == true); // 양수 < 양수

	assert((inf_int(100) < inf_int(-200)) == false); // 양수 < 음수

	assert((inf_int(-100) < inf_int(200)) == true); // 음수 < 양수

	assert((inf_int(-100) < inf_int(-200)) == false); // 음수 < 음수

	assert((inf_int(10000) < inf_int(200)) == false); // 양수 < 양수 (다른 자릿수)

	assert((inf_int(100) < inf_int(20000)) == true); // 양수 < 양수 (다른 자릿수)

	assert((inf_int("-30000000000") < inf_int("-30000000000")) == false);

	assert((inf_int("30000000000") < inf_int("-30000000000")) == false);
	for(int i = -99; i < 100; ++i) {
		for(int j = -99; j < 100; ++j) {
			std::cout << inf_int{i} << " + " << inf_int{j} << " = " << inf_int{i} + inf_int{j} << std::endl;
			assert(inf_int{i} + inf_int{j} == inf_int{i + j});
			std::cout << inf_int{i} << " - " << inf_int{j} << " = " << inf_int{i} - inf_int{j} << std::endl;
			assert(inf_int{i} - inf_int{j} == inf_int{i - j});
			std::cout << inf_int{i} << " * " << inf_int{j} << " = " << inf_int{i} * inf_int{j} << std::endl;
			assert(inf_int{i} * inf_int{j} == inf_int{i * j});
		}
	}
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
	const char* str = "14128134790127491238471029348710293487019247810923487019234870193284709134708123470934709128309812340978124810923478091234870192348709123470934092382758146534859924713840123417823046257896458471395728347812907135868173871234081273482765891345782694723049328901286586127895678430128471298478456914802478123401865781236124789128562147891912478216349120878750192850127192478234012934895891598124982748910925719208920357983271891275234";
	for(int i = 0; i < 10000; ++i) {
		(inf_int{str} == inf_int{str});
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << "total time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns" << std::endl;
	return 0;
}
