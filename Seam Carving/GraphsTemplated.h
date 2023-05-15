#pragma once

#include "Graphs.h"
#include "GraphSearch.h"

//Graph
template<typename T>
Graph<T>::Graph(size_t vertex_amount) {
	edges.reserve(vertex_amount);
}

template<typename T>
void Graph<T>::add_edge(T vertex1, T vertex2) {
	add_undirected_edge(vertex1, vertex2);
	add_undirected_edge(vertex2, vertex1);
}

template<typename T>
void Graph<T>::add_edge(const std::pair<T, T>& verticies) {
	add_undirected_edge(verticies.first, verticies.second);
	add_undirected_edge(verticies.second, verticies.first);
}

template<typename T>
void Graph<T>::add_edge(const std::vector<const std::pair<T, T>>& verticies) {
	for (auto& edge : verticies)
		add_edge(edge);
}

template<typename T>
void Graph<T>::add_edge(const std::forward_list<const std::pair<T, T>> verticies) {
	for (auto& edge : verticies)
		add_edge(edge);
}

template<typename T>
void Graph<T>::add_undirected_edge(T vertex1, T vertex2) {
	edges[vertex1].push_front(vertex2);
}

template<typename T>
void Graph<T>::add_undirected_edge(const std::pair<T, T>& verticies) {
	edges[verticies.first].push_front(verticies.second);
}

template<typename T>
void Graph<T>::add_undirected_edge(const std::vector<const std::pair<T, T>>& verticies) {
	for (auto& edge : verticies)
		add_undirected_edge(edge.first, edge.second);
}

template<typename T>
void Graph<T>::add_undirected_edge(const std::forward_list<const std::pair<T, T>> verticies) {
	for (auto& edge : verticies)
		add_undirected_edge(edge.first, edge.second);
}

template<typename T>
void Graph<T>::add_vertex(T vertex) {
	if (edges.find(vertex) == edges.end())
		edges[vertex] = std::forward_list<T>();
}

template<typename T>
void Graph<T>::add_vertex(const std::vector<T>& verticies) {
	for (auto& vertex : verticies)
		add_vertex(vertex);
}

template<typename T>
void Graph<T>::add_vertex(const std::forward_list<T>& verticies) {
	for (auto& vertex : verticies)
		add_vertex(vertex);
}

template<typename T>
auto Graph<T>::begin() const {
	return edges.begin();
}

template<typename T>
auto Graph<T>::end() const {
	return edges.end();
}

template<typename T>
const std::forward_list<T>& Graph<T>::get_adjacencies(const T& vertex) const {
	return (*edges.find(vertex)).second;
}

template<typename T>
const std::forward_list<T>& Graph<T>::operator[](const T& vertex) const {
	return get_adjacencies(vertex);
}

template<typename T>
size_t Graph<T>::vertex_size() const {
	return edges.size();
}

template<typename T>
size_t Graph<T>::edge_size() const {
	size_t size = 0;
	for (auto& edge_list : edges)
		for (const T& edge : edge_list.second)
			size++;
	return size;
}

template<typename T>
std::vector<std::reference_wrapper<const T>> Graph<T>::depth_first_search(const T& starting_vertex) {
	_depth_first_search<T> dfs;
	return dfs.search(*this, starting_vertex);
}

template<typename T>
std::vector<std::reference_wrapper<const T>> Graph<T>::breadth_first_search(const T& starting_vertex) {
	_breadth_first_search<T> bfs;
	return bfs.search(*this, starting_vertex);
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Graph<T>& graph) {
	for (auto iterator = graph.begin(); iterator != graph.end(); iterator++) {
		stream << "key: " << iterator->first << "; ";
		for (auto& edge : iterator->second) {
			stream << edge << " ";
		}
		stream << '\n';
	}
	return stream;
}