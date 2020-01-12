// Array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Array.h"

int sub_rob(vector<int>& nums, int start, int end)
{
	int r = 0, nr = 0, pnr = 0;
	for (int i = start; i < end; i++)
	{
		nr = max(r, nr);
		r = pnr + nums[i];
		pnr = nr;
	}
	return max(r, nr);
}

int rob(vector<int>& nums)
{
	if (nums.size() == 0)
		return 0;
	if (nums.size() == 1)
		return nums[0];

	return max(sub_rob(nums, 0, nums.size() - 1), sub_rob(nums, 1, nums.size()));
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
{
	int res = 0;
	for (int i = 0; i < cost.size(); i++)
	{
		res += gas[i] -= cost[i];
	}

	if (res < 0)
		return -1;

	//cout << gas << endl;

	int max_in = 0, max_out = 0;
	for (int i = 0; i < gas.size() * 2; i++)
	{	
		max_out = max(max_in, max_out);
		if (max_in < 0)
		{
			max_in = gas[i % gas.size()] - cost[i % gas.size()];
			res = i % gas.size();
		}
		else
			max_in += gas[i % gas.size()];
		//cout << 'max in:  ' << max_in << '\t';
		//cout << 'max out: ' << max_out << endl;
	}

	return res;
}

int candy(vector<int>& ratings)
{
	if (ratings.size() == 0)
		return 0;
	if (ratings.size() == 1)
		return 1;

	vector<int> v;
	
	int len = 1;
	for (int i = 0; i < ratings.size() - 1; i++)
	{
		if (ratings[i] > ratings[i + 1])
			len++;
		else
		{
			v.push_back(len);
			len = 1;
		}		
	}
	v.push_back(len);

	int res = 0, acc = 0; len = 0;
	int flag = false;

	for (int i = 0; i < v.size(); i++)
	{
		int num = 0;
		if(len >= 1 && ratings[len] > ratings[len - 1])
		{
			acc++;
			num += acc + 1;
			if (num >= v[i])
			{ 
				num += (1 + v[i] - 1) * (v[i] - 1) / 2;
				if (v[i] != 1)
					acc = 0;
			}
			else
			{
				num = (1 + v[i]) * (v[i]) / 2;
				acc = 0;
			}
		}
		else
		{
			num += (1 + v[i]) * (v[i]) / 2;
			acc = 0;	
		}
	//	cout << num << endl;
		len += v[i];
		res += num;
	}

	return res;
}

vector<vector<int>> subsets(vector<int>& nums)
{
	vector<vector<int>> res;
	vector<int> vec(nums.size());
	res.push_back(vector<int>());
	bool flag = true;
	while (true)
	{
		flag = true;
		vector<int> r;
		int c = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i] = vec[i] ^ 1 ^ c;
			c = (vec[i] & 1) | (c &(vec[i] ^ 1));
		}
		
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i])
				r.push_back(nums[i]);
			flag &= vec[i];
		}

		//cout << r << endl;
		res.push_back(r);

		if (flag)
			break;
	}
	return res;
}

vector<vector<int>> subsetsWithDup(vector<int>& nums)
{
	vector<vector<int>> res;
	vector<int> vec(nums.size());
	res.push_back(vector<int>());
	bool flag = true;
	while (true)
	{
		flag = true;
		vector<int> r;
		int c = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i] = vec[i] ^ 1 ^ c;
			c = (vec[i] & 1) | (c &(vec[i] ^ 1));
		}

		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i])
				r.push_back(nums[i]);
			flag &= vec[i];
		}

		//cout << r << endl;
		res.push_back(r);

		if (flag)
			break;
	}
	return res;
}

void fill(vector<vector<char>>& board, int row, int col, char h)
{
	queue<pair<int,int>> q;
	q.push(make_pair(row, col));
	while (!q.empty())
	{
		row = q.front().first, col = q.front().second;
		board[row][col] = h;
		//up
		if (row - 1 >= 0 && board[row - 1][col] == 'O')
		{
			board[row - 1][col] = h;
			q.push(make_pair(row - 1, col));
		}
			
		//down
		if (row + 1 < board.size() && board[row + 1][col] == 'O')
		{
			board[row + 1][col] = h;
			q.push(make_pair(row + 1, col));
		}
		//left
		if (col - 1 >= 0 && board[row][col - 1] == 'O')
		{
			board[row][col - 1] = h;
			q.push(make_pair(row, col - 1));
		}
			
		//right
		if (col + 1 < board[0].size() && board[row][col + 1] == 'O')
		{
			board[row][col + 1] = h;
			q.push(make_pair(row, col + 1));
		}
			
		q.pop();
		//cout << q.size() << endl;
	}
}

void solve(vector<vector<char>>& board) 
{
	if (board.size() == 0)
		return;

	int row = board.size(), col = board[0].size();
	//row
	for (int i = 0; i < col; i++)
	{
		if (board[0][i] == 'O')
			fill(board, 0, i, 'h');
		if (board[row - 1][i] == 'O')
			fill(board, row - 1, i, 'h');
	}

	//cout << board << endl;
	//col
	for (int i = 0; i < row; i++)
	{
		if (board[i][0] == 'O')
			fill(board, i, 0, 'h');
		if (board[i][col - 1] == 'O')
			fill(board, i, col - 1, 'h');
	}
	//cout << board << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == 'O')
			{
				fill(board, i, j, 'X');
			}
		}
	}
	//cout << board << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == 'h')
				board[i][j] = 'O';
		}
	}
	//cout << board << endl;
}

vector<int> reach;
bool wordBreakHelper(string s, int start, vector<string>& worddict)
{
	if (start == s.size())
		return true;

	//cout << s.substr(start) << endl;

	for (int i = 0; i < worddict.size(); i++)
	{
		if (s.substr(start, worddict[i].size()) == worddict[i] && reach[start + worddict[i].size()] == 0)
		{
			reach[start + worddict[i].size()] = 1;
			if (wordBreakHelper(s, start + worddict[i].size(), worddict))
				return true;
		}
	}

	return false;
}

bool wordBreak(string s, vector<string>& wordDict)
{
	reach = vector<int>(s.size() + 1);
	return wordBreakHelper(s, 0, wordDict);
}

//int compareVersion(string version1, string version2) 
//{
//	version1.push_back('.');
//	version2.push_back('.');
//
//	if (version1.size() < version2.size())
//	{
//		for (int i = version1.size() - 1; i < version2.size(); i++)
//		{
//			if (version2[i] == '.')
//				version1.push_back('.');
//			else
//				version1.push_back('0');
//		}
//	}
//
//	if (version1.size() > version2.size())
//	{
//		for (int i = version2.size() - 1; i < version1.size(); i++)
//		{
//			if (version1[i] != '.')
//				version2.push_back('0');
//			else
//				version2.push_back('.');
//		}
//	}
//
//	vector<int> split1 = split(version1, '.');
//	vector<int> split2 = split(version2, '.');
//
//	int start1 = 0, start2 = 0;
//	int v1 = 0, v2 = 0;
//
//	for (int i = 0; i < split1.size(); i++)
//	{
//		v1 = atoi(version1.substr(start1, split1[i] - start1).c_str());
//		//cout << version1.substr(start1, split1[i] - start1).c_str() << endl;
//		v2 = atoi(version2.substr(start2, split2[i] - start2).c_str());
//		//cout << version2.substr(start2, split2[i] -start2).c_str() << endl;
//		start1 = split1[i] + 1, start2 = split2[i] + 1;
//		if (v1 < v2)
//			return -1;
//		if (v1 > v2)
//			return 1;
//	}
//
//	return 0;
//}

vector<vector<int>> cs2Helper(vector<int>& candidates, int start, int target)
{
	//cout << start << endl;
	vector<vector<int>> res;
	
	if (start >= candidates.size())
		return res;

	for (int i = start; i < candidates.size(); i++)
	{
		if (candidates[i] > target)
			continue;
		else
		{
			if (candidates[i] == target)
			{
				res.push_back(vector<int>(1, target));
				break;
			}
			else
			{
				vector<vector<int>> tmp = cs2Helper(candidates, i + 1, target - candidates[i]);
				if (!tmp.empty())
				{
					reverse(tmp.begin(), tmp.end());
					for (vector<vector<int>>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						(*it).push_back(candidates[i]);
						res.push_back(*it);
					}
				}
				//cout << res << endl;
			}
		}
	}
	return res;
}

bool equal(vector<int>& a, vector<int>& b)
{
	if (a.size() != b.size())
		return false;
	for (unsigned int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
			return false;
	}
	return true;
}

int find(vector<vector<int>>& a, vector<int> &b)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (equal(a[i], b))
			return i;
	}
	return -1;
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
	sort(candidates.begin(), candidates.end());
	vector<vector<int>> res;
	vector<vector<int>> tmp = cs2Helper(candidates, 0, target);
	//cout << tmp << endl<<endl;
	for (unsigned int i = 0; i < tmp.size(); i++)
	{
		if (find(res, tmp[i]) == -1)
			res.push_back(tmp[i]);
	}
	return res;
}


int maxSubArray(vector<int>& nums)
{
	if (nums.size() == 0)
		return 0;

	int max_n_contain = 0, max_contain = nums[0];
	for (int i = 0; i < nums.size(); i++)
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

//int maxProfit(vector<int>& prices)
//{
//	int res = 0;
//	if (prices.empty())
//		return res;
//
//	for (int i = 0; i < prices.size() - 1; i++)
//	{
//		prices[i] = prices[i + 1] - prices[i];
//	}
//
//	for (int i = 0; i < prices.size() - 1; i++)
//	{
//		res = max(res, maxSubArray(prices, 0, i) + maxSubArray(prices, i + 1, prices.size() - 1));
//	}
//	return res;
//}

int numTrees(int n)
{
	if (n == 0)
		return n;

	vector<int> nums(n + 1);
	nums[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			int left = j - 1;
			int right = i - j;
			nums[i] += nums[left] * nums[right];
		}
		cout << nums << endl;
	}

	return nums.back();
}

vector<string> parse_path(string path)
{
	vector<string> res;
	string s;
	int start = 0, end = 0;
	for (int i = 0; i < path.size(); i++)
	{
		while (i < path.size() && path[i] == '/') i++;
		start = i;
		while (i < path.size() && path[i] != '/') i++;
		end = i;

		s = path.substr(start, end - start);
		if (!s.empty() && s != ".")
			res.push_back(s);	
	}
	return res;
}

string simplifyPath(string path)
{
	string res = "/";
	vector<string> path_item = parse_path(path);
	vector<string> tmp;
	//cout << path_item << endl;
	for (int i = 0; i < path_item.size(); i++)
	{
		if (path_item[i] == "..")
		{
			if (!tmp.empty())
				tmp.pop_back();
		}		
		else
			tmp.push_back(path_item[i]);
	}

	for (int i = 0; i < tmp.size(); i++)
		res += tmp[i] + '/';
	if (res.size() != 1)
		res.pop_back();
	return res;
}

#define LEFT_TO_RIGHT 0
#define UP_TO_DOWN 1
#define RIGHT_TO_LEFT 2
#define DOWN_TO_UP 3

vector<vector<int>> generateMatrix(int n)
{
	vector<vector<int>> matrix(n, vector<int>(n));
	if (n == 0)
		return matrix;

	int hor = matrix[0].size(), ver = matrix.size();
	int row = 0, col = 0, last_col = 0, last_row = 0;
	int direction = 0;

	int val = 0;
	while (true)
	{
		switch (direction % 4)
		{
		case LEFT_TO_RIGHT:
			last_col = col;
			while (col - last_col < hor)
				matrix[row][col++] = ++val;
			col--;
			row++;
			ver--;
			direction++;
			break;
		case UP_TO_DOWN:
			last_row = row;
			while (row - last_row < ver)
				matrix[row++][col] = ++val;
			row--;
			col--;
			hor--;
			direction++;
			break;
		case RIGHT_TO_LEFT:
			last_col = col;
			while (last_col - col < hor)
				matrix[row][col--] = ++val;
			col++;
			row--;
			ver--;
			direction++;
			break;
		case DOWN_TO_UP:
			last_row = row;
			while (last_row - row < ver)
				matrix[row--][col] = ++val;
			col++;
			row++;
			hor--;
			direction++;
			break;
		}

		if (val == matrix[0].size() * matrix.size())
			break;

		/*cout << "row: " << row << " col: " << col << endl;
		cout << "ver: " << ver << " hor: " << hor << endl;*/
	}
	return matrix;
}

vector<int> spiralOrder(vector<vector<int>> matrix)
{
	vector<int> res;
	if (matrix.empty())
		return res;
	
	int hor = matrix[0].size(), ver = matrix.size();
	int row = 0, col = 0, last_col = 0, last_row = 0;
	int direction = 0;
	while (true)
	{
		switch (direction % 4)
		{
		case LEFT_TO_RIGHT:
			last_col = col;
			while (col - last_col < hor)
				res.push_back(matrix[row][col++]);
			col--;
			row++;
			ver--;
			direction++;
			break;
		case UP_TO_DOWN:
			last_row = row;
			while (row - last_row < ver)
				res.push_back(matrix[row++][col]);
			row--;
			col--;
			hor--;
			direction++;
			break;
		case RIGHT_TO_LEFT:
			last_col = col;
			while (last_col - col < hor)
				res.push_back(matrix[row][col--]);
			col++;
			row--;
			ver--;
			direction++;
			break;
		case DOWN_TO_UP:
			last_row = row;
			while (last_row - row < ver)
				res.push_back(matrix[row--][col]);
			col++;
			row++;
			hor--;
			direction++;
			break;
		}

		if (res.size() == matrix[0].size() * matrix.size())
			break;

		/*cout << "row: " << row << " col: " << col << endl;
		cout << "ver: " << ver << " hor: " << hor << endl;*/
	}
	return res;
}

vector<vector<int>> combine_helper(vector<int> nums, int start, int k)
{
	vector<vector<int>> res;
	if (k == 1)
	{
		for (int i = start; i < nums.size(); i++)
		{
			res.push_back(vector<int>());
			res.back().push_back(nums[i]);
		}
	}
	else
	{
		for (int i = start; i < nums.size() - k + 1; i++)
		{
			vector<vector<int>> tmp = combine_helper(nums, i + 1, k - 1);
			for (int j = 0; j < tmp.size(); j++)
			{
				tmp[j].push_back(nums[i]);
				res.push_back(tmp[j]);
			}			
		}
	}
	return res;
}

vector<vector<int>> combine(int n, int k)
{
	vector<int> nums;
	for (int i = 0; i < n; i++)
		nums.emplace_back(i + 1);
	return combine_helper(nums, 0, k);
}
//#define LEFT(row, col)(board[row][col - 1])
//#define RIGHT(row, col)(board[row][col + 1])
//#define UP(row, col)(board[row - 1][col])
//#define DOWN(row, col)(board[row + 1][col])
//
//#define move_right 0
//#define move_left 1
//#define move_up 2
//#define move_down 3
//
//bool word_search(vector<vector<char>> board, int row, int col, string word, int index)
//{
//	//cout << board << endl;
//	board[row][col] = '#';
//	if (index == word.size())
//		return true;
//
//	//left
//	if (col > 0 && LEFT(row, col) == word[index])
//	{
//		//LEFT(row, col) = '#';
//		if (word_search(board, row, col - 1, word, index + 1))
//			return true;
//		//cout << board << endl;
//	}
//
//	//right
//	if (col + 1 < board[0].size() && RIGHT(row, col) == word[index])
//	{
//		//RIGHT(row, col) = '#';
//		if (word_search(board, row, col + 1, word, index + 1))
//			return true;
//		//cout << board << endl;
//	}
//
//	//down
//	if (row + 1 < board.size() && DOWN(row, col) == word[index])
//	{
//		//DOWN(row, col) = '#';
//		if (word_search(board, row + 1, col, word, index + 1))
//			return true;
//		//cout << board << endl;
//	}
//
//	//up
//	if (row > 0 && UP(row, col) == word[index])
//	{
//		//UP(row, col) = '#';
//		if (word_search(board, row - 1, col, word, index + 1))
//			return true;
//		//cout << board << endl;
//	}
//
//	return false;
//}
//
//bool exist(vector<vector<char>>& board, string word) 
//{
//	if (word.empty())
//		return true;
//
//	for (int i = 0; i < board.size(); i++)
//	{
//		for (int j = 0; j < board[0].size(); j++)
//		{
//			if (board[i][j] == word[0])
//			{
//				if (word_search(board, i, j, word, 1))
//				{
//					return true;
//				}				
//			}
//			
//		}
//	}
//	return false;
//}

vector<vector<int>> permute_help(vector<int>& nums, vector<int> used, int n)
{	
	vector<vector<int>> res;

	if (n == nums.size())
		return vector<vector<int>>(1, vector<int>());

	for (int i = 0; i < nums.size(); i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			vector<vector<int>> tmp = permute_help(nums, used, n + 1);

			for (int j = 0; j < tmp.size(); j++)
			{
				tmp[j].push_back(nums[i]);
				res.push_back(tmp[j]);
			}

			used[i] = 0;
		}
	}
	return res;
}

vector<vector<int>> permute(vector<int>& nums)
{
	return permute_help(nums, vector<int>(nums.size()), 0);
}

vector<int> toVector(int n)
{
	vector<int> res;
	if (n == 0)
		res.push_back(0);
	else while (n)
	{
		res.push_back(n % 10);
		n = n / 10;
	}

	for (int i = 0; i < res.size() - i - 1; i++)
		swap(res[i], res[res.size() - i - 1]);

	return res;
}

