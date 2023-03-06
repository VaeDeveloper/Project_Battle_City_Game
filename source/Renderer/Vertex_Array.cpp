#include "Vertex_Array.h"


using namespace RenderEngine;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vertex_Array::~Vertex_Array()
{
    glDeleteVertexArrays(1, &ID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vertex_Array::Vertex_Array()
: ID(0), Elements_Count(0)
{
    glGenVertexArrays(1, &ID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vertex_Array& Vertex_Array::operator=(Vertex_Array&& vertex_array) noexcept
{
    ID = vertex_array.ID;
    vertex_array.ID = 0;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vertex_Array::Vertex_Array(Vertex_Array&& vertex_array) noexcept
:Elements_Count(0)
{
    ID = vertex_array.ID;
    vertex_array.ID = 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Vertex_Array::Add_Buffer(const Vertex_Buffer& vertex_buffer, const Vertex_Buffer_Layout& layout)
{
    Bind();
    vertex_buffer.Bind();
    const auto& layout_elements = layout.Get_Layout_Elements();
    GLbyte* offset = nullptr;
    for (unsigned i = 0; i < layout_elements.size(); ++i)
    {
        const auto& current_layout_element = layout_elements[i];
        GLuint current_attrib_index = Elements_Count + i;

        glEnableVertexAttribArray(current_attrib_index);
        glVertexAttribPointer(current_attrib_index, current_layout_element.count, current_layout_element.type, current_layout_element.normalized, layout.Get_Stride(), offset);
        offset += current_layout_element.size;
    }
    Elements_Count += (unsigned)layout_elements.size();
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Vertex_Array::Bind() const
{
    glBindVertexArray(ID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Vertex_Array::Unbind() const
{
    glBindVertexArray(0);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
