#pragma once

#include "image.hh"
#include "bmplib.hh"


class ImageC : public Image
{

    public:
        
        using pix = struct pix;
        using pix_info = struct pix_info;

        ImageC(std::string picture_name);
        virtual ~ImageC() override;
        
        /* create the matrix of (uint8_t ** matrix ) that will contain the pixels */
        virtual void create_matrice() override;

        /* load the image information in the header object and the pixel part in the buffer */
        virtual void load_image() override;

        /*restore all the information in a new image file with a new name */
        virtual void reload_image(std::string output_fname) override;

        /*print the header of the image */
         virtual void copy_pix_matrice() override;

         pix **pic_pix_get() const;

    protected :

        pix **pic_pix_ = nullptr;
};

int operator * (struct pix& p, struct colored_center& c);
