// Concurrency.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <vector>
#include <iostream>
using namespace std;
#define THREAD_NUM 100


CRITICAL_SECTION critical_section;
HANDLE mutex = 0;

HANDLE s_foo = 0;
HANDLE s_bar = 0;

#define TIME 100
void foo(void* param)
{
	for (int i = 0; i < TIME; i++)
	{		
		WaitForSingleObject(s_foo, INFINITE);
		cout << "foo";
		ReleaseSemaphore(s_bar, 1, NULL);
	}
}

void bar(void* bar)
{	
	for (int i = 0; i < TIME; i++)
	{	
		WaitForSingleObject(s_bar, INFINITE);
		cout << "bar" << endl;
		ReleaseSemaphore(s_foo, 1, NULL);
	}
}

void test()
{
	HANDLE thread[2];
	DWORD thrad_id = 0;	
	s_foo = CreateSemaphore(NULL, 1, 1, L"full");
	s_bar = CreateSemaphore(NULL, 0, 1, L"empty");
	
	thread[0] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)(foo), NULL, NULL, NULL);
	thread[1] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)(bar), NULL, NULL, NULL);

	WaitForMultipleObjects(2, thread, true, INFINITE);

	CloseHandle(thread[0]);
	CloseHandle(thread[1]);
	CloseHandle(s_foo);
	CloseHandle(s_bar);
	cout << "end" << endl;
}

vector<vector<int>> dp = vector<vector<int>>(200, vector<int>(200));
int c(int n, int m)
{
	cout << n << ' ' << m << endl;
	if (n == m || m == 0)
		return dp[n][m] = 1;

	if (dp[n][m] || dp[n][n - m])
		return dp[n][m] ? dp[n][m] : dp[n][n - m];

	return c(n - 1, m - 1) + c(n, m);
}

int main()
{
	cout << c(5, 2) << endl;
	return 0;
}