#include <iostream>
#include "image.hh"

int main()
{
	Image I("birds.bmp");
	I.reload_image("new.bmp");
}
