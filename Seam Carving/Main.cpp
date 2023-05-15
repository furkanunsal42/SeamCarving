#include "GL/glew.h"
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

/*
int main() {
	Image image("photo1.jpg", 3, false);

	ImageGraph graph(image);
	graph.set_adjacencies_function([](AdjacencyFunctionParameters) {
			std::forward_list<ImageGraph::pixel_coord> adjacencies;
			if ((int)target_pixel.y <= -1) {
				for (int x = 0; x < self.image_reference.get().get_width(); x++)
					adjacencies.push_front(ImageGraph::pixel_coord(x, 0));
			}
			else if (target_pixel.y == self.image_reference.get().get_height()-1) {
				adjacencies.push_front(ImageGraph::pixel_coord(0, self.image_reference.get().get_height()));
			}
			else {
				for (int y = 1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						if (y != 0 || x != 0) {
							adjacencies.push_front(ImageGraph::pixel_coord(
								std::min(std::max((int)target_pixel.x + x, 0), self.image_reference.get().get_width() - 1),
								std::min(std::max((int)target_pixel.y + y, 0), self.image_reference.get().get_height() - 1)
							));
						}
			}
			
			return adjacencies;
		});

	auto dfs = graph.depth_first_search(vec2ui(0, -1));
	int i = 0;
	
	for (auto& pixel : dfs)
		image
		[std::min(std::max((int)pixel.y, 0), graph.image_reference.get().get_height()-1)]
		[std::min(std::max((int)pixel.x, 0), graph.image_reference.get().get_width()-1)] = vec3ui(255, 0, 0);

	std::cout << dfs.size() << std::endl;

	image.save_to_disc("dfs.png");

	std::cin.get();
}/**/

int main() {
	Graph<int> graph;
	graph.add_edge(0, 1);
	graph.add_edge(0, 2);
	graph.add_edge(0, 5);
	graph.add_edge(0, 6);

	graph.add_edge(6, 4);
	graph.add_edge(4, 3);
	graph.add_edge(5, 3);

	std::cout << "depth first search: \n";
	auto dps = graph.depth_first_search(0);
	for (auto object : dps)
		std::cout << object << '\n';
	
	std::cout << "breadth first search: \n";
	auto bps = graph.breadth_first_search(0);
	for (auto object : bps)
		std::cout << object << '\n';


	std::cout << graph << '\n';



	std::cin.get();
}/**/

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
}/**/