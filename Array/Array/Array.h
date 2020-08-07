#include <map>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <set>
#include <list>
#include <algorithm>
#include <functional>
#include <numeric>
#include <list>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

using namespace std;

#ifndef INT_MAX
#define INT_MAX (1 << 31 - 1)
#endif

#ifndef INT_MIN
#define INT_MIN (1 << 31)
#endif

typedef long long __int64;

#define leap_year(year)(year % 100 == 0 ? year % 400 == 0 : year % 4 == 0)
#define to_digit(c)(c - 'a')
#define TO_DIGIT(c)(c - '0') 

#define VOWEL(c) (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'||\
	c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')

//#define LETTER(c) (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')

#define upper(c) (c >= 'A' && c <= 'Z')
#define lower(c) (c >= 'a' && c <= 'z')
#define digit(c) (c >= '0' && c <= '9')
#define letter(c) (upper(c) || lower(c))

//#define IS_DIGIT(c)(c >= '0' && c <= '9')
//#define IS_LETTER(c) (c >= 'a' && c <= 'z' || c >= 'A' || c <= 'Z')
//#define is_digit(c)(c >= '0' && c <= '9')

#ifndef set_bit
#define set_bit(n, pos, b)(b == 1 ? n |= (pos < 32 ? 1 << pos : 0) : n &= ~(pos < 32 ? 1 << pos : 0))
#endif

#ifndef get_bit
#define get_bit(n,pos)((n & (1<<pos)) != 0)
#endif


#ifndef MALLOC
#define MALLOC(type, size)((type*)malloc(sizeof(type) * size))
#endif

vector<string> split(string s, char c, int* length = NULL)
{
	vector<string> res;
	int left = 0, right = 0;
	while (s[left] == c)right = ++left;
	while (right < s.size())
	{
		if (s[right] == c && right > left)
		{
			res.push_back(s.substr(left, right - left));
			if (length != NULL)
				*length = max(*length, right - left);
			left = right + 1;
		}
		++right;
	}
	if (right > left)
		res.push_back(s.substr(left, right - left));
	return res;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& os, pair<T1, T2> p)
{
	os << p.first << "," << p.second;
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v)
{
	for (int i = 0; i < v.size(); i++)
		os << v[i] << ", ";
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>> v)
{
	for (int i = 0; i < v.size(); i++)
		os << v[i] << endl;
	return os;
}


template <typename T>
size_t find(vector<T> v, const T& target)
{
	size_t idx = 0;
	while (idx != v.size() && v[idx] != target) idx++;
	return idx;
}

template<typename T>
ostream& operator<<(ostream& os, pair<T, T> p)
{
	os << p.first << "," << p.second;
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, set<T> s)
{
	for (auto i : s)
		os << i << ", ";
	return os;
}

vector<int> to_bin(int num)
{
	vector<int> res;
	int cnt = sizeof(num)* 8;
	while (cnt--)
	{
		res.push_back(num & 1);
		num >>= 1;
	}
	reverse(res.begin(), res.end());
	return res;
}

