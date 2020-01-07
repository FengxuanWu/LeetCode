// Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.h"

Node* construct_graph(const vector<vector<int>>& graph)
{
	int num_node = graph.size();
	vector<Node*> res;
	for (int i = 0; i < graph.size(); i++)
		res.push_back(new Node(i + 1));
		
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph.back().size(); j++)
		{
			if (graph[i][j])
				res[i]->neighbors.push_back(res[j]);
		}
	}

	return res[0];
}

class GraphPrinter : public Func
{
public:
	//GraphPrinter(){ cout << 1 << endl; };
	void operator()(void* node)
	{
		Node* n = ((Node*)node);
		cout << n << ' ';
	}
};

void dfs_traverse(Node* node, map<Node*, bool>& visited, Func& func)
{
	if (visited[node])
		return;
	visited[node] = true;
	func(((void*)(node)));

	vector<Node*>& neighbors = node->neighbors;
	for (int i = 0; i < neighbors.size(); i++)
	{
		dfs_traverse(neighbors[i], visited, func);
	}
}

void travese_graph(Node* node)
{
	Func* graph_printer = new GraphPrinter();
	map<Node*, bool> visited;
	dfs_traverse(node, visited, *graph_printer);
}

void dfs_clone(Node* node, map<Node*, bool>& visited, Node*& clone_node, map<int, Node*>& address)
{
	if (visited[node])
	{
		clone_node = address[node->val];
		return;
	}
		
	visited[node] = true;
	clone_node = new Node(node->val, vector<Node*>(node->neighbors.size(), NULL));
	address[clone_node->val] = clone_node;
	//cout << clone_node->val << endl;
	vector<Node*>& neighbors = node->neighbors;

	for (int i = 0; i < neighbors.size(); i++)
		dfs_clone(neighbors[i], visited, clone_node->neighbors[i], address);
}

Node* cloneGraph(Node* node)
{
	Node* clone_node = NULL;
	map<Node*, bool> visited;
	map<int, Node*> address;
	dfs_clone(node, visited, clone_node, address);
	return clone_node;
}

