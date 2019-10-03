#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>


int main()
{
	inf_int temp;
	inf_int p100(100);
	inf_int p200(200);
	inf_int m200(-200);
	inf_int m300(-300);

	inf_int m2x10sq10("-20000000000");
	inf_int p3x10sq10("30000000000");
	inf_int m3x10sq10("-30000000000");
	inf_int p8x10sq10("80000000000");

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
	std::cout << "p100_COPY : " << p100_COPY << std::endl;

	std::cout << std::endl;

	//////////////////////////
	/*			+			*/
	//////////////////////////
	temp = p100 + p200;	//양수 + 양수
	std::cout << "100 + 200 : " << temp << std::endl;

	temp = p100 + m200;	//양수 + 음수
	std::cout << "100 + -200 : " << temp << std::endl;

	temp = m200 + m300;	//음수 + 음수
	std::cout << "-200 + -300 : " << temp << std::endl;

	temp = p8x10sq10 + m3x10sq10;	//큰양수 + 큰음수
	std::cout << "80000000000 + -30000000000 : " << temp << std::endl;
	
	std::cout << std::endl;


	//////////////////////////
	/*			-			*/
	//////////////////////////
	temp = p100 - p200;	//양수 - 양수
	std::cout << "100 - 200 : " << temp << std::endl;

	temp = p100 - m200;	//양수 - 음수
	std::cout << "100 - -200 : " << temp << std::endl;

	temp = m200 - m300;	//음수 - 음수
	std::cout << "-200 - -300 : " << temp << std::endl;

	temp = p8x10sq10 - m3x10sq10;	//큰양수 - 큰음수
	std::cout << "80000000000 - -30000000000 : " << temp << std::endl;
	
	std::cout << std::endl;


	//////////////////////////
	/*			*			*/
	//////////////////////////
	temp = p100 * p200;	//양수 * 양수
	std::cout << "100 * 200 : " << temp << std::endl;

	temp = p100 * m200;	//양수 * 음수
	std::cout << "100 * -200 : " << temp << std::endl;

	temp = m200 * m300;	//음수 * 음수
	std::cout << "-200 * -300 : " << temp << std::endl;

	temp = p8x10sq10 * m3x10sq10;	//큰양수 * 큰음수
	std::cout << "80000000000 * -30000000000 : " << temp << std::endl;
	
	std::cout << std::endl;


	//////////////////////////
	/*			==			*/
	//////////////////////////
	std::cout << p100 << " == " << p200;
	if (p100 == p200)
		std::cout <<" is true" << std::endl;
	else
		std::cout << " is false" << std::endl;

	std::cout << m3x10sq10 << " == " << m3x10sq10_sec;
	if (m3x10sq10 == m3x10sq10_sec)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;
	
	std::cout << p3x10sq10 << " == " << m3x10sq10;
	if (p3x10sq10 == m3x10sq10)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;
	
	std::cout << std::endl;


	//////////////////////////
	/*			!=			*/
	//////////////////////////
	std::cout << p100 << " != " << p200;
	if (p100 != p200)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;

	std::cout << m3x10sq10 << " != " << m3x10sq10_sec;
	if (m3x10sq10 != m3x10sq10_sec)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;

	std::cout << p3x10sq10 << " != " << m3x10sq10;
	if (p3x10sq10 != m3x10sq10)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;
	
	std::cout << std::endl;


	//////////////////////////
	/*			>			*/
	//////////////////////////
	std::cout << p100 << " > " << p200;
	if (p100 > p200)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;

	std::cout << m3x10sq10 << " > " << m3x10sq10_sec;
	if (m3x10sq10 > m3x10sq10_sec)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;

	std::cout << p3x10sq10 << " > " << m3x10sq10;
	if (p3x10sq10 > m3x10sq10)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;
	
	std::cout << std::endl;


	//////////////////////////
	/*			<			*/
	//////////////////////////
	std::cout << p100 << " < " << p200;
	if (p100 < p200)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;

	std::cout << m3x10sq10 << " < " << m3x10sq10_sec;
	if (m3x10sq10 < m3x10sq10_sec)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;

	std::cout << p3x10sq10 << " < " << m3x10sq10;
	if (p3x10sq10 < m3x10sq10)
		std::cout << " is true" << std::endl;
	else
		std::cout << " is false" << std::endl;
	
	std::cout << std::endl;



	return 0;
}
