#include "Sprite.h"
#include "Shader_Program.h"
#include "Texture2D.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace Renderer;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Sprite
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Sprite::~Sprite()
{
	glDeleteBuffers(1, &Vertex_Coord_VB0);
	glDeleteBuffers(1, &Texture_Coord_VB0);
	glDeleteVertexArrays(1, &Vertex_Array_Obj);

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

	glGenVertexArrays(1, &Vertex_Array_Obj);
	glBindVertexArray(Vertex_Array_Obj);

	glGenBuffers(1, &Vertex_Coord_VB0);
	glBindBuffer(GL_ARRAY_BUFFER, Vertex_Coord_VB0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_coords), &vertex_coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &Texture_Coord_VB0);
	glBindBuffer(GL_ARRAY_BUFFER, Texture_Coord_VB0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), &tex_coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &Element_Buf_Obj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Element_Buf_Obj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), &indexes, GL_STATIC_DRAW);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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

	glBindVertexArray(Vertex_Array_Obj);
	Shader->Set_Matrix4("model_mat", model);

	glActiveTexture(GL_TEXTURE0);
	Texture->Bind_Texture();

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

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
