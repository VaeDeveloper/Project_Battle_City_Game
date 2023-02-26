#include "Animated_Sprite.h"
#include "Texture2D.h"

#include <iostream>



using namespace Renderer;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Animated_Sprite::Animated_Sprite(std::shared_ptr<Texture2D> texture, std::string initial_subtexture, std::shared_ptr<Shader_Program> shader_program, const glm::vec2& position, const glm::vec2& size, const float rotation)
	:Dirty(false),Sprite(std::move(texture), std::move(initial_subtexture), std::move(shader_program), position, size, rotation), Current_Frame(0), Current_Animation_Time(0), Current_Animation_Duration{}
{
	Current_Animation_Duration = States_Map.end();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Animated_Sprite::Render() const
{
	if (Dirty)
	{
		auto sub_texture = Texture->Get_SubTexture(Current_Animation_Duration->second[Current_Frame].first);

		const GLfloat tex_coords[] = {
			/*-U--V-*/
			sub_texture.Left_Bottom_UV.x, sub_texture.Left_Bottom_UV.y,
			sub_texture.Left_Bottom_UV.x, sub_texture.Right_Top_UV.y,
			sub_texture.Right_Top_UV.x, sub_texture.Right_Top_UV.y,
			sub_texture.Right_Top_UV.x, sub_texture.Left_Bottom_UV.y,
		};

		Texture_Coord_Buffer.Update(tex_coords, 2 * 4 * sizeof(GLfloat));
		Dirty = false;
	}
	
	Sprite::Render();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Animated_Sprite::Set_State(const std::string& new_state)
{
	auto it = States_Map.find(new_state);

	if (it == States_Map.end())
	{
		std::cout << "Can't find animation state: " << new_state << std::endl;
		return;
	}

	if (it != Current_Animation_Duration)
	{
		Current_Animation_Time = 0;
		Current_Frame = 0;
		Current_Animation_Duration = it;
		Dirty = true;

	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Renderer::Animated_Sprite::Update(const uint64_t delta)
{
	if (Current_Animation_Duration != States_Map.end())
	{
		Current_Animation_Time += delta;

		while (Current_Animation_Time >= Current_Animation_Duration->second[Current_Frame].second)
		{
			Current_Animation_Time -= Current_Animation_Duration->second[Current_Frame].second;
			++Current_Frame;
			Dirty = true;

			if (Current_Frame == Current_Animation_Duration->second.size())
			{
				Current_Frame = 0;
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Animated_Sprite::Insert_State(std::string state, std::vector<std::pair<std::string, uint64_t>> subtextures_duration)
{
	States_Map.emplace(std::move(state), std::move(subtextures_duration));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
