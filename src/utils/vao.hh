#pragma once

#include <vector>
#include <GL/glew.h>
#include <memory>
#include "vbo.hh"

namespace misc
{
    class Vao
    {
    public:
        Vao();
        unsigned int nb_triangles() const;
        ~Vao();

        void bind();
        void add_vbo(std::shared_ptr<Vbo> vbo);
        static void unbind_all();

    private:
        GLuint vao_;
        std::vector<std::shared_ptr<Vbo>> vbos_;
    };
} // namespace misc