bool cmp(int a, int b)
{
	if (a == b)
		return false;

	vector<int> dig_a = toVector(a), dig_b = toVector(b);

	int index_a = 0, index_b = 0;
	
	while (index_a < min(dig_a.size(), dig_b.size()))
	{
		if (dig_a[index_a] < dig_b[index_b])
			return false;
		if (dig_a[index_a] > dig_b[index_b])
			return true;
		index_a++;
		index_b++;
	}

	bool res = false;
	//824 8249
	if (dig_a.size() < dig_b.size())
	{
		index_a = 0;
		while (index_a < dig_b.size())
		{
			if (dig_b[index_a] > dig_b[index_b % dig_b.size()])
			{
				res = true;
				break;
			}
			else if (dig_b[index_a] < dig_b[index_b % dig_b.size()])
			{
				res = false;
				break;
			}
			index_a++;
			index_b++;
		}

	}
	//8247 824
	//8247 824
	//824 8248
	else if (dig_b.size() < dig_a.size())
	{
		index_b = 0;

		while (index_b < dig_a.size())
		{
			if (dig_a[index_b] > dig_a[index_a % dig_a.size()])
			{
				res = false;
				break;
			}
			else if (dig_a[index_b] < dig_a[index_a % dig_a.size()])
			{
				res = true;
				break;
			}
			index_a++;
			index_b++;
		}
		
	}

	return res;
}

string toString(int a)
{
	string s;
	if (a == 0)
		s.push_back('0');
	else while (a)
	{
		s.push_back(a % 10 + '0');
		a = a / 10;
	}

	for (int i = 0; i < s.size() - i - 1; i++)
	{
		swap(s[i], s[s.size() - i - 1]);
	}
	return s;
}

string largestNumber(vector<int>& nums) 
{
	sort(nums.begin(), nums.end(), cmp);
	cout << nums << endl;
	if (!nums.empty() && nums.front() == 0)
		return "0";
	string s;
	for (int i = 0; i < nums.size(); i++)
		s += toString(nums[i]);
	return s;
}

#define LEFT(row, col)(board[row][col - 1])
#define RIGHT(row, col)(board[row][col + 1])
#define UP(row, col)(board[row - 1][col])
#define DOWN(row, col)(board[row + 1][col])
void fill_in(vector<vector<int>>& board, int row, int col)
{
	board[row][col] = 0;
	if (col + 1 < board[0].size() && RIGHT(row, col) == 1)
		fill_in(board, row, col + 1);
	if (col - 1 >= 0 && LEFT(row, col) == 1)
		fill_in(board, row, col - 1);
	if (row + 1 < board.size() && DOWN(row, col) == 1)
		fill_in(board, row + 1, col);
	if (row - 1 >= 0 && UP(row, col) == 1)
		fill_in(board, row - 1, col);
}

int numIslands(vector<vector<int>>& board)
{
	int res = 0;
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			if (board[i][j] == 1)
			{
				res++;
				fill_in(board, i, j);
				cout << board << endl;
			}
		}
	}
	return res;
}

void toBin(unsigned int n)
{
	if (n)
	{
		toBin(n / 2);
	}
	if (n)
		cout << n % 2;
}

#define FIRST_BIT(num, n, size)(num & (((1 << size) - 1) ^ ((1 << (size - n)) - 1)))
#define LAST_BIT(num, n)(num & ((1 <<(n + 1)) - 1))


int rangeBitwiseAnd(int m, int n)
{
	int res = 0;
	for (int i = 31; i >= 0; i--)
	{
		if ((m & (1 << i)) == (n & (1 << i)))
			res |= (m & (1 << i));
		else
			break;
	}
	return res;
}

vector<string> summaryRanges(vector<int>& nums)
{
	vector<string> res;

	if (nums.empty())
		return res;

	int start = nums[0], end = start;
	for (int i = 0; i < nums.size() - 1; i++)
	{
		if (nums[i] + 1 == nums[i + 1])
		{
			end++;
		}
		else
		{
			if (start == end)
				res.push_back(string(to_string(start)));
			else
			{
				res.push_back(string(to_string(start)) + "->" + string(to_string(end)));
			}
			start = end = nums[i + 1];
		}
	}

	if (start == end)
		res.push_back(string(to_string(start)));
	else
	{
		res.push_back(string(to_string(start)) + "->" + string(to_string(end)));
	}

	return res;
}

string operator*(string s, int n)
{
	string res = "";
	for (int i = 0; i < n; i++)
		res += s;
	return res;
}

string part_reverse(string s, int n)
{
	for (int i = 0; i < n - i; i++)
	{
		swap(s[i], s[n - i - 1]);
	}
	//cout << s << endl;
	for (int i = n; i <= s.size() - i; i++)
	{
		swap(s[i], s[s.size() - i - 1 + n]);
	}
	//cout << s << endl;
	for (int i = 0; i < s.size() - i; i++){
		swap(s[i], s[s.size() - i - 1]);
	}
	return s;
}

int findKthLargest(vector<int>& nums, int k) 
{
	priority_queue<int, vector<int>, greater<int>> q;

	for (int i = 0; i < nums.size(); i++)
	{
		if (q.size() < k)
			q.push(nums[i]);
		else
		{
			q.push(nums[i]);
			q.pop();
		}
	}
	return q.top();
}


string getHint(string secret, string guess)
{
	vector<int> digits(10);
	int bull = 0, cow = 0;
	for (int i = 0; i < secret.size(); i++)
	{
		if (secret[i] == guess[i])
		{
			guess[i] = '$';
			bull++;
		}
		else
			digits[TO_DIGIT(secret[i])]++;
	}

	for (int i = 0; i < guess.size(); i++)
	{
		if (guess[i] != '$')
		{
			if (digits[TO_DIGIT(guess[i])])
			{
				cow++;

				if (digits[TO_DIGIT(guess[i])])
					digits[TO_DIGIT(guess[i])]--;
			}
		}		
	}

	return to_string(bull) + 'A' + to_string(cow) + 'B';
}

// 1 2 3 4 4 4 4 4
// 0 1 2 3 4 5 6 7
int search_left(vector<int>& nums, int start, int end, int target)
{
	int index = (start + end) / 2;
	while (start != end - 1)
	{
		if (nums[index] == target)
			end = index;
		else if (nums[index] < target)
			start = index;
		index = (start + end) / 2;
	}
	return nums[index] == target ? index : end;
}


int search_right(vector<int>& nums, int start, int end, int target)
{
	int index = (start + end) / 2;
	while (start != end - 1)
	{
		if (nums[index] == target)
			start = index;
		else if (nums[index] > target)
			end = index;
		index = (start + end) / 2;
	}
	return nums[index] == target ? index : start;
}

int search(vector<int>& nums, int target)
{
	int start = 0, end = nums.size(), index = start + (end - start) / 2;

	while (start != end - 1)
	{
		if (nums[index] == target)
			break;
		else if (nums[index] > target)
			end = index;
		else if (nums[index] < target)
			start = index;

		index = start + (end - start) / 2;
	}

	return nums[index] == target ? index : -1;
}

vector<int> searchRange(vector<int>& nums, int target)
{
	if (nums.size() == 0)
		return vector<int>({ -1, -1 });

	int idx = search(nums, target);
	if (idx == -1)
		return vector<int>({ -1, -1 });
	else
	{
		int start = idx, end = idx;
		start = search_left(nums, 0, idx + 1, target);
		end = search_right(nums, idx, nums.size(), target);
		return vector<int>({ start, end });
	}
}

#ifndef TO_DIGIT
	#define TO_DIGIT(c)(c - '0') 
#endif
string multiple_digit(string num, char c)
{
	if (c == '0')
		return "0";

	string res = "";
	int carry = 0, product = 0;
	
	for (int i = num.size() - 1; i >= 0; i--)
	{
		product = TO_DIGIT(num[i]) * TO_DIGIT(c) + carry;
		res.push_back(product % 10 + '0');
		carry = product / 10;
	}

	if (carry)
		res.push_back(carry + '0');

	return res;
}

string num_add(string num1, string num2)
{
	if(num1.size() < num2.size())
		swap(num1, num2);

	int index = 0;
	string  res;
	int sum = 0, carry = 0;
	while (index < num1.size())
	{
		sum = index < num2.size() ? (TO_DIGIT(num1[index]) + TO_DIGIT(num2[index]) + carry) : (TO_DIGIT(num1[index]) + carry);
		res.push_back(sum % 10 + '0');
		carry = sum / 10;
		index++;
	}

	if (carry)
		res.push_back('1');
	
	return res;
}

string multiply(string num1, string num2) 
{
	string  res, tmp;
	for (int i = num2.size() - 1; i >= 0; i--)
	{
		tmp = multiple_digit(num1, num2[i]);
		if (tmp != "0")
			for (int j = 0; j < num2.size() - 1 - i; j++)
				tmp.insert(tmp.begin(), '0');
		res = num_add(tmp, res);

		/*cout << tmp << endl;
		cout << res << endl << endl;;*/
	} 

	for (int i = 0; i <(int(res.size() - 1 - i)); i++)
	{
		swap(res[i], res[res.size() - i - 1]);
	}
	return res;
}

vector<string> ip_helper(string s, int start, int segments)
{
	vector<string> res;
	if (segments == 0)
	{
		switch (s.size() - start)
		{
		case 1:
			res = vector<string>({ s.substr(start, s.size() - start) });
			break;
		case 2:
			if (10 <= stoi(s.substr(start, 2)) && 99 >= stoi(s.substr(start, 2)))
				res = vector<string>({ s.substr(start, s.size() - start) });	
			break;
		case 3:
			if (100 <= stoi(s.substr(start, 3)) && 255 >= stoi(s.substr(start, 3)))
				res = vector<string>({ s.substr(start, s.size() - start) });
			break;
		}
		
		return res;
	}
	else
	{	
		vector<string> tmp;
		for (int i = 1; i <= 3; i++)
		{
			if (start + i < s.size())
			{
				if (i == 1 || (i == 2 && 10 <= stoi(s.substr(start, i)) && 99 >= stoi(s.substr(start, i))) || (i == 3 && 100 <= stoi(s.substr(start, i)) && 255 >= stoi(s.substr(start, i))))
					tmp = ip_helper(s, start + i, segments - 1);

				if (!tmp.empty())
					for (auto str : tmp)
						res.push_back(s.substr(start, i) + '.' + str);

				tmp.clear();
			}
		}
		return res;
	}
}

vector<string> restoreIpAddresses(string s)
{
	return ip_helper(s, 0, 3);
}

bool isPowerOfFour(int num)
{
	if (num <= 0)
		return false;

	while (num)
	{
		if (num & 1)
			return false;
		num >>= 1;
		if (num == 0 || num & 1)
			return false;

		num >>= 1;
		if (num == 1)
			return true;
	}

	return true;
}

bool isMonotonic(vector<int>& A)
{
	if (A.size() == 0 || A.size() == 1 || A.size() == 2)
		return true;
	else
	{
		int idx = 1;
		while (idx < A.size() && A[idx - 1] == A[idx])
			idx++;

		if (idx == A.size())
			return true;

		bool sign = A[idx - 1] > A[idx];
		idx++;
		while (idx < A.size())
		{
			if (A[idx - 1] == A[idx] || sign == A[idx - 1] > A[idx])
			{
				idx++;
				continue;
			}
			else
				return false;
			idx++;
		}
		return true;
	}
}

void replaceSpace(char *&str, int length)
{
	string s;
	while (*str)
	{
		if (*str != ' ')
			s.push_back(*str);
		else
			s += "%20";
		str++;
	}
	
	str = new char[s.size() + 1];
	char* tmp = str;
	const char* source = s.c_str();
	int i = 0;
	while (*str++ = *(source + i++));	
	str = tmp;
}

bool validUtf8(vector<int>& data)
{
	int index = 0, byte_cnt = -1;
	int wchar = 0;
	size_t buffer_size = data.size();

	if (data[index] >> 6 == 0x1)
	{
		wchar |= data[index];
		byte_cnt = 1;
	}
	else if (data[index] >> 5 == 0x6)
	{
		wchar |= data[index] & 0x1F;
		byte_cnt = 2;
	}

	else if (data[index] >> 4 == 0xe)
	{
		wchar |= data[index] & 0xF;
		byte_cnt = 3;
	}

	else if (data[index] >> 3 == 0x1e)
	{
		wchar |= data[index] & 0x7;
		byte_cnt = 4;
	}
	else if (data[index] >> 2 == 0x3e)
	{
		wchar |= data[index] & 0x3;
		byte_cnt = 5;
	}

	else if (data[index] >> 1 == 0x7e)
	{
		wchar |= data[index] & 0x1;
		byte_cnt = 6;
	}

	index++;

	while (index < byte_cnt)
	{
		if (index == buffer_size)
			return false;
		if (data[index] >> 6 == 0x2)
		{
			wchar <<= 6;
			wchar |= data[index] & 0x3f;
			index++;
		}
		else
		{
			wchar = 0;
			return false;
		}
	}

	bool res = true;
	switch (byte_cnt)
	{
	case 1:
		res &= (0x0 <= wchar && wchar >= 0x7F);
		break;
	case 2:
		res &= (0x80 <= wchar  && wchar >= 0x7FF);
		break;
	case 3:
		res &= (0x800 <= wchar && wchar >= 0xFFFF);
		break;
	case 4:
		res &= (0x10000 <= wchar && wchar >= 0x1FFFFF);
		break;
	case 5:
		res &= (0x200000 <= wchar && wchar >= 0x3FFFFFF);
		break;
	case 6:
		res &= (0x4000000 <= wchar && wchar >= 0x7FFFFFFF);
		break;
	default:
		res = false;
	}
	return res;
}

int arr[100000] = {};
bool duplicate(int numbers[], int length, int* duplication)
{
	int* bar_chart = new int[length];
	memset(bar_chart, 0, length * sizeof(int));
	int index = 0;
	for (int i = 0; i < length; i++)
	{
		bar_chart[numbers[i]]++;
		//cout << bar_chart[numbers[i]] << endl;
		if (bar_chart[numbers[i]] > 1)
			duplication[index++] = numbers[i];
	}
	
	delete bar_chart;
	if (index == 0)
		return false;
	return true;
}

vector<int> multiply(const vector<int>& a)
{
	vector<int> res(a.size(), 1);
	int product_l = 1, product_r = 1;
	for (int i = 1; i < a.size(); i++)
	{
		product_l *= a[i - 1];
		res[i] *= product_l;
		
		product_r *= a[a.size() - i];
		res[a.size() - i - 1] *= product_r;
	}
	return res;
}

int  NumberOf1(int n)
{
	unsigned int num = *((unsigned int*)&n);
	int res = 0;
	while (num)
	{
		res += num & 1;
		num >>= 1;
	}
	return res;
}

bool IsPopOrder(vector<int> pushV, vector<int> popV)
{
	int idx_pop = 0;
	if (pushV.size() != popV.size())
		return false;

	bool res = true;
	stack<int> s;
	for (int i = 0; i < pushV.size(); i++)
	{
		s.push(pushV[i]);
		while (!s.empty() && s.top() == popV[idx_pop])
		{
			s.pop();
			idx_pop++;
		}
	}
	return idx_pop == popV.size();
}

int Fibonacci(int n)
{
	if (n == 0 || n == 1)
		return n;
	int n_1 = 1, n_2 = 0, res = 0;
	for (int i = 1; i < n; i++)
	{
		res = n_1 + n_2;
		n_2 = n_1;
		n_1 = res;
	}
	return res;
}

#define get_bit(n,pos)((n & (1<<pos)) != 0)
#define last_bit(data) (get_bit(data, 0))

int reverse_int(int num)
{
	int res = num, bit_cnt = 0;
	while (res)
	{
		res >>= 1;
		bit_cnt++;
	}

	for (int i = 0; i < bit_cnt; i++)
		res |= (get_bit(num, bit_cnt - i - 1) << i);

	return res;
}

int Add(int a, int b)
{
	int res = 0, carry = 0;
	for (int i = 0; i < sizeof(int)* 8; i++)
	{
		res |= ((get_bit(a, i) ^ get_bit(b, i) ^ carry) << i);
		carry = (get_bit(a, i) & get_bit(b, i) || get_bit(a, i) & carry || get_bit(b, i) & carry);
	}
	return res;
}

////a is longer than b
//int equals_to(string a, string b)
//{
//	size_t idx = 0;
//	while (idx < a.size() && idx < b.size())
//		idx++;
//	return idx == b.size() ? b.size() : 0;
//}
//
//vector<int> splitIntoFibonacci(string s, int start, vector<int> tmp)
//{
//	if (start == s.size())
//		return tmp;
//
//	vector<int> res;
//	for (int i = 0; i < s.size(); i++)
//	{
//		if (atoi())
//	}
//
//	return res;
//}
//
//vector<int> splitIntoFibonacci(string s) 
//{
//		
//}

vector<int> dailyTemperatures(vector<int>& t)
{
	vector<int> res(t.size());
	
	if (t.empty())
		return res;

	stack<int> idx;
	idx.push(0);

	for (int i = 0; i < t.size(); i++)
	{
		while (!idx.empty() && t[i] > t[idx.top()])
		{
			res[idx.top()] = i - idx.top();
			idx.pop();
		}

		if (idx.empty() || t[i] <= t[idx.top()])
			idx.push(i);

		cout << res << endl;
	}

	return res;
}


string decodeString(string s)
{
	stack<int> digits;
	string sub_str;
	string num;

	for (int i = 0; i < s.size(); i++)
	{
		//cout << sub_str << endl;
		if (IS_DIGIT(s[i]))
		{
			num.push_back(s[i]);
		}
		else if (s[i] != ']')
		{
			if (!num.empty())
			{
				digits.push(atoi(num.c_str()));
				num.clear();
			}
			
			sub_str.push_back(s[i]);
		}
		else
		{
			string str = "";
			int idx = sub_str.size() - 1;
			int length = sub_str.size();

			while (idx >= 0 && sub_str[idx] != '[')
			{
		//		cout << sub_str[idx] << endl;
				idx--;
				str.insert(str.begin(), sub_str.back());
				sub_str.pop_back();
			}

			sub_str.pop_back();

	//		cout << str << endl;

			for (int i = 0; i < digits.top(); i++)
				sub_str += str;
			digits.pop();
		}
	}

	return sub_str;
}

bool isPalindrome(int n) 
{
	string num = to_string(n);
	int i = 0, j = num.size() - 1;
	while (i < j && num[i] == num[j])i++, j--;
	return i == j || i == j + 1;
}

