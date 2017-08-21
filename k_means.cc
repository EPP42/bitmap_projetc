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
    std::cout << " int operator () of image " << std::endl;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (uint32_t i = 0; i < cluster_; i++)
    {
        colored_center_.push_back(colored_center());
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

void Kmean::display_nb_center() const
{
    for (auto it : nb_center_)
    {
        std::cout << "x : " << it.x;
        std::cout << "y : " << it.y;
        std::cout << "grey :: " << it.pix_v;
    }
}


void Kmean::display_colored_center() const
{
    for (auto it : colored_center_)
    {
        std::cout << "x : " << it.x;
        std::cout << "y : " << it.y;
        std::cout << "green : " << it.pix_v.v;
        std::cout << "red : " << it.pix_v.r;
        std::cout << "blue : " << it.pix_v.b;
    }
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

