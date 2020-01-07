// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Trie.h"

int main()
{
	Trie trie;

	vector<string> products({"mob"});
		string searchWord = "mouse";

	for (int i = 0; i < products.size(); i++)
	{
		trie.insert(products[i]);
	}

	for (int i = 1; i <= searchWord.size(); i++)
	{
		cout << trie.searchStart(searchWord.substr(0, i)) << endl;
	}

	return 0;
}

