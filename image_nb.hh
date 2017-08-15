#include "image.hh"


class ImageNB : public Image
{
    public:
        ImageNB(std::string picture_name);
        virtual ~ImageNB() override;
        
        /* create the matrix of (uint8_t ** matrix ) that will contain the pixels */
        virtual void create_matrice() override;

        /* create the buffer that will contain the information between the 
         header part and the beginning of the picture */
        virtual void create_buffer() override;

        /* load the image information in the header object and the pixel part in the buffer */
        virtual void load_image() override;

        /*restore all the information in a new image file with a new name */
        virtual void reload_image(std::string output_fname) override;

        /*load the buffer in the image file*/
        virtual void reload_buffer() override; 

        /*print the header of the image */
         virtual void copy_pix_matrice() override;

};
