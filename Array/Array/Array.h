#include "stdafx.h"
#include <map>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <list>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define leap_year(year)(year % 100 == 0 ? year % 400 == 0 : year % 4 == 0)
#define to_digit(c)(c - 'a')
#define TO_DIGIT(c)(c - '0') 

#define VOWEL(c) (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'||\
	c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
#define LETTER(c) (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')

#define IS_DIGIT(c)(c >= '0' && c <= '9')
#define IS_LETTER(c) (c >= 'a' && c <= 'z' || c >= 'A' || c <= 'Z')

#ifndef MALLOC
#define MALLOC(type, size)((type*)malloc(sizeof(type) * size))
#endif

template<typename T1, typename T2>
ostream& operator<<(ostream& os, pair<T1, T2> p)
{
	os << p.first << ", " << p.second;
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v)
{
	for (int i = 0; i < v.size(); i++)
		os << v[i] << ",";
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
	os << p.first << ", " << p.second;
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, set<T> s)
{
	for (set<T>::iterator it = s.begin(); it != s.end(); it++)
		os << *it << ", ";
	return os;
}

