// Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"

vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
	vector<vector<int>> res;
	if (root != NULL)
	{
		queue<TreeNode*> q;
		q.push(root);
		int cnt = 1, next_cnt = 0, layer = 0;

		vector<int> t;
		while (!q.empty())
		{		
			while (cnt)
			{
				t.push_back(q.front()->val);
				if (q.front()->left)
				{
					q.push(q.front()->left);
					next_cnt++;
				}

				if (q.front()->right)
				{
					q.push(q.front()->right);
					next_cnt++;
				}

				q.pop();
				cnt--;
			}

			cnt = next_cnt;
			next_cnt = 0;
			if (layer % 2)
				reverse(t.begin(), t.end());
			
			layer++;
			
			res.push_back(t);
			t.clear();
		}	
	}
	return res;
}

//#define LEFT(v1,v2)(in[v1] < in[v2])
//TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
//{
//	if (preorder.empty() || inorder.empty())
//		return NULL;
//
//	map<int, int> in;
//	vector<TreeNode*> nodes;
//
//	for (vector<int>::size_type i = 0; i < preorder.size(); i++)
//	{
//		nodes.push_back(new TreeNode(preorder[i]));
//	}
//
//	for (vector<int>::size_type i = 0; i < inorder.size(); i++)
//	{
//		in[inorder[i]] = i;
//	}
//
//	for (int i = 1; i < preorder.size(); i++)
//	{
//		int j = i - 1;
//		while (j >= 0 && !LEFT(preorder[i], preorder[j]))j--;
//
//		if (j == i - 1)
//		{
//			nodes[j]->left = nodes[i];
//		}
//		else if (nodes[j + 1]->right == NULL)
//		{
//			nodes[j + 1]->right = nodes[i];
//		}
//		else
//		{
//			TreeNode** iter = &nodes[0];
//			
//			while (*iter)
//			{
//				if (LEFT(nodes[i]->val, (*iter)->val))
//				{
//					iter = &((*iter)->left);
//				}
//				else
//				{
//					iter = &((*iter)->right);
//				}
//			}
//
//			(*iter) = nodes[i];
//		}
//	}
//	
//	return nodes[0];
//}

int maxPathSum(TreeNode* root)
{
	int maxium = 0;
	if (root)
	{
		if (root->left == NULL && root->right == NULL)
			return root->val;
		
		if (root->left)
		{
			maxium = max(maxium, maxPathSum(root->left));
		}

		if (root->right)
			maxium = max(maxium, maxPathSum(root->right));
	}
	return maxium;
}

#include <map>
#define RIGHT(a, b)(in[a] > in[b])
#define LEFT(a, b)(in[a] < in[b])
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
{
	vector<TreeNode*> nodes;
	map<int, int> in;

	for (unsigned int i = 0; i < postorder.size(); i++)
	{
		nodes.emplace_back(new TreeNode(postorder[i]));
	}

	//the map from node whose value is postorder[i] to the index in inorder array
	for (unsigned int i = 0; i < inorder.size(); i++)
		in[inorder[i]] = i;

	
	/////////////////////////////////////////////////////////////////////////////////////
	for (int i = postorder.size() - 2; i >= 0; i--)
	{
		unsigned int predecessor = i + 1;
		cout << in[postorder[i]] << ' ' << in[postorder[predecessor]] << endl;
		while (predecessor <= postorder.size() - 1 && LEFT(postorder[i], postorder[predecessor]))
			predecessor++;

		if (predecessor == i + 1)
		{
			nodes[predecessor]->right = nodes[i];
		}
		else if (nodes[predecessor - 1]->left == NULL)
		{
			nodes[predecessor - 1]->left = nodes[i];
		}
		else
		{
			TreeNode** iter = &nodes.back();
			while (*iter)
			{
				if (LEFT((*iter)->val, postorder[i]))
					iter = &((*iter)->left);
				else
					iter = &((*iter)->right);
			}
			*iter = nodes[i];
		}	
	}
	return nodes.back();
}

int maxSubArray(vector<int>& nums, int start, int end)
{
	if (nums.empty())
		return 0;

	int max_n_contain = INT_MIN, max_contain = nums[0];
	for (int i = start + 1; i < end; i++)
	{
		if (max_contain + nums[i] < nums[i])
		{
			//max_n_contain = max(max_n_contain , max_contain);
			max_contain = nums[i];
		}
		else
		{
			if (nums[i] < 0)
				max_n_contain = max(max_n_contain, max_contain);
			max_contain += nums[i];
		}
	}
	return max(max_contain, max_n_contain);
}

