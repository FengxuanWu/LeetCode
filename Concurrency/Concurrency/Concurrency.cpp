// Concurrency.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;
#define THREAD_NUM 10

CRITICAL_SECTION critical_section;
#define TIME 100
int lock = 1;

void foo(void* param)
{
	for (int i = 0; i < TIME; i++)
	{
		//cout << lock << endl;
		while (!lock);
		cout << "foo";
		lock = 0;
	}

}

void bar(void* bar)
{	
	for (int i = 0; i < TIME; i++)
	{
		//cout << lock << endl;
		while (lock);
		cout << "bar" << endl;
		lock = 1;
	}
}

void test()
{
	HANDLE thread[2];
	DWORD thrad_id = 0;
	thread[0] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)(foo), NULL, NULL, NULL);
	thread[1] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)(bar), NULL, NULL, NULL);
	WaitForMultipleObjects(2, thread, true, INFINITE);
	//cout << "end" << endl;
}


int main()
{
	test();	
	cout << endl;
	return 0;
}

