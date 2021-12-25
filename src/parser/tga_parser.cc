#include "tga_parser.hh"

#include <cerrno>
#include <cstdio>
#include <iostream>

static void to_rgb(std::vector<u_int8_t>& image_data)
{
    for (size_t i = 0; i < image_data.size(); i += 3)
    {
        std::swap(image_data[i], image_data[i + 2]);
    }
}

shared_image_rgb open_tga_image(const char* filename)
{
    HeaderTGA header;

    FILE* fileptr = fopen(filename, "r");
    if (!fileptr)
    {
        std::cerr << "Could not open " << filename << " in reading\n";
        exit(EXIT_FAILURE);
    }

    if (fread(&header, sizeof(struct HeaderTGA), 1, fileptr) != 1)
    {
        std::cerr << "Could not read " << filename << " tga header\n";
        exit(EXIT_FAILURE);
    }

    if (header.pixel_size != 24)
    {
        std::cerr << "Image " << filename
                  << " has wrong pixel format: expected 24 got "
                  << (int)header.pixel_size << "\n";
        exit(EXIT_FAILURE);
    }

    size_t image_width = header.width;
    size_t image_height = header.height;
    auto image_byte_size = image_width * image_height * 3;

    auto image_data = std::vector<uint8_t>();
    image_data.resize(image_byte_size);

    if (fread(image_data.data(), sizeof(uint8_t), image_byte_size, fileptr)
        != image_byte_size)
    {
        std::cerr << "Could not read image data from " << filename << " : "
                  << errno << "\n";
        exit(EXIT_FAILURE);
    }

    fclose(fileptr);

    // Data is BGR we need to change it to RGB
    to_rgb(image_data);

    return std::make_shared<ImageRGB>(image_width, image_height, image_data);
}
