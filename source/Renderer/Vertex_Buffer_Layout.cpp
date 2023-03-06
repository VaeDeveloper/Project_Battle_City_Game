#include "Vertex_Buffer_Layout.h"

using namespace RenderEngine;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vertex_Buffer_Layout::Vertex_Buffer_Layout()
: Stride(0),Layout_Elements(0)
{
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Vertex_Buffer_Layout::ReserveElement(const size_t count)
{
	Layout_Elements.reserve(count);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Vertex_Buffer_Layout::Add_Element_Layout_Float(const unsigned count, const bool normalized)
{
	Layout_Elements.push_back( { count, GL_FLOAT, normalized, count * (unsigned)sizeof(GLfloat)});
	Stride += Layout_Elements.back().size;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
