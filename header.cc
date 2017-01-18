#include "header.hh"
#include <exception>
#include <cstdlib>

Header::Header() 
{
}

void Header::load_header(std::FILE *stream)
{
	std::cout<<sizeof(header_)<<"\n";
	auto nb_byte = sizeof(header_);
	if (nb_byte != std::fread(&header_, 1, nb_byte, stream))
		throw std::length_error("Bad read");
}

unsigned char *Header::get_id()
{
	return header_.id;
}

unsigned Header::get_size_file() const
{
	return header_.size_file;
}

unsigned int Header::get_offset_image() const
{
	return header_.offset_image;
}

int Header::get_width() const
{
	return header_.pic_width;
}

int Header::get_size() const
{
	return header_.size_of_image;
}

int Header::get_height() const
{
	return header_.pic_height;
}

void Header::reload_header(std::FILE *stream)
{
	auto size_total = sizeof (header_s);
	auto remain = 0u; 
	remain += std::fwrite(&header_, 1, sizeof(header_s), stream);
	if (remain != size_total)
		throw std::ios_base::failure("Uncomplete write operation");
}



