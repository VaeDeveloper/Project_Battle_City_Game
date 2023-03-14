#include "Water.h"

#include "../../Renderer/Sprite.h"
#include "../../Resources/Resource_Manager.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Water::Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
: Game_Object(position, size, rotation, layer),Sprites(Resource_Manager::Get_Sprite("water")),W_Sprite_Animator(Sprites),
  Block_Offsets{ glm::vec2(0, Size.y / 2.f),glm::vec2(Size.x / 2.f, Size.y / 2.f),glm::vec2(0, 0),glm::vec2(Size.x / 2.f, 0) }
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Water::Render() const
{
	Render_Block(EBlock_Location::Top_Left);
	Render_Block(EBlock_Location::Top_Right);
	Render_Block(EBlock_Location::Bottom_Left);
	Render_Block(EBlock_Location::Bottom_Right);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Water::Update(const uint64_t delta)
{
	W_Sprite_Animator.Update(delta);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Water::Render_Block(const EBlock_Location block_location) const
{
	Sprites->Render(Position + Block_Offsets[static_cast<size_t>(block_location)], Size / 2.f, Rotation,W_Sprite_Animator.Get_Current_Frame());
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
