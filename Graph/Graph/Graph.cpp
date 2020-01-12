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

//map<string, vector<string>> graph;
//bool found = false;

//void dfs_traverse(int current, int total, string current_node, vector<string> path, vector<string>& res)
//{
//	if (found) return; 
//
//	path.emplace_back(current_node);
//	if (current == total)
//	{
//		res = path;
//		found = true;
//		return;
//	}
//
//	for (int i = 0; i < graph[current_node].size(); i++)
//	{
//		if (graph[current_node][i] != "-")
//		{
//			string next_edge = graph[current_node][i];
//			graph[current_node][i] = "-";
//			dfs_traverse(current + 1, total, next_edge, path, res);
//			graph[current_node][i] = next_edge;
//		}	
//	}
//}
//
//vector<string> findItinerary(vector<vector<string>>& tickets) 
//{
//	int total = tickets.size(), current = 0;
//	for (int i = 0; i < tickets.size(); i++)
//		graph[tickets[i][0]].emplace_back(tickets[i][1]);
//	
//	for (auto &p : graph)
//		sort(p.second.begin(), p.second.end());
//
//	vector<string> res;
//	//map<string, bool> visited;
//	dfs_traverse(current, total, "JFK", vector<string>(), res);
//	return res;
//}

map<int, vector<int>> graph;
vector<int> path;

void dfs(int current, vector<int> visited, int d)
{
	visited[current] = true;
	for (int i = 0; i < graph[current].size(); i++)
	{
		int next = graph[current][i];
		if (visited[next])
			continue;
		
		path[next] = d + 1;
		dfs(graph[current][i], visited, d + 1);
	}
}


int treeDiameter(vector<vector<int>>& edges) 
{
	for (int i = 0; i < edges.size(); i++)
	{
		graph[edges[i][0]].push_back(edges[i][1]);
		graph[edges[i][1]].push_back(edges[i][0]);
	}

	if (graph.size() == 0)
		return 0;

	vector<int> visited(graph.size());
	path = vector<int>(graph.size());
	dfs(0, visited, 0);
	int max = 0;
	int index = 0;
	for (int i = 0; i < path.size(); i++)
	{
		if (max < path[i])
		{
			max = path[i];
			index = i;
		}		
	}
	//cout << "index : " << index << endl;
	//cout << path << endl;
	//cout << endl;
	dfs(index, visited, 0);
	for (int i = 0; i < path.size(); i++)
	{
		if (max < path[i])
		{
			max = path[i];
			index = i;
		}
	}
	return max;
}

void dfs(vector<vector<int>>& graph, unordered_set<int>& visited, int node, int& res)
{
	if (visited.find(node) != visited.end())
		return;
	
	res++;
	visited.insert(node);
	for (int i = 0; i < graph[node].size(); i++)
		dfs(graph, visited, graph[node][i], res);
	
}

int makeConnected(int n, vector<vector<int>>& connections)
{
	vector<vector<int>> graph(n);
	for (int i = 0; i < connections.size(); i++)
	{
		graph[connections[i][0]].push_back(connections[i][1]);
		graph[connections[i][1]].push_back(connections[i][0]);
	}

	int connected = 0;
	int connected_set = 0;
	unordered_set<int> visited;
	for (int i = 0; i < n; i++)
	{
		connected_set += visited.find(i) == visited.end();
		int tmp = 0;
		dfs(graph, visited, i, tmp);
		connected += (tmp > 1) ? tmp : 0;
	}

	int extra_connection = connections.size() - connected + 1;
	
	if (extra_connection + 1 < connected_set)
		return -1;
	
	return connected_set - 1;
}

int main()
{
	vector<vector<int>> connections = {
		{ 17, 51 },
		{ 33, 83 },
		{ 53, 62 },
		{ 25, 34 },
		{ 35, 90 },
		{ 29, 41 },
		{ 14, 53 },
		{ 40, 84 },
		{ 41, 64 },
		{ 13, 68 },
		{ 44, 85 },
		{ 57, 58 },
		{ 50, 74 },
		{ 20, 69 },
		{ 15, 62 },
		{ 25, 88 },
		{ 4, 56 },
		{ 37, 39 },
		{ 30, 62 },
		{ 69, 79 },
		{ 33, 85 },
		{ 24, 83 },
		{ 35, 77 },
		{ 2, 73 },
		{ 6, 28 },
		{ 46, 98 },
		{ 11, 82 },
		{ 29, 72 },
		{ 67, 71 },
		{ 12, 49 },
		{ 42, 56 },
		{ 56, 65 },
		{ 40, 70 },
		{ 24, 64 },
		{ 29, 51 },
		{ 20, 27 },
		{ 45, 88 },
		{ 58, 92 },
		{ 60, 99 },
		{ 33, 46 },
		{ 19, 69 },
		{ 33, 89 },
		{ 54, 82 },
		{ 16, 50 },
		{ 35, 73 },
		{ 19, 45 },
		{ 19, 72 },
		{ 1, 79 },
		{ 27, 80 },
		{ 22, 41 },
		{ 52, 61 },
		{ 50, 85 },
		{ 27, 45 },
		{ 4, 84 },
		{ 11, 96 },
		{ 0, 99 },
		{ 29, 94 },
		{ 9, 19 },
		{ 66, 99 },
		{ 20, 39 },
		{ 16, 85 },
		{ 12, 27 },
		{ 16, 67 },
		{ 61, 80 },
		{ 67, 83 },
		{ 16, 17 },
		{ 24, 27 },
		{ 16, 25 },
		{ 41, 79 },
		{ 51, 95 },
		{ 46, 47 },
		{ 27, 51 },
		{ 31, 44 },
		{ 0, 69 },
		{ 61, 63 },
		{ 33, 95 },
		{ 17, 88 },
		{ 70, 87 },
		{ 40, 42 },
		{ 21, 42 },
		{ 67, 77 },
		{ 33, 65 },
		{ 3, 25 },
		{ 39, 83 },
		{ 34, 40 },
		{ 15, 79 },
		{ 30, 90 },
		{ 58, 95 },
		{ 45, 56 },
		{ 37, 48 },
		{ 24, 91 },
		{ 31, 93 },
		{ 83, 90 },
		{ 17, 86 },
		{ 61, 65 },
		{ 15, 48 },
		{ 34, 56 },
		{ 12, 26 },
		{ 39, 98 },
		{ 1, 48 },
		{ 21, 76 },
		{ 72, 96 },
		{ 30, 69 },
		{ 46, 80 },
		{ 6, 29 },
		{ 29, 81 },
		{ 22, 77 },
		{ 85, 90 },
		{ 79, 83 },
		{ 6, 26 },
		{ 33, 57 },
		{ 3, 65 },
		{ 63, 84 },
		{ 77, 94 },
		{ 26, 90 },
		{ 64, 77 },
		{ 0, 3 },
		{ 27, 97 },
		{ 66, 89 },
		{ 18, 77 },
		{ 27, 43 },
	};
	int n = 100;
	cout << makeConnected(n, connections) << endl;
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