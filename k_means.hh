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

        using  pix_info = struct pix_info;
        using  nb_pix_info = struct nb_pix_info;
        /* constructer : *cluster the number of cluster */ 
        Kmean(int cluster, int redo);
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

        void colored_clusterise(int x, int y, int cluster);
        void nb_clusterise(int x, int y, int cluster);
        void colored_sigma() noexcept;
        void nb_sigma() noexcept;

    public:

        void apply_to_colored_pic() noexcept;
        void apply_to_nb_pic() noexcept;
        void colored_clean();
        void nb_clean();

    public:

        void compute_colored_distances(int x, int y) noexcept;
        void compute_nb_distances(int x, int y) noexcept;
        void display_nb_center() const;
        void display_colored_center() const;

    public :
        
        void colored_center_invariance_check(const std::vector<struct colored_center>& center);
        void nb_center_invariance_check(const std::vector<struct nb_center>& center);

    private :
       
       std::vector<std::vector<pix_info>> colored_cluster_;
       std::vector<std::vector<nb_pix_info>> nb_cluster_;
       std::vector<struct colored_center> colored_center_;
       std::vector<struct nb_center> nb_center_;
       std::vector<struct colored_sigma> colored_means_;
       std::vector<struct nb_sigma> nb_means_;
       uint8_t **matrix_nb_;
       pix **matrix_colour_;
       int cluster_;
       uint32_t width_;
       uint32_t height_;
       bool stable_ = false;
       int redo_ = 5;
    //   bool stable_;/* true if the precedent centers are the same that the new*/
};
