#include "Renderer.h"

using namespace RenderEngine;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Renderer::Draw(const Vertex_Array& vertex_array, const Index_Buffer& index_buffer, const Shader_Program& shader)
{
	shader.Use_Shader();
	vertex_array.Bind();
	index_buffer.Bind();

	//glDrawElements(GL_TRIANGLES, )
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
