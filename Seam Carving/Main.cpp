#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "CortexMath.h"
#include "Image.h"
#include "Graphs.h"
#include "GraphsTemplated.h"
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


/*int main() {
	int size = 18000000;
	{
		std::vector<vec2ui> vector;
		vector.reserve(size);
		std::cin.get();
	}
	{
		std::unordered_map<vec2ui, bool> map;
		map.reserve(size);
		std::cin.get();

	}
	{
		std::stack<vec2ui, std::vector<vec2ui>> stack;
		for (int i = 0; i < size; i++)
			stack.push(0);
		std::cin.get();
	}
}/**/

/*int main() {
	Image image("GoldBlock.png", 3, false);
	int kernel[3][3] =
	{
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1,
	};
	Image processed = kernel_filtering(image, kernel);
	processed._vertical_flip = false;

	ImageGraph graph(processed);
	graph.set_adjacencies_function([](AdjacencyFunctionParameters) {
			std::forward_list<ImageGraph::pixel_coord> adjacencies;
			if ((int)target_pixel.y <= -1) {
				for (int x = 0; x < self.image_reference.get().get_width(); x++)
					adjacencies.emplace_front(x, 0);
			}
			else if (target_pixel.y == self.image_reference.get().get_height()-1) {
				adjacencies.emplace_front(0, self.image_reference.get().get_height());
			}
			else {
				for (int y = 1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						if (y != 0 || x != 0) {
							adjacencies.emplace_front(
								std::min(std::max((int)target_pixel.x + x, 0), self.image_reference.get().get_width() - 1),
								std::min(std::max((int)target_pixel.y + y, 0), self.image_reference.get().get_height() - 1)
							);
						}
			}
			
			return adjacencies;
		});

	auto dfs = graph.depth_first_search(vec2ui(0, 100));
	int i = 0;
	
	for (auto& pixel : dfs)
		processed[pixel.y][pixel.x] = vec3ui(255, 0, 0);

	std::cout << dfs.size() << std::endl;

	processed.save_to_disc("dfs.png");

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