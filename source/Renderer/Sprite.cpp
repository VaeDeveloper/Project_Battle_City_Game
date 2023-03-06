#include "Sprite.h"
#include "Shader_Program.h"
#include "Texture2D.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace RenderEngine;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Sprite
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Sprite::~Sprite()
{
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Sprite::Sprite(std::shared_ptr<Texture2D> texture, std::string initial_subtexture, std::shared_ptr<Shader_Program> shader_program, const glm::vec2& position, const glm::vec2& size, const float rotation)
: Texture(std::move(texture)), Shader(std::move(shader_program)),Position(position), Size(size), Rotation(rotation)
{
	const GLfloat vertex_coords[] = {
		/*-X--Y-*/
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	auto sub_texture = Texture->Get_SubTexture(std::move(initial_subtexture));

	const GLfloat tex_coords[] = {
		/*-U--V-*/
		sub_texture.Left_Bottom_UV.x, sub_texture.Left_Bottom_UV.y,
		sub_texture.Left_Bottom_UV.x, sub_texture.Right_Top_UV.y,
		sub_texture.Right_Top_UV.x, sub_texture.Right_Top_UV.y,
		sub_texture.Right_Top_UV.x, sub_texture.Left_Bottom_UV.y,
	};

	const GLuint indexes[] = 
	{
		0, 1, 2,
		2, 3, 0
	};




	Vertex_Coord_Buffer.Init(vertex_coords, 2 * 4 * sizeof(GLfloat));
	Vertex_Buffer_Layout vertex_coord_layout;
	vertex_coord_layout.Add_Element_Layout_Float(2, false);
	Vertex_Array_Obj.Add_Buffer(Vertex_Coord_Buffer, vertex_coord_layout);

	Texture_Coord_Buffer.Init(tex_coords, 2 * 4 * sizeof(GLfloat));
	Vertex_Buffer_Layout texture_coord_layout;
	texture_coord_layout.Add_Element_Layout_Float(2, false);
	Vertex_Array_Obj.Add_Buffer(Texture_Coord_Buffer, texture_coord_layout);

	Index_Pixel_Buffer.Init(indexes, 6);

	Vertex_Array_Obj.Unbind();
	Index_Pixel_Buffer.Unbind();

}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Sprite::Render() const
{
	Shader->Use_Shader();

	glm::mat4 model(1.0f);

	model = glm::translate(model, glm::vec3(Position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * Size.x, 0.5f * Size.y, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * Size.x, -0.5f * Size.y, 0.0f));
	model = glm::scale(model, glm::vec3(Size, 1.0f));

	Vertex_Array_Obj.Bind();
	Shader->Set_Matrix4("model_mat", model);

	glActiveTexture(GL_TEXTURE0);
	Texture->Bind_Texture();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	Vertex_Array_Obj.Bind();

}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Sprite::Set_Position(const glm::vec2& position)
{
	Position = position;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Sprite::Set_Size(const glm::vec2& size)
{
	Size = size;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Sprite::Set_Rotation(const float rotation)
{
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
