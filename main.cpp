#include <iostream>

#include "ppm.hpp"

using pie::p3;
using pie::p6;
using pie::pixel;

int main() {
	p6 image;
	image.load("./images/bearP6.ppm");
	image.for_each([](pixel& px) {
		int total = px[0] + px[1] + px[2];
		total /= 3;
		px[0] = px[1] = px[2] = total;
	});
	image.save("b&w.ppm");
	return 0;
}
