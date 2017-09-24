#include "header.hh"
#include <exception>
#include <cstdlib>

Header::Header(std::ifstream& stream)
{
    load_header(stream);
}

const uint8_t *Header::get_id() const noexcept
{
	return header_.id;
}

uint32_t Header::get_size_file() const noexcept
{
	return header_.size_file;
}

uint32_t Header::get_offset_image() const noexcept
{
	return header_.offset_image;
}

uint32_t Header::get_width() const noexcept
{
	return header_.pic_width;
}

uint32_t Header::get_size() const noexcept
{
	return header_.size_of_image;
}

uint32_t Header::get_height() const noexcept
{
	return header_.pic_height;
}

void Header::print_header() const
{
    std::cout << "Id : " << header_.id
    << "\n"
    << "size of the file " << header_.size_file
    << "\n"
    << "size of the image " << header_.size_of_image
    << "\n"
    << "offset image : " << header_.offset_image
    << "\n"
    << "height : " << header_.pic_height
    << "\n"
    << "width : " << header_.pic_width
    << "\n"
    << "number of colour plane : " << header_.number_color_plane
    << "\n"
    << "number of bit pixel : " << header_.number_color_plane
    << "\n"
    << "resolution horizontal : " << header_.resolution_horizontal
    << "\n"
    << "resolution vertical : " << header_.resolution_vertical
    << "\n"
    << "number color palette (8 or 24 bit => 1 or 3 color per pixel)" 
    << header_.number_color_palette
    << std::endl;
}

void Header::reload_header(std::ofstream &stream)
{
    std::cout << "reload the header of the picture ." << "\n";
    stream.write(reinterpret_cast<const char *>(&header_), size_);
    if (!stream)
		    throw std::ios_base::failure("Bad read");
}

void Header::load_header(std::ifstream& stream)
{
    stream.read(reinterpret_cast<char *>(&header_),size_);
    if (!stream)
    {
        std::cout << "gcount : " << stream.gcount() << "size : " << size_ << std::endl;
        #if defined(DEBUG_MODE)
           assert(static_cast<const unsigned long>(stream.gcount()) != size_); 
        #else 
		    throw std::ios_base::failure("Bad read");
        #endif
    }
}


uint32_t Header::size_pix_get() const noexcept
{
    return header_.number_color_palette;
}

