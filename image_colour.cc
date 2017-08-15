#include "image_colour.hh"
#include <exception>

#define PIX 3 


ImageC::ImageC(std::string picture_name)
{
 try
    {
        istream_.open (picture_name, std::ifstream::binary | std::ifstream::in);
        if (istream_)
        {
            header_.load_header(istream_);
            auto size = header_.get_offset_image() - sizeof(header_s);
            create_buffer();
            istream_.read(reinterpret_cast<char*>(buffer_), size);
            create_matrice();
            load_image();
        }
        else
            throw std::ios_base::failure("unable to open file");
    }
    catch (const std::exception& mssg)
    {
        std::cout<<mssg.what();
    }
}

ImageC::~ImageC()
{
    for (uint32_t i = 0; i < header_.get_height(); i++)
        delete [] pic_pix_[i];
    delete [] pic_pix_;
    delete [] buffer_;
}

void ImageC::create_matrice()
{
   pic_pix_ = new uint8_t*[header_.get_height() * PIX];
    if (pic_pix_)
    {
        for (uint32_t i = 0; i < header_.get_height(); i++)
            pic_pix_[i] = new uint8_t[header_.get_width()];
    }
    else 
        throw std::bad_alloc();
  
}

void ImageC::load_image()
{
    long remains = 0;
    for (uint32_t i = 0; i < header_.get_height(); i++)
    {
        istream_.read(reinterpret_cast<char *>(pic_pix_[i]), 
        header_.get_width() * PIX);
        remains += istream_.gcount();
    }
    #if defined(DEBUG_MODE)
        assert(remains == header_.get_size());
    #else
        if (remains != header_.get_size())
            throw std::length_error("error");
    #endif
}


void ImageC::copy_pix_matrice()
{
    long remains = 0;
    for (uint32_t i = 0; i < header_.get_height(); i++)
         ostream_.write(reinterpret_cast<char *>(pic_pix_[i]),header_.get_width() * PIX);
    if (ostream_.fail() || ostream_.bad())
        throw std::ios_base::failure("error while writting");
    #if defined(DEBUG_MODE)
        assert(remains != PIX * header_.get_size());
    #else
        if (remains != header_.get_size() * PIX)
            throw std::length_error("Uncomplete copy");
    #endif
}

void ImageC::reload_image(std::string output_fname)
{
    ostream_.open(output_fname.c_str(), std::ofstream::out | std::ofstream::binary);
    if (ostream_)
    {
        std::streamsize size = 
        static_cast<std::size_t>(header_.get_offset_image()) - sizeof(header_s);
        header_.reload_header(ostream_);
        // wird have to look for buffer value 
        //ostream_.seekp(sizeof(header_s), std::ios_base::beg);
        ostream_.write(reinterpret_cast<char*>(buffer_),size);
        //std::fseek(output_stream_, header_.get_offset_image(), SEEK_SET);
        copy_pix_matrice();
    }
    else 
        throw std::ios_base::failure("Fail to open the file");
}



void ImageC::reload_buffer()
{
    ostream_.write(reinterpret_cast<char *>(buffer_), static_cast<std::size_t>(header_.get_offset_image()) -
    sizeof(header_s));
}

void ImageC::create_buffer() 
{
    auto size = static_cast<std::size_t>(header_.get_offset_image()) - sizeof(header_s);
    buffer_ = new uint8_t[size];
}




