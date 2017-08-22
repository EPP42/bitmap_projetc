#include "image_nb.hh"
#include <exception>



ImageNB::ImageNB(std::string picture_name)
{
 try
    {
        istream_.open (picture_name, std::ifstream::binary | std::ifstream::in);
        if (istream_)
        {
            header_.load_header(istream_);
            if (!is_8bit_pic()) 
            { 
                throw std::logic_error("Bad format pic ") ;
            }
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
        state_ = false;
    }
}


ImageNB::operator bool () const
{
    return state_;
}

bool ImageNB::is_8bit_pic() const
{
    std::cout << "size pix get " << header_.size_pix_get() << std::endl;
    return header_.size_pix_get() != 8 ? false : true;
}

ImageNB::~ImageNB()
{
    if (pic_pix_)
    {
    for (uint32_t i = 0; i < header_.get_height(); i++)
        delete [] pic_pix_[i];
    delete [] pic_pix_;
    }
    if (buffer_)
        delete [] buffer_;
}

void ImageNB::create_matrice()
{
   pic_pix_ = new uint8_t*[header_.get_height()];
    if (pic_pix_)
    {
        for (uint32_t i = 0; i < header_.get_height(); i++)
            pic_pix_[i] = new uint8_t[header_.get_width()];
    }
    else 
        throw std::bad_alloc();
  
}

void ImageNB::load_image()
{
    long remains = 0;
    for (uint32_t i = 0; i < header_.get_height(); i++)
    {
        istream_.read(reinterpret_cast<char *>(pic_pix_[i]), header_.get_width());
        remains += istream_.gcount();
    }
    #if defined(DEBUG_MODE)
        assert(remains == header_.get_size());
    #else
        if (remains != header_.get_size())
            throw std::length_error("error");
    #endif
}


void ImageNB::copy_pix_matrice()
{
    long remains = 0;
    for (uint32_t i = 0; i < header_.get_height(); i++)
         ostream_.write(reinterpret_cast<char *>(pic_pix_[i]),header_.get_width());
    if (ostream_.fail() || ostream_.bad())
        throw std::ios_base::failure("error while writting");
    #if defined(DEBUG_MODE)
        assert(remains != header_.get_size());
    #else
        if (remains != header_.get_size())
            throw std::length_error("Uncomplete copy");
    #endif
}

void ImageNB::reload_image(std::string output_fname)
{
    ostream_.open(output_fname.c_str(), std::ofstream::out | std::ofstream::binary);
    if (ostream_)
    {
        std::streamsize size = 
        static_cast<std::size_t>(header_.get_offset_image()) - sizeof(header_s);
        header_.reload_header(ostream_);
        ostream_.write(reinterpret_cast<char*>(buffer_),size);
        copy_pix_matrice();
    }
    else 
        throw std::ios_base::failure("Fail to open the file");
}

uint8_t** ImageNB::pic_pix_get() const
{
    return pic_pix_;
}

void ImageNB::reload_buffer()
{
    ostream_.write(reinterpret_cast<char *>(buffer_), static_cast<std::size_t>(header_.get_offset_image()) -
    sizeof(header_s));
}


void ImageNB::create_buffer() 
{
    auto size = static_cast<std::size_t>(header_.get_offset_image()) - sizeof(header_s);
    buffer_ = new uint8_t[size];
}

