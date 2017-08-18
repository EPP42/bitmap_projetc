#pragma once
#include "bmplib.hh"
#include <thread>
#include <mutex>
#include <exception>
#include <chrono>
#include <condition_variable>

class Kmean
{

    public :

        /* constructer : *cluster the number of cluster */ 
        Kmean(int cluster);
        Kmean() = delete;
        Kmean(Kmean& ) = delete;
        Kmean(Kmean&& ) = delete;
        ~Kmean() = default;

    public :

        void operator ()(ImageNB& image);
        void operator ()(ImageC& image);

   private :

        void operator ()(pix** matrix);
        void operator ()(uint8_t** matrix);

        /*clusterise : affect to each pix_info a cluster */

        void clusterise();
    public:

        void compute_distances(int x, int y);

    private :
       
       std::vector <struct pix_info> colored_cluster_;
       std::vector <struct nb_pix_info> nb_cluster;
       std::vector<struct colored_center> colored_center_;
       std::vector<struct nb_center> nb_center_;
       uint8_t **matrix_nb_;
       pix **matrix_colour_;
       uint32_t cluster_;
};
