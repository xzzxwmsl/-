// ConsoleApplication6.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
int main()
{
	const char *p = "xxx";//等价 char const *p， 只读指针
	p = "www";
	cout << p<<endl;
	p = p + 1;
	cout << p << endl;
	cout << *p<<endl;
	//p[1] = 'w'; //error

	char const *pp = "ppp";
	pp = "xxxx";
	cout << pp << endl;
	//pp[1] = 'c'; //error


	char s[10] = "xxxx";
	char * const k =  s;//单指向指针
	cout << k << endl;
	char ss[10] = "aaaaa";
	//k = ss; //会报单指向指针错
	k[1] = 'c';
	cout << s << endl;

	cout << "----------------------" << endl;

	const char *test[] = { "China","French","America","German" };
	const char *test2[] = { "AAA","BBB","CCC","DDD" };
	const char * const * ptr=test;//ptr只读，*ptr只读

	cout << *ptr << endl;
	cout<< *(ptr+1)<<endl;
	ptr = ptr + 1;
	cout << *ptr<<endl; //改变指针指向,无错
	//*ptr = "xxx"; //error

	ptr = test2;//ptr只读，可改变指向
	cout << *ptr << endl;

	cout << *(*ptr+1) << endl;//只读
	//**ptr = 'w';//*ptr只读，不可改变

	
	return 0;


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
