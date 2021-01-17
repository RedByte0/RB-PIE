#ifndef PPM_HPP_
#define PPM_HPP_

#include "pixel.hpp"
#include <fstream>
#include <algorithm>
#include <string>
#include <functional>

namespace pie {

class ppm {
private:
	const std::vector<char> type_;
	std::vector<char> header_;
	std::vector<pixel> pixels_;

public:
	ppm(std::vector<char>&& file_type);
	ppm(const ppm& p);
	ppm(const ppm&& p);
	virtual ~ppm() = 0; //pure virtual class

	int width();
	int height();

	void load_header(std::vector<char>&& buffer);
	void load_pixels(std::vector<pixel>&& buffer);
	void write_header(std::ofstream& file);

	std::vector<char> file_type();
	bool file_type_is_correct();

	long unsigned int size() {return pixels_.size();};
	void change_header_type();

	virtual void for_each(std::function<void(pixel&)> func);

	//some functoins just for fun
	void grayscale();
	void sepia();
	void vertical_flip();
	void horizontal_flip();
	void brightnes(float percentage);

	ppm& operator=(const ppm& p);
	void operator=(ppm&& p);
	pixel& operator[](int index);
	const pixel& operator[](int index) const;
	void operator+=(pixel px);

private:
	void normalize();
	std::vector<char*> width_and_height();
};

class p3 : public ppm {
public:
	p3();
	p3(const ppm& p);
	p3(ppm&& p);
	~p3();
	bool load(const char* file_name);
	void save(const char* file_name);

private:	
	void load_header(std::vector<char>& buffer);
	void load_pixels(std::vector<char>& buffer);
};

class p6 : public ppm {
public:
	p6();
	p6(const ppm& p);
	p6(ppm&& p);
	~p6();
	bool load(const char* file_name);
	void save(const char* file_name);

private:
	void load_header(std::vector<int>& buffer);
	void load_pixels(std::vector<int>& buffer);
};

}

#endif
