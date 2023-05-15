#pragma once

#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <iostream>
#include <codecvt>
#include <type_traits>
#include <functional>
#include <stack>

#include "Image.h"
#include "CortexMath.h"

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
class _breadth_first_search {
public:
	std::vector<std::reference_wrapper<const T>> search(const Graph<T>& graph, const T& starting_point) {
		_marked.clear();
		_marked.reserve(graph.vertex_size());

		std::vector<std::reference_wrapper<const T>> search;
		search.reserve(graph.vertex_size());

		std::stack<std::reference_wrapper<const T>> stack;
		_marked[starting_point] = true;
		search.push_back((T&)starting_point);
		stack.push(starting_point);

		while (!stack.empty()) {
			const T& object = stack.top();
			stack.pop();

			auto& adjacencies = graph.get_adjacencies(object);
			for (const T& adjacent : adjacencies) {
				if (!_marked[adjacent]) {
					_marked[adjacent] = true;
					search.push_back((T&)adjacent);
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
class _breadth_first_search<vec2ui> {
public:
	typedef vec2ui T;

	std::vector<std::reference_wrapper<const T>> search(const Graph<T>& graph, const T& starting_point);

	std::vector<T> search(const ImageGraph& graph, const T& starting_point);

private:
	std::unordered_map<T, bool> _marked;
};
