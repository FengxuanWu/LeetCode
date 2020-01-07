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

int leastInterval(vector<char>& tasks, int n)
{
	n++;
	int res = 0;
	if (tasks.empty())
		return res;

	vector<int> task(26);
	

	for (int i = 0; i < tasks.size(); i++)
	{
		task[tasks[i] - 'A']++;
	}


	cout << task << endl;
	
	int start = 0, end = 0;
	while (end <task.size() && task[end] != 0)
		end++;

	while (start < end)//////////////
	{
		sort(task.begin() + start, task.end(), greater<int>());
		int cold_down = n;
		int i = start;
		cout << task << endl;
		while (cold_down--)
		{
			if (i < end && task[i] > 0)
				task[i]--;
			else
			{
				while (i < end && task[i] == 0) i++;
				if (i < end)
				{
					task[i]--;
				}
			}
			i++;
			res++;

			while(start < end && task[start] == 0)
				start++;

			if (start == end)
				return res;
			
		}
		cout << res << endl;
	}

	return res;
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

vector<int> split(string s, char c)
{
	vector<int> res;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '.')
			res.push_back(i);
	}
	if (s.back() != '.')
		res.push_back(s.size());
	return res;
}

int compareVersion(string version1, string version2) 
{
	version1.push_back('.');
	version2.push_back('.');

	if (version1.size() < version2.size())
	{
		for (int i = version1.size() - 1; i < version2.size(); i++)
		{
			if (version2[i] == '.')
				version1.push_back('.');
			else
				version1.push_back('0');
		}
	}

	if (version1.size() > version2.size())
	{
		for (int i = version2.size() - 1; i < version1.size(); i++)
		{
			if (version1[i] != '.')
				version2.push_back('0');
			else
				version2.push_back('.');
		}
	}

	vector<int> split1 = split(version1, '.');
	vector<int> split2 = split(version2, '.');

	int start1 = 0, start2 = 0;
	int v1 = 0, v2 = 0;

	for (int i = 0; i < split1.size(); i++)
	{
		v1 = atoi(version1.substr(start1, split1[i] - start1).c_str());
		//cout << version1.substr(start1, split1[i] - start1).c_str() << endl;
		v2 = atoi(version2.substr(start2, split2[i] - start2).c_str());
		//cout << version2.substr(start2, split2[i] -start2).c_str() << endl;
		start1 = split1[i] + 1, start2 = split2[i] + 1;
		if (v1 < v2)
			return -1;
		if (v1 > v2)
			return 1;
	}

	return 0;
}

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


