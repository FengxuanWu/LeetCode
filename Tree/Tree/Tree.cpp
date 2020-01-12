// Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include<hash_map>

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

int pathSumHelper(TreeNode* root, int sum)
{
	if (root)
	{	
		return (root->val == sum) + pathSumHelper(root->left, sum - root->val) + pathSumHelper(root->right, sum - root->val);
	}
	return 0;
}
//10 5 3 3 -1 -1 -2 -1 -1 2 -1 1 -1 -1 -3 -1 11 -1 -1
//1 -2 1 -10 -1 -1 -1 3 -1 -1 -3 -2 -1 -1 -1
//-8 6 -1 -1 8 8 -1 -1 2 -1 -2 -1 -1
int pathSum(TreeNode* root, int sum)
{
	if (root)
	{
		return pathSumHelper(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
	}
	
	return 0;
}

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



//1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 7 -1 -1
//1 2 -1 -1 3 -1 4 -1 -1
int main()
{
	vector<string> nodes = { "1", "2", "2", "3", "4", "4", "3" };
	TreeNode* root = construct(nodes);
	cout << root << endl;
	return 0;
}