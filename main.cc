#include <iostream>
#include "k_means.hh"

int main()
{

    ImageC I("lena_colour.bmp");
    if (I)
    {
        std::cout << "here";
        Kmean cluster(100, 20);
        cluster(I);
        cluster.display_colored_center();
        I.reload_image("out.bmp");
    }
}
