#include "stdafx.h"
#include <queue>
#include <map>
#include <iostream>
#include <set>
#include <stack>
#include <algorithm>
#include <string>
using namespace std;

class TreeNode
{
public:
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	~TreeNode()
	{
		if (this->left)
			delete this->left;
		if (this->right)
			delete this->right;
		delete this;
	}
};
typedef TreeNode* PTreeNode;

#define IN 0
#define PRE 1
#define POST 2

ostream& operator<<(ostream& os, TreeNode* root)
{
	queue<PTreeNode> q;
	TreeNode* p = root;

	q.push(root);

	while (!q.empty())
	{
		cout << q.front()->val << ' ';

		if (q.front()->left)
			q.push(q.front()->left);
		//else cout << "null" << ' ';
		if (q.front()->right)
			q.push(q.front()->right);
		//else cout << "null" << ' ';

		q.pop();
		//cout << endl;
	}
	return os;
}

TreeNode* copy(TreeNode* root)
{
	TreeNode* t = NULL;
	if (root != NULL)
	{
		t = new TreeNode(root->val);
		t->left = copy(root->left);
		t->right = copy(root->right);
	}
	return t;
}

TreeNode* construct(TreeNode* root)
{
	int n;
	cin >> n;
	if (n != -1)
	{
		root = new TreeNode(n);
		root->left = construct(root->left);
		root->right = construct(root->right);
		return root;
	}
	return NULL;
}

void destruct(TreeNode* root)
{
	if (root)
	{
		destruct(root->left);
		destruct(root->right);
	}
	delete root;
}

TreeNode* construct(vector<string> nums)
{
	if (nums.size() == 0)
		return NULL;
	queue<TreeNode**> q;
	TreeNode* root = NULL;
	q.push(&root);
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] != "null")
		{
			*q.front() = new TreeNode(stoi(nums[i]));
			q.push(&((*q.front())->left));
			q.push(&((*q.front())->right));
		}		
		q.pop();
	}
	return root;
}

void print_tree(TreeNode* root)
{
	if (root)
	{
		cout << root->val << ' ';
		print_tree(root->left);
		print_tree(root->right);
	}
}


void print_inorder(TreeNode* root)
{
	if (root)
	{
		print_inorder(root->left);
		cout << root->val << ' ';
		print_inorder(root->right);
	}
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> t)
{
	for (vector<T>::size_type i = 0; i < t.size(); i++)
		os << t[i] << ' ';
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>> t)
{
	for (vector<vector<T>>::size_type i = 0; i < t.size(); i++)
		os << t[i] << endl;
	return os;
}

//#define check_left(s, visited)(if (!visited[s.top()->left]){current = PRE;break;})
//#define check_right(s, visited)(if (!visited[s.top()->right]){current = POST;break;})
//#define access_val(s, visited)(if (!visited[s.top()]){cout << s.top()->val << endl;visited[s.top()] = 1;})

void stack_preorder(TreeNode* root)
{
	stack<TreeNode*> s;
	map<TreeNode*, bool> visited;
	visited[NULL] = 1;
	s.push(root);
	int current = PRE;
	while (!s.empty())
	{
		switch (current)
		{
		case PRE:
			s.push(s.top()->left);
			current = IN;
			break;
		case IN:
			if (s.top())
			{
				if (!visited[s.top()]){ cout << s.top()->val << ' '; visited[s.top()] = 1; }
				if (!visited[s.top()->left]){ current = PRE; break; }
				if (!visited[s.top()->right]){ current = POST; break; }
			}		
			s.pop();
			break;
		case POST:
			s.push(s.top()->right);
			current = IN;
			break;
		}
	}
}

void stack_inorder(TreeNode* root)
{
	stack<TreeNode*> s;
	map<TreeNode*, bool> visited;
	visited[NULL] = 1;
	s.push(root);
	int current = IN;
	while (!s.empty())
	{
		switch (current)
		{
		case PRE:
			s.push(s.top()->left);
			current = IN;
			break;
		case IN:
			if (s.top())
			{
				if (!visited[s.top()->left]){ current = PRE; break; }
				if (!visited[s.top()]){ cout << s.top()->val << ' '; visited[s.top()] = 1; }
				if (!visited[s.top()->right]){ current = POST; break; }
			}		
			s.pop();
			break;
		case POST:
			s.push(s.top()->right);
			current = IN;
			break;
		}
	}
}

void stack_postorder(TreeNode* root)
{
	stack<TreeNode*> s;
	map<TreeNode*, bool> visited;
	visited[NULL] = 1;
	s.push(root);
	int current = IN;
	while (!s.empty())
	{
		switch (current)
		{
		case PRE:
			s.push(s.top()->left);
			current = IN;
			break;
		case IN:
			if (s.top())
			{
				if (!visited[s.top()->left]){ current = PRE; break; }
				if (!visited[s.top()->right]){ current = POST; break; }
				if (!visited[s.top()]){ cout << s.top()->val << ' '; visited[s.top()] = 1; }
			}		
			s.pop();
			break;
		case POST:
			s.push(s.top()->right);
			current = IN;
			break;
		}
	}
}
