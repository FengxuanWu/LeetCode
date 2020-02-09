#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;
#define STATUS_EMPTY 0
#define STATUS_LEVEL_MIN 1
#define STATUS_LEVEL_MAX 10

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define DIRECTION_UP 2
#define DIERCTION_DOWN 3

class Block
{
	int status;
public:
	Block(int s) : status(s) {};

	int get_val()
	{
		return status == STATUS_EMPTY ? 0 : (1 << status);
	}

	void set_val(int n)
	{
		status = n;
	}

	int elimate()
	{
		return status = STATUS_EMPTY;
	}

	int level_up()
	{
		return ++status;
	}
};


class Game
{
	vector<Block> pannel;
	int m_row;
	int m_col;
public:
	void get_random()
	{
		pannel[rand() % pannel.size()].set_val(rand() % 2 + 1);
	}

	int predecessor(int idx, int direction)
	{
		if (direction < 2)
			return idx - 1;
		else
			return idx - m_col;
	}

	int successor(int idx, int direction)
	{
		if (direction < 2)
			return idx + 1;
		else
			return idx + m_col;
	}

	vector<int> check(int direction)
	{
		int dir = direction % 2;

		int row = dir ? m_col - 1 : 0;
		int col = dir ? m_row - 1 : 0;

		int next_check = dir ? predecessor(row * m_col + col) : successor(row * m_col + col);

	}

	void slide(int direction)
	{
		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				
			}
		}
	}
};

ostream& operator<<(ostream& os, Block& b)
{
	os << b.get_val();
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T>& v)
{
	for (auto e : v)
		os << e << ' ';
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>>& v)
{
	for (auto e : v)
		os << e << endl;
	return os;
}