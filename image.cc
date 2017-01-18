#include <exception>
#include "image.hh"


Image::Image()
{
}

Image::Image(const std::string picture_name) : name_(picture_name)
{
	try
	{
		stream_ = std::fopen(name_.c_str(), "rb");
		if (stream_)
		{
			header_.load_header(stream_);
			fseek(stream_, header_.get_offset_image(), SEEK_SET);
			create_matrice();
			load_image(stream_);
		}
		else
			throw std::ios_base::failure("unable to open file");
	}
	catch (const std::exception& mssg)
	{
		std::cout<<mssg.what();
	}
}

void Image::create_matrice()
{
	pic_pix_ = new char*[header_.get_height()];
	if (pic_pix_)
	{
		for (int i = 0; i < header_.get_height(); i++)
			pic_pix_[i] = new char[header_.get_width()];
	}
	else 
		throw std::bad_alloc();
}

void Image::load_image(std::FILE *stream)
{
	auto size_total = header_.get_width() * header_.get_height();
	auto remains = 0;
	while (remains != size_total)
		remains += std::fread(pic_pix_, 1, size_total, stream);
}
