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

	Vertex_Coord_Buffer.Init(vertex_coords, 2 * 4 * sizeof(GLfloat));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	Texture_Coord_Buffer.Init(tex_coords, 2 * 4 * sizeof(GLfloat));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	Index_Pixel_Buffer.Init(indexes, 6 * sizeof(GLuint));



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
