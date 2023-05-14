#pragma once 

#include <string>
#include <memory>
#include <unordered_set>
#include "CortexMath.h"

class _image_row {
public:
	_image_row(unsigned char* data, int width, int channel);
	vec3uc& operator[](unsigned int index);
private:
	unsigned char* _row_data;
	int _width = NULL;
	int _channel = NULL;
};

class Image {
public:
	
	Image(int width = 1024, int height = 1024, int channel = 3);

	Image(const std::string& file_path, int desired_channels = 4, bool vertical_flip = true);
	Image(const Image& copy_image);
	Image(Image&& move_image);

	~Image();

	//void flip_verticaly();
	unsigned char* get_image_data();
	int get_width() const;
	int get_height() const;
	int get_channels() const;
	bool get_vertical_flip() const;
	size_t get_size() const;

	void resize(int target_width, int target_height);
	void save_to_disc(const std::string& target_filename);

	Image(unsigned char* image_data, int width, int height, int channels, bool vertical_flip);
	unsigned char* _image_data = nullptr;

	void create_blank_image();
	void create_blank_image(int width, int height, int channel);

	_image_row&& operator[](unsigned int index);

	void update();
	void remove_pixel(vec2ui pixel);
	void remove_vertical_line(unsigned int index);
	void remove_horizontal_line(unsigned int index);

	int new_width = NULL, new_height = NULL;
	bool _vertical_flip = true;
private:
	int _width = NULL, _height = NULL, _channels = NULL;
	void _read_image(const std::string& file_path, int desired_channels = 4);
	void _clear_ram();

	std::unordered_set<vec2ui> _removed_pixels;
	
};

