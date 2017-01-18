#pragma once
#include <vector>
#include <memory>
#include "header.hh"

class Image
{
	
	public:

	Image();
	Image(const std::string picture_name);
	void create_matrice();
	void load_image(std::FILE *stream);

	private:

	Header header_;
	char **pic_pix_;
	std::string name_;
	std::FILE* stream_;
};