//vector<int> majorityElement(vector<int>& nums)
//{
//	pair<int, int> majority1, majority2;
//
//	for (int i = 0; i < nums.size(); i++)
//	{
//		if ((majority1.second == 0 || majority1.first == nums[i]) && majority2.first != nums[i])
//		{
//			if (majority1.second == 0)
//			{
//				majority1.first = nums[i];
//			}
//			majority1.second += majority1.first == nums[i];
//		}
//		else if (majority2.second == 0 || majority2.first == nums[i])
//		{
//			if (majority2.second == 0)
//				majority2.first = nums[i];
//			majority2.second += majority2.first == nums[i];
//		}
//		else
//		{
//			majority1.second--;
//			majority2.second--;
//		}
//
//		cout << "m1\t" << majority1 << endl;
//		cout << "m2\t" << majority2 << endl;
//		cout << endl;
//	}
//	
//	majority1.second = majority2.second = 0;
//	//cout << majority1.first << endl;
//	//cout << majority2.first << endl;
//
//	for (int i = 0; i < nums.size(); i++)
//	{
//		if (nums[i] == majority1.first)
//			majority1.second++;
//		if (nums[i] == majority2.first && majority1.first != majority2.first)
//			majority2.second++;
//	}
//
//	vector<int> res;
//	if (majority1.second > nums.size() / 3)
//		res.push_back(majority1.first);
//	if (majority2.second > nums.size() / 3)
//		res.push_back(majority2.first);
//	return res;
//}

bool find132pattern(vector<int>& nums)
{
	bool res = false;
	if (nums.size() < 3)
		return res;

	vector<int> minimum(nums.size());
	minimum[0] = nums[0];
	int min = minimum[0];

	for (int i = 1; i < nums.size(); i++)
	{
		if (nums[i] < min)
			min = nums[i];
		minimum[i] = min;
	}
	
	//cout << minimum << endl;

	vector<int> s;
	int i = nums.size() - 1;
	while (i >= 0)
	{
		if (nums[i] > minimum[i])
		{
			while (!s.empty() && s.back() <= minimum[i])
			{
				s.pop_back();
				//cout << "reached here" << endl;
			}

			if (s.empty() || s.back() > nums[i])
				s.push_back(nums[i]);

			else if (nums[i] > s.back())
			{
				res = true;
				break;
			}
		}
		//cout << s << endl;
		i--;
	}
	return res;
}

vector<int> cal_idx(int total_row, int size)
{
	vector<int> res;
	int start = 0, step = (total_row - 1) << 1;
	for (int curr_row = 0; curr_row < total_row; curr_row++)
	{
		start = 0;
		while (start < size)
		{
			if (start + curr_row < size)
				res.push_back(start + curr_row);
			int offset = step - curr_row;
			if (offset < step && start + offset < size && res.back() != start + offset)
				res.push_back(start + step - curr_row);
			start += step;
		}
	}
	
	//cout << res << endl;
	return res;
}

string convert(string s, int row)	
{
	if (row == 1)
		return s;
	string res;
	
	vector<int> indices = cal_idx(row, s.size());
	for (auto e : indices)
		res.push_back(s[e]);

	return res;
}

void nextPermutation(vector<int>& nums)
{
	if (nums.size() < 2)
		return;

	for (int i = nums.size() - 1; i > 0; i--)
	{
		if (nums[i] > nums[i - 1])
		{
			for (int j = nums.size() - 1; j >= i; j--)
			{
				if (nums[i - 1] < nums[j])
				{
					swap(nums[i - 1], nums[j]);
					sort(nums.begin() + i, nums.end());
					return;
				}
			}
		}
	}
	sort(nums.begin(), nums.end());
	return;
}

vector<string> generate_help(int n, int curr_idx, int left)
{
	if (curr_idx == (n << 1) - 1)
	{
		vector<string> res(1, string(n << 1, ' '));
		res.back().back() = ')';
		return res;
	}

	int right = curr_idx - left;
	
	vector<string> res;
	if (left < n)
	{
		for (string& str : generate_help(n, curr_idx + 1, left + 1))
		{
			str[curr_idx] = '(';
			res.push_back(str);
		}
	}

	if (right < left)
	{
		for (string& str : generate_help(n, curr_idx + 1, left))
		{
			str[curr_idx] = ')';
			res.push_back(str);
		}
			
	}

	return res;
}

vector<string> generateParenthesis(int n)
{
	return generate_help(n, 0, 0);
}

//int minFallingPathSum(vector<vector<int>>& maze) 
//{
//	if (maze.size() == 0)
//		return 0;
//
//	for (int i = 1; i < maze.size(); i++)
//	{
//		for (int j = 0; j < maze[0].size(); j++)
//		{
//			int minimum = maze[i - 1][j];
//			if (j > 0)
//				minimum = min(maze[i - 1][j - 1], minimum);
//			if (j < maze[0].size() - 1)
//				minimum = min(maze[i - 1][j + 1], minimum);
//			maze[i][j] += minimum;
//		}
//	}
//
//	cout << maze << endl;
//
//	int res = INT_MAX;
//	for (int i = 0; i < maze.back().size(); i++)
//		res = min(maze.back()[i], res);
//	return res;
//}

int minPathSum(vector<vector<int>>& grid) 
{
	if (grid.size() == 0)
		return 0;

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			int minimum = INT_MAX;
			if (i == 0 && j == 0)
				continue;
			if (i > 0)
				minimum = min(grid[i - 1][j], minimum);
			if (j > 0)
				minimum = min(grid[i][j - 1], minimum);
			grid[i][j] += minimum;
		}
	}

	return grid.back().back();
}

bool detect_ring(vector<vector<int>>& graph, int curr, vector<int> visited, vector<int>& passed)
{
	//cout << "current course: " << curr << endl;

	bool res = false;
	if (visited[curr])
		return true;
	visited[curr] = true;
	for (int i = 0; i < graph[curr].size(); i++)
	{
		int node = graph[curr][i];
		if (passed[node])
			continue;

		if (visited[node])
		{
			res = true;
			goto ret;
		}
		
		if (detect_ring(graph, node, visited, passed))
		{
			res = true;
			goto ret;
		}
	}
	passed[curr] = true;
ret:	
	return res;
}

bool canFinish(int n, vector<vector<int>> prerequisites)
{
	bool res = false;
	vector<vector<int>> courses(n, vector<int>());

	for (int i = 0; i < prerequisites.size(); i++)
	{
		int row = prerequisites[i][0], col = prerequisites[i][1];
		courses[row].push_back(col);
	}
	//cout << courses << endl;

	vector<int> passed(n);
	for (int i = 0; i < n; i++)
	{
		if (!passed[i] && detect_ring(courses, i, vector<int>(n), passed))
		{
			res = true;
			break;
		}
	}

	return !res;
}

int substitute_string(string s, int m)
{
	vector<int> reach(26, -1);
	vector<int> count(26, 0);
	for (int i = 0; i < s.size(); i++)
	{
		for (int j = 0; j < reach.size(); j++)
		{
			if (to_digit(s[i]) == j)
			{
				reach[j] += (reach[j] + 1 == i);
			}
			else if (reach[j] < i)
			{
				reach[j] += m;
				count[j] ++;
			}
		}
		cout << "reach: " << reach << endl;
		cout << "count: " << count << endl;
		cout << endl;
	}

	int res = INT_MAX;
	for (int i = 0; i < count.size(); i++)
	if (reach[i] != -1)
		res = min(res, count[i]);
	return res;
}

int climbStairs(int n)
{
	if (n < 3)
		return n;

	int n_1 = 1, n_2 = 2, res = 0;
	int curr = 3;

	while (curr <= n)
	{
		res = n_1 + n_2;
		n_1 = n_2;
		n_2 = res;
		
		curr++;
	}
	return res;
}

#define DEBUG 1
int mctFromLeafValues(vector<int>& arr)
{
	if (arr.size() == 0)
		return 0;
	if (arr.size() == 1)
		return arr.back();
	if (arr.size() == 2)
		return arr[0] * arr[1];
	
	bool decrease = arr[0] > arr[1];
	int current_tree = arr[0] * arr[1];
	int max_idx = arr[0] > arr[1] ? 0 : 1;
	
	vector<int> peak_idx;
	if (max_idx == 0)
		peak_idx.push_back(max_idx);

	for (int i = 2; i < arr.size(); i++)
	{	//5 4
		if (arr[i] < arr[i - 1])
		{
			peak_idx.push_back(i - 1);
			current_tree += arr[i] * arr[i - 1];
		}//4 5
		else
		{
			if (peak_idx.empty())
				current_tree += arr[i] * arr[i - 1];
			else
			{
				if (arr[i] < arr[peak_idx.back()])
				{
					current_tree += (arr[i] - arr[i - 1]) * arr[peak_idx.back()] + arr[i] * arr[i - 1];
				}
				else
				{
					int last_peak = 0;
					while (!peak_idx.empty() && arr[peak_idx.back()] <= arr[i])
					{
						last_peak = peak_idx.back();
						peak_idx.pop_back();
					}
					if (!peak_idx.empty())
						current_tree += arr[i] * arr[last_peak] + (arr[i] - arr[last_peak]) * arr[peak_idx.back()];
					else
					{
						current_tree += arr[i] * arr[last_peak];
					}
				}
			}
		}
		cout << "peak_idx: " << peak_idx << endl;
		cout <<"current_tree: "<< current_tree << endl;
	}
	//cout << endl;
	return current_tree;
}

#define SINGLE 0
#define REPEAT 1

class ReElement
{
protected:
	char ch;
public:
	ReElement(){};
	int getChar(){ return ch; };
	virtual int operator()(string s, int start) = 0;
	virtual int getType() = 0;
};

class SingleChar : public ReElement
{
public:
	SingleChar(char c) { ch = c; };
	int operator()(string s, int start)
	{
		return start + (start < s.size() && (s[start] == ch || ch == '.'));
	}

	int getType(){ return SINGLE; };
};

class Repeat : public ReElement
{
public:
	Repeat(char c) { ch = c; };
	int operator()(string s, int start)
	{
		if (ch == '.')
			start = s.size();
		else
			while (start < s.size() && s[start] == ch) start++;		
		return start;
	}

	int getType(){ return REPEAT; };
};

#define DEFERENCE(p)(*p)
bool isMatch(string s, string p)
{
	vector<ReElement*> re_elements;
	for (int i = p.size() - 1; i >= 0; i--)
	{
		if (p[i] == '*')
			re_elements.push_back(new Repeat(p[i - 1]));
		else
			re_elements.push_back(new SingleChar(p[i]));
		i -= (p[i] == '*');
	}
	
	reverse(re_elements.begin(), re_elements.end());
	
	vector<int> reach;
	vector<int> temp;

	
	int reach_dist = DEFERENCE(re_elements[0])(s, 0);
	if (DEFERENCE(re_elements[0]).getType() == SINGLE)
	{
		if (reach_dist == 0)
			return false;
		else
			reach.push_back(reach_dist);
	}
	else
	{
		for (int i = 0; i <= reach_dist; i++)
			reach.push_back(i);
	}


	for (int i = 1; i < re_elements.size(); i++)
	{
		if (DEFERENCE(re_elements[i - 1]).getType() == REPEAT 
			&& DEFERENCE(re_elements[i]).getType() == REPEAT
			&& (DEFERENCE(re_elements[i - 1]).getChar() == '.' 
			|| DEFERENCE(re_elements[i]).getChar() == DEFERENCE(re_elements[i - 1]).getChar()))
			continue;

		temp.clear();
		
		for (int j = 0; j < reach.size(); j++)
		{
			int reach_dist = DEFERENCE(re_elements[i])(s, reach[j]);
			int re_type = DEFERENCE(re_elements[i]).getType();

			if (re_type == SINGLE)
			{
				if (reach_dist > reach[j])
					temp.push_back(reach_dist);
				if (j == reach.size() - 1 && temp.empty())
					return false;
			}
			else
			{
				for (int k = reach[j]; k <= reach_dist; k++)
					if (temp.empty() || temp.back() < k)
						temp.push_back(k);
			}
		}
		reach = temp;
		cout << temp << endl;
	}

	return reach.back() == s.size();
}

int longestCommonSubsequence(string text1, string text2) 
{
	if (text1.size() == 0 || text2.size() == 0)
		return 0;

	vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1));

	for (int i = 1; i <= text1.size(); i++)
	{
		for (int j = 1; j <= text2.size(); j++)
		{
			if (text1[i - 1] == text2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}				
			
		}
		//cout << dp << endl;
		}
	return dp.back().back();
}

int mincostTickets(vector<int>& days, vector<int>& costs)
{
	vector<unsigned int> dp(days.size(), INT_MAX);

	for (int i = 0; i < days.size(); i++)
	{
		unsigned int current_cost = i > 0 ? dp[i - 1] : 0;
		for (int j = 0; j < costs.size(); j++)
		{
			int num = (j == 0) + (j == 1) * 7 + (j == 2) * 30;
			for (int k = i; k < days.size() && days[k] - days[i] < num; k++)
			{
				dp[k] = min(dp[k], current_cost + costs[j]);
			}
		}
		cout << dp << endl;
	}
	return dp.back();
}

int integerBreak(int n) 
{
	if (n < 3)
		return n - 1;

	vector<int> dp(n + 1);
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 3;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i / 2; j++)
		{
			dp[i] = max(dp[i], dp[j] * dp[i - j]);
		}
		//cout << dp << endl;
	}
	return dp.back();
}

string longestPalindrome(string s)
{
	string res;
	if (s.empty())
		return res;

	string str("#");
	for (int i = 0; i < s.size(); i++)
	{
		str.push_back(s[i]);
		str.push_back('#');
	}

	vector<int> p(str.size());

	int mx = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (i < (mx + p[i]))
		{
			p[i] = p[2 * mx - i];
		}

		while (p[i] + i < str.size() && i - p[i] >= 0 && str[i - p[i]] == str[i + p[i]])
			p[i]++;

		if (i + p[i] > mx + p[mx])
			mx = i;
	}
	cout << str[mx] << endl;
	cout << p << endl;

	return s.substr(mx - (p[mx]) / 2, p[mx]);
}

#define STATE_START -1
#define STATE_DIGIT 1
#define STATE_SIGN 2
#define STATE_DOT 3
#define STATE_EXP 4
#define STATE_DIGIT_POST 5
#define STATE_SIGN_POST 6
#define STATE_DOT_POST 7
#define STATE_REFUSE 8

#define CHAR_DIGIT 1
#define CHAR_SIGN 2
#define CHAR_DOT 3
#define CHAR_EXP 4

class MiniDFA
{
protected:
	int current_state;
public:
	MiniDFA() :current_state(STATE_START){};

	bool read_char(char c)
	{
		//cout << c << endl;
		int char_type = 
			(c == '.') * CHAR_DOT + 
			(c == '-' || c == '+') * CHAR_SIGN + 
			(c == 'e') * CHAR_EXP + 
			(IS_DIGIT(c));

			switch (current_state)
			{
			case STATE_START:
				if (char_type != STATE_EXP)
					current_state = char_type;
				else
					current_state = STATE_REFUSE;
				break;

			case STATE_DOT:
				if (char_type == CHAR_DIGIT)
					current_state = STATE_DIGIT_POST;
				else
					current_state = STATE_REFUSE;
				break;

			case STATE_EXP:
				if (char_type == CHAR_DIGIT)
					current_state = STATE_DIGIT_POST;
				else if (char_type == CHAR_SIGN)
					current_state = STATE_SIGN_POST;
				else
					current_state = STATE_REFUSE;
				break;

			case STATE_DIGIT:
				if (char_type == CHAR_DIGIT || char_type == CHAR_EXP)
					current_state = char_type;
				else if (char_type == CHAR_DOT)
					current_state = STATE_DOT_POST;
				else
					current_state = STATE_REFUSE;
				break;

			case STATE_DIGIT_POST:
				if (char_type == CHAR_DIGIT)
					current_state = STATE_DIGIT_POST;
				else if (char_type == CHAR_SIGN)
					current_state = STATE_SIGN_POST;
				else
					current_state = STATE_REFUSE;
				break;
			
			case STATE_SIGN_POST:
				if (char_type != CHAR_DIGIT)
					current_state = STATE_REFUSE;
				else
					current_state = STATE_DIGIT_POST;
				break;

			case STATE_DOT_POST:
				if (char_type == CHAR_DIGIT)
					current_state = STATE_DIGIT_POST;
				else
					current_state = STATE_REFUSE;
				break;

			case STATE_SIGN:
				if (char_type == CHAR_DIGIT)
					current_state = STATE_DIGIT;
				else if (char_type == CHAR_DOT)
					current_state = STATE_DOT_POST;
				else
					current_state = STATE_REFUSE;

			case STATE_REFUSE:
				break;
			}
		
		return current_state == STATE_DIGIT || current_state == STATE_DIGIT_POST || current_state == STATE_DOT_POST;
	}

	bool accept()
	{
		return current_state == STATE_DIGIT || current_state == STATE_DIGIT_POST || current_state == STATE_DOT_POST;
	}

	bool read_string(string s)
	{
		int start = 0;
		int end = s.size() - 1;
		while (s[start] == ' ')start++;
		while (s[end] == ' ')end--;

		s = s.substr(start, end - start + 1);
		cout << s << endl;

		for (char c : s)
			read_char(c);

		return current_state == STATE_DIGIT || current_state == STATE_DIGIT_POST || current_state == STATE_DOT_POST;
	}
};

bool isNumber(string s)
{
	MiniDFA dfa;
	return dfa.read_string(s);
}

int lengthOfLongestSubstring(string s)
{
	size_t lower_bound = 0;
	size_t res = 0;
	vector<size_t> index(256, -1);

	for (int i = 0; i < s.size(); i++)
	{
		//cout << s[i] << endl;
		if (index[s[i]] != -1 && index[s[i]] >= lower_bound)
		{
			res = max(i - lower_bound, res);
			lower_bound = index[s[i]] + 1;
		}
		index[s[i]] = i;
		cout << res << endl;
	}
	
	res = max(s.size() - lower_bound, res);
	return res;
}

