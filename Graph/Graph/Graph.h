#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <set>
#include <unordered_set>
using namespace std;

class Node
{
public:
	int val;
	vector<Node*> neighbors;

	Node() :val(0), neighbors(vector<Node*>()){};
	Node(int _val) : val(_val){};
	Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors){};
};

ostream& operator<<(ostream& os, Node* node)
{
	return os << node->val << ' ';
}

template<typename T>
ostream& operator<<(ostream& os, queue<T> q)
{
	while (!q.empty())
	{
		os << q.front() << ' ';
		q.pop();
	}
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T>& v)
{
	for (int i = 0; i != v.size(); i++)
	{
		cout << v[i] << ' ';
	}
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>>& v)
{
	for (int i = 0; i != v.size(); i++)
	{
		cout << v[i] << endl;
	}
	return os;
}

class Func
{
public:
	virtual void operator()(void*) = 0;
};
