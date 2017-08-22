#pragma once
#include <ctime>
#include "image_colour.hh"
#include "image_nb.hh"
struct pix
    {
        uint8_t v;
        uint8_t r;
        uint8_t b;
    };


struct colored_sigma
{
    long v;
    long r;
    long b;
    long x;
    long y;
};

struct nb_sigma
{
    long v;
    long x;
    long y;
};

struct colored_center
{
    colored_center() = default;
    int x;
    int y;
    struct pix pix_v; // for 24 bit pic
};

struct nb_center
{
    nb_center() = default;
    int x;
    int y;
    uint8_t pix_v;
};

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

struct pix_info
{

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

/* definition of the operator "*" produit scalaire between a 
and a center */

int operator * (struct pix const& p, struct colored_center const & c);

/* compute the distance between a pixel and the center*/
int compute_colored_distance(int x, int y, const struct pix& p, 
const struct colored_center& c);


/* compute the distance between a pixel and a center */
int compute_nb_distance(int x, int y, uint8_t pix, const struct nb_center& c);

/* compare two integer return true if a < b */
bool compare(int a, int b);


/* return true if the two structure are equal */
bool operator == (const struct nb_center& a, const struct nb_center& b);

/*return true if the two structure are equal */
bool operator == (const struct colored_center& a, const struct colored_center& b);