int trap(vector<int>& height)
{
	stack<int> peak;
	int res = 0;
	//while (i < height.size() && !height[i])i++;
	int pre_h = 0;
	//peak.push(i);

	for (int i = 0; i < height.size() - 1; i++)
	{
		if (height[i] > height[i + 1])
			peak.push(i);
		else
		if (peak.size() > 0)
		{
			int prev = height[i];
			while (!peak.empty() && height[i + 1] > height[peak.top()])
			{
				res += (min(height[peak.top()], height[i + 1]) - prev) * (i - peak.top());
				prev = height[peak.top()];
				peak.pop();
			}
			
			if (!peak.empty())
			{
				res += (min(height[i + 1], height[peak.top()]) - prev) * (i - peak.top());
				if (height[peak.top()] == height[i + 1])
					peak.pop();
			}

		}

		//cout << res << endl;
	}

	return res;
}

bool dfs(vector<int>& nums, int current, int target, vector<int>& used)
{
	if (current == target)
		return true;
	else
	{
		for (int i = 0; i < nums.size(); i++)
		{
			if (used[i])
				continue;
			used[i] = 1;
			
			if (dfs(nums, current + nums[i], target, used))
				return true;

			used[i] = 0;
		}
	}
	return false;
}

bool canPartition(vector<int>& nums)
{
	int sum = 0;
	for (int i : nums)
		sum += i;
	
	if (nums.size() < 2 || sum % 2)
		return false;

	return dfs(nums, 0, sum/2, vector<int>(nums.size()));
}

#ifndef to_digit
#define to_digit(c)(c - 'A')
#endif
int permutataion(string nums)
{
	int res = -1;
	if (nums.size() < 26)
		return res;

	vector<int> indicies(256, -1);
	int lower_bound = 0;

	for (int i = 0; i < nums.size(); i++)
	{
		int digit = to_digit(nums[i]);
		if (indicies[digit] != -1 && lower_bound <= indicies[digit])
			lower_bound = indicies[digit] + 1;
		indicies[digit] = i;
		if (i - lower_bound == 25)
		{
			res = lower_bound;
			break;
		}
		cout << lower_bound << ' ' << i <<' '<< (i - lower_bound)<< endl;
	}

	return res;
}

int knightDialer(int n)
{
	vector<vector<int>> next_move = { { 4, 6 }, { 6, 8 }, { 7, 9 }, { 4, 8 }, { 0, 3, 9 }, {}, { 0, 1, 7 }, { 2, 6 }, { 1, 3 }, { 4, 2 } };
	vector<vector<int>> dp{ vector<int>(10, 1), vector<int>(10, 0) };

	int res = 0;
	int i = 0;
	for (; i < n - 1; i++)
	{	
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < next_move[j].size(); k++)
				dp[(i + 1) % 2][next_move[j][k]] += dp[i % 2][j];
		
		for (auto& i : dp[i % 2])
			i ^= i;
	}

	for (int j = 0; j < dp[i % 2].size(); j++)
		res += dp[i % 2][j];

	return res % 1000000007;
}

int lengthOfLIS(vector<int>& nums)
{
	if (nums.size() < 2)
		return 1;

	vector<int> lis(nums.size(), 1);

	for (int i = 1; i < nums.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (nums[i] > nums[j])
				lis[i] = max(lis[j] + 1, lis[i]);
		}
		cout << lis << endl;
	}

	int res = 0;
	for (int i = 0; i < lis.size(); i++)
		res = max(lis[i], res);

	return res;
}

vector<int> grayCode(int n) {
	vector<int> res(1);
	if (n == 0)
		return res;

	res.push_back(1);
	for (int i = 1; i < (n); i++)
	{
		int base = 1 << i;
		for (int j = 0; j < base; j++)
		{
			int idx = (base - 1 - j);
			//cout<<(res[idx])<<endl;
			res.push_back(base | res[idx]);
		}
	}
	return res;
}

#ifndef set_bit
#define set_bit(n, pos, b)(b == 1 ? n |= (1 << pos) : n &= ~(1 << pos))
#endif

#ifndef to_digit
#define to_digit(c)(c - 'a')
#endif

#ifndef get_bit
#define get_bit(n,pos)((n & (1<<pos)) != 0)
#endif

int cnt_one(int n){
	int res = 0;
	while (n)
	{
		n &= (n - 1);
		res++;
	}
	return res;
}

int encode_string(string s)
{
	int res = 0;
	for (int i = 0; i < s.size(); i++)
	{
		//if (!get_bit(res, to_digit(s[i])))
			set_bit(res, to_digit(s[i]), 1);
		//else
		//	return 0;
	}

	return res;
}

int can_cat(int s, int s2)
{
	return cnt_one(s) + cnt_one(s2) == cnt_one(s | s2) ? cnt_one(s | s2) : 0;
}

int maxLength_helper(int idx, int curr, vector<int>& mask)
{
	if (idx == mask.size())
		return cnt_one(curr);

	int res = 0;
	res = maxLength_helper(idx + 1, curr, mask);
	if (can_cat(curr, mask[idx]))
		res = max(maxLength_helper(idx + 1, curr|mask[idx], mask), res);

	return res;
}

int maxLength(vector<string>& arr)
{
	vector<int> mask;
	for (int i = 0; i < arr.size(); i++)
		mask.push_back(encode_string(arr[i]));

	return maxLength_helper(0, 0, mask);
}

int minimumDeleteSum(string s1, string s2)
{
	vector<vector<int>> dp(s2.size() + 1, vector<int>(s1.size() + 1, 0));

	for (int i = 1; i < s1.size() + 1; i++)
		dp[0][i] = s1[i - 1] + dp[0][i - 1];

	for (int i = 1; i < s2.size() + 1; i++)
		dp[i][0] = s2[i - 1] + dp[i - 1][0];

	for (int i = 1; i < s2.size() + 1; i++)
	{
		for (int j = 1; j < s1.size() + 1; j++)
			if (s1[j - 1] == s2[i - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = min(dp[i - 1][j] + s2[i - 1], dp[i][j - 1] + s1[j - 1]);

		//cout << dp << endl;
	}

	return dp.back().back();
}

vector<int> transformArray(vector<int>& arr) 
{
	vector<int> next(arr.size());
	while (next != arr)
	{
		cout << arr << endl;
		for (int i = 0; i < arr.size(); i++)
		{
			if (i == 0 || i == arr.size() - 1)
				next[i] = arr[i];

			else if (arr[i - 1] < arr[i] && arr[i] > arr[i + 1])
				next[i] = arr[i] - 1;
			else if (arr[i - 1] > arr[i] && arr[i] < arr[i + 1])
			{
				next[i] = arr[i] + 1;
			}
			else
				next[i] = arr[i];
		}
		//cout << next << endl;
		//system("pause");
		swap(next, arr);
	}
	return next;
}

int minimumRemove(vector<int>& nums)
{
	vector<vector<int>> minimum_remove(nums.size(), vector<int>(nums.size(), nums.size()));
	for (int i = 0; i < nums.size(); i++)
		minimum_remove[i][i] = 1;
	for (int i = 0; i < nums.size() - 1; i++)
		minimum_remove[i][i + 1] = (nums[i] != nums[i + 1]) + 1;
	
	cout << minimum_remove << endl;
	
	for (int size = 3; size <= nums.size(); size++)
	{
		cout << size << endl;
		for (int left = 0, right = left + size - 1; right < nums.size(); left++, right++)
		{
			if (nums[left] == nums[right])
				minimum_remove[left][right] = minimum_remove[left + 1][right - 1];
			else
			{
				for (int mid = left; mid < right; mid++)
					minimum_remove[left][right] = min(minimum_remove[left][mid] + minimum_remove[mid + 1][right], minimum_remove[left][right]);
			}
			
			cout << minimum_remove << endl;
		}
	}
	return minimum_remove[0].back();
}

int minimumSwap(string s1, string s2) 
{
	int x_y = 0, y_x = 0;

	for (int i = 0; i < s1.size(); i++)
	{
		if (s1[i] != s2[i]){
			if (s1[i] == 'x')
				x_y++;
			else
				y_x++;
		}
	}
	//cout << x_y << ' ' << y_x << endl;
	if ((x_y % 2) != (y_x % 2))
		return -1;
	else
		return (x_y - x_y % 2) / 2 + (y_x - y_x % 2) / 2 + x_y % 2 * 2;
}

int numberOfSubarrays(vector<int>& nums, int k) 
{
	int res = 0;
	vector<int> odd_idx;
	int left = 0, right = 0;
	while (right < nums.size())
	{
		if (nums[right] % 2)
		{
			odd_idx.push_back(right);
			if (odd_idx.size() == k)
			{
				right++;
				while (right < nums.size() && nums[right] % 2 == 0)
					right++;

				//cout << "odd_idx: " << odd_idx << endl;
				//cout << "left: " << left << ' ' << "right: " << right << endl;

				res += 1 + (odd_idx.front() - left) + (right - odd_idx.back() - 1) +
					(odd_idx.front() - left) * (right - odd_idx.back() - 1);

				left = odd_idx.front() + 1;
				odd_idx.erase(odd_idx.begin());
				continue;
			}
		}
		right++;
			
	}
	return res;
}

string minRemoveToMakeValid(string s)
{
	string res = "";
	vector<int> left_idx;
	vector<int> right_idx;

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
		{
			left_idx.push_back(i);
			if (!right_idx.empty() && right_idx.back() > i)
				right_idx.pop_back();
				
		}
		else if (s[i] == ')')
		{
			if (!left_idx.empty() && left_idx.back() < i)
				left_idx.pop_back();
			else
				right_idx.push_back(i);
		}
	}

	
	for (int i = 0, j = 0, k = 0; i < s.size(); i++)
	{
		if (j < left_idx.size() && i == left_idx[j])
			j++;
		else if (k < right_idx.size() && i == right_idx[k])
			k++;
		else
			res.push_back(s[i]);
	}

	return res;
}

int longestArithSeqLength(vector<int>& arr) 
{
	vector<vector<int>> difference(arr.size() - 1, vector<int>(arr.size() - 1));
	int res = 0;

	for (int i = 1; i < arr.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			difference[i - 1][j] = arr[i] - arr[j];
		}
		//cout << difference << endl;
	}

	//cout << difference << endl;

	vector<vector<int>> las(arr.size() - 1, vector<int>(arr.size() - 1, 2));

	for (int i = 1; i < arr.size() - 1; i++)
	{
		for (int j = 1; j <= i; j++)
		{
 			for (int k = 0; k < j; k++)
			{
				if (difference[i][j] == difference[j - 1][k])
					las[i][j] = las[j - 1][k] + 1;
				res = max(las[i][j], res);
			}
		}
		//cout << las << endl;
	}
	return res;
}

int heightChecker(vector<int>& heights)
{
	int res = 0;
	vector<int> lis(heights.size(), 1);
	for (int i = 1; i < heights.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (heights[j] <= heights[i])
			{
				lis[i] = max(lis[i], lis[j] + 1);
				res = max(res, lis[i]);
			}
		}
	}
	cout << lis << endl;
	return heights.size() - res;
}

int firstMissingPositive(vector<int>& nums) 
{
	int right = nums.size() - 1;
	while (right >= 0 && nums[right] > nums.size())right--;

	int left = 0;
	while (left <= right)
	{
		cout << nums << endl;
		if (nums[left] != left + 1)
		{
			if (nums[left] > 0 && nums[left] <= nums.size() && nums[nums[left] - 1] != nums[left])
			{
				right -= nums[left] == right + 1;
				swap(nums[left], nums[nums[left] - 1]);
			}
			else
				swap(nums[right--], nums[left]);		
			continue;
		}
		left++;
	}

	while (left < nums.size() && nums[left] == left + 1)
		left++;

	return left + 1;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k)
{
	vector<int> res;
	if (nums.size() == 0)
		return res;

	int largest_idx = 0;

	for (int i = 0; i < nums.size() && i < k; i++)
		largest_idx = nums[largest_idx] > nums[i] ? largest_idx : i;
	res.push_back(nums[largest_idx]);

	for (int i = k; i < nums.size(); i++)
	{
		if (largest_idx >= i - k + 1)
			largest_idx = nums[largest_idx] > nums[i] ? largest_idx : i;
		else
		{
			int start = ++largest_idx;
			while (start <= i)
			{
				largest_idx = nums[largest_idx] > nums[start] ? largest_idx : start;
				start++;
			}
		}
		res.push_back(nums[largest_idx]);
	}
	
	return res;
}

#define OPERAND 0
#define OPERATOR_AND 1
#define OPERATOR_OR 2
#define OPERATOR_NOT 3
#define OPERATOR_LB 4

#define is_operator(c)(OPERAND + (c == '!') * OPERATOR_NOT + (c == '&') * OPERATOR_AND \
+ (c == '|') * OPERATOR_OR)

bool parseBoolExpr(string expression)
{
	if (expression.size() == 0)
		return false;

	stack<char> exp;
	stack<int> left_idx;

	for (int i = 0; i < expression.size(); i++)
	{
		if (expression[i] == ',')
			continue;

		if (expression[i] != ')')
		{
			exp.push(expression[i]);
			if (expression[i] == '(')
				left_idx.push(i);
		}
		else
		{
			char cur_operator = expression[left_idx.top() - 1];
			left_idx.pop();

			int tmp = exp.top() == 't';
			exp.pop();
			while (exp.top() != '(')
			{
				switch (cur_operator)
				{
				case '&':
					tmp &= exp.top() == 't';
					break;
				case '|':
					tmp |= exp.top() == 't';
					break;
				default:
					break;
				}
				exp.pop();
			}
			exp.pop();
			exp.pop();
			exp.push((cur_operator == '!' ? !tmp : tmp) ? 't': 'f');
		}
	}
	return exp.top() == 't';
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
	int idx = nums1.size() - 1;
	int i = m - 1;
	int j = n - 1;

	while (i >= 0 && j >= 0)
	{
		if (nums1[i] > nums2[j])
			swap(nums1[i--], nums1[idx--]);	
		else
			swap(nums2[j--], nums1[idx--]);
	}

	while (idx >= 0 && j >= 0)
		swap(nums2[j--], nums1[idx--]);
}

vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum)
{
	vector<vector<int>> res;
	int check_sum = 0, upper_most = 0, lower_most = 0, cnt_two = 0;
	for (int i = 0; i < colsum.size(); i++)
	{
		check_sum += colsum[i];
		upper_most += colsum[i] > 0;
		lower_most += colsum[i] > 0;
		cnt_two += colsum[i] == 2;
	}
		
	if (check_sum != upper + lower || upper_most < upper || lower_most < lower)
		return res;

	res = vector<vector<int>>(2, vector<int>(colsum.size()));

	for (int i = 0; i < colsum.size(); i++)
	{
		if (colsum[i] == 2)
		{
			cnt_two--;
			res[0][i]++;
			upper--;
			res[1][i]++;
			lower--;
		}
		else
		if (colsum[i] == 1)
		{
			if (cnt_two)
			{
				if (cnt_two < upper)
				{
					res[0][i]++;
					upper--;
				}
				else
					res[1][i]++;
			}else 
			if (upper)
			{
				res[0][i]++;
				upper--;
			}
			else
				res[1][i]++;
		}
		
	}

	return res;
}

void fill(vector<vector<int>>& board, int row, int col)
{
	int h = 2;
	queue<pair<int, int>> q;
	q.push(make_pair(row, col));
	while (!q.empty())
	{
		row = q.front().first, col = q.front().second;
		board[row][col] = h;
		//up
		if (row - 1 >= 0 && board[row - 1][col] == 0)
		{
			board[row - 1][col] = h;
			q.push(make_pair(row - 1, col));
		}

		//down
		if (row + 1 < board.size() && board[row + 1][col] == 0)
		{
			board[row + 1][col] = h;
			q.push(make_pair(row + 1, col));
		}
		//left
		if (col - 1 >= 0 && board[row][col - 1] == 0)
		{
			board[row][col - 1] = h;
			q.push(make_pair(row, col - 1));
		}

		//right
		if (col + 1 < board[0].size() && board[row][col + 1] == 0)
		{
			board[row][col + 1] = h;
			q.push(make_pair(row, col + 1));
		}

		q.pop();
		//cout << q.size() << endl;
	}
}

int closedIsland(vector<vector<int>>& grid) 
{
	if (grid.size() < 3 || grid[0].size() < 3)
		return 0;

	int res = 0;
	
	for (int i = 0; i < grid[0].size(); i++)
	{
		if (grid[0][i] == 0)
			fill(grid, 0, i);
		if (grid[grid.size() - 1][i] == 0)
			fill(grid, grid.size() - 1, i);
	}
	
	for (int i = 0; i < grid.size(); i++)
	{
		if (grid[i][0] == 0)
			fill(grid, i, 0);
		if (grid[i][grid[0].size() - 1] == 0)
			fill(grid, i, grid[0].size() - 1);
	}

	cout << grid << endl;
	for (int i = 1; i < grid.size() - 1; i++)
	{
		for (int j = 1; j < grid[0].size() - 1; j++)
		{
			if (grid[i][j] == 0)
			{
				res++;
				fill(grid, i, j);
			}
		}
	}
	return res;
}

void moveZeroes(vector<int>& nums)
{
	if (nums.size() == 0)
		return;

	int zero_idx = 0;
	while (nums[zero_idx] != 0)
		zero_idx++;

	for (int i = zero_idx + 1; i < nums.size(); i++)
	{
		if (nums[i] != 0)
		{
			swap(nums[i], nums[zero_idx]);
			zero_idx++;
			while (nums[zero_idx] != 0)
				zero_idx++;
		}
	}
}

int minDominoRotations(vector<int>& A, vector<int>& B)
{
	vector<unsigned int> bar(6);
	vector<unsigned int> bar_b(6);

	for (int i = 1; i < bar.size() + 1; i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			if (A[j] != i)
			{
				if (B[j] == i)
					bar[i - 1]++;
				else
				{
					bar[i - 1] = -1;
					break;
				}
			}
		}

		for (int j = 0; j < A.size(); j++)
		{
			if (B[j] != i)
			{
				if (A[j] == i)
					bar_b[i - 1]++;
				else
				{
					bar_b[i - 1] = -1;
					break;
				}
			}
		}
	}

	unsigned int res = -1;
	for (int i = 0; i < bar.size(); i++)
		res = min(bar[i], min(res, bar_b[i]));
	return res;
}

