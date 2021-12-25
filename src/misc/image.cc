#include "misc/image.hh"

ImageRGB::ImageRGB(const size_t width, const size_t height,
                   const std::vector<uint8_t> data)
    : width(width)
    , height(height)
    , data(data)
{}
