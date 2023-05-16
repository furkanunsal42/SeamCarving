#include "GraphSearch.h"
#include "Graphs.h"
#include "GraphsTemplated.h"

std::vector<std::reference_wrapper<const _depth_first_search<vec2ui>::T>> _depth_first_search<vec2ui>::search(const Graph<T>& graph, T starting_point, Order order) {
	_marked.clear();
	_marked.reserve(graph.vertex_size());
	std::list<std::reference_wrapper<const T>> search_list;

	if (order == PRE_ORDER || order == REVERSE_PRE_ORDER) {

		std::stack<std::reference_wrapper<const T>> stack;
		stack.push(starting_point);

		while (!stack.empty()) {
			const T& object = stack.top();
			stack.pop();

			if (!_marked[object]) {
				_marked[object] = true;
				search_list.push_back((T&)object);
			}

			auto& adjacencies = graph.get_adjacencies(object);
			for (const T& adjacent : adjacencies) {
				if (!_marked[adjacent]) {
					stack.push(adjacent);
				}
			}
		}
	}
	else if (order == POST_ORDER || order == REVERSE_POST_ORDER) {

		// pair<bool (is_parent), object&>
		std::stack<std::pair<bool, std::reference_wrapper<const T>>> stack;
		stack.push(std::make_pair(false, std::reference_wrapper<const T>(starting_point)));

		while (!stack.empty()) {
			const auto object_pair = stack.top();
			const T& object = object_pair.second;
			bool is_parent = object_pair.first;
			stack.pop();

			if (is_parent) {
				search_list.push_back(object);
				continue;
			}

			if (_marked[object]) {
				continue;
			}

			_marked[object] = true;
			stack.push(std::make_pair(true, std::reference_wrapper<const T>(object)));
			auto& adjacencies = graph.get_adjacencies(object);
			for (const T& adjacent : adjacencies) {
				if (!_marked[adjacent]) {
					stack.push(std::make_pair(false, std::reference_wrapper<const T>(adjacent)));
				}
			}
		}
	}

	_marked.clear();

	if (order == REVERSE_POST_ORDER || order == REVERSE_PRE_ORDER)
		search_list.reverse();

	std::vector<std::reference_wrapper<const T>> search;
	search.reserve(search_list.size());
	for (auto& object : search_list)
		search.push_back(object);

	return search;
}

std::vector<_depth_first_search<vec2ui>::T> _depth_first_search<vec2ui>::search(const ImageGraph& graph, T starting_point, Order order) {
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

std::vector<std::reference_wrapper<const _breadth_first_search<vec2ui>::T>> _breadth_first_search<vec2ui>::search(const Graph<T>& graph, T starting_point) {
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

std::vector<_breadth_first_search<vec2ui>::T> _breadth_first_search<vec2ui>::search(const ImageGraph& graph, T starting_point) {
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
