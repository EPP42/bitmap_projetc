#include "k_means.hh"

Kmean::Kmean(int cluster) : cluster_(cluster)
{
    if (cluster_ <= 0)
        throw std::logic_error("Kmean must have at least 1 cluster");
}

void Kmean::operator () (ImageNB& image)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (uint32_t i = 0; i < cluster_; i++)
    {
       nb_center_[i].x = std::rand() % image.get_width();
       nb_center_[i].y = std::rand() % image.get_height();
       nb_center_[i].pix_v = image.pic_pix_get()[nb_center_[i].x][nb_center_[i].y];
    }
   this->operator()(image.pic_pix_get());
}

void Kmean::operator () (ImageC& image)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (uint32_t i = 0; i < cluster_; i++)
    {
       colored_center_[i].x = std::rand() % image.get_width();
       colored_center_[i].y = std::rand() % image.get_height();
       colored_center_[i].pix_v.v = 
       image.pic_pix_get()[colored_center_[i].x][colored_center_[i].y].v;
       colored_center_[i].pix_v.r = 
       image.pic_pix_get()[colored_center_[i].x][colored_center_[i].y].r;
       colored_center_[i].pix_v.b = 
       image.pic_pix_get()[colored_center_[i].x][colored_center_[i].y].b;
    }
    this->operator()(image.pic_pix_get());
}

void Kmean::operator() (pix **matrix)
{
    matrix_colour_ = matrix;
}

void Kmean::operator() (uint8_t **matrix)
{
  matrix_nb_ = matrix;   
}

void Kmean::compute_distances(int x, int y)
{
    if ( x && y )
        std::cout << "here " << std::endl;
}

