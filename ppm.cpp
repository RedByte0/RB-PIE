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
