#include "vbo.hh"

namespace misc
{
    Vbo::Vbo(const std::vector<float>& values, GLuint location, GLint size)
    {
        glGenBuffers(1, &vbo_);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * values.size(),
                     values.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, NULL);

        size_ = values.size();
        element_size_ = size;
        location_ = location;

        capacity_ = size_;
    }

    void Vbo::update(const std::vector<float>& new_values, unsigned size)
    {
        element_size_ = size;
        size_ = new_values.size();

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);

        if (size_ > capacity_)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size_,
                         new_values.data(), GL_STATIC_DRAW);

            capacity_ = size_;
        }

        else
        {
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * size_,
                            new_values.data());
        }

        glVertexAttribPointer(location_, element_size_, GL_FLOAT, GL_FALSE, 0,
                              NULL);
    }

    unsigned int Vbo::get_nb_element() const
    {
        return size_ / element_size_;
    }

    GLuint Vbo::get_id() const
    {
        return vbo_;
    }

    GLuint Vbo::get_location() const
    {
        return location_;
    }

    Vbo::~Vbo()
    {
        glDeleteBuffers(1, &vbo_);
    }
} // namespace misc
