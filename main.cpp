#include <iostream>

#include "ppm.hpp"

using pie::p3;
using pie::p6;
using pie::pixel;

//example code
int main() {
	p6 image, image2;
	p3 image3;
	image.load("./images/bearP6.ppm");
	image2.load("./images/pexelsP6.ppm");
	image3 = std::move(image2);
	image2 = image;

	image.sepia();
	image.brightnes(-10);

	image2.grayscale();
	image2.vertical_flip();

	image3.brightnes(20);

	image.save("sepia.ppm");
	image2.save("grayscale.ppm");
	image3.save("imageP3.ppm");
	return 0;
}
