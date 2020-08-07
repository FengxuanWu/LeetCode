// Graph.cpp : Defines the entry point for the console application.
//
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

int networkDelayTime(vector<vector<int>>& times, int n, int k)
{
	vector<vector<pair<int, int>>> graph(n);
	for (int i = 0; i < times.size(); i++)
		graph[times[i][0] - 1].push_back({ times[i][1], times[i][2] });

	vector<int> time(n, INT_MAX);
	time[k - 1] = 0;
	queue<int> q;
	q.push(k - 1);


	while (!q.empty())
	{
		int curr = q.front();
		for (int i = 0; i < graph[curr].size(); i++)
		{
			int node = graph[curr][i].first, latency = graph[curr][i].second;
			time[graph[curr][i].first] = min(time[curr] + graph[curr][i].second, time[graph[curr][i].first]);
			q.push(node);
		}
		q.pop();
	}

	int res = 0;
	for (int i = 0; i < time.size(); i++)
	if (time[i] == INT_MAX)
		return -1;
	else
		res = max(res, time[i]);
	return res;
}

bool buddyStrings(string a, string b)
{
	vector<int> bar(26);
	int idx1 = -1, idx2 = -1, diff = 0;
	for (int i = 0; i < a.size(); i++)
	{
		bar[a[i] - 'a']++;

		if (a[i] != b[i])
		{
			++diff;
			idx1 = idx1 == -1 ? i : idx1;
			idx2 = idx1 != -1 ? i : idx2;
		}
	}

	bool res = false;
	for (int i = 0; i < bar.size(); i++)
		res |= (bar[i] > 0 && bar[i] % 2 == 0);

	return (diff == 2 && a[idx1] == b[idx2] && a[idx2] == b[idx1]) || (diff == 0 && res);
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

bool dfs(vector<vector<int>>& graph, int curr, int c, vector<int>& color)
{
	if (color[curr] == c)
		return true;
	else if (color[curr] == !c)
		return false;

	color[curr] = c;
	for (int i = 0; i < graph[curr].size(); i++)
	{
		if (!dfs(graph, graph[curr][i], !c, color))
			return false;
	}

	return true;
}

bool possibleBipartition(int n, vector<vector<int>>& dislikes)
{
	vector<vector<int>> graph(n + 1);
	for (int i = 0; i < dislikes.size(); i++)
	{
		graph[dislikes[i][0]].push_back(dislikes[i][1]);
		graph[dislikes[i][1]].push_back(dislikes[i][0]);
	}

	vector<int> color(n + 1, -1);
	
	for (int i = 1; i <= n; i++)
	{
		if (graph[i].size() == 0 || color[i] != -1)
			continue;

		if (!dfs(graph, i, 0, color))
			return false;
	}

	return true;
}

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end)
{
	vector<vector<vector<double>>> graph(n);
	for (int i = 0; i < edges.size(); i++)
	{
		graph[edges[i][0]].push_back({ (double)edges[i][1], succProb[i] });
		graph[edges[i][1]].push_back({ (double)edges[i][0], succProb[i] });
	}

	vector<double> prob(n);
	prob[start] = 1;
	queue<int> q;
	q.push(start);

	while (!q.empty())
	{
		int curr = q.front();
		for (int i = 0; i < graph[curr].size(); i++)
		{
			int nxt = graph[curr][i][0];
			if (prob[curr] * graph[curr][i][1] > prob[nxt])
			{
				prob[nxt] = prob[curr] * graph[curr][i][1];
				q.push(nxt);
			}
		}
		q.pop();
	}

	return prob[end];
}

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
{
	vector<vector<vector<int>>> graph(n);
	for (int i = 0; i < flights.size(); i++)
		graph[flights[i][0]].push_back({ flights[i][1], flights[i][2] });

	vector<int> visited(n);
	queue<pair<int, int>> q;
	q.push({ src, 0 });
	visited[src] = 1;
	int res = INT_MAX;
	int cnt = 1;

	for (int i = 0; i <= k; i++)
	{
		int nxt = 0;
		while (cnt-- && q.size())
		{
			visited[q.front().first] = true;

			for (int i = 0; i < graph[q.front().first].size(); i++)
			{
				int node = graph[q.front().first][i][0], cost = graph[q.front().first][i][1];
				if (node != dst && res > q.front().second + cost)
				{
					q.push({ node, q.front().second + cost });
					nxt++;
				}
				else
					res = min(res, q.front().second + cost);
			}
			q.pop();
		}
		cnt = nxt;
	}

	return res == INT_MAX ? -1 : res;
}
int main()
{
	int n = 5;
	int start = 0;
	int end = 2;
	int k = 2;
	vector<vector<int>> graph = {
{0,1,5},
{1,2,5},
{0,3,2},
{3,1,2},
{1,4,1},
{4,2,1},
	};
	cout << findCheapestPrice(n, graph, start, end, k) << endl;
	return 0;
 }