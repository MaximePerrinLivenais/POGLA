#include "vao.hh"

namespace misc
{
    Vao::Vao()
    {
        glGenVertexArrays(1, &vao_);
        bind();
    }

    Vao::~Vao()
    {
        glDeleteVertexArrays(1, &vao_);
    }

    void Vao::bind()
    {
        glBindVertexArray(vao_);
    }

    void Vao::add_vbo(std::shared_ptr<Vbo> vbo)
    {
        bind();
        vbos_.push_back(vbo);
    }

    unsigned int Vao::nb_triangles() const
    {
        return vbos_.size() != 0 ? vbos_[0]->get_nb_element() : 0;
    }

    void Vao::unbind_all()
    {
        glBindVertexArray(0);
    }
} // namespace misc
