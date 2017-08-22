#include "k_means.hh"

Kmean::Kmean(int cluster, int redo) : cluster_(cluster), redo_(redo)
{
    if (cluster_ <= 0)
        throw std::logic_error("Kmean must have at least 1 cluster");
    for (int i = 0; i < cluster_; i++)
        colored_cluster_.push_back(std::vector<pix_info>());
}

void Kmean::operator () (ImageNB& image)
{
    try
    {
        nb_means_ = std::vector<struct nb_sigma>(cluster_);
        width_ = image.get_width();
        height_ = image.get_height();
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        for (int i = 0; i < cluster_; i++)
        {
            nb_center_[i].x = std::rand() % image.get_width();
            nb_center_[i].y = std::rand() % image.get_height();
            nb_center_[i].pix_v = 
                image.pic_pix_get()[nb_center_[i].x][nb_center_[i].y];
        }
        this->operator()(image.pic_pix_get());
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}

void Kmean::operator () (ImageC& image)
{
    try
    {
        std::cout << " int operator () of image " << std::endl;
        colored_means_ = std::vector<struct colored_sigma>(cluster_);
        width_ = image.get_width();
        height_ = image.get_height();
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        for (int i = 0; i < cluster_; i++)
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
    catch(std::exception& e)
    {
        std::cout << "In the Image \"()\" operator method " << e.what() << "\n";
    }
}

void Kmean::display_nb_center() const
{
    for (auto it : nb_center_)
    {
        std::cout << "x : " << it.x;
        std::cout << "y : " << it.y;
        std::cout << "grey :: " << it.pix_v << "\n\n";
    }
    std::cout << "\n\n\n\n";
}


void Kmean::display_colored_center() const
{
    for (auto it : colored_center_)
    {
        std::cout << "x : " << it.x;
        std::cout << "y : " << it.y;
        std::cout << "green : " << it.pix_v.v;
        std::cout << "red : " << it.pix_v.r;
        std::cout << "blue : " << it.pix_v.b << "\n\n";
    }
    std::cout << "\n\n\n\n";
}

void Kmean::operator() (pix **matrix)
{
    int lap = 0;
    matrix_colour_ = matrix;
    while (!stable_ && redo_ > lap)
    {
        for (uint32_t  i = 0; i < height_; i++)
            for (uint32_t j = 0; j < width_; j++)
                compute_colored_distances(i, j);
        colored_sigma();
        display_colored_center();
        lap++;
        if (!stable_ && redo_ > lap)
            colored_clean();
    }
    apply_to_colored_pic();
}


void Kmean::operator() (uint8_t **matrix)
{
    int lap = 0;
    while (!stable_ && redo_ > lap)
    {
        matrix_nb_ = matrix;
        for (uint32_t  i = 0; i < height_; i++)
            for (uint32_t j = 0; j < width_; j++)
                compute_nb_distances(i, j);
        nb_sigma();
        display_nb_center();
        lap++;
        if (!stable_ && redo_ > lap)
            nb_clean();
    }
    apply_to_nb_pic();
}


// une boucle for ok
// je calcul la distance du pixel a chaque centre 
// je save le tout
// une fois fait je determine la distance la plus courte 
// une fois determiné je l'affecte au cluster
// la question ? =>  je calcul des distances je les range dans l'ordre du vector 

void Kmean::colored_clusterise(int x, int y, int cluster)
{
    colored_cluster_[cluster].push_back(pix_info(x, y, matrix_colour_[x][y], cluster));
    colored_means_[cluster].v += matrix_colour_[x][y].v;
    colored_means_[cluster].r += matrix_colour_[x][y].r;
    colored_means_[cluster].b += matrix_colour_[x][y].b;
    colored_means_[cluster].x += x;
    colored_means_[cluster].y += y;
}

void Kmean::nb_clusterise(int x, int y, int cluster)
{
    nb_cluster_[cluster].push_back(nb_pix_info(x, y, matrix_nb_[x][y], cluster));
    nb_means_[cluster].v += matrix_nb_[x][y];
    nb_means_[cluster].x += x;
    nb_means_[cluster].y += y;

}

void Kmean::compute_colored_distances(int x, int y) noexcept
{
    int min = 0;
    int index = 0;
    min = compute_colored_distance(x, y, matrix_colour_[x][y], colored_center_[0]);
    for (int i = 1; i < cluster_; i++)
    {
        auto distance = compute_colored_distance(x, y, matrix_colour_[x][y], 
                colored_center_[i]);
        index = distance < min ? i : index;
        min = distance < min ? distance : min;
    }
    // affect to the cluster 
    colored_clusterise(x, y, index);
}


void Kmean::compute_nb_distances(int x, int y) noexcept
{
    int min = 0;
    int index = 0;
    min = compute_nb_distance(x, y, matrix_nb_[x][y], nb_center_[0]);
    for (int i = 1; i < cluster_; i++)
    {
        auto distance = compute_nb_distance(x, y, matrix_nb_[x][y], 
                nb_center_[i]);
        index = distance < min ? i : index;
        min = distance < min ? distance : min;
    }
    // affect to the cluster 
    nb_clusterise(x, y, index);
}


void Kmean::colored_sigma() noexcept
{
    auto old_center(colored_center_);
    for (auto i = 0; i < cluster_; i++)
    {
        colored_means_[i].v = colored_means_[i].v / colored_cluster_[i].size();
        colored_means_[i].r = colored_means_[i].r / colored_cluster_[i].size();
        colored_means_[i].b = colored_means_[i].b / colored_cluster_[i].size();
        colored_means_[i].x = colored_means_[i].x / colored_cluster_[i].size();
        colored_means_[i].y = colored_means_[i].y / colored_cluster_[i].size();

        /* new center */

        colored_center_[i].x = colored_means_[i].x;
        colored_center_[i].y = colored_means_[i].y;
        colored_center_[i].pix_v.v = 
            matrix_colour_[colored_center_[i].x][colored_center_[i].y].v;
        colored_center_[i].pix_v.r = 
            matrix_colour_[colored_center_[i].x][colored_center_[i].y].r;
        colored_center_[i].pix_v.b =
            matrix_colour_[colored_center_[i].x][colored_center_[i].y].b;
    }
}

void Kmean::colored_center_invariance_check(const std::vector<struct colored_center>& center)
{
    for (int i = 0; i < cluster_; i++)
        if (!(center[i] == colored_center_[i]))
            break;
    stable_ = true;
}

void Kmean::nb_center_invariance_check(const std::vector<struct nb_center>& center)
{
    for (int i = 0; i < cluster_; i++)
        if (!(center[i] == nb_center_[i]))
            break;
    stable_ = true;
}


void Kmean::nb_sigma() noexcept
{
    for (auto i = 0; i < cluster_; i++)
    {
        nb_means_[i].v = nb_means_[i].v / nb_cluster_[i].size();
        nb_means_[i].x = nb_means_[i].v / nb_cluster_[i].size();
        nb_means_[i].y = nb_means_[i].v / nb_cluster_[i].size();
    }
}

void Kmean::apply_to_colored_pic() noexcept
{
    for (auto it : colored_cluster_)
        for (auto itt : it)
        {
            matrix_colour_[itt.x][itt.y].v = 
                static_cast<uint8_t>(colored_center_[itt.cluster].pix_v.v);
            matrix_colour_[itt.x][itt.y].r = 
                static_cast<uint8_t>(colored_center_[itt.cluster].pix_v.r);
            matrix_colour_[itt.x][itt.y].b = 
                static_cast<uint8_t>(colored_center_[itt.cluster].pix_v.b);
        }
}

void Kmean::apply_to_nb_pic() noexcept
{
    for (auto it : nb_cluster_)
        for (auto itt : it)
        {
            matrix_nb_[itt.x][itt.y] = 
                static_cast<uint8_t>(nb_center_[itt.cluster].pix_v);
        }
}

void Kmean::colored_clean()
{
    colored_cluster_.clear();
    colored_means_.clear();
    colored_means_ = std::vector<struct colored_sigma>(cluster_);
    for (int i = 0; i < cluster_; i++)
        colored_cluster_.push_back(std::vector<pix_info>());
}

void Kmean::nb_clean()
{
    nb_cluster_.clear();
    nb_means_.clear();
    nb_means_ = std::vector<struct nb_sigma>(cluster_);
    for (int i = 0; i < cluster_; i++)
        nb_cluster_.push_back(std::vector<nb_pix_info>());
}




