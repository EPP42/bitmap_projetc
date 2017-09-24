#pragma once
#include <vector>
#include <memory>
#include "header.hh"

class Image
{

    public:

        virtual ~Image();

        /* create the matrix of (uint8_t ** matrix ) that will contain the pixels */
        virtual void create_matrice() = 0;

        /* load the image information in the header object and the pixel part in the buffer */
        virtual void load_image() = 0;

        /*restore all the information in a new image file with a new name */
        virtual void reload_image(std::string output_fname) = 0;

        /**/
        virtual void copy_pix_matrice() = 0;

        /*print the header of the image */

        void print_header() const; 
   
        /* return the width of the image */

        uint32_t  get_width() const noexcept;

        /* return the height of the picture */

        uint32_t get_height() const noexcept;

        /* return true if the picture is an 8 bit pic else false */

        /*return true no error occured else true*/

        bool is_good() const;


   protected:
 
        Header header_;
        std::string name_;
        std::ifstream istream_;
        std::ofstream  ostream_;
        bool state_ = true;
};