int maxSubArray(vector<int>& nums, int start, int end)
{
	if (start > end)
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

int maxProfit(vector<int>& prices)
{
	int res = 0;
	if (prices.empty())
		return res;

	for (int i = 0; i < prices.size() - 1; i++)
	{
		prices[i] = prices[i + 1] - prices[i];
	}

	for (int i = 0; i < prices.size() - 1; i++)
	{
		res = max(res, maxSubArray(prices, 0, i) + maxSubArray(prices, i + 1, prices.size() - 1));
	}
	return res;
}

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


#define SINGLE 0
#define REPEAT 1

class RExpression
{
private:
	int type;
	char ch;
public:
	RExpression(){};
	RExpression(int type, char ch) :type(type), ch(ch){};

	int operator()(string s, int start)
	{
		int res = start;

		if (type == SINGLE)
		{
			res += (start < s.size() && (ch == '.' || ch == s[start]));
		}
		else
		{
			if (ch == '.')
			{
				res = s.size();
			}
			else
			{
				while (s[res] == ch)res++;
			}
		}
		return res;
	}
 
	int getType()
	{
		return this->type;
	}

	char getChar()
	{
		return this->ch;
	}
};

//void reverse(string& s)
//{
//	for (int i = 0; i < s.size() - i; i++)
//		swap(s[i], s[s.size() - 1 - i]);
//}

//bool isMatch(string s, string p)
//{
//	reverse(s);
//	reverse(p);
//
//	cout << s << endl;
//	cout << p << endl << endl;
//
//	vector<RExpression> exp;
//	for (int i = 0; i < p.size(); i++)
//	{
//		exp.push_back(RExpression(p[i] == '*', p[i + (p[i] == '*')]));
//		i += p[i] == '*';
//	}
//
//	vector<vector<int>> match(s.size(), vector<int>(exp.size()));
//
//	int j = 0;
//	for (int i = 0; i < s.size(); i++)
//	{
//		for (; j < exp.size(); j++)
//		{
//			int end = exp[j](s, i);
//			//前一个是循环并且匹配成功
//			if (end > i)
//			{
//				match[i][j] = match[i - (i > 0)][j - (j > 0)] & end > i;
//			}
//			else
//			{
//
//			}
//		}
//	}
//	
//}

/*
"aabcbcbcaccbcaabc"
".*a*aa*.*b*.c*.*a*"
*/

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


bool isInterleave(string s1, string s2, string s3) 
{
	int length = 0;
	string s = "";
	for (int i = 0; i < s3.size(); i++)
	{
		if (s3[i] == s1[length])
			length++;
		else
		{
			s.push_back(s3[i]);
		}
	}
	
	cout << s << endl;
	if (length != s1.size())
		return false;

	if (s != s2)
		return false;
	
	return  true;
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

void toBin(int n)
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

int search(vector<int>& nums, int target)
{
	int start = 0, end = nums.size(), index = (start + end) / 2;

	while (start != end - 1)
	{
		if (nums[index] == target)
			break;
		else if (nums[index] > target)
			end = index;
		else if (nums[index] < target)
			start = index;

		index = (start + end) / 2;
	}

	return nums[index] == target ? index : -1;
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

int lengthOfLIS(vector<int>& nums) 
{
	if (nums.size() < 2)
		return 1;

	vector<int> isl(nums.size(), 1);

	for (int i = 1; i < nums.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (nums[j] < nums[i])
			{
				isl[i] = max(isl[j] + 1, isl[i]);
			}
		}
		//cout << isl << endl;
	}

	int res = 0;
	for (int i = 0; i < isl.size(); i++)
		res = max(isl[i], res);

	return res;
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

int findMin(vector<int>& nums)
{
	int start = 0, end = nums.size(), mid = (start + end) / 2;

	while (start != end - 1)
	{
		//cout << start << ' ' << mid << ' ' << end << endl;
		if (nums[start] < nums[mid])
		{
			start = mid;
		}
		else
		{
			end = mid;
		}

		mid = (start + end) / 2;
	}

	//cout << start << ' ' << mid << ' ' << end << endl;
	if (nums.size() == end)
		return nums[0];

	if (nums[end] < nums[mid])
	{
		mid = end;
	}

	return nums[mid];
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


vector<string> permute_help(string& nums, vector<int> used, int n)
{
	vector<string> res;
	//cout << used << endl;
	//cout << n << endl;

	if (n == nums.size())
		return vector<string>(1, string());

	for (int i = 0; i < nums.size(); i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			vector<string> tmp = permute_help(nums, used, n + 1);

			for (int j = 0; j < tmp.size(); j++)
			{
				//cout << tmp << endl;
				//cout << i << endl;

				tmp[j].push_back(nums[i]);
				if (find(res, tmp[j]) == res.size())
					res.push_back(tmp[j]);
			}

			used[i] = 0;
		}
	}
	return res;
}

vector<string> Permutation(string& nums)
{
	if (nums.empty())
		return vector<string>();
	return permute_help(nums, vector<int>(nums.size()), 0);
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

//#define to_digit(c)(c - 'a')
//#define TO_DIGIT(c)(c - '0') 
//string decodeAtIndex(string s, int k) 
//{
//	string res = "";
//	vector<int> sub_string_start;
//	vector<int> sub_string_end;
//	vector<int> digits;
//	int length = 0;
//	int cnt = 0;
//
//	for (int i = 0; i < s.size(); i++)
//	{
//		if (IS_LETTER(s[i]))
//		{
//			if (sub_string_start.empty() || sub_string_start.back() != i)
//				sub_string_start.push_back(i);
//		}
//		else
//		{
//			digits.push_back(i);
//
//			//start to consider about k
//			if (length == 0)
//		}
//	}
//
//
//	return res;
//}

#define IS_DIGIT(c)(c >= '0' && c <= '9')
#define IS_LETTER(c) (c >= 'a' && c <= 'z' || c >= 'A' || c <= 'Z')
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

vector<int> majorityElement(vector<int>& nums)
{
	pair<int, int> majority1, majority2;

	for (int i = 0; i < nums.size(); i++)
	{
		if ((majority1.second == 0 || majority1.first == nums[i]) && majority2.first != nums[i])
		{
			if (majority1.second == 0)
			{
				majority1.first = nums[i];
			}
			majority1.second += majority1.first == nums[i];
		}
		else if (majority2.second == 0 || majority2.first == nums[i])
		{
			if (majority2.second == 0)
				majority2.first = nums[i];
			majority2.second += majority2.first == nums[i];
		}
		else
		{
			majority1.second--;
			majority2.second--;
		}

		cout << "m1\t" << majority1 << endl;
		cout << "m2\t" << majority2 << endl;
		cout << endl;
	}
	
	majority1.second = majority2.second = 0;
	//cout << majority1.first << endl;
	//cout << majority2.first << endl;

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == majority1.first)
			majority1.second++;
		if (nums[i] == majority2.first && majority1.first != majority2.first)
			majority2.second++;
	}

	vector<int> res;
	if (majority1.second > nums.size() / 3)
		res.push_back(majority1.first);
	if (majority2.second > nums.size() / 3)
		res.push_back(majority2.first);
	return res;
}

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

int minFallingPathSum(vector<vector<int>>& maze) 
{
	if (maze.size() == 0)
		return 0;

	for (int i = 1; i < maze.size(); i++)
	{
		for (int j = 0; j < maze[0].size(); j++)
		{
			int minimum = maze[i - 1][j];
			if (j > 0)
				minimum = min(maze[i - 1][j - 1], minimum);
			if (j < maze[0].size() - 1)
				minimum = min(maze[i - 1][j + 1], minimum);
			maze[i][j] += minimum;
		}
	}

	cout << maze << endl;

	int res = INT_MAX;
	for (int i = 0; i < maze.back().size(); i++)
		res = min(maze.back()[i], res);
	return res;
}

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

int mctFromLeafValues(vector<int>& arr)
{
	if (arr.size() == 0)
		return 0;
	if (arr.size() == 1)
		return arr.back();
	if (arr.size() == 2)
		return arr[0] * arr[1];
	
	int max_idx = arr[0] > arr[1] ? 0 : 1, current_tree = arr[0] * arr[1];
	for (int i = 2; i < arr.size(); i++)
	{
		if (arr[i] > arr[max_idx])
		{
			current_tree += arr[i] * arr[max_idx];
			max_idx = i;
		}
		else
		{
			if (arr[i] > arr[i - 1])
			{
				current_tree += arr[i] * arr[i - 1] + (arr[i] - arr[i - 1]) * arr[max_idx];
			}
			else
				current_tree += arr[max_idx] * arr[i];
		}
	}
	
	return current_tree;
}

int main()
{	
	vector<int> arr = { 6, 2, 3, 4, 7, 1, 5, 6, 2};
	cout << mctFromLeafValues(arr) << endl;
	return 0;
}
