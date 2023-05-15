#pragma once

#include "GraphSearch.h"
#include "Graphs.h"

template<typename T>
std::vector<std::reference_wrapper<const T>> _depth_first_search<T>::search(const Graph<T>& graph, T starting_point) {
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

template<typename T>
std::vector<std::reference_wrapper<const T>> _breadth_first_search<T>::search(const Graph<T>& graph, T starting_point) {
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