#pragma once

#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <iostream>

template<typename T>
class Graph {
public:
	Graph(size_t vertex_amount = 0) {
		edges.reserve(vertex_amount);
	}

	void add_edge(T vertex1, T vertex2) {
		add_undirected_edge(vertex1, vertex2);
		add_undirected_edge(vertex2, vertex1);
	}

	void add_edge(const std::pair<T, T>& verticies) {
		add_undirected_edge(verticies.first, verticies.second);
		add_undirected_edge(verticies.second, verticies.first);
	}

	void add_edge(const std::vector<const std::pair<T, T>>& verticies) {
		for (auto& edge : verticies)
			add_edge(edge);
	}

	void add_edge(const std::forward_list<const std::pair<T, T>> verticies) {
		for (auto& edge : verticies)
			add_edge(edge);
	}

	void add_undirected_edge(T vertex1, T vertex2) {
		edges[vertex1].push_front(vertex2);
	}

	void add_undirected_edge(const std::pair<T, T>& verticies) {
		edges[verticies.first].push_front(verticies.second);
	}

	void add_undirected_edge(const std::vector<const std::pair<T, T>>& verticies) {
		for (auto& edge : verticies)
			add_undirected_edge(edge.first, edge.second);
	}

	void add_undirected_edge(const std::forward_list<const std::pair<T, T>> verticies) {
		for (auto& edge : verticies)
			add_undirected_edge(edge.first, edge.second);
	}

	void add_vertex(T vertex) {
		if (edges.find(vertex) == edges.end())
			edges[vertex] = std::forward_list<T>();
	}

	void add_vertex(const std::vector<T>& verticies) {
		for (auto& vertex : verticies)
			add_vertex(vertex);
	}

	void add_vertex(const std::forward_list<T>& verticies) {
		for (auto& vertex : verticies)
			add_vertex(vertex);
	}

	auto begin() const{
		return edges.begin();
	}

	auto end() const{
		return edges.end();
	}

	std::forward_list<T> get_adjacencies(const T& vertex) {
		return (*edges.find(vertex)).second;
	}

	std::forward_list<T> operator[](const T& vertex) {
		return get_adjacencies(vertex);
	}

	size_t vertex_size() const {
		return edges.size();
	}

	size_t edge_size() const {
		size_t size = 0;
		for (auto& edge_list : edges)
			for (const T& edge : edge_list.second)
				size++;
		return size;
	}

	template<typename T2>
	friend std::ostream& operator<<(std::ostream& os, const Graph<T2>& graph);

private:
	std::unordered_map<T, std::forward_list<T>> edges;

};

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
