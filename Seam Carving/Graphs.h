#pragma once

#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <iostream>
#include <codecvt>
#include <type_traits>
#include <functional>
#include "Image.h"
#include "CortexMath.h"
#include <stack>

template<typename T>
class Graph;

class ImageGraph;

template<typename T>
class _depth_first_search {
public:
	std::vector<std::reference_wrapper<const T>> search(const Graph<T>& graph, const T& starting_point) {
		_marked.clear();
		_marked.reserve(graph.vertex_size());

		std::vector<std::reference_wrapper<const T>> search;
		search.reserve(graph.vertex_size());

		std::stack<std::reference_wrapper<const T>> stack;
		stack.push(starting_point);

		while (!stack.empty()) {
			const T& object = stack.top();
			stack.pop();

			if (!_marked[object]) {
				_marked[object] = true;
				search.push_back((T&)object);
			}

			auto& adjacencies = graph.get_adjacencies(object);
			for (const T& adjacent : adjacencies) {
				if (!_marked[adjacent]) {
					stack.push(adjacent);
				}
			}
		}

		_marked.clear();

		return search;
	}

private:
	std::unordered_map<T, bool> _marked;

};

template<>
class _depth_first_search<vec2ui> {
public:
	typedef vec2ui T;

	std::vector<std::reference_wrapper<const T>> search(const Graph<T>& graph, const T& starting_point);

	std::vector<T> search(const ImageGraph& graph, const T& starting_point);

private:
	std::unordered_map<T, bool> _marked;
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

	const std::forward_list<T>& get_adjacencies(const T& vertex) const {
		return (*edges.find(vertex)).second;
	}

	std::forward_list<T> operator[](const T& vertex) const {
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

	std::vector<std::reference_wrapper<const T>> depth_first_search(const T& starting_vertex) {
		_depth_first_search<T> dfs;
		return dfs.search(*this, starting_vertex);
	}

	template<typename T2>
	friend std::ostream& operator<<(std::ostream& os, const Graph<T2>& graph);

private:

 	std::unordered_map<T, std::forward_list<T>> edges;

};

// implicit interpretation of images as graphs
class ImageGraph {
	typedef vec2ui pixel_coord;

public:
	ImageGraph(Image& image) :
		image_reference(image) {}

	std::forward_list<pixel_coord> get_adjacencies(const pixel_coord& vertex) const {
		return _adjacencies_function(*this, vertex);
	}

	size_t vertex_size() const {
		return image_reference.get().get_width() * image_reference.get().get_height();
	}

	size_t edge_size() const {
		size_t edge_size = 0;
		for (unsigned int y = 0; y < image_reference.get().get_height(); y++) {
			for (unsigned int x = 0; x < image_reference.get().get_width(); x++) {
				vec2ui pixel_coord(x, y);
				auto adjacencies = get_adjacencies(pixel_coord);
				for (auto& adjacent : adjacencies)
					edge_size++;
			}
		}

		return edge_size;
	}

	void set_adjacencies_function(std::function<std::forward_list<pixel_coord>(const ImageGraph&, const pixel_coord&) > new_function) {
		_adjacencies_function = new_function;
	}

	std::vector<vec2ui> depth_first_search(const vec2ui& starting_vertex) {
		_depth_first_search<vec2ui> dfs;
		return dfs.search(*this, starting_vertex);
	}

	std::reference_wrapper<Image> image_reference;
private:
	std::function<std::forward_list<pixel_coord>(const ImageGraph&, const pixel_coord&)> _adjacencies_function = [](const ImageGraph& self, const pixel_coord& target_pixel) {
		std::forward_list<pixel_coord> adjacencies;
		for (int y = -1; y <= 1; y++)
			for (int x = -1; x <= 1; x++)
				if (y != 0 || x != 0) {
					adjacencies.push_front(pixel_coord(
						std::min(std::max((int)target_pixel.x + x, 0), self.image_reference.get().get_width() - 1),
						std::min(std::max((int)target_pixel.y + y, 0), self.image_reference.get().get_height() - 1)
					));
				}

		return adjacencies;
	};
};

std::vector<std::reference_wrapper<const _depth_first_search<vec2ui>::T>> _depth_first_search<vec2ui>::search(const Graph<T>& graph, const T& starting_point) {
	_marked.clear();
	_marked.reserve(graph.vertex_size());

	std::vector<std::reference_wrapper<const T>> search;
	search.reserve(graph.vertex_size());

	std::stack<std::reference_wrapper<const T>> stack;
	stack.push(starting_point);

	while (!stack.empty()) {
		const T& object = stack.top();
		stack.pop();

		if (!_marked[object]) {
			_marked[object] = true;
			search.push_back((T&)object);
		}

		auto adjacencies = graph.get_adjacencies(object);
		for (const T& adjacent : adjacencies) {
			if (!_marked[adjacent]) {
				stack.push(adjacent);
			}
		}
	}

	_marked.clear();

	return search;
}

std::vector<_depth_first_search<vec2ui>::T> _depth_first_search<vec2ui>::search(const ImageGraph& graph, const T& starting_point) {
	_marked.clear();
	_marked.reserve(graph.vertex_size());

	std::vector<T> search;
	search.reserve(graph.vertex_size());

	std::stack<T> stack;
	stack.push(starting_point);

	while (!stack.empty()) {
		const T& object = stack.top();
		stack.pop();

		if (!_marked[object]) {
			_marked[object] = true;
			search.push_back(object);
		}

		auto adjacencies = graph.get_adjacencies(object);
		for (const T& adjacent : adjacencies) {
			if (!_marked[adjacent]) {
				stack.push(adjacent);
			}
		}
	}

	_marked.clear();

	return search;
}