//#define PATH 0
//#define FOLDER 1
//class Path
//{
//public:
//	int path;
//	string folder;
//	vector<Path*> children;
//	Path(string s) : folder(s), children(vector<Path*>()){};
//	Path(string s, int p) : folder(s), path(p), children(vector<Path*>()){};
//};
//
//void destory(Path* node)
//{
//	for (int i = 0; i < (*node).children.size(); i++)
//		destory((*node).children[i]);
//	delete node;
//}
//
//void traverse(Path* node)
//{
//	cout << node->folder << endl;
//	for (int i = 0; i < node->children.size(); i++)
//		traverse(node->children[i]);
//}
//
//void construct_result(Path* node, vector<string>& res, string curr)
//{
//	if (node->children.size() == 0)
//		res.push_back(curr + node->folder);
//
//	for (int i = 0; i < node->children.size(); i++)
//		construct_result(node->children[i], res, curr + node->folder);
//}
//
//int folder_compare(string& a, int start, string& b)
//{
//	int index = 0;
//	int res = 0;
//
//	while (index + start < a.size() && index < b.size() && a[index + start] == b[index])
//	{
//		if (a[index + start] == '/')
//			res = index;
//		++index;
//	}
//
//	if (index + start == a.size() || (a[index + start] == '/' && index == b.size()))
//		res = index;
//	return res;
//}
//
//void merge_folder(string s, int start, Path* node)
//{
//	bool found = false;
//
//	for (int i = 0; i < node->children.size(); i++)
//	{
//		int same = folder_compare(s, start, node->children[i]->folder);
//		found = same > 0;
//		
//		if (same > 0)
//		{
//			//current folder is already in the path
//			if (start + same == s.size())
//			{
//				destory(node->children[i]);
//				node->children[i] = new Path(s.substr(start, s.size() - start));
//				node->children[i]->path = FOLDER;
//			}
//			else
//			{
//				//parent folder is already exist
//				if (same == node->children[i]->folder.size())
//				{
//					if (node->children[i]->path != FOLDER)	
//						merge_folder(s, start + same, node->children[i]);
//				}					
//				else
//				{
//					Path* new_node = new Path(s.substr(start, same), PATH);
//					node->children[i]->folder = node->children[i]->folder.substr(same, node->children[i]->folder.size() - same);
//					new_node->children.push_back(node->children[i]);
//					node->children[i] = new_node;
//					new_node->children.push_back(new Path(s.substr(start + same, s.size() - same - start), FOLDER));
//				}
//			}
//			break;
//		}
//	}
//
//	if (!found)
//		node->children.push_back(new Path(s.substr(start, s.size() - start), FOLDER));
//}
//
//vector<string> removeSubfolders(vector<string>& folder)
//{
//	vector<string> res;
//	if (folder.size() == 0)
//		return res;
//
//	Path* root = new Path("");
//	for (int i = 0; i < folder.size(); i++)
//	{
//		merge_folder(folder[i], 0, root);
//	}
//	//traverse(root);
//	construct_result(root, res, "");
//	destory(root);
//	return res;
//}

int findMin_helper(vector<int>& nums, int start, int end)
{
	int mid = (start + end) / 2;
	if (mid == end - 1)
		return nums[mid];
	else
	{
		int res = INT_MAX;
		if (nums[start] <= nums[mid])
			res = findMin_helper(nums, mid, end);
		if (nums[mid] <= nums[end - 1])
			res = min(res, findMin_helper(nums, start, mid + 1));
		return res;
	}
}


int findMin(vector<int>& nums)
{
	return min(nums[0],findMin_helper(nums,0, nums.size()));
}

vector<int> singleNumber(vector<int>& nums)
{
	// Pass 1 : 
	// Get the XOR of the two numbers we need to find
	int diff = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		diff ^= nums[i];
	}
	// Get its last set bit
	cout << diff << endl;
	diff &= -diff;
	cout << diff << endl;
	// Pass 2 :
	vector<int> rets = { 0, 0 }; // this vector stores the two numbers we will return
	for (int num : nums)
	{
		if ((num & diff) == 0) // the bit is not set
		{
			rets[0] ^= num;
		}
		else // the bit is set
		{
			rets[1] ^= num;
		}
		cout << rets << endl;
	}
	return rets;
}

int numRollsToTarget(int d, int f, int target)
{
	if (target < d || target > d * f)
		return 0;
	int mod = 1e9 + 7;
	vector<vector<int>> dp(d, vector<int>(d * f + 1));
	for (int i = 0; i < f; i++)
		dp[0][i + 1] = 1;

	for (int i = 1; i < d; i++)
	{
		for (int j = 1; j <= f; j++)
		{
			for (int k = i; k <= i * f; k++)
			{
 				dp[i][k + j] = (dp[i][k + j] + dp[i - 1][k]) % mod;
			}
		}
	}
	//cout << dp << endl;
	return dp[d - 1][target];
}

//vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
//{
//
//	vector<int> ans;
//	int i = 0, j = 0;
//	while (i < nums1.size() && j < nums2.size())
//	{
//		while (i + 1 < nums1.size() && nums1[i] == nums1[i + 1])i++;
//		while (j + 1 < nums2.size() && nums2[j] == nums2[j + 1])j++;
//		if (nums1[i] == nums2[j])
//		{
//			ans.push_back(nums1[i]);
//			++i, ++j;
//		}
//		else if (nums1[i] <= nums2[j])
//			++i;
//		else
//			++j;
//	}
//	return ans;
//}

vector<int> findDisappearedNumbers(vector<int>& nums)
{
	vector<int> res;
	int left = 0, right = nums.size() - 1;
	while (right >= 0 && nums[right] > nums.size()) right--;

	while (left <= right)
	{
		if (nums[left] != left + 1)
		{
			if (nums[left] != nums[nums[left] - 1] && nums[left] < nums.size() + 1 && nums[left] > 0)
			{
				swap(nums[left], nums[nums[left] - 1]);
				right -= nums[right] == right + 1;
			}
			else
				swap(nums[left], nums[right--]);
			continue;
		}
		left++;
	}

	cout << nums << endl;

	while (left < nums.size())
	{
		if (left + 1 != nums[left])
			res.push_back(left + 1);
		left++;
	}
	return res;
}

vector<int> productExceptSelf(vector<int>& a)
{
	vector<int> res(a.size(), 1);
	int product_l = 1, product_r = 1;
	for (int i = 1; i < a.size(); i++)
	{
		product_l *= a[i - 1];
		res[i] *= product_l;

		product_r *= a[a.size() - i];
		res[a.size() - i - 1] *= product_r;
		cout << res << endl;
	}
	return res;
}

void sum_helper(vector<int>& nums, int index, int current, int& res)
{
	if (index == nums.size())
		res += current == 0;
	else
	{
		int sign_curr = current > 0;
		int sign_num = nums[index] > 0;
		if (sign_curr ^ sign_num || current == 0 || nums[index] == 0)
		{
			sum_helper(nums, index + 1, current - nums[index], res);
			sum_helper(nums, index + 1, current + nums[index], res);
		}
		else
		{
			if (sign_curr && sign_num)
			{
				sum_helper(nums, index + 1, current - nums[index], res);
				if (current <= INT_MAX - nums[index])
					sum_helper(nums, index + 1, current + nums[index], res);
			}
			else
			{
				if (current >= INT_MIN + nums[index])
					sum_helper(nums, index + 1, current - nums[index], res);
				sum_helper(nums, index + 1, current + nums[index], res);
			}
		}
	}
}

int findTargetSumWays(vector<int>& nums, int target) 
{
	int res = 0;
	sum_helper(nums, 0, target, res);
	return res;
}

string calculate_res(int n, int size)
{
	string res;
	while (n)
	{
		res.push_back((n & 1) + '0');
		n >>= 1;
	}
	while (res.size() < size)
		res.push_back('0');
	reverse(res.begin(), res.end());
	return res;
}

string encode(int num)
{
	int start = 0;
	while (((1 << start + 1) - 1) <= num)
		start++;
	return calculate_res(num - ((1 << start) - 1), start);
}

string getPermutation(int num, int k)
{
	string s = "";
	int n = 1;
	while (n * (n + 1) < k)
		++n;
	++n;
	if (n > num)
		return s;

	cout << n << endl;
	return s;
}

vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k)
{
	if (grid.size() == 0 || grid[0].size() == 0)
		return grid;

	vector<vector<int>> res(grid.size(), vector<int>(grid[0].size()));
	int total = grid.size() * grid[0].size();

	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[0].size(); col++)
		{
			int idx = (row * grid[0].size() + col + k) % total;
			int row_cpy = idx / grid[0].size();
			int col_cpy = idx % grid[0].size();
			res[row_cpy][col_cpy] = grid[row][col];
		}
	}
	return res;
}

int maxSumDivThree(vector<int>& nums)
{
	vector<vector<int>> dp(2, vector<int>(3));

	for (int i = 0; i < nums.size(); i++)
	{
		int r = nums[i] % 3;
		for (int j = 0; j < dp[0].size(); j++)
		{
			int index = (r + j) % 3;
			if (dp[i % 2][j] % 3 == j)
				dp[!(i % 2)][index] = max(dp[(i % 2)][index], nums[i] + dp[(i % 2)][j]);
			else
				dp[!(i % 2)][index] = dp[i % 2][index];
		}
		cout << dp << endl;
	}
	//cout << dp << endl;
	return dp[nums.size() % 2][0];
}

//string minWindow(string s, string t)
//{
//	vector<int> cnt(26);
//	vector<queue<int>>(26);
//
//	for (int i = 0; i < t.size(); i++)
//	{
//		cnt[t[i] - 'A'] = 
//	}
//
//}

string frequencySort(string s)
{
	map<char, pair<int, int>> chars;
	for (int i = 0; i < s.size(); i++)
	{
		if (chars.find(s[i]) == chars.end())
			chars[s[i]] = make_pair(1, i);
		else
			chars[s[i]].first++;
	}

	priority_queue<pair<int, char>> q;
	for (auto it = chars.begin(); it != chars.end(); it++)
		q.push(make_pair((*it).second.first, (*it).first));

	int idx = 0;
	while (!q.empty())
	{
		for (int i = 0; i < q.top().first; i++)
		{
			s[idx++] = q.top().second;
		}		
		q.pop();
	}
	return s;
}

string longestCommonPrefix(vector<string>& strs)
{
	string res = "";
	if (strs.size() == 0)
		return res;
	if (strs.size() == 1)
		return strs[0];

	for (int i = 0; i < strs[1].size() && strs[0].size(); i++)
	{
		if (strs[0][i] == strs[1][i])
			res += strs[0][i];
		else
			break;
	}

	int max_length = res.size();

	for (int i = 2; i < strs.size(); i++)
	{
		if (strs[i] == "" || res == "")
		{
			max_length = 0;
			break;
		}

		int idx = 0;
		while (idx < res.size() && idx < strs[i].size())
		if (res[idx] == strs[i][idx])
			idx++;
		else
			break;
		max_length = min(max_length, idx);
	}
	return res.substr(0, max_length);
}

int cal_minute(string& s)
{
	int hour = 0, minute = 0, res = 0, flag = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ':'){ flag = true; continue; }
		if (!flag)
		{
			hour += s[i] - '0';
			hour *= 10;
		}
		else
		{
			minute += s[i] - '0';
			minute *= 10;
		}
	}
	return hour * 6 + minute / 10;
}

int findMinDifference(vector<string>& timePoints)
{
	vector<int> minutes;
	for (int i = 0; i < timePoints.size(); i++)
		minutes.push_back(cal_minute(timePoints[i]));
	sort(minutes.begin(), minutes.end());
	int res = INT_MAX;
	for (int i = 0; i < minutes.size() - 1; i++)
		res = min(res, (minutes[i + 1] - minutes[i]));
	return min(res, minutes.front() - minutes.back() + 24 * 60);
}

bool canJump(vector<int>& nums)
{
	if (nums.size() < 2)
		return true;

	int index = 0;
	int max_distance = nums[index];
	while (index < nums.size())
	{
		for (int i = 1; i <= nums[index]; i++)
		{
			if (index + i >= nums.size() - 1 || max_distance >= nums.size())
				return true;
			max_distance = max(max_distance, index + i + nums[index + i]);
		}

		if (index == max_distance)
			return false;
		else
			index++;
	}
	return max_distance >= nums.size() - 1;
}

bool isPalindrome(string s)
{
	string str = "";
	for (int i = 0; i < s.size(); i++)
	if (s[i] >= 'a' && s[i] <= 'z')
		str += s[i];
	else if (s[i] >= 'A' && s[i] <= 'Z')
		str += s[i] - 'A' + 'a';
	cout << str << endl;
	for (int i = 0; i < (int)(str.size() - i - 1); i++)
	{
		if (str[i] != str[str.size() - i - 1])
			return false;
	}
	return true;
}

unsigned int reverseBits(unsigned int n){
	unsigned int ans = 0;
	for (int i = 0; i < 32; i++)
	{
		if (n & (1 << i))
			ans |= (1 << (32 - i - 1));
	}
	return ans;
}

int missingNumber(vector<int>& nums)
{
	int left = 0, right = nums.size() - 1;
	while (left < right)
	{
		if (nums[left] != left)
		{
			if (nums[left] >= nums.size())
				swap(nums[left], nums[right--]);
			else
				swap(nums[left], nums[nums[left]]);
			cout << nums << endl;
			continue;
		}
		left++;
	}
	while (left == nums[left])
		left++;
	return left;
}

bool increasingTriplet(vector<int>& nums) {
	stack<int> s;
	for (int i = 0; i < nums.size(); i++)
	{
		while (!s.empty() && s.top() > nums[i])
			s.pop();
		if (s.empty() || s.top() < nums[i])
			s.push(nums[i]);

		if (s.size() == 3)
			return true;
	}
	return s.size() == 3;
}

int countPrimes(int n)
{
	if (n < 2)
		return 0;

	vector<int> primes;
	primes.push_back(2);
	bool isPrime = true;
	for (int i = 3; i <= n; i++)
	{
		bool isPrime = true;
		for (int j = 0; j < primes.size() && primes[j] * primes[j] <= i; j++)
		{
			if (i % primes[j] == 0)
			{
				isPrime = false;
				break;
			}
		}

		if (isPrime)
			primes.push_back(i);
		cout << primes << endl;
	}
	return primes.size();
}

int length(vector<vector<int>>& matrix, vector<vector<int>> dp, int i, int j)
{
	if (dp[i][j])
		return dp[i][j];
	//up
	if (i > 0 && matrix[i][j] < matrix[i - 1][j])
		dp[i][j] = max(dp[i][j], 1 + length(matrix, dp, i - 1, j));

	//down
	if (i < matrix.size() - 1 && matrix[i][j] < matrix[i + 1][j])
		dp[i][j] = max(dp[i][j], 1 + length(matrix, dp, i + 1, j));

	//left
	if (j > 0 && matrix[i][j] < matrix[i][j - 1])
		dp[i][j] = max(dp[i][j], 1 + length(matrix, dp, i, j - 1));

	//right
	if (j < matrix[0].size() - 1 && matrix[i][j] < matrix[i][j + 1])
		dp[i][j] = max(dp[i][j], 1 + length(matrix, dp, i, j + 1));

	return dp[i][j];
};

int longestIncreasingPath(vector<vector<int>>& matrix)
{
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return 0;

	vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size()));

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			dp[i][j] = length(matrix, dp, i, j);
		}
	}
	cout << dp << endl;
	int ans = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			ans = max(ans, dp[i][j]);
		}
	}
	return ans;
}

vector<string> split(string& s)
{
	size_t sub_start = 0, sub_end = 0;
	while (sub_end < s.size() && (s[sub_end] == '\n' || s[sub_end] == '\t'))
		sub_end++;

	vector<string> res;
	while (sub_end < s.size())
	{
		sub_start = sub_end;
		while (sub_end < s.size() && !(s[sub_end] == '\n' || s[sub_end] == '\t'))sub_end++;
		res.push_back(s.substr(sub_start, sub_end - sub_start));
		while (sub_end < s.size() && (s[sub_end] == '\n' || s[sub_end] == '\t'))sub_end++;
	}

	return res;
}

string licenseKeyFormatting(string S, int K)
{
	string ans = "";
	int cnt = 0;

	for (int i = S.size() - 1; i >= 0; i--)
	{
		if ((S[i] >= 'A' && S[i] <= 'Z') || (S[i] >= '0' && S[i] <= '9'))
		{
			ans += S[i];
			cnt++;
		}
		else if (S[i] >= 'a' && S[i] <= 'z')
		{
			ans += S[i] - 'a' + 'A';
			cnt++;
		}

		if (cnt % K == 0 && ans.back() != '-')
			ans += '-';
	}
	//cout << ans << endl;
	if (ans.back() == '-')
		ans.pop_back();
	reverse(ans.begin(), ans.end());
	return ans;
}

int getline(string& s, int start, int& level, int& file)
{
	int offset = 0;
	while (start + offset < s.size() && s[start + offset] != '\n')
	{
		level += (s[start + offset] == '\t');
		file |= (s[start + offset] == '.');
		offset++;
	}
	return offset;
}

int lengthLongestPath(string input)
{
	vector<int> length(1000);
	int index = 0;

	int ans = 1;
	while (index < input.size())
	{
		int level = 0, file = false;
		int offset = getline(input, index, level, file);
		length[level] = offset - level + 1;
		
		if (file)
		{
			int tmp = 0;
			for (int i = 0; i <= level; i++)
				tmp += length[i];
			ans = max(tmp, ans);
		}
		index += offset + 1;
	}
	return ans - 1;
}

vector<int> idx;
int alien_cmpare(string& a, string& b)
{
	for (int i = 0; i < min(a.size(), b.size()); i++)
	{
		if (idx[a[i] - 'a'] == idx[b[i] - 'a'])
			continue;
		else
			return idx[a[i] - 'a'] < idx[b[i] - 'a'];
	}
	return a.size() < b.size();
}

bool isAlienSorted(vector<string>& words, string& order)
{
	idx = vector<int>(26);
	for (int i = 0; i < order.size(); i++)
		idx[order[i] - 'a'] = i;

	vector<string> cpy = words;
	sort(words.begin(), words.end(), alien_cmpare);
	return words == cpy;
}

