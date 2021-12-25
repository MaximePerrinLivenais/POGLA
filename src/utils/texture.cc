#include "texture.hh"

#include "parser/tga_parser.hh"

namespace misc
{
    int Texture::texture_unit_count = 0;

    Texture::Texture(std::string texture_path)
    {
        texture_unit_id_ = texture_unit_count++;
        glGenTextures(1, &texture_);
        glActiveTexture(GL_TEXTURE0 + texture_unit_id_);

        glBindTexture(GL_TEXTURE_2D, texture_);

        auto texture = open_tga_image(texture_path.c_str());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height,
                     0, GL_RGB, GL_UNSIGNED_BYTE, texture->data.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &texture_);
    }

    int Texture::get_texture_unit_id() const
    {
        return texture_unit_id_;
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, texture_);
    }
} // namespace misc
