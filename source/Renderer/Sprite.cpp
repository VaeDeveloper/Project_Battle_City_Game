#include "Sprite.h"
#include "Shader_Program.h"
#include "Texture2D.h"
#include "Renderer.h"

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
Sprite::Sprite(std::shared_ptr<Texture2D> texture, std::string initial_subtexture, std::shared_ptr<Shader_Program> shader_program)
: Texture(std::move(texture)), Shader(std::move(shader_program)), Last_Frame_ID(0)
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
void Sprite::Render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer , const size_t frame_id) const
{
	if (Last_Frame_ID != frame_id)
	{
		Last_Frame_ID = frame_id;

		const Frame_Discription& curr_frame_discr = Frame_Discriptions[frame_id];

		const GLfloat tex_coords[] = {
			/*-U--V-*/
			curr_frame_discr.Left_Bottom_UV.x, curr_frame_discr.Left_Bottom_UV.y,
			curr_frame_discr.Left_Bottom_UV.x, curr_frame_discr.Right_Top_UV.y,
			curr_frame_discr.Right_Top_UV.x, curr_frame_discr.Right_Top_UV.y,
			curr_frame_discr.Right_Top_UV.x, curr_frame_discr.Left_Bottom_UV.y,
		};

		Texture_Coord_Buffer.Update(tex_coords, static_cast<unsigned long long>(2) * 4 * sizeof(GLfloat));

	}

	Shader->Use_Shader();

	glm::mat4 model(1.0f);

	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	Shader->Set_Matrix4("model_mat", model);
	Shader->Set_Float("layer", layer);

	glActiveTexture(GL_TEXTURE0);
	Texture->Bind_Texture();

	Renderer::Draw(Vertex_Array_Obj, Index_Pixel_Buffer, *Shader);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint64_t Sprite::Get_Frame_Duration(const size_t frame_id) const
{
	return Frame_Discriptions[frame_id].Duration;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
size_t Sprite::Get_Frames_Count() const
{
	return Frame_Discriptions.size();
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void RenderEngine::Sprite::Insert_Frame(std::vector<Frame_Discription> frames_discriptions)
{
	Frame_Discriptions = std::move(frames_discriptions);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
