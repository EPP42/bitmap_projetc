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
            istream_.seekg(header_.get_offset_image(), std::ios_base::beg);
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


int operator * (struct pix& p, struct colored_center& c)
{
    return (c.pix_v.v - p.v) * (c.pix_v.v - p.v) +  
    (c.pix_v.r - p.r) * (c.pix_v.r - p.r) +
    (c.pix_v.b - p.b) * (c.pix_v.b - p.b);
}
