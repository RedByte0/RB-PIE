#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include <iostream>
#include <vector>
#include <numeric>

//pie = ppm_image_editor
namespace pie {
class pixel {
private:
	const int NUMBER_OF_COLOR_CHANNELS = 3;
	std::vector<int> rgb_;

	bool out_of_bounds(int channel) const;	
public:
	pixel();	
	pixel(const pixel& px);
	pixel(pixel&& px);
	pixel(std::vector<int>&& colors);
	~pixel();

	long unsigned int size() {return rgb_.size();}
	float brightness();

	pixel& operator=(const pixel& px);
	void operator=(pixel&& px);
	int & operator[](const int channel);
	const int & operator[](const int channel) const;
	bool operator==(const pixel& px) const;
	bool operator!=(const pixel& px) const;
};
}
#endif