bool checkInclusion(string& s1, string& s2)
{
	if (s1.size() == 0)
		return true;

	vector<int> bar(26);
	for (char c : s1)
		bar[c - 'a']++;

	for (int i = 0; i < s2.size(); )
	{
		if (bar[s2[i] - 'a'])
		{
			vector<int> cpy = bar;
			int j = 0;
			while (j < s1.size() && i + j < s2.size() && cpy[s2[i + j] - 'a'])
				cpy[s2[i + j] - 'a']--, j++;

			if (j == s1.size())
				return true;
			else
			{
				i += j;
				continue;
			}
		}
		i++;
	}

	return false;
}

int romain_integer_mapping(char c)
{
	int ans = 0;
	switch (c)
	{
	case 'I':
		ans = 1;
		break;
	case 'V':
		ans = 5;
		break;
	case 'X':
		ans = 10;
		break;
	case 'L':
		ans = 50;
		break;
	case 'C':
		ans = 100;
		break;
	case 'D':
		ans = 500;
		break;
	case 'M':
		ans = 1000;
		break;
	}
	return ans;
}

int romanToInt(string s)
{

	int ans = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (i + 1 < s.size() && romain_integer_mapping(s[i + 1]) > romain_integer_mapping(s[i]))
			ans += (romain_integer_mapping(s[i + 1]) - romain_integer_mapping(s[i])), ++i;
		else
			ans += romain_integer_mapping(s[i]);
	}
	return ans;
}

void bfs(vector<vector<int>>& grid, queue<pair<int, int>>& positions, int& fresh)
{
	int cnt = positions.size();
	while (cnt)
	{
		int row = positions.front().first;
		int col = positions.front().second;

		if (row > 0 && grid[row - 1][col] == 1)
		{
			positions.push(make_pair(row - 1, col));
			grid[row - 1][col] = 2;
		}
			
		if (row + 1 < grid.size() && grid[row + 1][col] == 1)
		{
			positions.push(make_pair(row + 1, col));
			grid[row + 1][col] = 2;
		}
			
		if (col > 0 && grid[row][col - 1] == 1)
		{
			positions.push(make_pair(row, col - 1));
			grid[row][col - 1] = 2;
		}
		
		if (col + 1 < grid[row].size() && grid[row][col + 1] == 1)
		{
			positions.push(make_pair(row, col + 1));
			grid[row][col + 1] = 2;
		}
			
		cnt--;
		positions.pop();
	}
	fresh -= positions.size();
}

int orangesRotting(vector<vector<int>>& grid)
{
	int ans = 0, fresh = 0, rotton;
	queue<pair<int, int>> position;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j] == 2)
				position.push(make_pair(i, j));
			fresh += grid[i][j] == 1;
		}
	}

	while (!position.empty())
	{
		bfs(grid, position, fresh);
		cout << grid << endl;
		ans++;
	}

	return fresh == 0 ? ans - 1 : -1;
}

//map<int, int> priority;
//int compare(int a, int b)
//{
//	return priority[a] < priority[b];
//}
//
//
//vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2)
//{
//	priority.clear();
//	for (int i = 0; i < arr2.size(); i++)
//		priority[arr2[i]] = i;
//
//	for (int i = 0; i < arr1.size(); i++)
//	{
//		if (priority.find(arr1[i]) == priority.end())
//		{
//			priority[arr1[i]] = 1001 + arr1[i];
//		}
//	}
//
//	sort(arr1.begin(), arr1.end(), compare);
//	return arr1;
//}

vector<int> majorityElement(vector<int>& nums)
{
	pair<int, int> majority1, majority2;

	for (int i = 0; i < nums.size(); i++)
	{
		if (majority1.second == 0 && majority2.first != nums[i])
		{
			majority1.first = nums[i];
			majority1.second = 1;
		}
		else if (majority1.first == nums[i])
			majority1.second++; 
		else if (majority2.second == 0)
		{
			majority2.first = nums[i];
			majority2.second = 1;
		}		
		else if (majority2.first == nums[i])
			majority2.second++;
		else
		{
			--majority1.second;
			--majority2.second;
		}
		/*cout << "majority1: " << majority1 << endl;
		cout << "majority2: " << majority2 << endl;
		cout << endl;*/
	}

	majority1.second = majority2.second = 0;
	
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == majority1.first)
			majority1.second++  ;
		else if (nums[i] == majority2.first)
			majority2.second++;
	}

	vector<int> res;
	if (majority1.second > nums.size() / 3)
		res.emplace_back(majority1.first);
	if (majority2.second > nums.size() / 3)
		res.emplace_back(majority2.first);
	return res;

}

string process_email(string& s)
{
	string res = "";
	int i = 0;
	int filtered = false;
	while (i < s.size())
	{
		filtered |= s[i] == '+';
		if (!filtered && s[i] != '.' && s[i] != '@')
			res += s[i];
		if (s[i] == '@')
			break;
		i++;
	}
	return res += s.substr(i, s.size() - i);
}

int numUniqueEmails(vector<string>& emails)
{
	set<string> s;
	for (int i = 0; i < emails.size(); i++)
		s.insert(process_email(emails[i]));
	return s.size();
}

int totalFruit(vector<int>& tree) 
{
	vector<int> baskets(2, -1);
	int ans = 0;
	int left = 0;
	for (int i = 0; i < tree.size(); i++)
	{
		if (baskets[0] == -1 || tree[baskets[0]] == tree[i])
		{
			baskets[0] = i;
			if (baskets[0] > baskets[1] && baskets[1] != -1)
				swap(baskets[0], baskets[1]);
		}
		else if (baskets[1] == -1 || tree[baskets[1]] == tree[i])
			baskets[1] = i;
		else
		{
			ans = max(ans, i - left);
			left = baskets[0] + 1;
			baskets[0] = baskets[1];
			baskets[1] = i;
		}
	}	
	return max(ans, (int)tree.size() - left);
}

int maxDistToClosest(vector<int>& seats)
{
	vector<int> from_left(seats.size());
	vector<int> from_right(seats.size());

	int left_closest = -20000, right_closest = INT_MAX;
	for (int i = 0; i < seats.size(); i++)
	{
		if (seats[i] == 1)
			left_closest = i, from_left[i] = 0;
		else
			from_left[i] = i - left_closest;

		if (seats[seats.size() - i - 1] == 1)
			right_closest = seats.size() - i - 1, from_right[seats.size() - i - 1] = 0;
		else
			from_right[seats.size() - i - 1] = right_closest - seats.size() + i + 1;
	}

	int ans = 0;
	for (int i = 0; i < seats.size(); i++)
	{
		ans = max(ans, min(from_left[i], from_right[i]));
	}

	return ans;
}

vector<int> twoSum(vector<int>& nums, int target)
{
	map<int, int> mapping;
	for (int i = 0; i < nums.size(); i++)
	{
		mapping[nums[i]] = i;
	}

	for (int i = 0; i < nums.size(); i++)
	{
		if (mapping.find(target - nums[i]) != mapping.end())
			return vector<int>({ i, mapping[target - nums[i]] });
	}
	return vector<int>();
}

vector<int> prisonAfterNDays(vector<int>& cells, int n) 
{
	vector<int> next(8);
	for (int i = 1; i < cells.size() - 1; i++)
	{
		next[i] = (cells[i - 1] == cells[i + 1]);
	}

	vector<vector<int>> loop(1, next);
	while (loop.size() < n)
	{
		for (int i = 1; i < loop.back().size() - 1; i++)
			next[i] = (loop.back()[i - 1] == loop.back()[i + 1]);

		if (next == loop.front())
			break;
		else
			loop.push_back(next);
	}

	//cout << loop << endl;
	if (loop.size() == n)
		return loop.back();
	return loop[(n - 1) % loop.size()];
}

class FreqStack {
public:
	int max_freq;
	map<int, int> freq;
	map<int, stack<int>> freq_map;

	FreqStack()
	{
		max_freq = 0;
	}

	void push(int x)
	{
		int f = ++freq[x];
		max_freq = max(f, max_freq);
		freq_map[f].push(x);
	}

	int pop()
	{
		int ans = freq_map[max_freq].top();
		freq_map[max_freq].pop();
		max_freq -= freq_map[max_freq].empty();
		freq[ans]--;
		return ans;
	}
};

void dfs(vector<int>& nums, int start, int target, vector<int>& tmp, vector<vector<int>>& ans)
{
	if (target == 0)
	{
		ans.emplace_back(tmp);
		return;
	}

	for (int i = start; i < nums.size(); i++)
	{
		if (target - nums[i] >= 0)
		{
			tmp.emplace_back(nums[i]);
			dfs(nums, i, target - nums[i], tmp, ans);
			tmp.pop_back();
		}
	}
}

vector<vector<int>> combinationSum(vector<int>& nums, int target)
{
	vector<vector<int>> ans;
	vector<int> tmp;
	dfs(nums, 0, target, tmp, ans);
	return ans;
}



void bfs(vector<vector<int>>& grid, int row, int col, int& res)
{
	queue<pair<int, int>> q;
	q.push(make_pair(row, col));
	int land = -1;
	while (!q.empty())
	{
		land++;
		int r = q.front().first;
		int c = q.front().second;

		if (grid[r][c] != 0)
		{
			grid[r][c] = 0;

			if (c > 0 && grid[r][c - 1] == 1)
				q.push(make_pair(r, c - 1));
			else
				res++;

			if (c < grid[r].size() - 1 && grid[r][c + 1] == 1)
				q.push(make_pair(r, c + 1));
			else
				res++;

			if (r > 0 && grid[r - 1][c] == 1)
				q.push(make_pair(r - 1, c));
			else
				res++;

			if (r < grid.size() - 1 && grid[r + 1][c] == 1)
				q.push(make_pair(r + 1, c));
			else
				res++;
		}
		
		// cout  << res << endl;
		q.pop();
	}
	res -= land;
}

int islandPerimeter(vector<vector<int>>& grid)
{
	int ans = 0;
	queue<pair<int, int>> q;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j] == 1)
				bfs(grid, i, j, ans);
		}
	}
	return ans;
}

vector<int> partitionLabels(string s)
{
	vector<int> first_appear(26, -1);
	vector<int> ans;
	if (s == "")
		return ans;

	for (int i = 0; i < s.size(); i++)
	{
		//cout << s[i] << endl;
		if (first_appear[to_digit(s[i])] != -1)
		{
			while (ans.size() > 0 && ans.back() > first_appear[to_digit(s[i])])
				ans.pop_back();

			if (ans.size() > 0 && ans.back() == first_appear[to_digit(s[i])])
				ans.pop_back();
		}
		else
			first_appear[to_digit(s[i])] = i;
		ans.push_back(i);
		//cout << ans << endl;
	}

	for (int i = ans.size() - 1; i > 0; i--)
		ans[i] = ans[i] - ans[i - 1];
	ans[0] += 1;
	return ans;
}

bool validMountainArray(vector<int>& arr)
{
	bool decrease_started = false;
	for (int i = 0; i < arr.size() - 1; i++)
	{
		if (i > 0 && decrease_started == false && arr[i] > arr[i + 1])
			decrease_started = true;

		if (arr[i] == arr[i + 1] || !decrease_started && arr[i] > arr[i + 1] || decrease_started && arr[i] < arr[i + 1])
			return false;
	}
	return true;
}

class Rect
{
public:
	int t_x;
	int t_y;
	int d_x;
	int d_y;

	Rect(int x1, int y1, int x2, int y2)
	{
		t_x = max(x1, x2);
		t_y = max(y1, y2);
		d_x = min(x1, x2);
		d_y = min(y1, y2);
	}

	bool in(int x, int y)
	{
		return t_x > x && d_x < x && y < t_y && d_y < y;
	}

	void extend(int x, int y)
	{
		t_x = max(x, t_x);
		d_x = min(x, d_x);
		t_y = max(y, t_y);
		d_y = min(y, d_y);
	}

	int space()
	{
		return (t_x - d_x) * (t_y - d_y);
	}
};

ostream& operator<< (ostream& os, Rect r)
{
	os << "top: " << r.t_x << ' ' << r.t_y <<endl;
	os << "down: " << r.d_x << ' ' << r.d_y << endl;
	return os;
}

class Solution {
public:
	int minAreaRect(vector<vector<int>>& points)
	{
		if (points.size() < 2)
			return 0;

		Rect rect(points[0][0], points[0][1], points[1][0], points[1][1]);

		for (int i = 2; i < points.size(); i++)
		{
			int x = points[i][0], y = points[i][1];
			if (!rect.in(x, y))
				rect.extend(x, y);
			cout << rect << endl;
		}

		return rect.space();
	}
};

class MyCircularQueue {
public:
	size_t front, rear;
	vector<int> q;
	/** Initialize your data structure here. Set the size of the queue to be k. */
	MyCircularQueue(int k)
	{
		front = rear = 0;
		q = vector<int>(k);
		front = rear = 0;
	}

	/** Insert an element into the circular queue. Return true if the operation is successful. */
	bool enQueue(int value)
	{
		if (isFull())
			return false;
		else
		{
			q[(rear++) % q.size()] = value;
			return true;
		}
	}

	/** Delete an element from the circular queue. Return true if the operation is successful. */
	bool deQueue()
	{
		if (isEmpty())
			return false;
		front++;
		return true;
	}

	/** Get the front item from the queue. */
	int Front() {
		if (isEmpty())
			return -1;
		return q[front % q.size()];
	}

	/** Get the last item from the queue. */
	int Rear() {
		if (isEmpty())
			return -1;
		return q[(rear - 1) % q.size()];
	}

	/** Checks whether the circular queue is empty or not. */
	bool isEmpty()
	{
		return front == rear;
	}

	/** Checks whether the circular queue is full or not. */
	bool isFull() {
		return (rear - front) == q.size();
	}
};

class MyQueue {
public:
	/** Initialize your data structure here. */
	stack<int> s1;
	stack<int> s2;
	MyQueue()
	{

	}

	/** Push element x to the back of queue. */
	void push(int x) {
		while (!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}

		s2.push(x);
		while (!s2.empty())
		{
			s1.push(s2.top());
			s2.pop();
		}
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop()
	{
		int ans = -1;
		if (!s1.empty())
		{
			ans = s1.top();
			s1.pop();
		}
		return ans;
	}

	/** Get the front element. */
	int peek() {
		if (!s1.empty())
			return s1.top();
		return -1;
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		return s1.empty();
	}
};



string hex(int x)
{
	string ans = "";
	while (x)
	{
		char r = x % 16;
		r = r >= 10 ? r + 'A' : r + '0';
		ans += r;
		x >>= 4;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int binary_search(vector<int> nums, int target)
{
	int start = 0, end = nums.size(), mid = start + (end - start) / 2;
	while (start != end)
	{
		if (target == nums[mid])
			return mid;

		if (target < nums[mid])
			end = mid;
		else
			start = mid;

		mid = start + (end - start) / 2;
	}

	return end;
}

int binSearch(vector<vector<int>> &intervals, int target)
{
	int start = 0, end = intervals.size(), mid = start + (end - start) / 2;
	while (start < end - 1)
	{
		if (intervals[mid][0] <= target && intervals[mid][1] >= target)
			return mid;
		
		if (intervals[mid][0] > target)
			end = mid;

		else if (intervals[mid][1] < target)
			start = mid;

		mid = start + (end - start) / 2;
	}
	return -end;
}

vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved)
{
	vector<vector<int>> ans;
	int lower_bound = toBeRemoved[0], upper_bound = toBeRemoved[1];
	cout << binSearch(intervals, lower_bound) << endl;
	cout << binSearch(intervals, upper_bound) << endl;
	
	return ans;
}


int countSquares(vector<vector<int>>& matrix)
{
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return 0;

	// vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size()));
	int max_length = min(matrix.size(), matrix[0].size());
	int ans = 0;

	vector<vector<int>> next(matrix.size(), vector<int>(matrix[0].size()));

	for (int i = 1; i <= max_length; i++)
	{
		//next = vector<vector<int>>(matrix.size(), vector<int>(matrix[0].size()));
		for (int row = i - 1; row < matrix.size(); row++)
		{
			for (int col = i - 1; col < matrix[0].size(); col++)
			{
				ans += matrix[row][col] &= ((i == 1) || (matrix[row - 1][col] & matrix[row][col - 1] & matrix[row - 1][col - 1]));
			}
		}
		cout << matrix << endl;
		cout << ans << endl;
		//matrix = next;
	}

	return ans;
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
	vector<int> ans;
	sort(nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());

	int p1 = 0, p2 = 0;

	while (p1 < nums1.size() && p2 < nums2.size())
	{
		int p1_next = 0, p2_next = 0;
		if (nums1[p1] == nums2[p2])
		{
			ans.push_back(nums1[p1]);
			p1_next = p2_next = 1;
		}
		else if (nums1[p1] < nums2[p2])
			p1_next = 1;
		else
			p2_next = 1;

		if (p1_next)
		{
			int num = nums1[p1];
			while (p1 < nums1.size() && num == nums1[p1])p1++;
		}

		if (p2_next)
		{
			int num = nums1[p2];
			while (p2 < nums2.size() && num == nums2[p2])p2++;
		}

		cout << nums1[p1] << endl;
		cout << nums2[p2] << endl;
	}

	return ans;
}

int origin_target = 0;
bool canPartition(vector<int>& nums, int idx, int k, int target, vector<int>& used)
{
	if (k == 1)
		return true;

	if (idx == nums.size() || nums[idx] > target)
		return false;

	for (int i = idx; i < nums.size(); i++)
	{
		if (!used[i])
		{
			used[i] = 1;

			if (canPartition(nums,
				(i + 1) * (!(target == nums[i])),
				k - (target == nums[i]),
				target == nums[i] ? origin_target : (target - nums[i]),
				used)
				)
				return true;

			used[i] = 0;
		}	
	}
	return false;
}

bool canPartitionKSubsets(vector<int>& nums, int k)
{
	sort(nums.begin(), nums.end(), greater<int>());

	int sum = 0;
	for (int i = 0; i < nums.size(); i++)
		sum += nums[i];

	if (sum % k)
		return false;

	vector<int> used(nums.size());
	origin_target = sum / k;
	return canPartition(nums, 0, k, origin_target, used);
}

int twoCitySchedCost(vector<vector<int>> &costs)
{
	sort(costs.begin(), costs.end(), [=](vector<int>& a, vector<int>& b){return (a[0] - a[1]) < (b[0] - b[1]); });
	int res = 0;
	for (int i = 0; i < costs.size(); i++)	
		res += costs[i][i >= costs.size() / 2];
	return  res;
}

//int largestRectangleArea(vector<int>& heights)
//{
//	if (heights.size() == 0)
//		return 0;
//
//	vector<int> largest = heights;
//	int mini_idx = 0, closest_zero_idx = -1;
//
//	for (int i = 1; i < heights.size(); i++){
//		if (heights[i] == 0){
//			mini_idx = (i + 1), closest_zero_idx = i;
//		}
//		else if (heights[mini_idx] >= heights[i]){
//			mini_idx = i;
//			largest[i] = heights[i] * (i - closest_zero_idx);
//		}
//		else{
//			largest[i] = max(largest[i], heights[mini_idx] * (i - closest_zero_idx));
//			int j = i - 1, local_min = heights[i];
//			while (j > mini_idx)
//			{
//				local_min = min(local_min, heights[j]);
//				largest[i] = max(largest[i], local_min * (i - j + 1));
//				j--;
//			}
//		}
//	}
//	//cout << largest << endl;
//	int res = 0;
//	for (int i = 0; i < largest.size(); i++)
//		res = max(res, largest[i]);
//	return res;
//}

int largestRectangleArea(vector<int>& heights)
{
	heights.push_back(0);
	stack<int> s;
	int width = 0, height = 0, res = 0;
	for (int i = 0; i < heights.size(); i++)
	{
		while (!s.empty() && heights[s.top()] >= heights[i])
		{
			height = heights[s.top()];
			s.pop();

			if (s.empty())
				width = i;
			else
				width = i - 1 - s.top();
			res = max(res, height * width);
			//cout << res << ' ';
		}
		s.push(i);
	}
	//cout << endl;
	return res;
}

bool valid_parenthese(string& s)
{
	stack<char> left;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
			left.push(s[i]);
		else if (s[i] == ')')
		{
			if (left.empty())
				return false;
			else
				left.pop();
		}
	}
	return left.empty();
}

void build(string& s, int idx, int left, int right, int extra_left, int extra_right, string& tmp, set<string>& res)
{
	if (idx == s.size() || extra_left == 0 && extra_right == 0)
	{
		string r = tmp + s.substr(idx, s.size() - idx);
		if (valid_parenthese(r))
			res.insert(r);
	}
	else if (s[idx] == '(')
	{
		if (left)
		{
			tmp += s[idx];
			build(s, idx + 1, left - 1, right, extra_left, extra_right, tmp, res);
			tmp.pop_back();
		}

		if (extra_left)
			build(s, idx + 1, left, right, extra_left - 1, extra_right, tmp, res);
	}
	else if (s[idx] == ')')
	{
		if (left < right)
		{
			tmp += s[idx];
			build(s, idx + 1, left, right - 1, extra_left, extra_right, tmp, res);
			tmp.pop_back();
		}
		else
		if (left == right && extra_right > 0 || extra_right)
			build(s, idx + 1, left, right, extra_left, extra_right - 1, tmp, res);
	}
	else
	{
		build(s, idx + 1, left, right, extra_left, extra_right, tmp += s[idx], res);
		tmp.pop_back();
	}
}

vector<string> removeInvalidParentheses(string s)
{
	int left = 0, right = 0, valid_left = 0, valid_right = 0;
	set<string> res;
	string tmp = "";

	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '(':
			++left;
			break;
		case ')':
			++right;
			valid_left += left > valid_left;
			break;
		default:
			break;
		}
	}

	build(s, 0, valid_left, valid_left, (left - valid_left), (right - valid_left), tmp, res);
	vector<string> ans;
	for (auto it = res.begin(); it != res.end(); it++)
		ans.push_back(*it);
	return ans;
}

