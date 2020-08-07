// Trie.cpp : Defines the entry point for the console application.
//

#include "Trie.h"

vector<vector<string>> mem;

vector<string> wordBreakHelper(string& s, Trie& trie, int idx)
{
	vector<string> res;
	if (idx == s.size())
		return vector<string>(1, "");

	if (mem[idx].size())
	{
		cout << mem << endl;
		system("pause");
		return mem[idx];
	}
		

	string substr = "";
	
	for (int i = 0; idx + i < s.size() && trie.startsWith(substr); i++)
	{
		substr += s[idx + i];
		if (trie.search(substr))
		{
			vector<string> r = wordBreakHelper(s, trie, idx + substr.size());
			for (int i = 0; i < r.size(); i++)
				res.push_back(substr + ' ' + r[i]);
		}
	}
	mem[idx] = res;
	return res;
}

vector<string> wordBreak(string s, vector<string>& wordDict)
{
	Trie trie;
	for (int i = 0; i < wordDict.size(); i++)
		trie.insert(wordDict[i]);
	mem.resize(s.size());
	return wordBreakHelper(s, trie, 0);
}

int numDecodings(string s)
{
	if (s.size() < 2)
		return s.size();

	int idx_1 = s[0] > '0', idx_2 = 1;
	int idx = 0;
	for (int i = 1; i < s.size(); i++)
	{
		int val = stoi(s.substr(i - 1, 2));
		idx = idx_1 * (s[i] > '0') + (10 <= val && val <= 26) * (idx_2);
		if (idx == 0)
			break;
		idx_2 = idx_1;
		idx_1 = idx;

		cout << idx_2 << endl;
		cout << idx_1 << endl;
		cout << idx << endl;
		cout << endl;
	}
	return idx;
}

vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries)
{
	Trie tire;
	vector<string> res;
	for (int i = 0; i < wordlist.size(); i++)
		tire.insert(wordlist[i]);
	for (int i = 0; i < queries.size(); i++)
		res.push_back(tire.match(queries[i]));
	return res;
}

char kthSingleChar(int k, string& str)
{
	vector<int> bar(256);
	for (int i = 0; i < str.size(); i++)
		bar[str[i]]++;
	cout << bar << endl;
	for (int i = 0; i < str.size(); i++)
	{
		if (bar[str[i]] == 1)
		{
			cout << k << endl;
			if (--k == 0)
				return str[i];
		}
	}
	return -1;
}

int main()
{
	//string s;
	//while (cin >> n)
	//{
	//	cin >> s;
	//	cout << s << endl;
	//	int c = kthSingleChar(n, s);
	//	if (c == -1)
	//		cout << "Myon~" << endl;
	//	else
	//		cout << '[' <<  (char)c << ']'<< endl;
	//}
	return 0;
}

