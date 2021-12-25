#pragma once

#include <string>
#include <GL/glew.h>
#include <memory>

namespace misc
{
    class Texture
    {
    public:
        Texture(std::string texture_path);
        ~Texture();

        int get_texture_unit_id() const;

        void bind();

    private:
        GLuint texture_;
        int texture_unit_id_;
        static int texture_unit_count;
    };
} // namespace misc

using shared_texture = std::shared_ptr<misc::Texture>;
