#include "ppm.hpp"

using namespace pie;

ppm::ppm(std::vector<char>&& file_type)  : type_(file_type) {
	header_ = std::vector<char>();
	pixels_ = std::vector<pixel>();
}

ppm::ppm(const ppm& p) {
	*this = p;
}

ppm::ppm(const ppm&& p) {
	*this = p;
}

ppm::~ppm() {
	
}

void ppm::load_header(std::vector<char>&& buffer) {
	header_ = buffer;
}

void ppm::load_pixels(std::vector<pixel>&& buffer) {
	pixels_ = buffer;
}

void ppm::write_header(std::ofstream& file) {
	for(const char& ch : header_)
		file << ch;
}

std::vector<char> ppm::file_type() {
	std::vector<char> file_type;
	for(int i = 0; i < 3; i++)
		file_type.push_back(header_[i]);
	return file_type;	
}

bool ppm::file_type_is_correct() {
	bool correct = true;
	for(long unsigned int i = 0; i < type_.size() && correct == true; i++) {
		correct = type_[i] == header_[i];
	}
	return correct; 
}

void ppm::change_header_type() {
	for(long unsigned int i = 0; i < type_.size(); i++)
		header_[i] = type_[i];
}

void ppm::for_each(std::function<void(pixel&)> func) {
	for(pixel& px : pixels_)
		func(px);
	normalize();
}

void ppm::grayscale() {
	for_each([](pixel& px) {px[0] = px[1] = px[2] = (int)px.brightness();});
}

void ppm::sepia() {
	for_each([](pixel& px)  {
		px[0] = (px[0] * 1.8);
		px[1] = (px[1] * 1.2);
		px[2] = (px[2] * 0.8);
	});
}

void ppm::vertical_flip() {
	std::reverse(pixels_.begin(), pixels_.end());
}

void ppm::brightnes(float percentage) {
	//this function can break the balance between colors	
	percentage = percentage / 100 + 1;
	for(pixel& px : pixels_) {
		for(long unsigned int channel = 0; channel < px.size(); channel++) {
			px[channel] = px[channel] * percentage;
		}
	}
	normalize();
}

void ppm::normalize() {
	for(pixel& px : pixels_) {
		for(long unsigned int channel = 0; channel < px.size(); channel++) {
			if(px[channel] > 255)
				px[channel] = 255;
			else if(px[channel] < 0)
				px[channel] = 0;
		}
	}
}

ppm& ppm::operator=(const ppm& p) {
	header_ = p.header_;
	pixels_ = p.pixels_;
	return *this;
}

void ppm::operator=(ppm&& p) {
	header_ = std::move(p.header_);
	pixels_ = std::move(p.pixels_);
}

pixel& ppm::operator[](int index) {
	return pixels_[index];
}

const pixel& ppm::operator[](int index) const {
	return pixels_[index];
}

void ppm::operator+=(pixel px) {
	pixels_.push_back(px);
}
