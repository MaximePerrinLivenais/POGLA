#pragma once

#include "misc/image.hh"

struct HeaderTGA
{
    uint8_t idl_length;

    uint8_t color_map_type;
    uint8_t image_type;

    uint16_t color_map_start;
    uint16_t color_map_length;
    uint8_t color_map_depth;

    uint16_t x_offset;
    uint16_t y_offset;

    uint16_t width;
    uint16_t height;
    uint8_t pixel_size;

    uint8_t image_desc_alpha_channel_bits : 4;
    uint8_t image_desc_image_origin : 2;
    uint8_t image_desc_unused : 2;
} __attribute__((packed));

shared_image_rgb open_tga_image(const char* filename);
