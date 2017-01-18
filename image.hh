#pragma once
#include <vector>
#include <memory>
#include "header.hh"

class Image
{
	
	public:

	Image();
	Image(const std::string picture_name);
	~Image();
	void create_matrice();
	void create_buffer();
	void load_image(std::FILE *stream);
        void reload_image(std::string output_fname);
	void copy_pix_matrice();
	void print_pix() const;
	void reload_buffer(); 
	private:

	Header header_;
	char *buffer; 
	char **pic_pix_;
	std::string name_;
	std::FILE *stream_;
	std::FILE *output_stream_;
};
