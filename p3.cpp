#include "ppm.hpp"

using namespace pie;

p3::p3() : ppm(std::vector<char>({'P','3','\n'})) {
}

p3::p3(const ppm& p) : p3() {
	this->ppm::operator=(p);
	this->ppm::change_header_type();
}

p3::p3(ppm&& p) : p3() {
	this->ppm::operator=(std::move(p));
	this->ppm::change_header_type();
}

p3::~p3() {
	;
}

bool p3::load(const char* file_name) {
	std::ifstream file(file_name);
	if(file.is_open()) {
		std::vector<char> buffer = std::vector<char>(std::istreambuf_iterator<char>(file), {});
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

void p3::save(const char* file_name) {
	std::ofstream file(file_name);
	this->ppm::write_header(file);
	for(long unsigned int px = 0; px < this->ppm::size(); px++) {
		for(long unsigned int channel = 0; channel < this->ppm::operator[](px).size(); channel++)
			file << this->ppm::operator[](px)[channel] << '\n';
	}
	file.close();
}

void p3::load_header(std::vector<char>& buffer) {
	const std::vector<char> end_of_header_flag = {'2','5','5','\n'};
	bool end_of_header_flag_found = false;
	long unsigned int header_size = 0;

	for(header_size = 0; header_size < buffer.size() && end_of_header_flag_found == false; header_size++) {
		std::vector<char> last_four_characters_from_buffer = std::vector<char>();
		for(long unsigned int i = 0; i < end_of_header_flag.size(); i++)
			last_four_characters_from_buffer.push_back(buffer[header_size + i]);
		end_of_header_flag_found = (last_four_characters_from_buffer == end_of_header_flag);
	}
	header_size += 3;

	this->ppm::load_header(std::vector<char>(buffer.begin(), buffer.begin() + header_size));
	buffer.erase(buffer.begin(), buffer.begin() + header_size);
}

void p3::load_pixels(std::vector<char>& buffer) {
	std::vector<pixel> pixels;
	std::string color = "";
	int current_color_channel = 0;
	pixel px;
	for(char ch : buffer) {
		if(ch != '\n' && ch !='\r')
			color += ch;
		else {
			px[current_color_channel++] = std::stoi(color);
			if(current_color_channel == 3) {
				current_color_channel = 0;
				pixels.push_back(px);
			}
			color = "";
		}
	}
	this->ppm::load_pixels(std::move(pixels));
}


