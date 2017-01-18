#pragma once 
#include <iostream>
#include <cstdio>

typedef struct header header_s;
#pragma pack (push, 1)
struct header
{
	// first part
	unsigned char id[2];
	unsigned size_file;
        char unused[4];
	unsigned int offset_image; // starting point 

	// DIBH header

	int number_of_byte_in_DIB;
	int pic_width;
	int pic_height;
	short number_color_plane;
	short number_of_bit_pixel;
	int compression_used;
	int size_of_image;
	int resolution_horizontal;
	int resolution_vertical;
	int number_color_palette;// 8 or 24 bits 
	int importance_color; // 0 mens all means 
	char red[3];
	char white[3];
	char padding [2];
	char blue[3];
	char green[3];
	char padding_2[2];
};



class Header
{
	private:

	  header_s header_;

	public:

	Header();
	unsigned char *get_id();
	unsigned get_size_file() const;
	unsigned int get_offset_image() const;
	int get_width() const;
	int get_height() const;
	void load_header(std::FILE* stream);
	void reload_header(std::FILE* stream); // output file 
        int get_size() const;

};
