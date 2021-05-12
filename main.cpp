#include <iostream>

#include "ppm.hpp"

using pie::p3;
using pie::p6;
using pie::pixel;

//example code
int main() {
	p6 image;
	image.load("");
	p3 image2 = image;
	image2.save("test.ppm");
	return 0;
}
