#include "image.hh"


Image::~Image()
{
}

void Image::print_header() const
{
    header_.print_header();
}

uint32_t Image::get_width() const noexcept
{
    return header_.get_width();
}


uint32_t Image::get_height() const noexcept
{
    return header_.get_height();
}


