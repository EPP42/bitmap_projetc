#pragma once 
#include <iostream>
#include <fstream>
#include <cstdio>

#if defined(DEBUG_MODE)

#include <cassert>

#endif 


typedef struct header header_s;
#pragma pack (push, 1)
struct header
{
	// first part information about the header of the image 
	uint8_t id[2];
	uint32_t size_file;
    uint8_t unused[4]; // application specific 
	uint32_t offset_image; // starting point 

	// DIBH header second part of the header contains information about
    // the image 

	uint32_t number_of_byte_in_DIB; // number of byte in the bitmap 
	uint32_t pic_width;
	uint32_t pic_height;
	uint16_t number_color_plane;
	uint16_t number_of_bit_pixel;
	uint32_t compression_used;
	uint32_t size_of_image;
	uint32_t resolution_horizontal;
	uint32_t resolution_vertical;
	uint32_t number_color_palette;// 8 or 24 bits 
	uint32_t importance_color; // 0 mens all means 
	uint8_t  red[3];
	uint8_t  white[3];
	uint8_t padding [2];
	uint8_t blue[3];
	uint8_t green[3];
	uint8_t padding_2[2];
};



class Header
{
	private:

	  header_s header_;
      const size_t size_ = sizeof(header_s);

	public:

	Header() = default;

    Header(std::ifstream& stream);

    /* Return the id BM if it's a BMP picture */
	const uint8_t* get_id() const noexcept;

	uint32_t  get_size_file() const noexcept;

    /*return the offset where the picture start */
	uint32_t get_offset_image() const noexcept;
  
    /* get the width of the picture */
	uint32_t get_width() const noexcept;
   
   /* get the height of the picture */
	uint32_t get_height() const noexcept;
    
   /* get the full size of the picture */
    uint32_t get_size() const noexcept;

    /* this function read the header from an existing BMP pict */
	void load_header(std::ifstream& stream);

    /* This function restore the header for the new image */
	void reload_header(std::ofstream& stream); // output file 

    /*print the heaeder*/
    void print_header() const;
};
