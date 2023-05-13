#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "CortexMath.h"
#include "Image.h"

int main() {
	Image image("GoldBlock.png", 3, false);

	image.save_to_disc("original.png");

	for (int i = 0; i < image.get_width(); i++) {
		image.remove_pixel(vec2ui(i, i));
	}
	image.new_width--;
	image.update();

	image.save_to_disc("modified.png");

	//std::cin.get();
}