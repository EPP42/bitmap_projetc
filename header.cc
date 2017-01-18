#include "header.hh"
#include <cstdlib>

Header::Header() 
{
}

void Header::load_header(std::FILE *stream)
{
	auto nb_byte = sizeof(header_);
	if (nb_byte != std::fread(&header_, 1, nb_byte, stream))
		throw std::length_error("Bad read");
}

unsigned char *Header::get_id()
{
	return this->header_.id;
}

unsigned Header::get_size_file() const
{
	return this->header_.size_file;
}

unsigned int Header::get_offset_image() const
{
	return this->header_.offset_image;
}

int Header::get_width() const
{
	return this->header_.pic_width;
}

int Header::get_height() const
{
	return this->header_.pic_height;
}


