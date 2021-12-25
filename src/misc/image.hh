#pragma once

#include <memory>
#include <vector>

struct ImageRGB
{
    explicit ImageRGB(const size_t width, const size_t height, const std::vector<uint8_t> data);

    ~ImageRGB() = default;

    const size_t width;
    const size_t height;
    const std::vector<uint8_t> data;
};

using shared_image_rgb = std::shared_ptr<ImageRGB>;
