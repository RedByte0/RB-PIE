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


int ppm::width() {
	std::string width = "";
	std::vector<char*> header_section = width_and_height();
	//remove height
	for(long unsigned int i = 0; i < header_section.size() && *header_section[i] != ' '; i++) {
		width += *header_section[i];
	}
	return std::stoi(width);
}

int ppm::height() {
	std::string height = "";
	std::vector<char*> header_section = width_and_height();
	//remove height
	for(std::size_t i = header_section.size(); i > 0 && *header_section[i] != ' '; i--) {
		height += *header_section[i];
	}
	std::reverse(height.begin(), height.end());
	return std::stoi(height);
}

void ppm::load_header(std::vector<char>&& buffer) {
	header_ = std::move(buffer);
}

void ppm::load_pixels(std::vector<pixel>&& buffer) {
	pixels_ = std::move(buffer);
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
		px[0] = int(px[0] * 1.8);
		px[1] = int(px[1] * 1.2);
		px[2] = int(px[2] * 0.8);
	});
}

void ppm::vertical_flip() {
	std::reverse(pixels_.begin(), pixels_.end());
}


void ppm::horizontal_flip() {
	for(long unsigned int i = 0; i < pixels_.size(); i += width()) {
		std::reverse(pixels_.begin() + i, pixels_.begin() + i + width() - 1);
	}
}

void ppm::brightnes(float percentage) {
	//this function can break the balance between colors	
	percentage = percentage / 100 + 1;
	for(pixel& px : pixels_) {
		for(long unsigned int channel = 0; channel < px.size(); channel++) {
			px[channel] = int(px[channel] * percentage);
		}
	}
	normalize();
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

pixel& ppm::operator[](std::size_t index) {
	return pixels_[index];
}

const pixel& ppm::operator[](std::size_t index) const {
	return pixels_[index];
}

void ppm::operator+=(pixel px) {
	pixels_.push_back(px);
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

std::vector<char*> ppm::width_and_height() {
	std::vector<char*> header_section;
	for(std::size_t i = header_.size() - 6; i > 0; i--) {
		if (header_[i] == '\n')
			break;
		header_section.push_back(&header_[i]);
	}
	std::reverse(header_section.begin(), header_section.end());
	return header_section;
}