void process_one_layer(vector<int>& indegree, vector<int>& res, vector<int> curr)
{
	for (int i = 0; i < (int)(curr.size() - 1); i++)
	{
		int idx = i;
		for (int j = i + 1; j < curr.size(); j++)
			idx = indegree[curr[j]] < indegree[curr[idx]] ? j : idx;
		swap(curr[idx], curr[i]);
		res.push_back(curr[i]);
	}
	if (!curr.empty())
		res.push_back(curr.back());
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
{
	vector<vector<int>> graph(numCourses, vector<int>());
	vector<int> indegree = vector<int>(numCourses);
	int start_point = 0;
	for (int i = 0; i < prerequisites.size(); i++)
	{
		graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
		indegree[prerequisites[i][0]]++;
	}

	//find start node
	while (start_point < indegree.size())
	if (indegree[start_point] == 0)
		break;
	else
		start_point++;

	queue<int> q;

	vector<int> res;
	q.push(start_point);
	res.push_back(start_point);
	int cnt = 1;
	int count = 0;
	vector<int> visited(numCourses);
	visited[start_point] = true;
	vector<int> courses;
	while (!q.empty())
	{
		while (cnt--)
		{
			for (int c : graph[q.front()])
			{
				//if (courses.end() != find(courses.begin(), courses.end(), c) || visited[c])
				if (visited[c])
					continue;
				visited[c] = true;
				courses.push_back(c);
				q.push(c);
			}
			q.pop();
		}

		//cout << courses << endl;
		process_one_layer(indegree, res, courses);
		cnt = courses.size();
		courses.clear();
	}
	for (int i = 0; i < numCourses; i++)
	{
		if (!visited[i])
			res.push_back(i);
	}
	return res;
}


int string_subtraction(string& s1, string& s2)
{
	int res = 0, cnt = min(s1.size(), s2.size());
	for (int i = 0; i < cnt; i++)
		res += s1[i] != s2[i];
	return res;
}

int build_graph_ladder(string begin, string end, vector<vector<int>>& graph, vector<string>& word_list)
{
	int end_point = -1;
	for (int i = 0; i < word_list.size() - 1; i++)
	{
		end_point = string_subtraction(end, word_list[i]) == 0 ? i : end_point;
		for (int j = i + 1; j < word_list.size(); j++)
		{
			if (string_subtraction(word_list[i], word_list[j]) == 1)
			{
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}
		
	return (end_point == -1 && string_subtraction(end, word_list.back()) == 0) ? word_list.size() - 1 : end_point;
}

vector<vector<string>> bfs_ladder(int start, int end, vector<vector<int>>& graph, vector<string>& wordList)
{
	vector<int> traversed(graph.size());
	vector<vector<int>> res(1, vector<int>(1, start));

	int cnt = res.size();
	int next_layer = 0;
	int depth = 1;
	bool flag = false;
	int start_idx = -1;
	//cout << graph << endl;
	while (!res.empty())
	{
		while (cnt--)
		{
			traversed[res.front().back()] = 1;
			vector<int> tmp = res.front();
			for (int i = 0; i < graph[res.front().back()].size(); i++)
			{
				if (traversed[graph[res.front().back()][i]])
					continue;

				if (graph[res.front().back()][i] == end)
				{
					if (flag == false)
						start_idx = res.size();
					flag = true;
				}

				tmp.push_back(graph[res.front().back()][i]);
				
				if (flag)
				{
					if (graph[res.front().back()][i] == end)
						res.push_back(tmp);
				}
				else
					res.push_back(tmp);

				tmp.pop_back();
					
				next_layer++;
			}

			res.erase(res.begin());
			if (start_idx != -1)
				start_idx--;

			cout << res << endl;
		}

		if (flag)
			break;
		cnt = next_layer;
		next_layer &= 0;
		depth++;
	}

	vector<vector<string>> ret;
	for (int i = start_idx; i < res.size(); i++)
	{
		vector<string> tmp;
		for (int j = 0; j < res[i].size(); j++)
			tmp.push_back(wordList[res[i][j]]);
		ret.push_back(tmp);
	}

	return ret;
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
{
	vector<vector<string>> res;

	wordList.insert(wordList.begin(), beginWord);
	vector<vector<int>> graph(wordList.size());
	int end = build_graph_ladder(beginWord, endWord, graph, wordList);

	if (end == -1)
		return res;

	return bfs_ladder(0, end, graph, wordList);
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) 
{
	//vector<int> in_degree(n);
	vector<vector<int>> graph(n);
	vector<vector<int>> res;
	
	for (int i = 0; i < connections.size(); i++)
	{
		//in_degree[connections[i][0]]++;
		//in_degree[connections[i][1]]++;
		graph[connections[i][0]].push_back(connections[i][1]);
		graph[connections[i][1]].push_back(connections[i][0]);
	}
	cout << graph << endl;
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i].size() == 1)
		{
			res.push_back({ i, graph[i].front() });
		}
	}
	//cout << res << endl;
	return res;
}

//map<int, vector<int>> graph;
//vector<int> path;
//
//void dfs(int current, vector<int> visited, int d)
//{
//	visited[current] = true;
//	for (int i = 0; i < graph[current].size(); i++)
//	{
//		int next = graph[current][i];
//		if (visited[next])
//			continue;
//		
//		path[next] = d + 1;
//		dfs(graph[current][i], visited, d + 1);
//	}
//}
//
//
//int treeDiameter(vector<vector<int>>& edges) 
//{
//	for (int i = 0; i < edges.size(); i++)
//	{
//		graph[edges[i][0]].push_back(edges[i][1]);
//		graph[edges[i][1]].push_back(edges[i][0]);
//	}
//
//	if (graph.size() == 0)
//		return 0;
//
//	vector<int> visited(graph.size());
//	path = vector<int>(graph.size());
//	dfs(0, visited, 0);
//	int max = 0;
//	int index = 0;
//	for (int i = 0; i < path.size(); i++)
//	{
//		if (max < path[i])
//		{
//			max = path[i];
//			index = i;
//		}		
//	}
//
//	dfs(index, visited, 0);
//	for (int i = 0; i < path.size(); i++)
//	{
//		if (max < path[i])
//		{
//			max = path[i];
//			index = i;
//		}
//	}
//	return max;
//}
vector<string> split(string& s, char split = ' ')
{
	size_t sub_start = 0, sub_end = 0;
	while (sub_end < s.size() && s[sub_end] == split)
		sub_end++;
	
	vector<string> res;
	while (sub_end < s.size())
	{
		sub_start = sub_end;
		while (sub_end < s.size() && s[sub_end] != split)sub_end++;
		res.push_back(s.substr(sub_start, sub_end - sub_start));
		while (sub_end < s.size() && s[sub_end] == split)sub_end++;
	}

	return res;
}

void generateHelper(map<string, vector<string>>& graph, string& curr, map<string, bool>& used, vector<string> words, string s, vector<string>& res)
{
		
}

vector<string> generateSentences(vector<vector<string>>& synonyms, string text)
{
	map<string, vector<string>> graph;
	set<string> substitute;
	for (int i = 0; i < synonyms.size(); i++)
	{
		string word1 = synonyms[i][0], word2 = synonyms[i][0];
		if (substitute.find(word1) == substitute.end() && text.find(word1) != -1)
			substitute.insert(word1);
		if (substitute.find(word2) == substitute.end() && text.find(word2) != -1)
			substitute.insert(word2);
		graph[word1].push_back(word2);
	}

	vector<string> res(1, text);
	map<string, bool> used;
	
	return res;
}

void dfs(vector<vector<int>>& m, int curr, vector<int>& used)
{
	if (used[curr])
		return;
		
	used[curr] = 1;
	m[curr][curr] = 0;
	for (int i = 0; i < m[curr].size(); i++)
	{
		if (m[curr][i])
		{
			m[curr][i] = 0;
			m[i][curr] = 0;
			dfs(m, i, used);
		}
	}
}

int findCircleNum(vector<vector<int>>& m) 
{
	if (m.size() == 0 || m[0].size() == 0)
		return 0;
	vector<int> used(m.size());
	int ans = 0;
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[0].size(); j++)
		{
			if (m[i][j])
			{
				ans++;
				dfs(m, i, used);
			}
		}
	}

	return ans;
}

