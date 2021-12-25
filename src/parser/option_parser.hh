#pragma once

#include <string>
#include <filesystem>

namespace misc
{
    struct Options
    {
        Options(int argc, char* argv[]);

        std::string obj_file_path;
        std::filesystem::path shaders_dir_path;
        int screen_width;
        int screen_height;
    };
} // namespace misc