vector<int> rightSideView(TreeNode* root)
{
	vector<int> res;
	if (root != NULL)
	{
		queue<TreeNode*> q;
		q.push(root);
		int cnt = 1, next_cnt = 0, layer = 0;

		while (!q.empty())
		{
			while (cnt)
			{
				if (q.front()->left)
				{
					q.push(q.front()->left);
					next_cnt++;
				}

				if (q.front()->right)
				{
					q.push(q.front()->right);
					next_cnt++;
				}

				cnt--;
				if (cnt == 0)
					res.emplace_back(q.front()->val);
				q.pop();
			}

			cnt = next_cnt;
			next_cnt = 0;
		}
	}
	return res;
}

//9 10 -1 -1 5 -1 -1
//1 2 -1 5 -1 -1 3 -1 4 -1 -1

int TreeDepth(TreeNode* root)
{
	if (!root)
		return 0;
	else
		return max(TreeDepth(root->left), TreeDepth(root->right)) + 1;
}
//1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 -1
int countNodes(TreeNode* root)
{
	if (root == NULL)
		return 0;
	return 1 + countNodes(root->left) + countNodes(root->right);
}

int distributeCoins(TreeNode* root)
{
	int res = 0;
	if (root)
	{
		if (root->left)
		{
			res += distributeCoins(root->left);
			root->val += (root->left->val - 1);
		}
		if (root->right)
		{
			res += distributeCoins(root->right);
			root->val += (root->right->val - 1);
		}
		res += abs(root->val - 1);
		//cout << root->val << endl;
	}
	return res;
}

void in_order(TreeNode* root, vector<int>& v)
{
	if (root)
	{
		in_order(root->left, v);
		v.push_back(root->val);
		in_order(root->right, v);
	}
}

int kthSmallest(TreeNode* root, int k)
{
	vector<int> v;
	in_order(root, v);
	return v[k - 1];
}

//int pathSumHelper(TreeNode* root, int sum)
//{
//	if (root)
//	{	
//		return (root->val == sum) + pathSumHelper(root->left, sum - root->val) + pathSumHelper(root->right, sum - root->val);
//	}
//	return 0;
//}
////10 5 3 3 -1 -1 -2 -1 -1 2 -1 1 -1 -1 -3 -1 11 -1 -1
////1 -2 1 -10 -1 -1 -1 3 -1 -1 -3 -2 -1 -1 -1
////-8 6 -1 -1 8 8 -1 -1 2 -1 -2 -1 -1
//int pathSum(TreeNode* root, int sum)
//{
//	if (root)
//	{
//		return pathSumHelper(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
//	}
//	
//	return 0;
//}

int idx;
int length;

TreeNode* buildBST(vector<int>& nums, int length)
{
	if (length == 0)
		return NULL;
	TreeNode* root = new TreeNode(0);
	root->left = buildBST(nums, length / 2);
	root->val = nums[idx];
	idx++;
	root->right = buildBST(nums, length - length / 2 - 1);
	return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
	idx = 0;
	return buildBST(nums, nums.size());
}

class FindElements {
public:
	set<int> vals;
	void recover(TreeNode* root, int val)
	{
		if (root)
		{
			root->val = val;
			vals.insert(val);
			recover(root->left, (val * 2) + 1);
			recover(root->right, (val * 2) + 2);
		}
	}

	FindElements(TreeNode* root)
	{
		recover(root, 0);
	}

	bool find(int target) {
		return  vals.find(target) != vals.end();
	}
};

void tilt(TreeNode* root, int& res)
{
	int left = 0, right = 0;
	if (root->left)
	{
		tilt(root->left, res);
		left = root->left->val;
	}
	if (root->right)
	{
		tilt(root->right, res);
		right = root->right->val;
	}
	root->val += (left + right);
	res += abs(left - right);
}

int findTilt(TreeNode* root) {
	int ans = 0;
	if (root)
		tilt(root, ans);
	return ans;
}


void path(TreeNode* root, int target, vector<int>& p)
{
	if (root)
	{
		if (root->val == target)
			p.push_back(root->val);
		else
		{
			path(root->left, target, p);
			if (p.empty())
				path(root->right, target, p);
			if (!p.empty())
				p.push_back(root->val);
		}
	}
}