bool repeatedSubstringPattern(string s)
{
	vector<int> idx(26, -1);
	int window_size = 0;
	int window_idx = 0;

	for (int i = 0; i < s.size(); i++)
	{
		if (idx[to_digit(s[i])] != -1)
		{
			if (window_size == 0)
				window_size = i - idx[to_digit(s[i])];
		
			if (i - idx[to_digit(s[i])] != window_size)
				return false;
			else
				window_idx = (window_idx + 1) % window_size;
		}
		else if (window_size)
			return false;

		idx[to_digit(s[i])] = i;
	}
	return window_size && window_idx == 0;
}

int reverse(int x)
{
	string s = to_string(x);
	reverse(s.begin() + (s[0] == '-'), s.end());
	long long int res = stoll(s);
	return res <= INT_MAX && res >= INT_MIN ? res : 0;
}

class Func
{
public:
	virtual __int64 operator()(__int64, __int64) = 0;
};

class Plus : public Func
{
public:
	__int64 operator()(__int64 a, __int64 b)
	{
		return a + b;
	}
};

class Minus :public Func
{
public:
	__int64 operator()(__int64 a, __int64 b)
	{
		return a - b;
	}
};

vector<Func*> funcs = { new Minus(), new  Plus()};


//void search(string& s, int idx, vector<int> current, int target, string& tmp, vector<string>& res)
//{
//	if (target == accumulate(current.begin(), current.end(), 0) && idx == s.size())
//	{
//		tmp.pop_back();
//		if (res.empty() || tmp != res.back())
//			res.push_back(tmp);
//	}
//	else
//	{
//		__int64 val = 0;
//		size_t length = tmp.size();
//
//		for (int i = idx; i < s.size(); i++)
//		{
//			val *= 10;
//			val += s[i] - '0';
//			
//			tmp += s[i];
//
//			
//			search(s, i + 1, current, target, tmp + '*', res);
//			search(s, i + 1, current, target, tmp + '+', res);
//			search(s, i + 1, current, target, tmp + '-', res);
//			
//			current.pop_back();
//		}
//	}
//}
//
//vector<string> addOperators(string num, int target)
//{
//	vector<string> res;
//	vector<int> exp;
//	string tmp = "";
//	search(num, 0, exp, target, tmp, res);
//	return res;
//}

bool search_word(vector<vector<char>>& board, string& s, int idx, int row, int col)
{
	//cout << board << endl;
	if (idx + 1 == s.size() && s[idx] == board[row][col])
		return true;
	else if (s[idx] != board[row][col])
		return false;
	else
	{
		bool found = false;
		board[row][col] = '#';
		//up
		if (row > 0)
			found |= search_word(board, s, idx + 1, row - 1, col);
		//down
		if (row + 1 < board.size())
			found |= search_word(board, s, idx + 1, row + 1, col);
		//left
		if (col > 0)
			found |= search_word(board, s, idx + 1, row, col - 1);
		//right
		if (col + 1 < board[row].size())
			found |= search_word(board, s, idx + 1, row, col + 1);

		board[row][col] = s[idx];
		return found;
	}
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
{
	vector<string> res;
	if (words.size() == 0)
		return res;

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			for (int k = 0; k < words.size(); k++)
			{
				if (words[k] == "")
					continue;
				if (words[k][0] == board[i][j])
				{
					if (search_word(board, words[k], 0, i, j))
						res.push_back(words[k]);
				}		
			}
		}
	}
	return res;
}

#define isBadVersion(c)(c >= 2)

int search(int start, int end)
{
	if (start + 1 == end)
		return isBadVersion(start) ? start : end;

	int mid = start + (end - start) / 2;
	if (isBadVersion(mid))
		end = mid;
	else
		start = mid;

	return search(start, end);
}

int firstBadVersion(int n)
{
	return search(1, n + 1);
}

int pivotIndex(vector<int>& nums)
{
	int res = -1;
	if (nums.size() == 0)
		return res;

	vector<int> sums(nums.size());
	int sum = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		sum += nums[i];
		sums[i] = sum;
	}

	cout << sums << endl;
	for (int i = 0; i < nums.size(); i++)
	{
		int left = sums[i] - nums[i];
		int right = sums.back() - sums[i];

		if (left == right)
			return i;
	}

	return -1;
}

int coinChange(vector<int>& coins, int amount)
{
	if (amount < 1)
		return -1;

	sort(coins.begin(), coins.end());
	vector<unsigned int> dp(max(amount, coins.back()) + 1, -1);

	for (int i = 0; i < coins.size(); i++)
		dp[coins[i]] = 1;

	dp[0] = 0;

	for (int i = 1; i <= amount; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			if (dp[j] != -1 && dp[i - j] != -1)
				dp[i] = min(dp[i], dp[j] + dp[i - j]);
		}
		cout << dp << endl;
	}
	return dp[amount];
}

void duplicateZeros(vector<int>& arr)
{
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i] == 0)
			{
				arr.push_back(0);
				reverse(arr.begin() + i, arr.begin() + arr.size() - 1);
				reverse(arr.begin() + i, arr.end());
				++i;
			}
		}
}

vector<int> extract_int(string& version)
{
	vector<int> res;
	int left = 0, right = left;
	while (right < version.size())
	{
		while (right < version.size() && version[right] != '.')++right;
		res.push_back(stoi(version.substr(left, right - left)));
		left = right + 1;
		right = left + 1;
	}
	if (right == version.size())
		res.push_back(stoi(version.substr(left, right - left)));
	return res;
}

int compareVersion(string version1, string version2)
{
	vector<int> nums1 = extract_int(version1);
	vector<int> nums2 = extract_int(version2);
	cout << nums1 << endl;
	cout << nums2 << endl;
	int i = 0, j = 0;
	while (i < nums1.size() && j < nums2.size())
	{
		if (nums1[i] < nums2[j])
			return -1;

		else if (nums1[i] > nums2[j])
			return 1;

		else
			++i, ++j;
	}

	if (i == nums1.size() && j < nums2.size())
	{
		while (j < nums2.size())
		{
			if (nums2[j] != 0)
				return -1;
			++j;
		}
		return 0;
	}
	else if (i < nums1.size() && j == nums2.size())
	{
		while (i < nums1.size())
		{
			if (nums1[i] != 0)
				return 1;
			++i;
		}
		return 0;
	}
	else
		return 0;
}

bool overlap(vector<int>& interval1, vector<int>& interval2)
{
	return interval1.back() >= interval2.front() && interval1.front() <= interval2.back()
		|| interval1.front() <= interval2.back() && interval1.front() >= interval2.back();
}

vector<int> mergeIntervals(vector<int>& interval1, vector<int>& interval2)
{
	return vector<int>({ max(interval1.front(), interval2.front()), min(interval1.back(), interval2.back()) });
}

vector<vector<int>> intervalIntersection(vector<vector<int>>& a, vector<vector<int>>& b)
{
	int i = 0, j = 0;
	vector<vector<int>> res;

	while (i < a.size() && j < b.size())
	{
		if (overlap(a[i], b[j]))
			res.push_back(mergeIntervals(a[i], b[j]));

		if (a[i].back() < b[j].back())
			++i;
		else
			++j;
	}
	return res;
}

bool canConstruct(string ransomNote, string magazine)
{
	vector<int> bar(26);
	for (int i = 0; i < magazine.size(); i++)
		++bar[magazine[i] - 'a'];
	cout << bar << endl;
	for (int i = 0; i < ransomNote.size(); i++)
	{
		if (bar[ransomNote[i] - 'a'])
			bar[ransomNote[i] - 'a']--;
		else
			return false;
	}

	return true;
}

int maximumProduct(vector<int>& nums)
{
	if (nums.size() == 0)
		return 0;
	if (nums.size() == 1)
		return nums.front();

	int max_in = 1, max_all = INT_MIN, min_negative = 1;

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == 0)
			max_in = 1, max_all = max(max_all, 0), min_negative = 0;
		else if (nums[i] > 0)
		{
			min_negative *= nums[i], max_in *= nums[i];
			max_all = max(max_all, max_in);
		}
		else
		{
			max_all = max(max_all, min_negative * nums[i]);
			max_in = min_negative * nums[i];
			min_negative = max_in * nums[i];
		}
	}

	return max(max_all, max_in);
}

vector<int> sequentialDigits(int low, int high)
{
	string s = "0123456789";
	int length = 0, idx = 0;
	int tmp = low;

	while (tmp)
	{
		++length;
		tmp /= 10;
		if (tmp / 10 == 0)
			idx = tmp;
	}
	vector<int> res;
	while (true)
	{
		tmp = stoi(s.substr(idx, length));
		if (tmp >= low && tmp <= high)
			res.push_back(tmp);

		if (tmp > high || idx == 1 && idx + length == s.size())
			break;

		if (idx + length == s.size())
			idx = 1, length = length + 1;
		else
			++idx;

		//cout << tmp << endl;
	}
	return res;
}

void calPath(vector<vector<int>>& grid, vector<vector<int>>& path)
{
	queue<vector<int>> q;
	q.push(vector<int>({(int)grid.size() - 1, (int)grid[0].size() - 1, 0 }));

	while (!q.empty())
	{
		int row = q.front()[0], col = q.front()[1], length = q.front()[2];
		path[row][col] = length;

		if (row > 0 && grid[row - 1][col] == 0 && path[row - 1][col] == INT_MAX)
			q.push(vector<int>({row - 1, col, length + 1}));

		if (row < grid.size() - 1 && grid[row + 1][col] == 0 && path[row + 1][col] == INT_MAX)
			q.push(vector<int>({ row + 1, col, length + 1 }));

		if (col > 0 && grid[row][col - 1] == 0 && path[row][col - 1] == INT_MAX)
			q.push(vector<int>({ row, col - 1, length + 1 }));

		if (col < grid[row].size() - 1 && grid[row][col + 1] == 0 && path[row][col + 1] == INT_MAX)
			q.push(vector<int>({ row, col + 1, length + 1 }));

		q.pop();

		cout << path << endl;
	}
}

int shortestPath(vector<vector<int>>& grid, int k)
{
	vector<vector<int>> path(grid.size(), vector<int>(grid[0].size(), INT_MAX));
	calPath(grid, path);
	cout << path << endl;

	return 0;
}

vector<vector<int>> hor;

void init(vector<vector<char>>& matrix)
{
	hor = vector<vector<int>>(matrix.size(), vector<int>(matrix[0].size()));

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			if (hor[i][j] = (matrix[i][j] == '1'))
			{
				if (j > 0)
					hor[i][j] += hor[i][j - 1];
			}
		}
	}
}

int calArea(int row, int col)
{
	int hor_min = hor[row][col];
	int res = hor_min;
	//cout << "row: " << row <<  ' ' << "col: " << col << endl;
	for (int r = row - 1; r >= 0 && hor[r][col]; r--)
	{
		hor_min = min(hor_min, hor[r][col]);
		res = max(res, hor_min * (row - r + 1));
	}
	return res;
}

int maximalRectangle(vector<vector<char>>& matrix)
{
	int res = 0;
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return res;

	init(matrix);

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			if (hor[i][j])
				res = max(res, calArea(i, j));
		}
	}

	return res;
}

vector<vector<int>> largetsNum(vector<int>& nums)
{
	vector<vector<int>> res;
	res.resize(nums.size() + 1);
	res.back() = nums;

	for (int i = res.size() - 2; i >= 0; i--)
	{	
		int idx = 0;
		while (idx + 1< res[i + 1].size())
		{
			if (res[i + 1][idx] < res[i + 1][idx + 1])
				break;
			idx++;
		}

		for (int j = 0; j < res[i + 1].size(); j++)
		{
			if (idx != j)
				res[i].push_back(res[i + 1][j]);
		}
	}
	return res;
}

int compare(vector<int>& nums1, vector<int>& nums2, int start_i, int start_j)
{
	int loop_size = min(nums1.size() - start_i, nums2.size() - start_j);
	int i = 0;
	for (; i < loop_size; i++)
	{
		if (nums1[i + start_i] < nums2[i + start_j])
			return i;
		else if (nums1[i + start_i] > nums2[i + start_j])
			return -i;
	}

	if (nums1.size() - start_i < nums2.size() - start_j)
		return i;
	else if (nums1.size() - start_i == nums2.size() - start_j)
		return 0;
	else
		return i;
}

vector<int> merge(vector<int>& nums1, vector<int>& nums2)
{
	vector<int> res;
	int i = 0, j = 0;
	while (i < nums1.size() || j < nums2.size())
	{
		if (i == nums1.size() || (j < nums2.size() && nums2[j] > nums1[i]))
			res.push_back(nums2[j++]);
		else if (j == nums2.size() || (i < nums1.size() && nums2[j] < nums1[i]))
			res.push_back(nums1[i++]);
		else
		{
			int r = compare(nums1, nums2, i, j);
			if (r > 0)
			{
				for (int k = 0; k < r; k++)
					res.push_back(nums2[j++]);
			}
			else
			{
				for (int k = 0; k < abs(r); k++)
					res.push_back(nums1[i++]);
			}
		}
	}
	return res;
}

vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, size_t k) 
{
	vector<vector<int>> largest_num1 = largetsNum(nums1);
	vector<vector<int>> largest_num2 = largetsNum(nums2);

	vector<int> res;

	int start = k > nums2.size() ? k - nums2.size() : 0;

	for (int i = start; i < largest_num1.size() && i <= k; i++)
	{
		vector<int> tmp = merge(largest_num1[i], largest_num2[k - i]);
		if (res.empty() || res < tmp)
			res = tmp;
	}

	return res;
}

int minFallingPathSum(vector<vector<int>>& arr)
{

	for (int i = 0; i + 1 < arr.size(); i++)
	{
		priority_queue<pair<int, int>> q;

		for (int j = 0; j < arr[0].size(); j++)
		{
			int val = arr[i][j];
			int idx = j;
			q.push(make_pair(val, idx));
			if (q.size() > 2)
				q.pop();
		}

		int idx_1 = -1, idx_2 = -1;
		if (!q.empty())
		{
			idx_1 = q.top().second;
			q.pop();
		}

		if (!q.empty())
		{
			idx_2 = q.top().second;
			q.pop();
		}

		for (int j = 0; j < arr[0].size(); j++)
		{
			if (idx_2 != -1 && j != idx_2)
				arr[i + 1][j] += arr[i][idx_2];
			else if (idx_1 != -1 && j != idx_1)
				arr[i + 1][j] += arr[i][idx_1];
		}

		//cout << arr << endl;
	}
	int res = INT_MAX;
	for (int i = 0; arr.size() && i < arr[0].size(); i++)
		res = min(res, arr.back()[i]);
	return arr.size() == 0 ? 0 : res;
}

