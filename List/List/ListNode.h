#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

#ifndef INT_MAX
#define INT_MAX (1 << 31 - 1)
#endif

#ifndef INT_MIN
#define INT_MIN (1 << 31)
#endif

typedef unsigned int size_type;

class  ListNode
{
public:
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(NULL){}

	bool operator<(const ListNode& n)
	{
		return val < n.next->val;
	}
};


class List
{	
	ListNode* m_head;
	size_type m_length;
public:
	List() :m_head(NULL), m_length(0){}

	List(vector<int>& a)
	{
		if (a.empty())
			m_head = NULL, m_length = 0;
		else
		{
			m_head = new ListNode(a[0]);
			ListNode* iter = m_head;

			for (int i = 1; i < a.size(); i++)
			{
				iter->next = new ListNode(a[i]);
				iter = iter->next;
			}
		}
	}

	void setHead(ListNode* head)
	{
		this->m_head = head;
	}

	size_type length(void)
	{
		return this->m_length;
	}

	ListNode* head(void)
	{
		return this->m_head;
	}

	~List()
	{
		ListNode* iter = this->m_head;
		while (this->m_head)
		{
			m_head = m_head->next;
			delete iter;
			iter = m_head;
		}
	}
};


void exchange(ListNode** node1, ListNode** node2)
{
	ListNode* tmp = *node1;
	*node1 = *node2;
	*node2 = tmp;

	tmp = (*node1)->next;
	(*node1)->next = (*node2)->next;
	(*node2)->next = tmp;
}

ListNode* Construct(vector<int> v)
{
	ListNode* head = NULL;
	ListNode** iter = &head;

	for (int i = 0; i < v.size(); i++)
	{
		(*iter) = new ListNode(v[i]);
		iter = &((*iter)->next);
	}

	return head;
}

void createOrbit(ListNode* h, int pos)
{
	ListNode** iter = &h;
	ListNode* p = NULL;
	while (*iter)
	{
		if (pos-- == 0)
			p = *iter;
		iter = &((*iter)->next);
	}
	*iter = p;
}

void Destruct(ListNode* h)
{
	ListNode* iter = h;
	while (h)
	{
		iter = h->next;
		delete h;
		h = iter;
	}
}

ostream& operator<<(ostream& os, ListNode* t)
{
	while (t)
	{
		os << t->val << ' ';
		t = t->next;
	}
	return os;
}

ostream& operator<<(ostream& os, List& t)
{
	os << t.head();
	return os;
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
	for (vector<vector>::size_type i = 0; i < t.size(); i++)
		os << t[i] << endl;
	return os;
}