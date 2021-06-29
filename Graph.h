#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Graph {
	/**
	* This class represents a structure which contains nodes (of type T) together with all the neighbouring nodes bound together by a list (adjacency list)
	* The graph is implemented using a std::unsorted_map<T, list<T>>, which gives Theta(1) complexity for accessing a node
	*/
public:
	//void printAdjacencyLists(); //this function has pure testing purpose

	void addEdges(T node1, T node2);

	bool bfs(T start, T target, unordered_map<T, int>& dist, unordered_map<T, T>& pred);

	void displayShortestPath(T start, T target);

	void addElem(T elem);

	inline vector<T>& modifyList(T elem) { return m_adjLists[elem]; }

private:
	unordered_map<T, vector<T>> m_adjLists;
};
template <typename T>
void Graph<T>::addElem(T elem) {
	/**
	* Input: T elem - represents an element we want to add to the graph
	* Output: -
	* The node is not added if it already exists
	*/
	if (m_adjLists.find(elem) == m_adjLists.end())
	{
		vector<T> emptyVector;
		m_adjLists[elem] = emptyVector;
	}
}

template <typename T>
void Graph<T>::addEdges(T node1, T node2) {
	/**
	* Input: T node1, T node2 represent the nodes to which we want to add edges
	* Output: void
	*/
	m_adjLists[node1].insert(m_adjLists[node1].end(), m_adjLists[node2].begin(), m_adjLists[node2].end());
	m_adjLists[node2].insert(m_adjLists[node2].end(), m_adjLists[node1].begin(), m_adjLists[node1].end());

}

template <typename T>
bool Graph<T>::bfs(T start, T target, unordered_map<T, int>& dist, unordered_map<T, T>& pred) {
	/**
	* Input: - T start represents the node we start with
	*		 - T target represents the node we want to get to
	*		 - unordered_map<T, int>& dist represents the distance from the key to the start
	* 		 - unordered_map<T, T>& pred represents the previous node of the key on the path start -> end
	* Output: - true if the path exists
	*		  - false otherwise
	*/
	//First we mark all vertices in the graph as not visited
	unordered_map<T, bool> visited;

	for (auto elem : m_adjLists) {
		visited[elem.first] = false;
		dist[elem.first] = INT_MAX;
		pred[elem.first] = "";
	}
	//Now we build our queue and we add the node
	queue<T> q;
	q.push(start);
	visited[start] = true;
	dist[start] = 0;
	while (!(q.empty())) {
		T elem = q.front();
		q.pop();
		for (auto neighbour : m_adjLists[elem]) {
			if (!visited[neighbour]) {
				visited[neighbour] = true;
				dist[neighbour] = dist[elem] + 1;
				pred[neighbour] = elem;
				q.push(neighbour);
				if (elem == target) {
					return true;
				}
			}
		}
	}
	return false;
}

template <typename T>
void Graph<T>::displayShortestPath(T start, T target) 
{
	/**
	* Input: - T start represents the node we start with
	*		 - T target represents the node we want to get to
	* Output: void
	* Displays the shortest path from start to target.
	*/
	unordered_map<T, int> dist;
	unordered_map<T, T> pred;
	bfs(start, target, dist, pred);
	vector<T> path;
	T crawl = target;
	path.push_back(crawl);
	while (pred[crawl] != "") 
	{
		path.push_back(pred[crawl]);
		crawl = pred[crawl];
	}
	reverse(path.begin(), path.end());
	cout << "Shortest path length is: " << dist[target] << endl;
	cout << "Shortest path is: ";
	for (auto node: path) 
	{
		cout << node << " ";
	}
	cout << endl;
}