void dfs(vector<vector<int>>& grid, int row, int col, int& res)
{
	res += 1;
	grid[row][col] = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		if (grid[i][col] == 1)
			dfs(grid, i, col, res);
    	}

	for (int i = 0; i < grid[row].size(); i++)
	{
		if (grid[row][i] == 1)
			dfs(grid, row, i, res);
	}
}

int countServers(vector<vector<int>>& grid) 
{
	int ans = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			int res = 0;
			if (grid[i][j])
			{
				dfs(grid, i, j, res);
				if (res > 1)
					ans += res;
				//cout << res << endl;
			}
		}	
	}
	return ans;
}

int networkDelayTime(vector<vector<int>>& times, int n, int k)
{
	vector<vector<vector<int>>> graph(n + 1);
	vector<int> time(n + 1, INT_MAX);

	for (int i = 0; i < times.size(); i++)
		graph[times[i][0]].push_back(vector<int>({ times[i][1], times[i][2] }));

	queue<int> q;
	q.push(k);

	while (!q.empty())
	{
		for (int i = 0; i < graph[q.front()].size(); i++)
		{
			int target = graph[q.front()][i][0], delay = graph[q.front()][i][1];
			if (time[target] > delay)
			{
				time[target] = delay;
				q.push(target);
			}
		}
		q.pop();
	}

	int res = 0;
	for (int i = 0; i < time.size(); i++)
	{
		res = max(res, time[i]);
	}

	return res == INT_MAX ? -1 : res;
}
vector<int> bfs(vector<vector<int>>& friends, int id, int level)
{
	vector<int> res;
	queue<pair<int, int>> q;
	vector<int> checked(friends.size());
	q.push(make_pair(id, 0));
	checked[id] = 1;
	 
	while (!q.empty() && q.front().second < level)
	{
		int curr = q.front().second;
		while (!q.empty() && q.front().second == curr)
		{
			int f = q.front().first;
			for (int i = 0; i < friends[f].size(); i++)
			{
				if (!checked[friends[f][i]])
				{
					q.push(make_pair(friends[f][i], curr + 1));
					checked[friends[f][i]] = 1;
				}
			}
			q.pop();
		}
	}

	while (!q.empty())
	{
		res.push_back(q.front().first);
		q.pop();
	}

	return res;
}

vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level)
{
	vector<int> fs = bfs(friends, id, level);
	vector<string> res;
	unordered_map<string, int> s;
	map<int, vector<string>> freq;
	
	for (int i = 0; i < fs.size(); i++)
	{
		for (int j = 0; j < watchedVideos[fs[i]].size(); j++)
			s[watchedVideos[fs[i]][j]]++;
	}
		
	for (auto it = s.begin(); it != s.end(); it++)
		freq[(*it).second].push_back((*it).first);
	
	for (auto it = freq.begin(); it != freq.end(); it++)
	{
		vector<string> &r = ((*it).second);
		sort(r.begin(), r.end());
		for (string& s : r)
			res.push_back(s);
	}
	return res;
}

int main()
{
	vector<vector<string>> videos = { { "vsb", "ccxdjk", "iqbl", "c", "mlx", "dvki", "q", "dlzzux", "tim", "vs", "snrmjhuj", "btq", "fh", "nira", "riqip", "mwd", "curlrr", "t", "oveec", "vgp", "ljfezm", "mdteijvv", "r", "u", "mxr", "oa", "tvnilnm", "bdpybuww", "z", "d", "qqy", "rizsul", "whzthdrl" }, { "yb", "nxlivu", "t", "nmljyko", "utqe", "k", "qf", "kywdsapg", "ufmwhdh", "kvhzvo", "lpuyvxgn", "mrdspiee", "m", "dzaucfo", "vqzjeeq", "ia", "mzuwxzhr", "arzhnfv", "kvh", "yr", "fms" }, { "nhzb", "wqwt", "hm" }, { "dsubmcrd", "bqhyaajo", "xnfte", "yruoqz", "rfwmwmz", "pile", "sifyx", "xl", "eiiilm", "soaee", "hgczs", "rnwh", "rom", "cuce", "a", "mnveste", "hm", "jgv", "lxfhjwe", "prjcqj", "woaj", "tl", "itbbzkfz", "udd", "ushxgqq", "dwgmvqe", "xawdz", "ysmv", "rthibufv", "niyv", "mipdvef", "o", "p", "mxrk", "dcvx", "n", "gftqgqmq", "ghlvsy", "kb", "btfejpbs", "sm", "mz", "milpb", "anjsxkze", "ctzzy", "nmqzas", "bs", "d", "klyrbu", "scpucr", "kqzrafkl", "eses", "mk", "lkitlbw", "yu", "ziym", "sztcc", "inc", "jrx", "hgdix", "bxqjzzgr", "rk", "jqebol", "nxfrbw", "fghdses", "xi", "gzbloktx", "huaapb", "irb", "h", "qf", "q", "gojh", "qlkmucgt", "gvt", "sntpl", "wskkcun", "wqzp", "tvxsyotp", "ivq", "syzmt", "ijaty", "z", "olhqogwp", "wuemnb", "lz", "i", "j", "akkjszb", "wckd", "ey", "ntkha", "yyy", "jjmnqo", "gn", "tbth", "hwmm", "texj", "awwvjo", "fvealnrk" }, { "ktdsujzr", "najyc", "dqhtxuxi", "lzhbdtq", "ejb", "ga", "n", "c", "a", "r", "kzatar", "pgij", "hfgmb", "rwob", "kndasf", "yf", "hfjz", "bz", "xecoeh", "x", "lbsco", "zhvf", "bg", "cz", "jwiq", "hxbxiyg", "lloyvt", "vmcnhpk", "tud", "cyzn", "rjkyl", "ollkmpq", "l", "jfj", "rwx", "fou", "efc", "hlukf", "pjcne", "odevkc", "prb", "ulxl", "zquzvl", "udfmbi", "bhjk", "hlybhjw", "g", "eh", "qiefhc", "sqqrt", "osqpfql", "nzci", "hyee", "afpl", "bzl", "th", "couu", "tkfs", "prbblp", "epcqkv", "tkzsc", "kncicvuk", "f", "hkiijp", "ajfujbd", "ntgilyu" }, { "sjtivfke", "dmlqxs", "moep", "bxuh", "xc", "q", "spwkqzfs", "mamrxrxo", "ssl", "x", "lohwuv", "coylg", "eob", "skzfsp", "ashtbouf", "modk", "efkef", "hrwno", "qrjfqtqj", "jvev", "k", "nm", "too", "lgbcxddr", "eomfpoq", "s", "sopm", "lyyft", "fyarb", "rh", "kokxdmbx", "inokqdfm", "txpqeke", "etghzz", "oued", "nb", "elrkimam", "wojxwjus", "kyjfdpf", "eodrdrkk", "vrukxskr", "kpwmrgfh", "thby", "tybkna", "llttvn", "zjhk", "wmvyfam", "tzythh", "tk", "gwjdnaz", "cznedr", "yke", "nkruwqi", "gffr", "edo", "nek", "tealyf", "hwps", "bucerpse", "lwei", "cmpaqo", "xhgw", "biqgc", "zy", "mk", "ow", "vienluly", "nnlrggc", "hha", "vmoz", "sdbfqabn", "nehwy", "nyksxb", "ewqlsbld", "uudn", "zal", "eja", "uapcyzsn", "pr", "er", "utrnhqm", "xkodcgst", "ddldgd", "aq", "hcjptbs", "rjmubvt", "i", "ohikypor", "xwo", "jssfkqvm", "vrtmpyu", "jace", "dlijzrje" }, { "obo", "xskrlewa", "yitz", "zo", "auixq", "s", "ddvkttu", "ctpqksvb", "fbtd", "d", "yzgfr", "hgc", "wsnite", "szhct" }, { "a", "tjpnnzc", "gyv", "u", "nllqefz", "hzbl", "ok", "hiew", "dpvxzta", "jiyzwjgz", "wum", "z", "oraehpu", "jw", "gqkdhhp", "fp", "wututn", "rnyaume", "ebjmtnu", "gt", "ptniq", "kz", "rwr", "vvarv", "yl", "iydjezcn", "apsxeyy", "pzyhqam", "n", "hv", "o", "jt", "l", "c" }, { "s", "ljcrp", "kyfulq", "kthh", "jjrk", "savpi", "ehfc", "mgefr", "km", "fbog" }, { "wj", "xujq", "kccchdqo", "atfonrdg", "h", "gqtjj", "lijba", "u", "bgckovjd", "vdga", "uett", "o", "r", "pfra", "ecae", "scqrig", "arilirm", "qqroicf", "smetgqaq", "k", "hkm", "n", "qzczwber", "rmrisbg", "jwmj", "s", "grqxr", "hcg", "fbvmjaez", "bw", "pfgsozv", "vm", "cekq", "pqvlnsho", "mlmzs", "mtdf", "canspb", "duuyholq", "kv", "i", "esfnvj", "xhpxmaqi", "ji", "ku", "hjx", "fo", "muyozv", "vvdspscv", "b", "frptw", "aokhhl", "a" }, { "mefh", "mb", "kao", "bnh", "vqogb", "nmqniok", "c", "xxnfnfrq", "inx", "jlwomrmj", "lrrz", "iavc", "wmfiy", "pafpd", "edmb", "cdo", "zabibqpx", "ltod", "kmumjc", "xorl", "nwxxnsi", "ebk", "mcuszk", "eyx", "rg", "whltquwf", "jfxe", "nplwybr", "al", "egmo", "ntkpk", "st", "y", "rxp", "cac", "f", "gxomw", "wvirm", "wm", "hcxxkevt", "u", "ubjlyva", "ksayrkxz", "wyxbsvo", "nm", "sa", "ylfmxbe", "qwtnu", "zsp", "sztix", "rsnekfo", "srvequc", "impxbzu", "fuimi", "ia", "vz", "oe" }, { "zhbh", "dd", "s", "bi", "eldbzmz", "frsp", "ltm", "kqc", "a", "docav", "x", "rjsty", "omdzu", "juvy", "qqx", "l", "dnzveidl", "ygkte", "tahw", "luenvknt", "dibqjwqk", "ghxh", "liapyqe", "ypcqzid", "dnme", "vo", "fgil", "lxisye", "h", "pytra", "azfwgi", "cnwl", "yygdam", "skvznk", "mytiy", "tcznht", "lyjwadtq", "f", "yroj", "mtacmex", "pvmp", "nz", "wvp", "ujry", "j", "zeiuq", "penkq", "gibjqs", "pjifj", "zkeim", "vpxfmbcs", "kbqx", "bnzdt", "ealhtl", "whqcbka", "afzxizvt", "znju", "bbp", "rvvdmjn", "nssptg" }, { "kz", "ufyhqpc", "vmgiyaj", "i", "ft", "yownj", "jz", "p", "irg", "bvm", "s", "axmkd", "ftwgc", "ywv", "qsxahmv", "v", "q", "ytzyfbx", "ungfhct", "rrkvvigq", "mhvjt", "wewui", "sxiquh", "rvad", "ifxk", "fuub", "miig", "mbybe", "njlmyltg", "izipt", "zsl", "mbc", "cypgo", "bikaw", "znnnyltx", "ygxnmjdc", "wkl", "wmdmbnt", "dhwp", "fvehtdw", "kqozyf", "upsfbqg", "yedi", "a", "jgbjvv", "ecw", "sni", "cgy", "tng", "rpftczp", "gcve", "gttw", "ric", "clqifv", "nzrswrhe", "zn", "lhovrmk", "byb", "tofvxo", "leogrp", "tgeth", "dvcuh", "qgvjpwb", "guwbjxj", "nayo", "nhudfq", "x", "faqpplr", "autvnmh", "r", "u", "ukbe", "wfoeeiqm", "qd", "wm" }, { "gbqnhp", "fhgq", "uwjpzy", "ygjd", "y", "t", "czqufo", "nx", "rbz", "kvx", "oxgmoz", "ml", "j", "sllu", "d", "zymjwfjx", "xkkg", "b", "w", "tok", "i", "cwuha", "ynl", "zpbmd", "wnyhh", "siaazey", "wyelcthr", "eme", "geetwd", "ybt", "ilaew", "c", "wnwmjvem", "ylzoljp", "iaj", "wbpb", "azuhewmz", "hstifxg", "ckl", "dz", "gkzr", "zywcnslf", "tdl", "vpt", "on", "ccvu", "kmlsk", "qttucgn", "qxplwd", "kahjnvve", "iwqt", "f", "bvdiu", "fw", "shonbepz", "qjxmcs", "evwqhnp", "sx", "rqfbwg", "alhh", "rnfzhah", "u" }, { "za", "rih", "kxedin", "tbrbvo", "x", "jjvxmj", "pjvdsvu", "w", "nc", "duah", "cgkgjjoo", "womc", "c", "xtogx", "nfutv", "mxohhpa", "ipply", "sx", "gw", "mgnbxfyw" }, { "nlqezcq", "bsy", "yqrx", "ujjpeawo", "vvslnwl", "yigv", "spivtnji", "cdkovvjq", "qkhe", "iwh", "avnmhec", "fo", "zzhjtmi", "j", "dxn", "xvjwn", "v", "dyf", "ndblukjb", "zoblj", "ixif", "qkrcw", "e", "mkk", "fjayiaru", "n", "yaztqmdd", "z", "cpglsbn", "rkgaeppi", "uqdnorq", "zcbne", "zygcol", "st", "zvdgtk", "fky", "gx", "rscps", "qomlqyuq", "zfveafjf", "gye", "ozec", "qrmmtuxn", "pipevvg", "bitzeog", "mou", "l", "vejs", "keztuxcv", "vccaavc", "er", "bgnkv", "vlgvf", "cldnokq", "av", "ytwggcv", "oqa", "wztjvj", "obb", "fyatk", "dhizu", "pgcejauh", "yvf", "stod", "g", "uufidc", "hmzjr", "jej", "jq", "yy", "omuy", "az", "puajwpp", "fgprgq", "enwx", "wlph", "h", "lc", "kxnooov", "lbgvieqy", "zy", "gkdaxuh", "wzmg", "jvylh", "tijf", "al", "wsy", "poyvdht" } };
	vector<vector<int>> friends = { { 13, 1, 14, 4, 3, 10, 12, 9, 6, 7 }, { 9, 10, 0, 7, 5, 13, 6, 14, 2, 3, 11, 15 }, { 13, 11, 15, 7, 5, 3, 1, 6, 14, 9 }, { 14, 5, 12, 0, 2, 8, 1, 15 }, { 11, 6, 8, 7, 10, 14, 0, 15, 13, 12 }, { 7, 3, 8, 9, 1, 10, 2, 13, 12, 15, 6 }, { 9, 4, 12, 15, 11, 1, 14, 10, 13, 2, 0, 8, 5 }, { 12, 5, 8, 4, 15, 1, 2, 11, 14, 10, 0 }, { 15, 4, 7, 5, 13, 11, 10, 3, 9, 6 }, { 6, 12, 1, 5, 11, 15, 0, 10, 8, 14, 2 }, { 14, 11, 12, 1, 4, 5, 0, 8, 9, 6, 15, 7 }, { 4, 2, 10, 12, 9, 8, 6, 14, 7, 1, 15 }, { 7, 9, 15, 10, 11, 6, 3, 0, 13, 14, 5, 4 }, { 0, 2, 8, 1, 5, 12, 6, 4 }, { 3, 10, 0, 4, 1, 6, 11, 15, 7, 12, 9, 2 }, { 8, 12, 7, 6, 2, 9, 14, 4, 3, 10, 1, 5, 11 } };
	int id = 11,
		level = 1;
	cout << watchedVideosByFriends(videos, friends, id, level) << endl;
	return 0; 
}

