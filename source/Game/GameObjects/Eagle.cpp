#include "Eagle.h"

#include "../../Renderer/Sprite.h"
#include "../../Resources/Resource_Manager.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Eagle::Eagle(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
: Game_Object(position, size, rotation,layer), Sprites{ Resource_Manager::Get_Sprite("eagle"), Resource_Manager::Get_Sprite("eagle_dead") },
  Block_Offsets{ glm::vec2(0, Size.y / 2.f),glm::vec2(Size.x / 2.f, Size.y / 2.f),glm::vec2(0, 0),glm::vec2(Size.x / 2.f, 0) },
  Eagle_State(EEagle_State::Alive)
{
    Colliders.emplace_back(glm::vec2(0), Size);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Eagle::Render() const
{
	Sprites[static_cast<size_t>(Eagle_State)]->Render(Position, Size, Rotation, Layer);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Eagle::Update(const double delta)
{
	//TODO !!!
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
