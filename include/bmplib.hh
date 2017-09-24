#pragma once

#include <ctime>
#include "image_colour.hh"
#include "image_nb.hh"

///!
///!\version 1.0
///!\author Remy.w.h DEME
///!\file bmpli.hh
///!\brief Bmplib header contains all the structure create for implement the
///!k_means algorithm.
///!\date 01 septembre 2017
///!




///!
///! \struct pix bmplib.hh "bmplib.h"
///! \brief store a colored pixel value
///!
struct pix
    {
        uint8_t v; ///! \brief strore the green pixel 
        uint8_t r; ///! \brief store the red pixel
        uint8_t b; ///! \brief store the blue pixel
    };


///! \struct colored_sigma bmplib.hh "bmplib.hh"
///! \brief Used to save and compute the mean of the value of 
///! \brief all the coloured pixel of picture  that  belong to the cluster
struct colored_sigma
{
    long v;
    long r;
    long b;
    long x;
    long y;
};

///! \struct nb_sigma bmplib.hh "bmplib.hh"
///! \bief Used to save and compute the means of the value of all the 
///! black and white picture pixel that belong to a cluster
struct nb_sigma
{
    long v;
    long x;
    long y;
};


/// \struct colored_center bmplib.hh "Save the value of the center"
struct colored_center
{
    colored_center() = default;
    int x;
    int y;
    struct pix pix_v; // for 24 bit pic
};

/// \struct nb_center bmlibp.hh "Store the black and white picture center"
struct nb_center
{
    nb_center() = default;
    int x;
    int y;
    uint8_t pix_v;
};

/// \struct nb_pix_info bmplib.hh "Store black and white picture pixels info"
struct nb_pix_info
{
    nb_pix_info(int x, int y, uint8_t pix, int cluster) : 
    x(x), 
    y(y), 
    pix_v(pix), 
    cluster(cluster)
    {
    }

    nb_pix_info(struct nb_pix_info&& ) = default;
    nb_pix_info(struct nb_pix_info& ) = default;
    nb_pix_info() = default;
    int x;
    int y;
    uint8_t pix_v;
    int cluster;
};

///! \struct pix_info bmplib.hh "Store the coloured picture information"
struct pix_info
{
    /*! \brief default constructor  
    */
    pix_info() = default;
    pix_info(struct pix_info& ) = default;
    pix_info(struct pix_info&& ) = default;
    pix_info(int x, int y, struct pix p, int cluster) :
    x(x),
    y(y),
    pix_v(p),
    cluster(cluster)
    {
    }

    int x;
    int y;
    struct pix pix_v;
    int cluster;
};

///! \func operator
///! \brief definition of the operator "*" produit scalaire between a 
///!and a center

int operator * (struct pix const& p, struct colored_center const & c);

/* compute the distance between a pixel and the center*/
int compute_colored_distance(int x, int y, const struct pix& p, 
const struct colored_center& c);


/*! \func compute_nb_distance
*   \brief compute the distance between a center and a pixel 
*/
int compute_nb_distance(int x, int y, uint8_t pix, const struct nb_center& c);

/*! \func compare
*\brief  compare two integer return true if a < b 
*/
bool compare(int a, int b);


/*!
* \func operator ==
* \brief operator == return true if the two structure nb_center are equal 
*/
bool operator == (const struct nb_center& a, const struct nb_center& b);

/*! \func operator ==
*   \brief return return true if the two structure are equal 
*/
bool operator == (const struct colored_center& a, const struct colored_center& b);