//int build_graph_ladder(string begin, string end, vector<vector<unsigned int>>& graph, vector<string>& wordList)
//{
//	int end_point = -1;
//
//	for (int i = 0; i < wordList.size() - 1; i++)
//	{
//		if (end_point == -1)
//			end_point = string_subtraction(end, wordList[i]) == 0 ? i : end_point;
//		graph[i][i] = 0;
//		for (int j = i + 1; j < wordList.size(); j++)
//		if (string_subtraction(wordList[i], wordList[j]) == 1)
//			graph[i][j] = graph[j][i] = 1;
//	}
//
//	graph.back().back() = 0;
//	if (end_point == -1)
//		end_point = string_subtraction(end, wordList.back()) == 0 ? wordList.size() - 1 : end_point;
//
//	return end_point;
//}
//
//vector<vector<string>> build_path(vector<vector<int>>& path, vector<string>& wordList, int depth, int end)
//{
//	vector<vector<int>>res(1, vector<int>(1, end));
//	vector<vector<string>> ret(1, vector<string>(1, wordList[end]));
//
//	for (int d = 0; d < depth; d++)
//	{
//		int size = res.front().size();
//		
//		while (size == res.front().size())
//		{
//			int curr = res.front().back();
//			vector<int> curr_path(res.front());
//			vector<string> curr_path_str(ret.front());
//
//			for (int i= 0; i < path.size(); i++){
//				if (path[i][curr] != -1)
//				{
//					if (d < depth - 1 || path[i][curr] == 0)
//					{
//						curr_path.push_back(i);
//						res.push_back(curr_path);
//						curr_path.pop_back();
//
//						curr_path_str.push_back(wordList[i]);
//						ret.push_back(curr_path_str);
//						curr_path_str.pop_back();
//					}				
//				}
//			}
//			res.erase(res.begin());
//			ret.erase(ret.begin());
//		}
//	}
//
//	for (int i = 0; i < ret.size(); i++)
//		reverse(ret[i].begin(), ret[i].end());
//	return ret;
//}

