#include "pixel.hpp"

using namespace pie;

pixel::pixel() {
	for(int i = 0; i < NUMBER_OF_COLOR_CHANNELS; i++)
		rgb_.push_back(0);
}

pixel::pixel(const pixel& px) {
	*this = px;
}

pixel::pixel(std::vector<int>&& colors) {
	for(int i = 0; i < NUMBER_OF_COLOR_CHANNELS; i++)
		rgb_.push_back(colors[i]);
}

pixel::pixel(pixel&& px) {
	*this = std::move(px);
}

pixel::~pixel() {
	;
}

pixel& pixel::operator=(const pixel& px) {
	rgb_ = px.rgb_;
	return *this;
}

void pixel::operator=(pixel&& px) {
	rgb_ = std::move(px.rgb_);
}

int& pixel::operator[](const int channel) {
	return rgb_[channel];
}

const int& pixel::operator[](const int channel) const {
	return rgb_[channel];
}

bool pixel::operator==(const pixel& px) const {
	return rgb_ == px.rgb_;
}

bool pixel::operator!=(const pixel& px) const {
	return !operator==(px);
}

bool pixel::out_of_bounds(int channel) const {
	return (channel < 0 || channel >= NUMBER_OF_COLOR_CHANNELS);
}