//int  lowestCommonAncestor(TreeNode* root, int p, int q)
//{
//	vector<int> p1;
//	vector<int> p2;
//	path(root, p, p1);
//	path(root, p, p2);
//
//	int i = p1.size() - 1, j = p2.size() - 1;
//	cout << p1 << endl;
//	cout << p2 << endl;
//	while (i >= 0 && j >= 0)
//	{
//		if (p1[i] == p2[j])
//			i--, j--;
//		else
//			break;
//	}
//	return p1[i + 1];
//}

bool isCompleteTree(TreeNode* root)
{
	if (root == NULL)
		return true;

	queue<pair<int, TreeNode*>> q;
	int cnt = 1, num = 0;
	q.push(make_pair(cnt, root));

	while (!q.empty())
	{
		num = q.front().first;
		
		++cnt;
		if (q.front().second->left)
			q.push(make_pair(cnt, q.front().second->left));
		
		++cnt;
		if (q.front().second->right)
			q.push(make_pair(cnt, q.front().second->right));

		q.pop();
		if (!q.empty() && q.front().first != num + 1)
			return false;
	}
	return true;
}

TreeNode* trimBST(TreeNode* root, int L, int R)
{
	if (!root) return root; // Go to bottom of tree. DO nothing with this returned value
	if (root->left) root->left = trimBST(root->left, L, R);
	if (root->right) root->right = trimBST(root->right, L, R);
	if (root->val < L || root->val > R) {
		if (root->left) {
			root = root->left; // We need to overwrite this value, do so with left branch
		}
		else if (root->right) {
			root = root->right;
		}
		else if (!root->right && !root->left) {
			root = nullptr; // Root has no children we need to deal with
		}
	}
	return root;
}

void dfs(TreeNode* root, int val)
{
	if (root)
	{
		root->val = val;
		dfs(root->left, val * 2);
		dfs(root->right, val * 2 + 1);
	}
}

int widthOfBinaryTree(TreeNode* root)
{
	if (!root)
		return 0;

	dfs(root, 1);
	
	queue<pair<int, TreeNode*>> q;
	q.push(make_pair(1, root));

	int ans = 1;
	while (!q.empty())
	{
		int layer = q.front().first;
		int width = 0;
		int start = 0;
		while (!q.empty() && q.front().first == layer)
		{
			if (start == 0)
				start = q.front().second->val;
			width = q.front().second->val;

			if (q.front().second->left)
				q.push(make_pair(layer + 1, q.front().second->left));

			if (q.front().second->right)
				q.push(make_pair(layer + 1, q.front().second->right));
			
			q.pop();
		}

		ans = max(width - start + 1, ans);
		start = width;
	}
	return ans;
}
//1 1 1 1 -1 -1 -1 -1 1 -1 1 -1 1 -1 -1
//1 3 5 -1 -1 3 -1 -1 -1
//1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 -1
//1 2 4 -1 -1 5 -1 -1 3 -1 7 -1 -1


pair<TreeNode*, int> tree_depth(TreeNode* root)
{
	if (root)
	{
		pair<TreeNode*, int> left = tree_depth(root->left);
		pair<TreeNode*, int> right = tree_depth(root->right);

		int left_depth = left.second, right_depth = right.second;

		if (left_depth == right_depth)
			return make_pair(root, left_depth + 1);
		else if (left_depth > right_depth)
		{
			++left.second;
			left.first = root->right == NULL ? root : left.first;
			return left;
		}
		else
		{
			++right.second;
			right.first = root->left == NULL ? root : right.first;
			return right;
		}
	}
	return make_pair(root, 0);
}

TreeNode* subtreeWithAllDeepest(TreeNode* root)
{
	pair<TreeNode*, int> ans = tree_depth(root);
	return ans.first;
}

void destory(TreeNode*& root)
{
	if (root)
	{
		destory(root->left);
		destory(root->right);
		root = NULL;
	}
}
//1 2 -5 -1 -1 -1 -3 4 -1 -1 -1
bool needRemove(TreeNode* &root, int sum, int limit)
{
	if (root)
	{
		bool leaf = root->left == NULL && root->right == NULL;
		bool left_remove = needRemove(root->left, sum + root->val, limit);
		bool right_remove = needRemove(root->right, sum + root->val, limit);
		if (left_remove && right_remove)
			destory(root);

		if (!leaf && root->left == NULL && root->right == NULL)
			destory(root);

		return left_remove && right_remove;
	}
	return sum < limit;
}

