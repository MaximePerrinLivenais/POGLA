#pragma once

#include <vector>
#include <string>

namespace parser
{
    struct ObjData
    {
        std::vector<float> points;
        std::vector<float> normals;
        std::vector<float> colors;
        std::vector<float> uvs;
    };

    ObjData parse_obj(std::string file);
} // namespace parser
