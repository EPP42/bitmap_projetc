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
	                auto size = header_.get_offset_image() - sizeof(header_s);
			create_buffer();
			std::fseek(stream_, sizeof(header_s), SEEK_SET);
			std::fread(buffer, 1, size, stream_);
			std::fseek(stream_, header_.get_offset_image(), SEEK_SET);
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



Image::~Image()
{
	for (int i = 0; i < header_.get_height(); i++)
		delete [] pic_pix_[i];
	delete [] pic_pix_;
	delete [] buffer;
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
	int remains = 0;
	for (int i = 0; i < header_.get_height(); i++)
		remains += std::fread(pic_pix_[i], 1, header_.get_width(), stream);
	if (remains != header_.get_size())
		std::length_error("error");
}

void Image::print_pix() const
{
	for (int i = 0; i < header_.get_height(); i++)
	{
		for (int j = 0; j < header_.get_width(); j++)
			std::cout<<pic_pix_[i][j]<<std::endl;
		std::cout<<std::endl;
	}
}

void Image::copy_pix_matrice()
{
	int remains = 0;
	for (int i = 0; i < header_.get_height(); i++)
		remains += std::fwrite(pic_pix_[i], 1, header_.get_width(), output_stream_);
	if (remains != header_.get_size())
		std::length_error("Uncomplete copy");
}

void Image::reload_image(std::string output_fname)
{
	output_stream_ = std::fopen(output_fname.c_str(), "wb");
	if (output_stream_)
	{
	        auto size = header_.get_offset_image() - sizeof(header_s);
		header_.reload_header(output_stream_);
		std::fseek(stream_, sizeof(header_s), SEEK_SET);
		std::fwrite(buffer, 1, size, output_stream_);
		std::fseek(output_stream_, header_.get_offset_image(), SEEK_SET);
		copy_pix_matrice();
	}
	else 
		throw std::ios_base::failure("Fail to open the file");
}

void Image::create_buffer() 
{
	auto size = header_.get_offset_image() - sizeof(header_s);
	buffer = new char[size];
}
