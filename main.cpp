/**
	@file   main.cpp
	@date   2019/10/04
	@author 김명승(mskim9967@gmail.com) 중앙대학교 소프트웨어학부 20186274
	@brief  122줄부터 교수님 main함수
*/

#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
<<<<<<< Updated upstream
#include <stdlib.h>
=======
>>>>>>> Stashed changes

int main()
{
	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////OUR TESTCASE//////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	
	std::cout << "---------------------Our TestCase---------------------" << endl;

	inf_int temp;
	inf_int p100(100);
	inf_int p200(200);
	inf_int m200(-200);
	inf_int m300(-300);

	inf_int m2x10sq10("-20000000000");
	inf_int p3x10sq10("30000000000");
	inf_int m3x10sq10("-30000000000");
	inf_int p8x10sq10("80000000000");
	inf_int m9999999999("-9999999999");
	inf_int m9999999998("-9999999998");

	inf_int p100_COPY(p100);

	inf_int p200_sec(200);
	inf_int m3x10sq10_sec("-30000000000");

	std::cout << "temp : " << temp << std::endl;
	std::cout << "p100 : " << p100 << std::endl;
	std::cout << "p200 : " << p200 << std::endl;
	std::cout << "m200 : " << m200 << std::endl;
	std::cout << "m300 : " << m300 << std::endl;
	std::cout << "m2x10sq10 : " << m2x10sq10 << std::endl;
	std::cout << "m3x10sq10 : " << m3x10sq10 << std::endl;
	std::cout << "p3x10sq10 : " << p3x10sq10 << std::endl;
	std::cout << "p8x10sq10 : " << p8x10sq10 << std::endl;
	std::cout << "m9999999999 : " << m9999999999 << std::endl;
	std::cout << "m9999999998 : " << m9999999998 << std::endl;
	std::cout << "p100_COPY : " << p100_COPY << std::endl;

	std::cout << std::endl;

	//////////////////////////
	/*			+			*/
	//////////////////////////
	assert((p100 + p200) == 300);	//양수 + 양수

	assert((p100 + m200) == -100);	//양수 + 음수

	assert((m200 + m300) == -500);	//음수 + 음수

	assert((p8x10sq10 + m3x10sq10) == 50000000000);	//큰양수 + 큰음수

	assert((m9999999998 + m9999999999) == -19999999997‬);	//큰음수 + 큰음수 올림수테스트

	//////////////////////////
	/*			-			*/
	//////////////////////////
	assert((p100 - p200) == -100);	//양수 - 양수

	assert((p100 - m200) == 300);	//양수 - 음수

	assert((m200 - m300) == 100);	//음수 - 음수

	assert((p8x10sq10 - m3x10sq10) == 110000000000);	//큰양수 - 큰음수

	assert((m9999999998 - m9999999999) == 1‬);	//큰음수 - 큰음수 올림수테스트

	//////////////////////////
	/*			*			*/
	//////////////////////////
	assert((p100 * p200) == 20000);	//양수 * 양수

	assert((p100 * m200) == -20000);	//양수 * 음수

	assert((m200 * m300) == 60000);	//음수 * 음수

	temp = p8x10sq10 * m3x10sq10;	//큰양수 * 큰음수
	std::cout << "80000000000 * -30000000000 : " << temp << std::endl;

	temp = m9999999998 * m9999999999;	//큰음수 * 큰음수 올림수테스트
	std::cout << "-9999999998 * -9999999999 : " << temp << std::endl;
	//////////////////////////
	/*			==			*/
	//////////////////////////
	assert((p100 == p200) == false);

	assert((m3x10sq10 == m3x10sq10_sec) == true);

	assert((p3x10sq10 == m3x10sq10) == false);

	//////////////////////////
	/*			!=			*/
	//////////////////////////
	assert((p100 != p200) == true);

	assert((m3x10sq10 != m3x10sq10_sec) == false);

	assert((p3x10sq10 != m3x10sq10) == true);

	//////////////////////////
	/*			>			*/
	//////////////////////////
	assert((p100 > p200) == false);

	assert((m3x10sq10 > m3x10sq10_sec) == false);

	assert((p3x10sq10 > m3x10sq10) == true);

	//////////////////////////
	/*			<			*/
	//////////////////////////
	assert((p100 < p200) == true);

	assert((m3x10sq10 < m3x10sq10_sec) == false);

	assert((p3x10sq10 < m3x10sq10) == false);


	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////GIVEN TESTCASE////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	std::cout << "---------------------Given TestCase---------------------" << endl;

	inf_int a, e;
	inf_int b(100);
	inf_int c("321111111111122222222222233333333333444444444445555555555");
	inf_int d("123451987651234572749499923455022211");
	inf_int f = d;
	inf_int g(f);

	// cin >> g ;   // not required

	a = b * c;
	// e=g/f;       // not required

	b = c - d;


	if (f == d) {
		cout << "a : " << a << endl;
		cout << "b : " << b << endl;
		cout << "c : " << c << endl;
		cout << "d : " << d << endl;
		// cout << "e : " << e << endl;
		cout << "f : " << f << endl;
		// cout << "g : " << g << endl;
	}

	return 0;
}
