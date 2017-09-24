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
            std::cout << "header load " << std::endl;
            istream_.seekg(header_.get_offset_image(), std::ios_base::beg);
            std::cout << "seekg made "<< std::endl;
            create_matrice();
            load_image();
        }
        else
            throw std::ios_base::failure("unable to open file");
    }
    catch (const std::exception& mssg)
    {
        std::cout<<mssg.what();
        state_ = false;
    }
}


ImageC::operator bool() const
{
    return state_;
}

bool ImageC::is_24bit_pic() const
{
    return header_.size_pix_get() != 24 ? false : true; 
}

ImageC::~ImageC()
{
    if (pic_pix_)
    {
        for (uint32_t i = 0; i < header_.get_height(); i++)
            delete [] pic_pix_[i];
        delete [] pic_pix_;
    }
}

void ImageC::create_matrice()
{
    pic_pix_ = new pix*[header_.get_height()];
    if (pic_pix_)
    {
        for (uint32_t i = 0; i < header_.get_height(); i++)
            pic_pix_[i] = new pix[header_.get_width() * PIX];
    }
    else 
        throw std::bad_alloc();

}

void ImageC::load_image()
{
    std::cout << "In load image " << std::endl;
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
        ostream_.write(reinterpret_cast<char *>(pic_pix_[i]), header_.get_width() * PIX);
    if (ostream_.fail() || ostream_.bad())
        throw std::ios_base::failure("error while writting");
#if defined(DEBUG_MODE)
    assert(remains != header_.get_size());
#else
    if (remains != header_.get_size() * PIX)
        throw std::length_error("Uncomplete copy");
#endif
}

void ImageC::reload_image(std::string output_fname)
{
    std::cout << "In the reload function " << std::endl;
    ostream_.open(output_fname.c_str(), std::ofstream::out | std::ofstream::binary);
    if (ostream_)
    {
        header_.reload_header(ostream_);
        ostream_.seekp(header_.get_offset_image(), std::ios_base::beg);
        copy_pix_matrice();
    }
    else 
        throw std::ios_base::failure("Fail to open the file");
}

pix** ImageC::pic_pix_get() const
{
    return pic_pix_;
}



