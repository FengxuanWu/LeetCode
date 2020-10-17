#include "stdafx.h"

#include <stdlib.h>
#include <string>

#define to_idx(c) ((c) - 'a')

typedef struct CTrie
{
	int word;
	struct CTrie* children[26];
} CTrie;

CTrie* CTrieCreate()
{
	CTrie* trie = (CTrie*)malloc(sizeof(CTrie));
	memset(trie, 0, sizeof(CTrie));
	return trie;
}

void CTrieFree(CTrie* CTrie)
{
	for (int i = 0; i < 26; i++)
	{
		if (CTrie->children[i])
			CTrieFree(CTrie->children[i]);
	}
	free(CTrie);
}

void CTrieInsert(CTrie* trie, char* word)
{
	CTrie* iter = trie;
	while (*word)
	{
		if (iter->children[to_idx(*word)] == NULL)
			iter->children[to_idx(*word)] = CTrieCreate();

		iter = iter->children[to_idx(*word)];
		if (*(word + 1) == NULL)
			iter->word = 1;
		word++;
	}
}

int CTrieSearchPrefix(CTrie* trie, char* s)
{
	int idx = 0;
	while (s[idx] && trie)
	{
		trie = trie->children[to_idx(s[idx])];
		if (trie && trie->word) {
			return idx + 1;
		}
		++idx;
	}

	return -1;
}

bool CTrieStartsWith(CTrie* trie, char* prefix) 
{
	while (*prefix && trie)
		trie = trie->children[to_idx(*prefix++)];
	return *prefix == 0 && trie;
}

int CTrieSearch(CTrie* trie, char* s)
{
	while (*s && trie)
		trie = trie->children[to_idx(*(s++))];
	return *s == 0 && trie->word;
}