#include "Index_Buffer.h"

using namespace RenderEngine;


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Index_Buffer::~Index_Buffer()
{
	glDeleteBuffers(1, &ID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Index_Buffer::Index_Buffer()
: ID(0), Count(0)
{
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Index_Buffer& Index_Buffer::operator=(Index_Buffer&& index_buffer) noexcept
{
	ID = index_buffer.ID;
	index_buffer.ID = 0;
	Count = index_buffer.Count;
	index_buffer.Count = 0;
	return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Index_Buffer::Index_Buffer(Index_Buffer&& index_buffer) noexcept
{
	ID = index_buffer.ID;
	index_buffer.ID = 0;
	Count = index_buffer.Count;
	index_buffer.Count = 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Index_Buffer::Init(const void* data, const unsigned count)
{
	Count = count;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Index_Buffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Index_Buffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
