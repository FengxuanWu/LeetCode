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

bool isSymmetric(TreeNode* root)
{
	if (root == NULL)
		return true;

	queue<TreeNode*> q;
	q.push(root);
	vector<int> layer;
	int cnt = 1, next_cnt = 0;

	while (!q.empty())
	{
		while (cnt)
		{
			if (q.front()->left)
			{
				layer.push_back(q.front()->val);
				q.push(q.front()->left);
				next_cnt++;
			}
			else
			{
				layer.push_back(INT_MIN);
			}

			if (q.front()->right)
			{
				layer.push_back(q.front()->val);
				q.push(q.front()->right);
				next_cnt++;
			}
			else
			{
				layer.push_back(INT_MIN);
			}
		}

		cnt = next_cnt;
		next_cnt = 0;
		
		for (int i = 0, j = layer.size() - 1; i <= j; i++, j--)
		{
			if (layer[i] != layer[j])
				return false;
		}
	}
	return true;
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

int disstributionCoins(TreeNode* root)
{
	int res = 0;
	if (root)
	{
		if (root->left == NULL && root->right == NULL)
		{
			res = root->val - 1;
		}
		else
		{
			if (root->left)
			{
				res += disstributionCoins(root->left);
			}
			if (root->right)
			{
				res += disstributionCoins(root->right);
			}
			
			res += abs(root->val - 1);
		}	
	}
	return res;
}

//0 3 -1 -1 0 -1 -1

int main()
{
	TreeNode* root = NULL;
	root = construct(root);
	cout << disstributionCoins(root) << endl;
	return 0;
}