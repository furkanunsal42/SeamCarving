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

template<typename T, typename cost_type>
class Graph {
public:
	Graph(size_t vertex_amount = 0);

	void add_edge(T vertex1, T vertex2, cost_type cost);
	void add_edge(const std::pair<std::pair<T, T>, cost_type>& verticies);
	void add_edge(const std::vector<const std::pair<std::pair<T, T>, cost_type>>& verticies);
	void add_edge(const std::forward_list<const std::pair<std::pair<T, T>, cost_type>> verticies);
	
	void add_undirected_edge(T vertex1, T vertex2, cost_type cost);
	void add_undirected_edge(const std::pair<std::pair<T, T>, cost_type>& verticies);
	void add_undirected_edge(const std::vector<const std::pair<std::pair<T, T>, cost_type>>& verticies);
	void add_undirected_edge(const std::forward_list<const std::pair<std::pair<T, T>, cost_type>> verticies);
	
	void add_vertex(T vertex) ;
	void add_vertex(const std::vector<T>& verticies);
	void add_vertex(const std::forward_list<T>& verticies);
	
	auto begin() const;
	auto end() const;
	
	const std::forward_list<std::pair<T, cost_type>>& get_adjacencies(const T& vertex) const;
	const std::forward_list<std::pair<T, cost_type>>& operator[](const T& vertex) const;
	
	size_t vertex_size() const;
	size_t edge_size() const;

	enum Order {
		PRE_ORDER = 0,
		POST_ORDER = 1,
		REVERSE_PRE_ORDER = 2,
		REVERSE_POST_ORDER = 3,
	};
	
	std::vector<std::reference_wrapper<const T>> depth_first_search(const T& starting_vertex, Order Order = PRE_ORDER);
	std::vector<std::reference_wrapper<const T>> breadth_first_search(const T& starting_vertex, Order Order = PRE_ORDER);

	template<typename T2>
	friend std::ostream& operator<<(std::ostream& os, const Graph<T2>& graph);

private:

 	std::unordered_map<T, std::forward_list<std::pair<T, cost_type>>> edges;

};

#define AdjacencyFunctionParameters const ImageGraph& self, const ImageGraph::pixel_coord& target_pixel

// implicit interpretation of images as graphs
class ImageGraph {
public:
	typedef vec2ui pixel_coord;

	std::reference_wrapper<Image> image_reference;
	
	ImageGraph(Image& image);
	size_t vertex_size() const;
	size_t edge_size() const;

	std::forward_list<pixel_coord> get_adjacencies(const pixel_coord& vertex) const;
	void set_adjacencies_function(std::function<std::forward_list<pixel_coord>(const ImageGraph&, const pixel_coord&)> new_function);
	
	std::vector<vec2ui> depth_first_search(const vec2ui& starting_vertex);
	std::vector<vec2ui> breadth_first_search(const vec2ui& starting_vertex);

private:

	std::function<std::forward_list<pixel_coord>(const ImageGraph&, const pixel_coord&)> _adjacencies_function;
		

};
