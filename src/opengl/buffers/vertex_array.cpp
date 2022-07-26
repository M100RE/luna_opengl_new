#include <luna/opengl/buffers/vertex_array.h>
#include <luna/shared/log.h>

namespace luna
{
    vertex_array::vertex_array(GLboolean bound)
    {
        glGenVertexArrays(1, &_id);
        if(bound) 
        {
            bind();
        }
    }

    vertex_array::vertex_array(const vertex_array& copy)
    {
        LN_WARNING << "if any copy of this object runs out of scope, all objects are unusable, due to destructor, instead use move constructor";
        _id = copy._id;
        _attrib_index = copy._attrib_index;
    }

    vertex_array::vertex_array(vertex_array&& move)
    {
        _id = move._id;
        _attrib_index = move._attrib_index;
        move._id = 0;
    }

    void vertex_array::bind()
    {
        glBindVertexArray(_id);
    }

    void vertex_array::unbind()
    {
        glBindVertexArray(_id);
    }

    vertex_array::~vertex_array()
    {
        glDeleteVertexArrays(1, &_id);
    }

    void vertex_array::add_data(GLint component_count, GLenum type, GLboolean normalized, GLsizei stride, int offset)
    {
        bind();
        switch(type)
        {
            case GL_BYTE:
            case GL_UNSIGNED_BYTE:
            case GL_SHORT:
            case GL_UNSIGNED_SHORT:
            case GL_INT:
            case GL_UNSIGNED_INT:
            case GL_INT_2_10_10_10_REV:
            case GL_UNSIGNED_INT_2_10_10_10_REV:
            glVertexAttribIPointer(_attrib_index, component_count, type, stride, (void*)offset);
            break;
            default:
            //glVertexAttribPointer(_attrib_index, component_count, type, GL_FALSE, stride, (void*)offset);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
        }
        glEnableVertexAttribArray(0);
        _attrib_index++;
    } 
}