

#include <cstring>
#include <vector>
#include "matrix"

typedef int MY_TYPE;

int main()
{
	

	MY_TYPE aaa[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	matrix<MY_TYPE,3,2> a(aaa);
	matrix<MY_TYPE,3,2> b(&aaa[6]);
	std::cout << "a:\n" << a <<"\nb:\n" << b << std::endl;

	std::cout << "aT:\n" << ~a << std::endl;

	matrix<MY_TYPE,3,2> c = a + b;
	std::cout << "c=a+b:\n" << c << std::endl;


	matrix<MY_TYPE,3,2> d = a - b;
	std::cout << "d=a-b:\n" << d << std::endl;

	// 编译错误
	//matrix<MY_TYPE,3,3> e = a-b;

	matrix<MY_TYPE,2,4> e(aaa);
	std::cout << "e:\n" << e << std::endl;
	matrix<MY_TYPE,3,4> f = a*e;
	std::cout << "f=a*e:\n" << f << std::endl;

}