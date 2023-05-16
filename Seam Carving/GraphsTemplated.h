#pragma once

#include "Graphs.h"
#include "GraphSearch.h"
#include "GraphSearchTemplated.h"

//Graph
template<typename T, typename cost_type>
Graph<T, cost_type>::Graph(size_t vertex_amount) {
	edges.reserve(vertex_amount);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_edge(T vertex1, T vertex2, cost_type cost) {
	add_undirected_edge(vertex1, vertex2, cost);
	add_undirected_edge(vertex2, vertex1, cost);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_edge(const std::pair<std::pair<T, T>, cost_type>& verticies) {
	add_undirected_edge(verticies.first.first, verticies.first.second, verticies.second);
	add_undirected_edge(verticies.first.second, verticies.first.first, verticies.second);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_edge(const std::vector<const std::pair<std::pair<T, T>, cost_type>>& verticies) {
	for (auto& edge : verticies)
		add_edge(edge);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_edge(const std::forward_list<const std::pair<std::pair<T, T>, cost_type>> verticies) {
	for (auto& edge : verticies)
		add_edge(edge);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_undirected_edge(T vertex1, T vertex2, cost_type cost) {
	edges[vertex1].emplace_front(vertex2, cost);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_undirected_edge(const std::pair<std::pair<T, T>, cost_type>& verticies) {
	edges[verticies.first.first].emplace_front(verticies.first.second, verticies.second);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_undirected_edge(const std::vector<const std::pair<std::pair<T, T>, cost_type>>& verticies) {
	for (auto& edge : verticies)
		add_undirected_edge(edge);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_undirected_edge(const std::forward_list<const std::pair<std::pair<T, T>, cost_type>> verticies) {
	for (auto& edge : verticies)
		add_undirected_edge(edge);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_vertex(T vertex) {
	if (edges.find(vertex) == edges.end())
		edges[vertex] = std::forward_list<T>();
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_vertex(const std::vector<T>& verticies) {
	for (auto& vertex : verticies)
		add_vertex(vertex);
}

template<typename T, typename cost_type>
void Graph<T, cost_type>::add_vertex(const std::forward_list<T>& verticies) {
	for (auto& vertex : verticies)
		add_vertex(vertex);
}

template<typename T, typename cost_type>
auto Graph<T, cost_type>::begin() const {
	return edges.begin();
}

template<typename T, typename cost_type>
auto Graph<T, cost_type>::end() const {
	return edges.end();
}

template<typename T, typename cost_type>
const std::forward_list<std::pair<T, cost_type>>& Graph<T, cost_type>::get_adjacencies(const T& vertex) const {
	return (*edges.find(vertex)).second;
}

template<typename T, typename cost_type>
const std::forward_list<std::pair<T, cost_type>>& Graph<T, cost_type>::operator[](const T& vertex) const {
	return get_adjacencies(vertex);
}

template<typename T, typename cost_type>
size_t Graph<T, cost_type>::vertex_size() const {
	return edges.size();
}

template<typename T, typename cost_type>
size_t Graph<T, cost_type>::edge_size() const {
	size_t size = 0;
	for (auto& edge_list : edges)
		for (const T& edge : edge_list.second)
			size++;
	return size;
}

template<typename T, typename cost_type>
std::vector<std::reference_wrapper<const T>> Graph<T, cost_type>::depth_first_search(const T& starting_vertex, Order order) {
	_depth_first_search<T> dfs;
	return dfs.search(*this, starting_vertex, _depth_first_search<T>::Order(+order));
}

template<typename T, typename cost_type>
std::vector<std::reference_wrapper<const T>> Graph<T, cost_type>::breadth_first_search(const T& starting_vertex, Order order) {
	_breadth_first_search<T> bfs;
	return bfs.search(*this, starting_vertex);
}

template<typename T, typename cost_type>
std::ostream& operator<<(std::ostream& stream, const Graph<T, cost_type>& graph) {
	for (auto iterator = graph.begin(); iterator != graph.end(); iterator++) {
		stream << "key: " << iterator->first << "; ";
		for (auto& edge : iterator->second) {
			stream << edge << " ";
		}
		stream << '\n';
	}
	return stream;
}