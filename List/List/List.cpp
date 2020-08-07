// List.cpp : Defines the entry point for the console application.
//

#include "ListNode.h"

ListNode* insertionSortList(ListNode* head)
{
	if (head == NULL)
		return head;

	ListNode **phead = &head, **iter1 = &(head->next), **iter2 = &head;

	while ((*iter1))
	{
		while ((*iter2)->next && (*iter1)->val > (*iter2)->val)
		{
			iter2 = &((*iter2)->next);
		}

		if (*iter1 != *iter2)
		{
			ListNode* tmp = *iter1;
			*iter1 = (*iter1)->next;

			tmp->next = *iter2;
			*iter2 = tmp;
		}
		else
		{
			iter1 = &((*iter1)->next);
		}
		iter2 = phead;
	}
	
	return *phead;
}

ListNode* partition(ListNode* head, int x)
{
	ListNode* h1 = NULL;
	ListNode* h2 = NULL;
	ListNode** iter1 = &h1, **iter2 = &h2;

	while (head)
	{
		if ((head)->val < x)
		{
			*iter1 = head;
			iter1 = &((*iter1)->next);
		}
		else
		{
			*iter2 = head;
			iter2 = &((*iter2)->next);
		}
		head = head->next;
	}
	*iter2 = NULL;
	(*iter1) = h2;
	return h1;
}

ListNode* Merge(ListNode* head1, ListNode* head2)
{
	ListNode* h = NULL;
	ListNode** iter = &h;
	while (head1 || head2)
	{
		if (head1 && head2)
		{
			if (head1 < head2)
				*iter = new ListNode(head1->val);
			else
				*iter = new ListNode(head2->val);
		}

		else if (head1)
			*iter = new ListNode(head1->val);
		else
			*iter = new ListNode(head2->val);

		iter = &((*iter)->next);
	}
	return h;
}

//2 1 4 3 6
//1 2 4 3 6
//
void reOrderArray(vector<int> &nums)
{
	int odd = 0, even = nums.size() - 1;
	vector<int> cpy = nums;
	for (int i = 0; i < nums.size(); i++)
	{
		if (cpy[i] % 2)
			nums[odd++] = cpy[i];
		else
			nums[even--] = cpy[i];
	}
	even = nums.size() - 1;
	while (odd < even)
		swap(nums[odd++], nums[even--]);
	cout << nums << endl;
}

void reorderArray(vector<int> &nums){
	int odd = 0, even = 0;
	while (odd < nums.size())
	{
		if (nums[odd] % 2)
			swap(nums[odd], nums[even++]);
		odd++;
	}
	cout << nums << endl;
}

ListNode* collosion_point(ListNode *head)
{
	ListNode* slow = head;
	ListNode* fast = head->next;

	while (true)
	{
		if (slow)
			slow = slow->next;

		if (fast)
			fast = fast->next;

		if (fast)
			fast = fast->next;

		if (!fast || slow == fast)
			break;
	}
	return fast;
}

ListNode* converge_point(ListNode* start, ListNode* collosion)
{
	collosion = collosion->next;
	
	while (start != collosion)
	{
		start = start->next;
		collosion = collosion->next;
	}
	return start;
}

vector<ListNode*> splitListToParts(ListNode* root, int k)
{
	int length = 0;
	ListNode* iter = root;
	while (iter)
	{
		iter = iter->next;
		length++;
	}

	int sub_length = length / k;
	int remainder = length % k;
	vector<ListNode*> res;
	res.push_back(root);
	iter = root;
	while (iter)
	{
		int length_part = length / k + (remainder-- > 0);
		while (length_part-- > 1)
			iter = iter->next;
		res.push_back(iter->next);
		iter->next = NULL;
		iter = res.back();
	}
	res.pop_back();
	res.resize(k);
	return res;
}

ListNode* oddEvenList(ListNode* head)
{
	ListNode **odd = &head, *even_head = NULL, **even = &even_head;
	while (*odd)
	{
		odd = &((*odd)->next);
		if (*even = *odd)
		{
			*odd = (*odd)->next;
			even = &((*even)->next);
		}	
	}
	*odd = even_head;
	return head;
}

int minSteps(int n) {
	int res = 0;
	while (n % 2 == 0)
	{
		++res;
		n >>= 1;
		cout << res << endl;
		cout << n << endl;
	}
	return res += n;
}
//1 3 5 7 9 2 4 6 8 10

ListNode* deleteDuplicates(ListNode* head)
{
	if (head == NULL || head->next == NULL)
		return head;
	int val = head->next->val;
	ListNode** iter = &head;
	while (*iter)
	{
		if (val == (*iter)->val)
		{
			while (*iter && val == (*iter)->val)
			{
				ListNode* tmp = *iter;
				*iter = (*iter)->next;
				delete tmp;
			}
		}
		else
			iter = &((*iter)->next);

		if (*iter && (*iter)->next)
			val = (*iter)->next->val;
		else
			break;
	}
	return head;
}


