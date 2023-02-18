#include "Animated_Sprite.h"

#include <iostream>

using namespace Renderer;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Animated_Sprite::Animated_Sprite(std::shared_ptr<Texture2D> texture, std::string initial_subtexture, std::shared_ptr<Shader_Program> shader_program, const glm::vec2& position, const glm::vec2& size, const float rotation)
	:Sprite(std::move(texture), std::move(initial_subtexture), std::move(shader_program), position, size, rotation), Current_Frame(0), Current_Animation_Time(0), Current_Animation_Duration{}
{

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Animated_Sprite::Render() const
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Animated_Sprite::Set_State(const std::string& new_state)
{
	auto it = States_Map.find(new_state);

	if (it != States_Map.end())
	{
		std::cout << "Can't find animation state: " << new_state << std::endl;
		return;
	}

	Current_Animation_Time = 0;
	Current_Frame = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Renderer::Animated_Sprite::Update(const size_t delta)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Animated_Sprite::Insert_State(std::string state, std::vector<std::pair<std::string, uint64_t>> subtextures_duration)
{
	States_Map.emplace(std::move(state), std::move(subtextures_duration));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
