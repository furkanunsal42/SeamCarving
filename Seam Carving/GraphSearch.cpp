#include "GraphSearch.h"
#include "Graphs.h"
#include "GraphsTemplated.h"

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

std::vector<std::reference_wrapper<const _breadth_first_search<vec2ui>::T>> _breadth_first_search<vec2ui>::search(const Graph<T>& graph, const T& starting_point) {
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

		auto adjacencies = graph.get_adjacencies(object);
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

std::vector<_breadth_first_search<vec2ui>::T> _breadth_first_search<vec2ui>::search(const ImageGraph& graph, const _breadth_first_search<vec2ui>::T& starting_point) {
	_marked.clear();
	_marked.reserve(graph.vertex_size());

	std::vector<T> search;
	search.reserve(graph.vertex_size());

	std::stack<T> stack;
	_marked[starting_point] = true;
	search.push_back((T&)starting_point);
	stack.push(starting_point);


	while (!stack.empty()) {
		const T& object = stack.top();
		stack.pop();

		auto adjacencies = graph.get_adjacencies(object);
		for (const T& adjacent : adjacencies) {
			if (!_marked[adjacent]) {
				_marked[adjacent] = true;
				search.push_back(adjacent);
				stack.push(adjacent);
			}
		}
	}

	_marked.clear();

	return search;
}
