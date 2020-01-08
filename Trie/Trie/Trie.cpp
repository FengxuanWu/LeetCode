// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

int main()
{
	string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	vector<string> wordDict = { "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa" };

	for (string& s : wordBreak(s, wordDict))
		cout << s << endl;

	return 0;
}