TreeNode* sufficientSubset(TreeNode* root, int limit)
{
	needRemove(root, 0, limit);
	return root;
}
//6 2 0 -1 -1 4 3 -1 -1 5 -1 -1 8 7 -1 -1 9 -1 -1
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
	if (root)
	{
		if (root->val == p->val || root->val == q->val 
			|| (p->val < root->val && q->val > root->val)
			|| (q->val < root->val && p->val > root->val))
			return root;

		if (p->val > root->val && q->val > root->val)
			return lowestCommonAncestor(root->right, p, q);

		if (p->val < root->val && q->val < root->val)
			return lowestCommonAncestor(root->left, p, q);
	}
	return root;
}

int minDepth(TreeNode* root)
{
	if (root)
	{
		int left = minDepth(root->left);
		int right = minDepth(root->right);
		if (left == 0 && right == 0)
			return 1;
		if (left == 0 && right != 0)
			return right + 1;
		if (left != 0 && right == 0)
			return left + 1;
	}
	return 0;
}

void tag(TreeNode*& root, vector<int>& to_delete, vector<TreeNode*>& res, TreeNode* parent = NULL)
{
	if (root)
	{
		for (int i = 0; i < to_delete.size(); i++)
		{
			if (0 == (root->val *= !(to_delete[i] == root->val)))
				break;
		}

		tag(root->left, to_delete, res, root);
		tag(root->right, to_delete, res, root);

		if (root->val != 0 && (parent == NULL || parent->val == 0))
			res.push_back(root);

		if (root->val == 0)
		{
			//delete root;
			root = NULL;
		}
	}
}


vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete)
{
	vector<TreeNode*> res;
	tag(root, to_delete, res);
	return res;
}

bool isSameTree(TreeNode* root1, TreeNode* root2)
{
	if (root1 && root2)
	{
		int res = true;
		res &= isSameTree(root1->left, root2->left);
		res &= root1->val == root2->val;
		res &= isSameTree(root1->right, root2->right);
		return res;
	}
	return root1 == NULL && root2 == NULL;
}

bool HasSubtree(TreeNode* root1, TreeNode* root2)
{
	if (root1 && root2)
	{
		if (root1->val == root2->val && isSameTree(root1, root2))
			return true;
		return HasSubtree(root1->left, root2) || HasSubtree(root1->right, root2);
	}
	return false;
}

TreeNode* removeLeafNodes(TreeNode*& root, int target)
{
	if (root)
	{
		removeLeafNodes(root->left, target);
		removeLeafNodes(root->right, target);
		if (root->left == NULL && root->right == NULL && root->val == target)
			root = NULL;
	}
	return root;
}

int calDepth(TreeNode* root)
{
	if (root)
	{
		int left = calDepth(root->left);
		int right = calDepth(root->right);
		return root->val = max(left, right) + 1;
	}
	return 0;
}

bool isAVL(TreeNode* root)
{
	if (root)
	{
		int left = root->left ? root->left->val : 0;
		int right = root->right ? root->right->val : 0;
		return abs(left - right) < 2;
	}
	return true;
}

bool IsBalanced_Solution(TreeNode* root)
{
	calDepth(root);
	return isAVL(root);
}

TreeNode* flattenBST(TreeNode* root, TreeNode **&tail)
{
	TreeNode* head = NULL;
	if (root)
	{
		if (root->left)
			head = flattenBST(root->left, tail);

		if (tail == NULL)
			tail = &root;
		else
			(*tail) = root;
		tail = &((*tail)->right);
		TreeNode **cpy = tail;
		if (root->right)
			(*cpy) = flattenBST(root->right, tail);

		if (head == NULL)
			head = root;
	}
	return head;
}

TreeNode* Convert(TreeNode* root)
{
	if (root == NULL)
		return root;

	TreeNode* head, **tail = NULL;
	head = flattenBST(root, tail);

	TreeNode* iter = head;

	while (iter->right)
	{
		iter->right->left = iter;
		iter = iter->right;
	}

	return head;
}

bool helper(vector<int> &sequence, int start, int end)
{
	if (start == end || start + 1 == end)
		return true;

	int x = sequence[end];
	int left = start, right = end - 1;
	
	while (left < end && sequence[left] < x)left++;
	while (right > start && sequence[right] > x)right--;

	if (left - right != 1)
		return false;
	return helper(sequence, start, right) && helper(sequence, left, end - 1);
}

