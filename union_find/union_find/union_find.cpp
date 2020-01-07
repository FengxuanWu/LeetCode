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

int find_vector(vector<string>& v, string val)
{
	for (int i = 0; i < v.size(); i++)
	if (val == v[i])
		return i;
	return -1;
}

string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) 
{
	map<string, string> parent;
	for (int i = 0; i < regions.size(); i++)
	{
		for (int j = 1; j < regions[i].size(); j++)
		{
			parent[regions[i][j]] = regions[i][0];
		}
	}
		
	vector<string> path(1, region1);
	while (parent.find(region1) != parent.end())
	{
		region1 = parent[region1];
		path.push_back(region1);
	}

	while (find_vector(path, region2) == -1)
	{
		region2 = parent[region2];
	}
	return region2;
}
