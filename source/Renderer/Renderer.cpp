#include "Renderer.h"

using namespace RenderEngine;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Renderer::Draw(const Vertex_Array& vertex_array, const Index_Buffer& index_buffer, const Shader_Program& shader)
{
	shader.Use_Shader();
	vertex_array.Bind();
	index_buffer.Bind();

	glDrawElements(GL_TRIANGLES, index_buffer.Get_Count(), GL_UNSIGNED_INT, nullptr);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Renderer::Set_Clear_Color(float r, float g, float b, float alpha)
{
	glClearColor(r, g, b, alpha);
}
void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void RenderEngine::Renderer::Set_Viewport(unsigned width, unsigned height, unsigned left_offset, unsigned bottom_offset)
{
	glViewport(left_offset, bottom_offset, width, height);
}
std::string Renderer::Get_Renderer_Str()
{
	return (char*)glGetString(GL_RENDERER);
}
std::string RenderEngine::Renderer::Get_Version_Str()
{
	return (char*)glGetString(GL_VERSION);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
