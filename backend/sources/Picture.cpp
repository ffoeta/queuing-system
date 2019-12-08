#include "../headers/Picture.hpp"
#include <algorithm>

Picture::Picture(std::vector<int> * source, std::vector<int> * buffer, std::vector<int> * device)
{
    this -> source_ = *source;
    this -> buffer_ = *buffer;
    this -> device_ = *device;
}

std::vector<int> Picture::getSourcePicture()
{
    return this -> source_;
}

std::vector<int> Picture::getBufferPicture()
{
    return this -> buffer_;
}

std::vector<int> Picture::getDevicePicture()
{
    return this -> device_;
}