bool VerifySquenceOfBST(vector<int> sequence)
{
	return helper(sequence, 0, sequence.size() - 1);
}

int getSum(TreeNode* root)
{
	return root == NULL ? 0 : root->val + getSum(root->left) + getSum(root->right);
}

void helper(TreeNode* root, int& sum)
{
	if (root)
	{
		helper(root->right, sum);
		root->val = sum += root->val;
		helper(root->left, sum);
	}
}

TreeNode* bstToGst(TreeNode* root)
{
	int sum = 0;
	helper(root, sum);
	return root;
}

bool match(ListNode* head, TreeNode* root)
{
	if (head == NULL)
		return true;

	if (root)
	{
		if (root->val == head->val)
			return match(head->next, root->left) || match(head->next, root->right);
		return false;
	}
	return false;
}

bool isSubPath(ListNode* head, TreeNode* root)
{
	if (root)
	{
		if (match(head, root))
			return true;
		return isSubPath(head, root->left) || isSubPath(head, root->right);
	}
	return false;
}

string rankTeams(vector<string>& votes)
{
	vector<pair<vector<int>, char>> teams(26);
	for (int i = 0; i < teams.size(); i++)
	{
		teams[i].second = 'A' + i;
	}


	for (int i = 0; i < votes.size(); i++)
		for (int j = 0; j < votes[i].size(); j++)
		{
			if (teams[votes[i][j] - 'A'].first.size() == 0)		
				teams[votes[i][j] - 'A'].first.resize(26);		
			teams[votes[i][j] - 'A'].first[j]++;
		}
			

		sort(teams.begin(), teams.end(), [=](pair<vector<int>, char> &a, pair<vector<int>, char> &b)
		{
			return a.first > b.first || a.first == b.first && a.second < b.second;
		});
	string  res = "";
	for (int i = 0; i < teams.size(); i++)
	if (teams[i].first.size() > 0)
		res += teams[i].second;
	return res;
}

TreeNode* buildTree(vector<string>& layer)
{
	TreeNode *root = NULL;
	queue<TreeNode**> q;
	q.push(&root);

	for (int i = 0; i < layer.size(); i++)
	{
		if (layer[i] != "#")
		{
			*q.front() = new TreeNode(stoi(layer[i]));
			q.push(&((*q.front())->left));
			q.push(&((*q.front())->right));
		}
		q.pop();
	}

	return root;
}

void traverse(TreeNode* root)
{
	stack<TreeNode**> s;
	unordered_map<TreeNode**, bool> visited;
	s.push(&root);
	int current = IN;
	while (!s.empty())
	{
		switch (current)
		{
		case PRE:
			s.push(&((*s.top())->left));
			current = IN;
			break;
		case IN:
			if (*s.top())
			{
				if (!visited[s.top()]){ cout << (*s.top())->val << endl; visited[s.top()] = 1; }
				if (!visited[&((*s.top())->left)]){ current = PRE; break; }
				if (!visited[&((*s.top())->right)]){ current = POST; break; }
			}
			else
			{
				visited[s.top()] = 1;
				cout << '#' << endl;
			}
			s.pop();
			break;
		case POST:
			s.push(&((*s.top())->right));
			current = IN;
			break;
		}
	}
}

int maximum = 0;

int isBST(TreeNode* root)
{
	if (root)
	{
		if (root->left == NULL && root->right == NULL)
		{
			maximum = max(maximum, root->val);
			return root->val;
		}

		int left = isBST(root->left);
		int right = isBST(root->right);

		int res = false;

		if (left && right && (root->left ? left < root->val : true) && (root->right ? root->val < right : 1))
			res = true;

		int rv = root->val;
		if (root->left)
			root->val += root->left->val;
		if (root->right)
			root->val += root->right->val;
		

		if (res)
			maximum = max(maximum, root->val);

		return res * (root->left ? left : rv);
	}
	return 1;
}

int maxSumBST(TreeNode* root)
{
	isBST(root);
	return maximum;
}