//for (int i = 0; i < distance.size(); i++)
//{
//	for (int j = 0; j < distance.size(); j++)
//	{
//		for (int k = 0; k < distance[j].size(); k++)
//		{
//			if (distance[j][k] != INT_MAX)
//			{
//				for (int l = 0; l < distance[k].size(); l++)
//				{
//					distance[j][l] = min(distance[j][l], distance[j][k] + distance[k][l]);
//				}
//			}
//		}
//	}
//}

//#define DEBUG 0
//
//int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
//{
//	wordList.insert(wordList.begin(), beginWord);
//
//	vector<vector<int>> path(wordList.size(), vector<int>(wordList.size(), -1));
//	vector<vector<unsigned int>> distance(wordList.size(), vector<unsigned int>(wordList.size(), INT_MAX));
//	int end = build_graph_ladder(beginWord, endWord, distance, wordList); 
//
//	//cout << distance << endl;
//
//	if (end == -1)
//		return 0;
//	
//	for (int i = 0; i < wordList.size(); i++)
//	{
//#ifdef DEBUG
//		cout << "current middle point: " << i << endl;
//#endif	
//		cout << "current middle point: " << i << endl;
//		for (int j = 0; j < wordList.size(); j++)
//		{
//			if (i == j || distance[i][j] == INT_MAX)
//				continue;
//#ifdef DEBUG
//			cout << "current start: " << j << endl;
//#endif
//			for (int k = 0; k < wordList.size(); k++)
//			{
//				//distance[i][j] = distance[i][j] = min(distance[j][i], distance[i][j] + distance[j][k]);
//				if (k == i || k == j || distance[i][k] == INT_MAX)
//					continue;
//#ifdef DEBUG
//				cout << "current end: " << k << endl;
//				cout << "new distance: " << distance[i][j] + distance[i][k] << endl;
//#endif
//				if ((distance[i][j] + distance[i][k]) < distance[j][k])
//				{
//					distance[j][k] = distance[k][j] = (distance[i][j] + distance[i][k]);
//					path[j][k] = i;
//				}
//			}
//		}
//		cout << distance << endl;
//	}
//
//	return distance[0][end] == INT_MAX ? 0 : distance[0][end] + 1;
//}
//
//int bfs_ladder(int start, int end, vector<vector<int>>& graph, vector<vector<int>>& path)
//{
//	queue<int> nodes;
//	vector<int> traversed(graph.size());
//	nodes.push(start);
//	int cnt = nodes.size();
//	int next_layer = 0;
//	int depth = 1;
//	int res = 0;
//	bool flag = false;
//	//cout << graph << endl;
//	while (!nodes.empty() && !flag)
//	{
//		while (cnt--)
//		{
//			traversed[nodes.front()] = 1;
//			for (int i = 0; i < graph[nodes.front()].size(); i++)
//			{
//				if (traversed[graph[nodes.front()][i]])
//					continue;
//
//				if (graph[nodes.front()][i] == end)
//				{
//					flag = true;
//					res = depth + 1;
//					//path[nodes.front()][end] = end;
//				}
//
//				next_layer++;
//				nodes.push(graph[nodes.front()][i]);
//
//				path[nodes.front()][graph[nodes.front()][i]] = nodes.front();
//			}
//			//cout << path << endl;
//			nodes.pop();
//		}
//		if (flag)
//			break;
//		cnt = next_layer;
//		next_layer &= 0;
//		depth++;
//	}
//
//	return depth;
//}