#include "ppm.hpp"

using namespace pie;
p6::p6() : ppm(std::vector<char>({'P','6','\n'})){
}

p6::p6(const ppm& p) : p6() {
	this->ppm::operator=(p);
	this->ppm::change_header_type();
}

p6::p6(ppm&& p) : p6() {
	this->ppm::operator=(std::move(p));
	this->ppm::change_header_type();
}
p6::~p6() {

}

bool p6::load(const char* file_name) {
	std::ifstream file(file_name);
	if(file.is_open()) {
		std::vector<int> buffer = std::vector<int>(std::istreambuf_iterator<char>(file), {});
		load_header(buffer);
		if(this->ppm::file_type_is_correct()) {
			load_pixels(buffer);
			return true;
		}
		else
		std::cerr << "The expected file type and the type within the header do not match !" << std::endl;
	}
	else
		std::cerr << "Error while loading the picture !" << std::endl;
	return false;

}

void p6::save(const char* file_name) {
	std::ofstream file(file_name);
	this->ppm::write_header(file);
	for(long unsigned int px = 0; px < this->ppm::size(); px++) {
		for(long unsigned int channel = 0; channel < this->ppm::operator[](px).size(); channel++)
			file << (char)this->ppm::operator[](px)[channel];
	}
	file.close();
}	

void p6::load_header(std::vector<int>& buffer) {
	const std::vector<char> end_of_header_flag = {'2','5','5','\n'};
	bool end_of_header_flag_found = false;
	long unsigned int header_size = 0;

	for(header_size = 0; header_size < buffer.size() && end_of_header_flag_found == false; header_size++) {
		std::vector<char> last_four_characters_from_buffer = std::vector<char>();
		for(long unsigned int i = 0; i < end_of_header_flag.size(); i++)
			last_four_characters_from_buffer.push_back((char)buffer[header_size + i]);
		end_of_header_flag_found = (last_four_characters_from_buffer == end_of_header_flag);
	}
	header_size += 3;

	this->ppm::load_header(std::vector<char>(buffer.begin(), buffer.begin() + header_size));
	buffer.erase(buffer.begin(), buffer.begin() + header_size);
}

void p6::load_pixels(std::vector<int>& buffer) {
	std::vector<pixel>pixels;
	int current_color_channel = 0;
	pixel px;
	for(int i : buffer) {
		px[current_color_channel++] = (i >= 0 ? i : 256+i);
		if(current_color_channel == 3) {
			pixels.push_back(px);
			current_color_channel = 0;
		}
	}
	this->ppm::load_pixels(std::move(pixels));
}
