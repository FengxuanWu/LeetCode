// union_find.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "union_find.h"

int test(vector<int>& nums, vector<vector<int>>& link)
{
	vector<UnionFind<int>> sets;
	for (int i = 0; i < nums.size(); i++)
	{
		sets.push_back(UnionFind<int>(nums[i]));
	}

	for (int i = 0; i < link.size(); i++)
	{
		sets[link[i][0] - 1].merge(sets[link[i][1] - 1]);
		cout << "------------------------------------------------" << endl;
		cout << sets << endl;
	}

	cout << sets << endl;

	return 0;
}


int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps)
{
	vector<UnionFind<int>> sets(source.size());
	for (int i = 0; i < sets.size(); i++)
		sets[i] = UnionFind<int>(i);

	for (int i = 0; i < allowedSwaps.size(); i++)
	{
		int a = min(allowedSwaps[i][0], allowedSwaps[i][1]), b = max(allowedSwaps[i][0], allowedSwaps[i][1]);
		sets[a].merge(sets[b]);
	}
	
	unordered_map<int, vector<int>> idx;
	for (int i = 0; i < sets.size(); i++) {
		idx[sets[i].find().val].push_back(sets[i].val);
	}

	int res = 0;
	for (auto iter = idx.begin(); iter != idx.end(); iter++)
	{
		vector<int> a(iter->second.size()), b(iter->second.size());
		for (int i = 0; i < iter->second.size(); i++)
			a[i] = source[iter->second[i]], b[i] = target[iter->second[i]];
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		int i = 0, j = 0;
		while (i < a.size() && j < b.size())
		{
			if (a[i] == b[j])
				res++, i++, j++;
			else if (a[i] < b[j])
				i++;
			else
				j++;
		}
	}

	return source.size()-res;
}

int main()
{
	vector<vector<int>> swaps = {
		{0, 7},
		{3, 0},
	{4, 7},
	{3, 1},
	{8, 4},
	{5, 6},
	{2, 8},
	{1, 6},
	{3, 7},
	{2, 5},
	{8, 5},
	{2, 1},
	{6, 7},
	{5, 1},
	{3, 6},
	{4, 0},
	{7, 2},
	{2, 6},
	{4, 1},
	{3, 2},
	{8, 6},
	{8, 0},
	{5, 3},
	{1, 0},
	{4, 6},
	{8, 7},
	{5, 7},
	{3, 8},
	{6, 0},
	{8, 1},
	{7, 1},
	{5, 0},
	{4, 3},
	{0, 2},
	};

	vector<int> nums = { 18,67,10,36,17,62,38,78,52 };
	vector<int> nums2 = { 3,4,99,36,26,58,29,33,74 };
	cout << minimumHammingDistance(nums, nums2, swaps) << endl;
	return 0;
}