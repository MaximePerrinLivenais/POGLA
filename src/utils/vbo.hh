#pragma once

#include <vector>
#include <GL/glew.h>

namespace misc
{
    class Vbo
    {
    public:
        Vbo(const std::vector<float>& values, GLuint location, GLint size);
        unsigned int get_nb_element() const;
        GLuint get_id() const;
        GLuint get_location() const;
        void update(const std::vector<float>& new_values, unsigned size);
        ~Vbo();

    private:
        GLuint vbo_;
        GLuint location_;
        unsigned int size_;
        unsigned int element_size_;
        unsigned int capacity_;
    };
} // namespace misc
