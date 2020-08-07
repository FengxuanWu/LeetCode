#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

#ifndef INT_MAX
#define INT_MAX (1 << 31 - 1)
#endif 

#ifndef INT_MIN
#define INT_MIN (1 << 31)
#endif 

template<typename T>
class UnionFind
{
public:
	UnionFind*  parent;
	T val;
	int rank;

	UnionFind(){};
	UnionFind(T v) :val(v), parent(NULL), rank(1){};

	UnionFind& find()
	{
		if (parent != NULL)
			return *parent = parent->find();
		return *this;
	}

	void merge(UnionFind& set)
	{
		UnionFind* s1 = &(this->find()), *s2 = &(set.find()), *root = NULL;

		if (s2->rank > s1->rank)
			root = s1->parent = s2;
		else
			root = s2->parent = s1;

		root->rank = s1->rank + s2->rank;
	}

	int count()
	{
		return find().rank;
	}
};

template<typename T>
ostream& operator<<(ostream& os, vector<T> v)
{
	for (T& val : v)
		os << val << ' ';
	return os;
}


template<typename T>
ostream& operator<<(ostream& os, UnionFind<T>& u)
{
	os << "val: " << u.val << endl;
	os << "root: " << u.find().val << endl;
	os << "size: " << u.find().rank << endl;
	os << endl;
	return os;
}