ListNode* removeNthFromEnd(ListNode* head, int n)
{
	stack<ListNode**> s;
	ListNode** iter = &head;

	int len = 0;
	while (*iter)
	{
		s.push(iter);
		iter = &((*iter)->next);
	}
		

	while (n--)
		s.pop();
	
	if (s.size())
	{
		ListNode* tmp = (*s.top())->next->next;
		delete ((*s.top())->next);
		(*s.top())->next = tmp;
	}
	else
	{
		ListNode* tmp = head->next;
		delete head;
		head = tmp;
	}

	return head;
}

void remove(ListNode*& head, int val)
{
	ListNode** iter = &head;
	while (*iter)
	{
		if ((*iter)->val == val)
		{
			ListNode* tmp = *iter;
			*iter = (*iter)->next;
			tmp->next = NULL;
			delete tmp;
		}
		else
			iter = &((*iter)->next);
	}
}

void reorderList(ListNode* head)
{
	ListNode** iter = &head;
	stack<ListNode**> s;
	int len = 0;
	while (*iter)
	{
		s.push(iter);
		iter = &((*iter)->next);
		len++;
	}
	len  = len / 2 - !(len % 2);
	iter = &head;

	while (len--)
	{
		ListNode** tail = s.top();
		s.pop();

		(*tail)->next = (*iter)->next;
		(*iter)->next = *tail;

		*tail = NULL;

		iter = &((*iter)->next);
		iter = &((*iter)->next);
	}
}

string addStrings(string num1, string num2)
{
	if (num1 == "" || num2 == "")
		return "";

	if (num1.size() < num2.size())
		swap(num1, num2);

	int idx1 = num1.size() - 1, idx2 = num2.size() - 1;
	int carry = 0, sum = 0;
	string ans = "";
	while (idx2 >= 0)
	{
		sum = num2[idx2] + num1[idx1] + carry - ('0' << 1);
		ans += (sum % 10) + '0';
		carry = sum / 10;

		--idx1, --idx2;
	}
	
	while (idx1 >= 0)
	{
		sum = num1[idx1] + carry - '0';
		ans += (sum % 10) + '0';
		carry = sum / 10;
		--idx1;
	}

	if (carry)
		ans += '1';

	reverse(ans.begin(), ans.end());
	return ans;
}

void reverse(ListNode*& head)
{
	ListNode **list_head = &head;
	ListNode *iter = head ? head->next : NULL;
	*list_head ? (*list_head)->next = NULL : *list_head;

	while (iter)
	{
		ListNode *nxt = iter->next;
		iter->next = *list_head;
		*list_head = iter;
		iter = nxt;
	}
}

void swapNode(ListNode* &node1, ListNode*& node2)
{
	ListNode* tmp = node1;
	node1 = node2;
	node2 = tmp;

	if (node1->next != node2)
	{


		tmp = node2->next;
		node2->next = node1->next;
		node1->next = tmp;
	}
	else
	{
		//ListNode* tmp = node1;
		//node1 = node2;
		//node2 = tmp;

		tmp = node2->next;
		node2->next = node1;
		node1->next = tmp;
	}


}

ListNode* swapPairs(ListNode* head)
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode **iter1 = &head, **iter2 = &((*iter1)->next);

	while (*iter2)
	{
		swapNode(*iter1, *iter2);
		if (*iter1)
			iter1 = &((*iter1)->next);
		else
			break;
		if (*iter1)
			iter1 = &((*iter1)->next);
		else
			break;
		if (*iter1)
			iter2 = &((*iter1)->next);
		else
			break;
	}

	return head;
}

void reverse(ListNode*& start, ListNode**& end)
{
	ListNode *iter = start, **head = &start;
	if (iter->next != *end)
	{
		iter = iter->next;
		start->next = *end;
		end = &(start->next);
		// iter = &((*iter)->next);
		while (iter != *end)
		{
			ListNode* nxt = iter->next;
			iter->next = *head;
			*head = iter;
			iter = nxt;
		}
	}
}

ListNode* reverseKGroup(ListNode* head, int k)
{
	ListNode **iter = &head;
	while (iter)
	{
		int size = k;
		ListNode** end = iter;
		
		while (size && *end)
		{
			size--;
			end = &((*end)->next);
		}
		
		if (size > 0)
			break;
		else
			reverse(*iter, end);
		iter = end;
	}
	return head;
}

ListNode* middleNode(ListNode* head)
{
	int len = 0;
	ListNode* iter = head;
	while (iter)
	{
		len++;
		iter = iter->next;
	}

	int idx = 0;
	iter = head;
	while (idx * 2 < len)
		iter = iter->next;
	return iter;
}

int main()
{
	ListNode* head = Construct(vector<int>({ 1, 2, 3, 4, 5 }));
	head = middleNode(head);
	cout << head << endl;
	return 0; 
}