TreeNode* addOneRow(TreeNode* root, int v, int d)
{
	queue<pair<TreeNode**, int>> q;
	int layer = 1;
	q.push({ &root, layer });

	while (!q.empty() && layer + 1 < d)
	{
		while (!q.empty() && layer == q.front().second)
		{
			TreeNode** r = q.front().first;
			if ((*r)->left)
				q.push({ &((*r)->left), layer + 1 });
			if ((*r)->right)
				q.push({ &((*r)->right), layer + 1 });
			q.pop();
		}
		layer = q.front().second;
	}

	while (!q.empty())
	{
		TreeNode** r = q.front().first;
		TreeNode* child = NULL;
		if ((*r)->left)
		{
			child = (*r)->left;
			(*r)->left = new TreeNode(1);
			(*r)->left->left = child;
		}

		if ((*r)->left)
		{
			child = (*r)->right;
			(*r)->right = new TreeNode(1);
			(*r)->right->right = child;
		}

		q.pop();
	}

	return root;
}

int rob(TreeNode* root)
{
	if (root == NULL)
		return 0;

	vector<int> val(2);
	int layer_cnt = 1, next_layer = 0, layer = 0;

	queue<TreeNode*> q;
	q.push(root);

	while (!q.empty())
	{
		while (layer_cnt--)
		{
			val[layer % 2] += q.front()->val;
			if (q.front()->left)
			{
				q.push(q.front()->left);
				next_layer++;
			}

			if (q.front()->right)
			{
				q.push(q.front()->right);
				next_layer++;
			}

			q.pop();
		}

		layer_cnt = next_layer;
		next_layer = 0;
		layer++;
	}

	return max(val[0], val[1]);
}

class Solution {
public:
	int parent = 0;
	int left = 0;
	int right = 0;

	int traverse(TreeNode* root, int x)
	{
		if (root)
		{
			int l = traverse(root->left, x);
			int r = traverse(root->right, x);

			if (root->val == x)
				left = l, right = r;

			return 1 + l + r;
		}
		return 0;
	}

	bool btreeGameWinningMove(TreeNode* root, int n, int x)
	{
		traverse(root, x);
		parent = n - left - right - 1;
		cout << left << ' ' << right << ' ' << parent << endl;
		return left > (parent + right) || right > (parent + left) || parent > (left + right);
	}
};

