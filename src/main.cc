#include <iostream>
#include "k_means.hh"

int main()
{

    ImageNB I("lena.bmp");
    if (I)
    {
        Kmean cluster(666, 100);
        cluster(I);
        cluster.display_colored_center();
        I.reload_image("remy.bmp");
    }
}
