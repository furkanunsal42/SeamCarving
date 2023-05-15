#include "Image.h"

#include <iostream>

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"

#include "Debuger.h"

Image::Image(int width, int height, int channel) :
	_width(width), _height(height), _channels(channel), new_width(width), new_height(height) 
{
	create_blank_image();
}


Image::Image(const std::string& file_path, int desired_channels, bool vertical_flip) :
	_vertical_flip(vertical_flip)
{
	_read_image(file_path, desired_channels);
}

Image::Image(const Image& copy_image) :
	_width(copy_image._width), _height(copy_image._height), _channels(copy_image._channels), new_width(copy_image._width), new_height(copy_image._height)
{
	size_t buffer_size = copy_image._width * copy_image._height * copy_image._channels;
	_image_data = new unsigned char[buffer_size];
	std::memcpy(_image_data, copy_image._image_data, buffer_size);
}

Image::Image(Image&& move_image) :
	_width(move_image._width), _height(move_image._height), _channels(move_image._channels), _image_data(move_image._image_data), new_width(move_image._width), new_height(move_image._height)
{
	move_image._image_data = nullptr;
}

Image::~Image() {
	_clear_ram();
}

void Image::_read_image(const std::string& file_path, int desired_channels) {
	if (_image_data != nullptr) {
		std::cout << "Image::_read_image() was called but _image_data was already initialized" << std::endl;
		ASSERT(false);
	}

	stbi_set_flip_vertically_on_load(_vertical_flip);

	_image_data = stbi_load(file_path.c_str(), &_width, &_height, &_channels, desired_channels);
	
	new_width = _width;
	new_height = _height;
	
	_channels = desired_channels;
}

void Image::resize(int target_width, int target_height) {
	//if (_width == target_width && _height == target_height)
	//	return;
	unsigned char* resized_image = (unsigned char*)malloc(target_width * target_height * _channels);
	stbir_resize_uint8(_image_data, _width, _height, _channels * _width, resized_image, target_width, target_height, _channels * target_width, _channels);
	stbi_image_free(_image_data);
	_width = target_width;
	_height = target_height;
	_image_data = resized_image;
}

void Image::_clear_ram() {
	stbi_image_free(_image_data);
}

//void Image::flip_verticaly() {
//	
//	unsigned char* flipped_data = new unsigned char[get_size()];
//
//	for (int y = 0; y < _height; y++) {
//		for (int x = 0; x < _width; x++) {
//			for (int ch = 0; ch < _channels; ch++)
//				flipped_data[((_height - 1 - y) * _width + x) * _channels + ch] = flipped_data[(y * _width + x) * _channels + ch];
//		}
//	}
//
//
//}


unsigned char* Image::get_image_data(){
	return _image_data;
}
int Image::get_width() const {
	return _width;
}
int Image::get_height() const {
	return _height;
}
int Image::get_channels() const {
	return _channels;
}

size_t Image::get_size() const {
	return _width * _height * _channels;
}

bool Image::get_vertical_flip() const {
	return _vertical_flip;
}


// Image will take ownership of the data
Image::Image(unsigned char* image_data, int width, int height, int channels, bool vertical_flip) :
	_image_data(image_data), _width(width), _height(height), _channels(channels), _vertical_flip(vertical_flip)
{
	if (image_data == nullptr) {
		ASSERT(false);
	}
	if (width == NULL) {
		ASSERT(false);
	}
	if (height == NULL) {
		ASSERT(false);
	}
	if (channels == NULL) {
		ASSERT(false);
	}
}


void Image::save_to_disc(const std::string& target_filename) {
	stbi_flip_vertically_on_write(_vertical_flip);
	int result_flag = stbi_write_png(target_filename.c_str(), _width, _height, _channels, _image_data, _width * _channels);
}

_image_row::_image_row(unsigned char* data, int width, int channel) :
	_row_data(data), _width(width), _channel(channel) {}

vec3uc& _image_row::operator[](unsigned int index) {
	index = std::min(std::max((int)index, 0), _width - 1);
	return *(vec3uc*)(_row_data + index * _channel);
}

_image_row&& Image::operator[](unsigned int index) {
	index = std::min(std::max((int)index, 0), _height - 1);
	return _image_row(_image_data + index * _width * _channels, _width, _channels);
}

void Image::create_blank_image(){
	_removed_pixels.clear();

	if (_image_data != nullptr)
		delete _image_data;
	_image_data = new unsigned char[_width * _height * _channels];
}
void Image::create_blank_image(int width, int height, int channel){
	_width = width;
	_height = height;
	_channels = channel;
	new_width = width;
	new_height = height;
	_removed_pixels.clear();

	create_blank_image();
}

void Image::update() {
	unsigned int pixel_amount = _width * _height;
	unsigned int new_pixel_amount = new_width * new_height;
	unsigned char* new_image = new unsigned char[new_pixel_amount* _channels];
	
	int new_index = 0;
	for (int old_index = 0; old_index < pixel_amount; old_index++) {
		vec2ui pixel_coords(old_index % (_width), old_index / (_width));
		if (_removed_pixels.find(pixel_coords) == _removed_pixels.end()){
			for (int channel_index = 0; channel_index < _channels; channel_index++) {
				new_image[new_index * 3 + channel_index] = _image_data[old_index * 3 + channel_index];
			}
			new_index++;
		}
	}

	delete _image_data;
	_image_data = new_image;

	_width = new_width;
	_height = new_height;

	_removed_pixels.clear();
}
void Image::remove_pixel(vec2ui pixel) {
	_removed_pixels.insert(pixel);
}


void Image::remove_vertical_line(unsigned int index){
	for (int y = 0; y < _height; y++) {
		vec2ui pixel_coord(index, y);
		remove_pixel(pixel_coord);
	}
	new_width--;
}

void Image::remove_horizontal_line(unsigned int index){
	for (int x = 0; x < _width; x++) {
		vec2ui pixel_coord(x, index);
		remove_pixel(pixel_coord);
	}
	new_height--;
}