void swap(int* a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int *left_max = NULL;
int *right_min = NULL;
bool found = false;

pair<int*, int*> recover(TreeNode* root)
{
	pair<int*, int*> res = { NULL, NULL };
	if (root)
	{	
		pair<int*, int*> left = recover(root->left);
		if (left.second && (*left.second) > root->val)
			swap(left.second, &root->val);
		
		pair<int*, int*> right = recover(root->right);
		if (right.first && (*left.first) < root->val)
			swap(right.first, &root->val);
		
		res.first = left.first == NULL ? &root->val : left.first;
		res.second = right.second == NULL ? &root->val : right.second;
	}
	return res;
}

void recoverTree(TreeNode* root)
{
	recover(root);
}

int res = 0;
pair<int, int> zigzag(TreeNode* root)
{
	if (root)
	{
		pair<int, int> left = zigzag(root->left);
		pair<int, int> right = zigzag(root->right);
		res = max(res, max(left.first, left.second));
		res = max(res, max(right.first, right.second));
		cout << left << ' ' << right << endl;
		return { left.second + 1, right.first + 1 };
	}
	return { 0, 0 };
}

int longestZigZag(TreeNode* root)
{
	zigzag(root);
	return res - 1;
}

TreeNode* bstFromPreorder(vector<int>& preorder, int start, int end)
{
	if (start < end)
	{
		TreeNode* root = new TreeNode(preorder[start]);
		int idx = start + 1;
		while (idx < preorder.size() && preorder[start] > preorder[idx]) idx++;
		root->left = bstFromPreorder(preorder, start + 1, idx);
		root->right = bstFromPreorder(preorder, idx, end);
		return root;
	}
	return NULL;
}

TreeNode* bstFromPreorder(vector<int>& preorder)
{
	return  bstFromPreorder(preorder, 0, preorder.size());
}

bool isCousins(TreeNode* root, int x, int y)
{
	queue<pair<TreeNode*, TreeNode*>> q;
	q.push({ root, NULL });

	int cnt = 1, nxt = 0;
	TreeNode *p1 = NULL, *p2 = NULL;

	while (!q.empty())
	{
		nxt = 0;
		while (cnt--)
		{
			if (q.front().first->val == x)
				p1 = q.front().second;
			else if (q.front().first->val == y)
				p2 = q.front().second;


			if (q.front().first->left)
			{
				q.push({ q.front().first->left, q.front().first });
				nxt++;
			}

			if (q.front().first->right)
			{
				q.push({ q.front().first->right, q.front().first });
				nxt++;
			}

			q.pop();
		}

		cnt = nxt;
		if ((bool)p1 ^ (bool)p2)
			return false;
		else if (p1 != NULL && p2 != NULL)
			return p1 != p2;
	}

	return false;
}

//void count(TreeNode* root, vector<int>& cnt, int& res, int distance)
//{
//	if (root)
//	{
//		if (root->left == NULL && root->right == NULL)
//		{
//			cnt[1] = 1;
//			return;
//		}
//
//		vector<int> cpy = cnt;
//		count(root->left, cnt, res, distance);
//		count(root->right, cpy, res, distance);
//	
//		for (int i = 1; i <= distance; i++)
//			for(int j = 1; j <= i; j++)
//				res += cnt[j] * cpy[i - j];
//
//		for (int i = 1; i <= distance; i++)
//			cnt[i] += cpy[i];
//	
//		for (int i = distance; i >= 1; i--)
//			cnt[i] = cnt[i - 1];
//	}
//}
//
//int countPairs(TreeNode* root, int distance)
//{
//	if (distance < 2)
//		return 0;
//
//	vector<int> cnt(distance + 1);
//	int res = 0;
//	count(root, cnt, res, distance);
//	return res;
//}

void count(TreeNode* root, int*& cnt, int distance, int& res)
{
	if (root)
	{
		if (root->left == NULL && root->right == NULL)
		{
			cnt[1] = 1;
			return;
		}

		//vector<int> cpy = cnt;
		int* cpy = new int[distance + 1];
		memcpy(cpy, cnt, (distance + 1) * sizeof(int));

		count(root->left, cnt, distance, res);
		count(root->right, cpy, distance, res);

		for (int i = 1; i <= distance; i++)
			for (int j = 1; j <= i; j++)
				res += cnt[j] * cpy[i - j];

		for (int i = 1; i <= distance; i++)
			cnt[i] += cpy[i];

		for (int i = distance; i > 0; i--)
			cnt[i] = cnt[i - 1];

		delete[] cpy;
	}
}

int countPairs(TreeNode* root, int distance)
{
	if (distance < 2)
		return 0;

	int* cnt = new int[distance + 1];
	memset(cnt, 0, sizeof(int) * (distance + 1));
	//vector<int> cnt(distance + 1);
	int res = 0;
	count(root, cnt, distance, res);
	delete[] cnt;
	return res;
}

void dfs(TreeNode* root, int sum, vector<int>& nums, int start, int& res)
{
	if (root)
	{
		int val = root->val;
		
		dfs(root->right, sum, nums, nums.size(), res);
		dfs(root->left, sum, nums, nums.size(), res);

		for (int i = start; i < nums.size(); i++)
			res += (nums[i] += val) == sum;

		res += val == sum;
		nums.push_back(val);
	}
}

int pathSum(TreeNode* root, int sum)
{
	vector<int> nums;
	int res = 0;
	dfs(root, sum, nums, 0, res);
	return res;
}

bool check(vector<int>& nums, int level)
{
	int r = !(level % 2);
	if (nums.front() % 2 != r)
		return false;

	for (int i = 1; i < nums.size(); i++)
	{
		if (nums[i] % 2 != r)
			return false;

		if (level % 2 == 0 && nums[i - 1] >= nums[i])
			return false;

		if (level % 2 && nums[i - 1] <= nums[i])
			return false;
	}
	return true;
}

bool isEvenOddTree(TreeNode* root)
{
	queue<TreeNode*> q;
	q.push(root);
	int level = 0;
	while (!q.empty())
	{
		int sz = q.size();
		vector<int> layer;
		for (int i = 0; i < sz; i++)
		{
			layer.push_back(q.front()->val);
			if (q.front()->left)
				q.push(q.front()->left);
			if (q.front()->right)
				q.push(q.front()->right);
			q.pop();
		}

		if (!check(layer, level))
			return false;
		level++;
	}
	return true;
}

int main()
{
	//{ "4","5","3","null","null","null","2" }; //
	vector<string> nodes = { "1", "10", "4", "3", "null", "7", "9", "12", "8", "6", "null", "null", "2" };
	TreeNode* root = construct(nodes);
	cout << isEvenOddTree(root) << endl;
	return 0;
}