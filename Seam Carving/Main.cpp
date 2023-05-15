﻿#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "CortexMath.h"
#include "Image.h"
#include "Graphs.h"
#include <unordered_map>

Image kernel_filtering(Image& source, int kernel[3][3]) {
	int width = source.get_width();
	int height = source.get_height();
	int channel = source.get_channels();
	Image new_image(width, height, channel);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			vec3 value;
			for (int kernel_y = 0; kernel_y < 3; kernel_y++) {
				for (int kernel_x = 0; kernel_x < 3; kernel_x++) {
					int source_x = std::min(std::max(x + kernel_x - 1, 0), width-1);
					int source_y = std::min(std::max(y + kernel_y - 1, 0), height-1);
					value = value + (kernel[kernel_y][kernel_x] * (vec3)source[source_y][source_x]);
				}
			}
			new_image[y][x] = value.length();
		}
	}


	return new_image;
}
int main() {
	Image image("small.png", 3);

	ImageGraph graph(image);
	auto adj = graph.depth_first_search(vec2ui(0, 0));
	int i = 0;
	for (auto object : adj)
		std::cout << i++ << " " << object << '\n';
	std::cout << adj.size() << std::endl;

	std::cin.get();
}

/*
int main() {
	Graph<int> graph;
	graph.add_edge(0, 1);
	graph.add_edge(0, 2);
	graph.add_edge(0, 5);
	graph.add_edge(0, 6);

	graph.add_edge(6, 4);
	graph.add_edge(4, 3);
	graph.add_edge(5, 3);

	auto dps = graph.depth_first_search(0);
	for (auto object : dps)
		std::cout << object << '\n';
	
	std::cout << graph << '\n';



	std::cin.get();
}
*/

/*
int main() {
	Image image("photo1.jpg", 3);
	
	int kernel[3][3] =
	{
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1,
	};

	image.save_to_disc("original.png");

	Image processed = kernel_filtering(image, kernel);

	processed.save_to_disc("processed.png");

	for (int i = 0; i < image.get_width(); i++) {
		image.remove_pixel(vec2ui(i, i));
	}
	image.new_width--;
	image.update();
	
	image.save_to_disc("modified.png");

	//std::cin.get();
}
*/