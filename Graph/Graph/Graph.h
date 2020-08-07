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

#ifndef INT_MAX
#define INT_MAX (1 << 31 - 1)
#endif

#ifndef INT_MIN
#define INT_MIN (1 << 31)
#endif

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
		os << q.front() << ", ";
		q.pop();
	}
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T>& v)
{
	for (int i = 0; i != v.size(); i++)
	{
		cout << v[i] << ", ";
	}
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>>& v)
{
	for (int i = 0; i != v.size(); i++)
		cout << v[i] << endl;
	return os;
}

class Func
{
public:
	virtual void operator()(void*) = 0;
};

vector<vector<int>> floyed(int n, vector<vector<int>>& edges)
{
	vector<vector<int>> distance(n, vector<int>(n, INT_MAX));
	for (int i = 0; i < edges.size(); i++)
		distance[edges[i][1]][edges[i][0]] = distance[edges[i][0]][edges[i][1]] = edges[i][2];

	for (int i = 0; i < n; i++)
		distance[i][i] = 0;

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX)
						distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);

	return distance;
}