#include "Ice.h"

#include "../../Renderer/Sprite.h"
#include "../../Resources/Resource_Manager.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Ice::Ice(const glm::vec2& position, const glm::vec2& size, const float rotation)
: Game_Object(position, size, rotation),Sprites(Resource_Manager::Get_Sprite("ice")),
  Block_Offsets{ glm::vec2(0, Size.y / 2.f),glm::vec2(Size.x / 2.f, Size.y / 2.f),glm::vec2(0, 0),glm::vec2(Size.x / 2.f, 0) }
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Ice::Render() const
{
	Render_Block(EBlock_Location::Top_Left);
	Render_Block(EBlock_Location::Top_Right);
	Render_Block(EBlock_Location::Bottom_Left);
	Render_Block(EBlock_Location::Bottom_Right);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Ice::Render_Block(const EBlock_Location block_location) const
{
	Sprites->Render(Position + Block_Offsets[static_cast<size_t>(block_location)], Size / 2.f, Rotation);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
