#include "bmplib.hh"

int operator * (struct pix const & p, struct colored_center const& c)
{
    return (c.pix_v.v - p.v) * (c.pix_v.v - p.v) +  
    (c.pix_v.r - p.r) * (c.pix_v.r - p.r) +
    (c.pix_v.b - p.b) * (c.pix_v.b - p.b);
}

int compute_colored_distance(int x, int y, const struct pix& p, 
  const struct colored_center& c)
{
    return (x - c.x) * (x - c.x) + (y - c.y) * (y - c.y) + p * c;
}

int compute_nb_distance( int x, int y, uint8_t pix, const struct nb_center& c)
{
    return (x - c.x) * (x - c.x) + (y - c.y) + (pix - c.pix_v) * (pix - c.pix_v);  
}

bool compare(int a, int b)
{
    return a < b ? true : false; 
}

bool operator == (const struct colored_center& a, const struct colored_center& b)
{
    return a.x == b.x && a.y == b.y && a.pix_v.v == b.pix_v.v
    && a.pix_v.r == b.pix_v.r && a.pix_v.b == b.pix_v.b ? true : false;
}

bool operator == (const struct nb_center& a, const struct nb_center& b)
{
    return a.x == b.x && a.y == b.y && a.pix_v == b.pix_v ? true : false;
}
