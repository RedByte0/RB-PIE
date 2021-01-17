#include <iostream>

#include "ppm.hpp"

using pie::p3;
using pie::p6;
using pie::pixel;

//example code
int main() {
	p6 image;
	image.load("./images/bearP6.ppm");
	image.horizontal_flip();
	image.vertical_flip();
	image.save("test.ppm");
	return 0;
}
