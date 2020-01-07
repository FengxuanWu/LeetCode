#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

class Trie
{
private:
	int critical;
	map<char, Trie*> children;
public:
	Trie(): critical(false){};
	
	Trie* insert(string s)
	{
 		Trie* iterator = this;
		for (int i = 0; i < s.size(); i++)
		{
			if (iterator->children.find(s[i]) == iterator->children.end())
				iterator->children[s[i]] = new Trie();
			iterator = iterator->children[s[i]];
			if (i == s.size() - 1)
				(iterator->critical += 1);
		}
		return iterator;
	}

	bool startsWith(string s)
	{
		Trie* iterator = this;
		for (int i = 0; i < s.size(); i++)
		{
			if (iterator->children.find(s[i]) != iterator->children.end())
				iterator = iterator->children[s[i]];
			else
				return false;
		}
		return true;
	}

	bool search(string s)
	{
		Trie* iterator = this;
		for (int i = 0; i < s.size() - 1; i++)
		{
			if (iterator->children.find(s[i]) != iterator->children.end())
				iterator = iterator->children[s[i]];	
			else
				return false;
		}
		return iterator->children.find(s.back()) != iterator->children.end() && iterator->children[s.back()]->critical;
	}

	void collect(Trie* root, string& tmp, vector<string>& s)
	{
		if (root->critical)
		{
			for (int i = 0; i < root->critical; i++)
				s.push_back(tmp);
		}

		for (auto it = root->children.begin(); it != root->children.end(); it++)
		{
			tmp += (*it).first;
			collect((*it).second, tmp , s);
			tmp.pop_back();
		}
	}

	vector<string> searchStart(string start)
	{
		vector<string> ans;
		Trie* iter = this;
		for (int i = 0; i < start.size(); i++)
		{
			if (iter->children.find(start[i]) != iter->children.end())
				iter = iter->children[start[i]];
			else
				return ans;
		}
		collect(iter, start, ans);
		return ans;
	}
	
	~Trie()
	{
		for (auto it = children.begin(); it != children.end(); it++)
			delete (*it).second;
	}
};

vector<string> split(string s, char c)
{
	vector<string> res;
	int left = 0, right = 0;
	while (s[left] == c)right = ++left;
	while (right < s.size())
	{
		if (s[right] == c && right > left)
		{
			res.push_back(s.substr(left, right - left));
			left = right + 1;
		}
		++right;
	}
	return res;
}


class PrefixTree
{
public:
	string prefix;
	vector<PrefixTree*> children;
	PrefixTree(string s) : prefix(s), children(vector<PrefixTree*>()){};
};

int string_compare(string& a, int start, string& b)
{
	int index = 0;

	while (index + start < a.size() && index < b.size() && a[index + start] == b[index])
		++index;

	return index;
}

void destory(PrefixTree* node)
{
	for (int i = 0; i < (*node).children.size(); i++)
		destory((*node).children[i]);
	delete node;
}

void traverse(PrefixTree* node)
{
	cout << node->prefix << endl;
	for (int i = 0; i < node->children.size(); i++)
		traverse(node->children[i]);
}

void construct_result(PrefixTree* node, vector<string>& res, string curr)
{
	cout << (curr + node->prefix) << endl;
	if (node->children.size() == 0)
		res.push_back(curr);

	for (int i = 0; i < node->children.size(); i++)
		construct_result(node->children[i], res, curr + node->prefix);
}

void merge_prefix_ree(string s, int start, PrefixTree* node)
{
	bool found = false;

	for (int i = 0; i < node->children.size(); i++)
	{
		int same = string_compare(s, start, node->children[i]->prefix);
		found = same > 0;
		if (same > 0)
		{
			//root found and the new path is different from root
			if (start + same < s.size())
			{
				//root found
				if (same == node->children[i]->prefix.size())
					merge_prefix_ree(s, start + same, node->children[i]);
				else
				{
					// /aa/ab/ac /aa/ab/ac/ad, /aa/ab/ac and does not exist in the tree
					PrefixTree* new_node = new PrefixTree(s.substr(start, same));
					node->children[i]->prefix = node->children[i]->prefix.substr(same, node->children[i]->prefix.size() - same);
					new_node->children.push_back(node->children[i]);
					node->children[i] = new_node;
					if (s.size() > same)
					{
						new_node->children.push_back(new PrefixTree(s.substr(start + same, s.size() - same - start)));
					}
				}
			}
			break;
		}
	}

	if (!found)
		node->children.push_back(new PrefixTree(s.substr(start, s.size() - start)));
}

template<typename T>
ostream& operator<<(ostream& os, vector<T>& v)
{
	for (auto c : v)
		os << c << ' ';
	return os;
}