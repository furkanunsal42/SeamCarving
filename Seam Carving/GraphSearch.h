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

template<typename T, typename cost_type = int>
class Graph;
class ImageGraph;


// depth first
template<typename T>
class _depth_first_search {
public:
	enum Order {
		PRE_ORDER = 0,
		POST_ORDER = 1,
		REVERSE_PRE_ORDER = 2,
		REVERSE_POST_ORDER = 3,
	};

	std::vector<std::reference_wrapper<const T>> search(const Graph<T>& graph, T starting_point, Order order = PRE_ORDER);

private:
	std::unordered_map<T, bool> _marked;

};

template<>
class _depth_first_search<vec2ui> {
public:
	typedef vec2ui T;
	enum Order {
		PRE_ORDER = 0,
		POST_ORDER = 1,
		REVERSE_PRE_ORDER = 2,
		REVERSE_POST_ORDER = 3,
	};

	std::vector<std::reference_wrapper<const T>> search(const Graph<T>& graph, T starting_point, Order order = PRE_ORDER);
	std::vector<T> search(const ImageGraph& graph, T starting_point, Order order = PRE_ORDER);

private:
	std::unordered_map<T, bool> _marked;
};


// breadth first
template<typename T>
class _breadth_first_search {
public:

	std::vector<std::reference_wrapper<const T>> search(const Graph<T>& graph, T starting_point);

private:
	std::unordered_map<T, bool> _marked;

};

template<>
class _breadth_first_search<vec2ui> {
public:
	typedef vec2ui T;

	std::vector<std::reference_wrapper<const T>> search(const Graph<T>& graph, T starting_point);
	std::vector<T> search(const ImageGraph& graph, T starting_point);

private:
	std::unordered_map<T, bool> _marked;
};