void fourSumDfs(vector<int>& nums, int idx, int target, vector<int>& tmp, vector<vector<int>> &res)
{
	if (tmp.size() == 4)
	{
		if (target == 0)
			res.push_back(tmp);
	}
	else
	{
		int num_required = 3 - tmp.size();

		for (int i = idx; i + num_required < nums.size();)
		{
			//cout << tmp << endl;
			tmp.push_back(nums[i]);
			fourSumDfs(nums, i + 1, target - nums[i], tmp, res);
			tmp.pop_back();

			if (nums[i] * (int)(4 - tmp.size()) > target)
				break;

			int offset = 1;
			while (i + offset < nums.size() && nums[i] == nums[i + offset])offset++;
			i += offset;
		}
	}
}

vector<vector<int>> fourSum(vector<int>& nums, int target)
{
	sort(nums.begin(), nums.end());
	cout << nums << endl;
	vector<int> tmp;
	vector<vector<int>> res;
	fourSumDfs(nums, 0, target, tmp, res);
	return res;
}

bool checkPossibility(vector<int>& nums)
{
	int idx = 0;
	bool skipped = false;
	for (int i = 0; i < nums.size() - 1; i++)
	{
		if (nums[i] > nums[i + 1])
		{
			if (skipped)
				return false;
			else
			{
				skipped = ++i;
				if (nums[idx] > nums[i])
					return false;
				continue;
			}
		}
		else
			idx++;
	}
	return true;
}


void solveSudoku(vector<vector<char>>& board) 
{
	vector<int> hor(9), ver(9);
	vector<vector<int>> cell(3, vector<int>(3));

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] != '.')
			{
				int pos = board[i][j] - '0' - 1;
				set_bit(cell[i / 3][j / 3], pos, 1);
				set_bit(hor[i], pos, 1);
				set_bit(ver[j], pos, 1);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			toBin(cell[i][j]);
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < hor.size(); i++)
	{
		toBin(hor[i]);
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < ver.size(); i++)
	{
		toBin(ver[i]);
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			toBin((cell[i / 3][j / 3] | hor[i] | ver[j]));
			cout << ' ';
		}
		cout << endl;
	}
}

#define to_idx(c)(c - 'a')
int dnc(string& s, int k, int start, int end)
{
	vector<int> freq(26);
	for (int i = start; i < end; i++)
		freq[to_idx(s[i])]++;

	int idx = start;
	while (idx < end)
	{
		if (freq[to_idx(s[idx])] < k)
			break;
		++idx;
	}

	if (idx == end)
		return idx - start;

	return max(dnc(s, k, start, idx),
		dnc(s, k, idx + 1, end));
}

int longestSubstring(string& s, int k)
{
	return dnc(s, k, 0, s.size());
}

int compare(string& s1, string& s2, string& s3, int i, int j, int k)
{
	if (s1[i] != s2[j])
	{
		if (s1[i] == s3[k])
			return 1;
		else if (s2[j] == s3[k])
			return -1;
		else return 0;
	}
	else
	{
		if (s1[i] != s3[k])
			return false;
		++k;
		while (k < s3.size() && s3[k - 1] == s3[k]) ++k;

		if (k == s3.size())
			return 0;

		++i, ++j;
		while (i < s1.size() && s1[i] == s1[i - 1]) i++;
		while (j < s2.size() && s2[j] == s2[j - 1]) j++;

		if (i == s1.size() && j == s1.size())
			return 0;
		else if (i == s1.size() && j < s2.size())
		{
			if (s2[j] == s3[k])
				return -1;
			else
				return 0;
		}
		else if (j == s2.size() && i < s1.size())
		{
			if (s1[i] == s3[k])
				return 1;
			else
				return 0;
		}
		else
		{
			if (s1[i] == s3[k])
				return 1;
			else if (s2[j] == s3[k])
				return -1;
			else
				return 0;
		}
	}

}

//bool isInterleave(string s1, string s2, string s3)
//{
//	if (s1.size() + s2.size() != s3.size())
//		return false;
//
//	int i = 0, j = 0, k = 0;
//
//	while (i < s1.size() || j < s2.size())
//	{
//		if (i == s1.size())
//		{
//			if (j < s2.size() && s2[j] == s3[k])
//				j++, k++;
//			else
//				return false;
//		}
//		else if (j == s1.size())
//		{
//			if (i < s1.size() && s1[i] == s3[k])
//				i++, k++;
//			else
//				return false;
//		}
//		else
//		{
//			int cmp = compare(s1, s2, s3, i, j, k);
//			if (cmp == 1)
//				i++;
//			else if (cmp == -1)
//				j++;
//			else
//				return false;
//			k++;
//		}
//	}
//
//	return k == s3.size();
//}

bool isPossibleDivide(vector<int>& nums, int k)
{
	if (nums.size() == 0 || nums.size() % k)
		return false;

	map<int, int> m;
	for (int i = 0; i < nums.size(); i++)
		m[nums[i]]++;

	while (true)
	{
		auto it = m.begin();
		if (it == m.end())
			break;

		int val = (*it).first;
		(*it).second--;
		for (int i = 1; i < k; i++)
		{
			auto iter = m.find(++val);
			if (iter == m.end())
				return false;
			else
				(*iter).second--;
		}

		for (auto it = m.begin(); it != m.end();)
		{
			if ((*it).second == 0)
			{
				m.erase(it);
				it = m.begin();
			}
			else
				++it;
		}
	}
	return true;
}

int stringMatch(string&s, string& target)
{
	if (s.size() < target.size())
		return 0;

	int mod = 1e+9 + 7;
	int hash_val = 0, tmp_hash = 0, power = 1;
	for (int i = 0; i < target.size(); i++)
	{
		hash_val = (hash_val * 257 + target[i]) % mod;
		tmp_hash = (tmp_hash * 257 + s[i]) % mod;
		power = (power * 257) % mod;
	}
		
	int res = hash_val == tmp_hash;
	for (int i = 1; i + target.size() <= s.size(); i++)
	{
		tmp_hash = (tmp_hash * 257 + s[i + target.size() - 1]) % mod;
		tmp_hash = (tmp_hash - power * s[i - 1]) % mod;
		if (tmp_hash < 0)
			tmp_hash += mod;

		res += hash_val == tmp_hash;
	}
	return res;
}
//ab
//aa
//abaa
bool isInterleave(string s1, string s2, string s3)
{
	if (s1.size() + s2.size() != s3.size())
		return false;

	vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1));

	for (int i = 0; i <= s1.size(); i++)
		dp[i][0] = 1;

	for (int j = 0; j <= s2.size(); j++)
		dp[0][j] = 1;

	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = 0; j < s2.size(); j++)
		{
			if (s2[j] != s3[i + j])
				break;
			else
				dp[i + 1][j + 1] = dp[i][j + 1] & dp[i + 1][j];
		}

		cout << dp << endl;
	}
	return dp[s1.size()][s2.size()];
}

//vector<int> reach;
bool helper(vector<int>& arr, int start)
{
	if (reach[start] == 0)
		return false;

	if (reach[start] == 1 || arr[start] == 0)
		return true;

	reach[start] = 0;
	if (start + arr[start] < arr.size() && helper(arr, start + arr[start]))
		return true;

	if (start - arr[start] >= 0 && helper(arr, start - arr[start]))
		return true;

	return false;
}

bool canReach(vector<int>& arr, int start)
{
	reach = vector<int>(arr.size(), -1);
	return helper(arr, start);
}

int jump(vector<int>& nums)
{
	int step = 0, start = 0;
	vector<pair<int, int>> q;
	unordered_set<int> passed;
	q.push_back(make_pair(0, step));

	while (!q.empty())
	{
		sort(q.begin() + start, q.end());
		step = q[start].second;
		int tmp = start;
		while (step == q[tmp].second)
		{
			if (q[tmp].first >= nums.size() - 1)
				goto ret;

			for (int i = nums[q[tmp].first]; i > 0; i--)
			{
				if (passed.find(q[tmp].first + i) == passed.end())
				{
					q.push_back(make_pair(q[tmp].first + i, step + 1));
					passed.insert(q[tmp].first + i);
				}
			}
			tmp++;
		}
		start = tmp;
	}
ret:
	return step;
}

//int leastInterval(vector<char>& tasks, int n)
//{
//	n++;
//	int res = 0;
//	if (tasks.empty())
//		return res;
//
//	vector<int> task(26);
//
//
//	for (int i = 0; i < tasks.size(); i++)
//	{
//		task[tasks[i] - 'A']++;
//	}
//
//
//	cout << task << endl;
//
//	int start = 0, end = 0;
//	while (end <task.size() && task[end] != 0)
//		end++;
//
//	while (start < end)//////////////
//	{
//		sort(task.begin() + start, task.end(), greater<int>());
//		int cold_down = n;
//		int i = start;
//		cout << task << endl;
//		while (cold_down--)
//		{
//			if (i < end && task[i] > 0)
//				task[i]--;
//			else
//			{
//				while (i < end && task[i] == 0) i++;
//				if (i < end)
//				{
//					task[i]--;
//				}
//			}
//			i++;
//			res++;
//
//			while (start < end && task[start] == 0)
//				start++;
//
//			if (start == end)
//				return res;
//
//		}
//		cout << res << endl;
//	}
//
//	return res;
//}

int leastInterval(vector<char>& tasks, int n)
{
	vector<pair<int, int>> task_cnt(26);
	n++;
	int time = 0;
	for (int i = 0; i < tasks.size(); i++)
		task_cnt[tasks[i] - 'A'].first++;
	sort(task_cnt.begin(), task_cnt.end(), greater<pair<int, int>>());
	int end = task_cnt.size() - 1;
	while (end >= 0 && task_cnt[end].first == 0) end--;
	
	while (true)
	{
		sort(task_cnt.begin(), task_cnt.end(), greater<pair<int, int>>());
		int found = false;
		bool finished = true;
		for (int i = 0; i <= end; i++)
		{
			finished &= (task_cnt[i].first == 0);
			if (task_cnt[i].first > 0)
			{
				if (!found && task_cnt[i].second == 0)
				{
					task_cnt[i].first--;
					found = true;
					task_cnt[i].second = (task_cnt[i].second + 1) % n;
				}
				else if (task_cnt[i].second > 0)
					task_cnt[i].second = (task_cnt[i].second + 1) % n;
			}
		}
		//cout << task_cnt << endl;
		if (finished)
			break;
		time++;
	}

	return time;
}

bool ismatch(string s, string p)
{
	vector<int> last_match;

	if (p.size() == 0)
		return false;
	
	if (s.size() == 0)
	{
		for (int i = 0; i < p.size(); i++)
		if (p[i] != '*')
			return false;
		return true;
	}

	if (p[0] == '?' || p[0] == s[0])
		last_match.push_back(0);
	else if (p[0] == '*')
	{
		for (int i = -1; i < (int)s.size(); i++)
			last_match.push_back(i);
	}

	if (last_match.empty())
		return false;

	for (int i = 1; i < p.size(); i++)
	{
		vector<int> tmp;

		if (p[i] == '*')
		{
			int start = (last_match.size() == 0 ? 0 : last_match.front());
			while (start < (int)s.size())
				tmp.push_back(start++);
		}
		else if (p[i] == '?')
		{
			for (int i = 0; i < last_match.size(); i++)
			if (last_match[i] + 1 < s.size())
				tmp.push_back(last_match[i] + 1);
		}
		else
		{
			for (int j = 0; j < last_match.size(); j++)
			{
				if (last_match[j] + 1 < s.size() &&
					s[last_match[j] + 1] == p[i])
					tmp.push_back(last_match[j] + 1);
			}
		}

		if (tmp.size() == 0)
			return false;

		last_match = tmp;
		cout << last_match << endl;
	}
	cout << last_match << endl;
	return last_match.back() + 1 == s.size();
}


vector<int> get_absdiff(vector<int>& arr)
{
	vector<int> res;
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = i; j < arr.size(); j++)
		{
			res.push_back(abs(arr[i] - arr[j]));
		}
	}
	return res;
}

int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2)
{
	vector<int> sum1 = get_absdiff(arr1);
	vector<int> sum2 = get_absdiff(arr2);
	int res = 0;
	cout << sum1 << endl;
	cout << sum2 << endl;
	for (int p = 0; p < sum1.size(); p++)
	{
		int i = p / arr1.size(), j = p % arr1.size();
		cout << i << ' ' << j << endl;
		res = max(res, abs(i - j) + sum1[p] + sum2[p]);
		cout << res << endl;
	}
	return res;
}

int searchPos(vector<int>& nums, int target)
{
	int start = 0, end = nums.size(), index = start + (end - start) / 2;

	while (start != end - 1)
	{
		if (nums[index] >= target)
			end = index;
		else if (nums[index] < target)
			start = index;

		index = start + (end - start) / 2;
	}

	if (target <= nums[index])
		return index;
	else
		return index + 1;
}

vector<int> findClosestElements(vector<int>& arr, int k, int x)
{
	int index = searchPos(arr, x);
	int start = index - k >= 0 ? index - k : 0;
	int end = index + k < arr.size() ? index + 1 : arr.size() - k + 1;

	int diff = 0;
	int s = start;
	for (int i = 0; i < k; i++)
		diff += abs(arr[start + i] - x);

	for (int i = start + 1; i < end; i++)
	{
		int new_diff = diff - abs(x - arr[i - 1]) + abs(x - arr[i + k - 1]);
		if (new_diff < diff)
			s = i;
		diff = new_diff;
	}

	vector<int> res;
	for (int i = 0; i < k; i++)
	{
		res.push_back(arr[s + i]);
	}

	return res;
}

int sumRegion(vector<vector<int>>& sum, int row1, int col1, int row2, int col2)
{

	int res = sum[row2][col2];

	if (col1 > 0)
		res -= sum[row2][col1 - 1];
	if (row1 > 0)
		res -= sum[row1 - 1][col2];
	if (row1 > 0 && col1 > 0)
		res += sum[row1 - 1][col1 - 1];

	return res;
}

vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k)
{
	if (mat.size() == 0 || mat[0].size() == 0)
		return vector<vector<int>>();

	vector<vector<int>> sum = vector<vector<int>>(mat.size(), vector<int>(mat[0].size()));
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
		{
			if (i > 0)
				mat[i][j] += mat[i - 1][j];
			if (j > 0)
				mat[i][j] += mat[i][j - 1];
			if (i > 0 && j > 0)
				mat[i][j] -= mat[i - 1][j - 1];
		}
		//cout << sum << endl;
	}
	cout << mat << endl;

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			int lr = max(i - k, 0), lc = max(j - k, 0), rr = min(i + k, (int)mat.size() - 1), rc = min(j + k, (int)mat[i].size() - 1);
			sum[i][j] = sumRegion(mat, lr, lc, rr, rc);
		}
		//cout << sum << endl;
	}

	return sum;
}

int distinctEchoSubstrings(string text) 
{
	unordered_set<string> vis;
	int res = 0;
	for (int i = 0; i < text.size(); i++)
	{
		for (int j = i + 1; j + (j - i) <= text.size(); j++)
		{
			if (text[i] == text[j] && vis.find(text.substr(i, (j - i) * 2)) == vis.end())
			{
				vis.insert(text.substr(i, (j - i) * 2));
				int k = 0;
				while (k + i < j)
				{
					if (text[i + k] != text[j + k])
						break;
					k++;
				}
				res += (k + i == j);
			}
		}
	}

	return res;
}

vector<int> getNoZeroIntegers(int n)
{
	int a = 1;
	string b;
	for (int i = 0; i < n; i++)
	{
		b = to_string(n - a);
		int idx = 0;
		while (idx < b.size())
		{
			if (b[idx] == '0')
				break;
			idx++;
		}
		
		if (idx == b.size())
			break;
	}

	return{ a, stoi(b) };
}

bool not_contain(string s)
{
	int idx = 0;
	while (idx < s.size())
	{
		if (s[idx] == '0')
			break;
		idx++;
	}

	return idx == s.size();
}

int minFlips(int a, int b, int c)
{
	int res = 0;
	for (int i = 0; i < 32; i++)
	{
		if (get_bit(c, i) == 1)
			res += (get_bit(a, i) | get_bit(b, i)) == 0;
		else
			res += (get_bit(a, i) == 1) + (get_bit(b, i) == 1);
	}
	return res;
}

vector<int> get_coordintate(char c)
{
	return { (c - 'A') / 6, (c - 'A') % 6};
}

int minimumDistance(string& word)
{
	vector<vector<int>> distance(26,vector<int>(26));
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			distance[i][j] = abs(i / 6 - j / 6) + abs(i % 6 + j % 6);

	cout << distance << endl;;
	int res = 0;
	
		
	return res;
}

int main()
{
	string s = "CAKE";
	cout << minimumDistance(s) << endl;
	return 0;
}

// SEND
// MORE
//MONEY

/*
D + E % 10 = Y;
N + R + c = E;
E + O + 
*/

/*
"aabaac"
"aadaaeaaf"
"aadaaeaabaafaac"
*/

//int main()
//{
//	vector<vector<char>> matrix = { 
//		{ '5', '3', '.', '.', '7', '.', '.', '.', '.' }, 
//		{ '6', '.', '.', '1', '9', '5', '.', '.', '.' }, 
//		{ '.', '9', '8', '.', '.', '.', '.', '6', '.' }, 
//		{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
//		{ '4', '.', '.', '8', '.', '3', '.', '.', '1' }, 
//		{ '7', '.', '.', '.', '2', '.', '.', '.', '6' }, 
//		{ '.', '6', '.', '.', '.', '.', '2', '8', '.' }, 
//		{ '.', '.', '.', '4', '1', '9', '.', '.', '5' }, 
//		{ '.', '.', '.', '.', '8', '.', '.', '7', '9' } 
//	};
//	stack<unordered_map<int, int>::iterator> s;
//	solveSudoku(matrix);
//	return 0;
//}
