#pragma once

#include "Graphs.h"
#include "GraphSearch.h"


// ImageGraph
ImageGraph::ImageGraph(Image& image) :
	image_reference(image), 
	_adjacencies_function([](const ImageGraph& self, const pixel_coord& target_pixel) {
		std::forward_list<pixel_coord> adjacencies;
		for (int y = -1; y <= 1; y++)
		for (int x = -1; x <= 1; x++)
		if (y != 0 || x != 0) {
			adjacencies.emplace_front(
				std::min(std::max((int)target_pixel.x + x, 0), self.image_reference.get().get_width() - 1),
				std::min(std::max((int)target_pixel.y + y, 0), self.image_reference.get().get_height() - 1)
			);
		}
		return adjacencies;
	})

{ }

std::forward_list<ImageGraph::pixel_coord> ImageGraph::get_adjacencies(const pixel_coord& vertex) const {
	return _adjacencies_function(*this, vertex);
}

size_t ImageGraph::vertex_size() const {
	return image_reference.get().get_width() * image_reference.get().get_height();
}

size_t ImageGraph::edge_size() const {
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

void ImageGraph::set_adjacencies_function(std::function<std::forward_list<pixel_coord>(const ImageGraph&, const pixel_coord&) > new_function) {
	_adjacencies_function = new_function;
}

std::vector<vec2ui> ImageGraph::depth_first_search(const vec2ui& starting_vertex) {
	_depth_first_search<vec2ui> dfs;
	return dfs.search(*this, starting_vertex);
}

std::vector<vec2ui> ImageGraph::breadth_first_search(const vec2ui& starting_vertex) {
	_breadth_first_search<vec2ui> bfs;
	return bfs.search(*this, starting_vertex);
}
