#ifndef PICTURE_HPP
#define PICTURE_HPP 

#include <vector>
#include "Package.hpp"

class Picture 
{
public:
	Picture(std::vector<int> * source, std::vector<int> * buffer, std::vector<int> * device);

    std::vector<int> getSourcePicture();
    std::vector<int> getBufferPicture();
    std::vector<int> getDevicePicture();

private:
    std::vector<int> source_;
    std::vector<int> buffer_;
    std::vector<int> device_;
};


#endif
