#include "Brick_Wall.h"

#include "../../Renderer/Sprite.h"
#include "../../Resources/Resource_Manager.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Brick_Wall::Brick_Wall(const EBrick_Wall_Type brick_wall_type, const glm::vec2& position, const glm::vec2& size, const float rotation)
: Game_Object(position, size, rotation), Curr_Brick_State{ EBrick_State::Destroyed,EBrick_State::Destroyed,EBrick_State::Destroyed,EBrick_State::Destroyed }
{
	Sprites[static_cast<size_t>(EBrick_State::All)] = Resource_Manager::Get_Sprite("brickWall_All");
	Sprites[static_cast<size_t>(EBrick_State::Top_Left)] = Resource_Manager::Get_Sprite("brickWall_TopLeft");
	Sprites[static_cast<size_t>(EBrick_State::Top_Right)] = Resource_Manager::Get_Sprite("brickWall_TopRight");
	Sprites[static_cast<size_t>(EBrick_State::Top)] = Resource_Manager::Get_Sprite("brickWall_Top");
	Sprites[static_cast<size_t>(EBrick_State::Bottom_Left)] = Resource_Manager::Get_Sprite("brickWall_BottomLeft");
	Sprites[static_cast<size_t>(EBrick_State::Left)] = Resource_Manager::Get_Sprite("brickWall_Left");
	Sprites[static_cast<size_t>(EBrick_State::Top_Right_Bottom_Left)] = Resource_Manager::Get_Sprite("brickWall_TopRight_BottomLeft");
	Sprites[static_cast<size_t>(EBrick_State::Top_Bottom_Left)] = Resource_Manager::Get_Sprite("brickWall_Top_BottomLeft");
	Sprites[static_cast<size_t>(EBrick_State::Bottom_Right)] = Resource_Manager::Get_Sprite("brickWall_BottomRight");
	Sprites[static_cast<size_t>(EBrick_State::Top_Left_Bottom_Right)] = Resource_Manager::Get_Sprite("brickWall_TopLeft_BottomRight");
	Sprites[static_cast<size_t>(EBrick_State::Right)] = Resource_Manager::Get_Sprite("brickWall_Right");
	Sprites[static_cast<size_t>(EBrick_State::Top_Bottom_Right)] = Resource_Manager::Get_Sprite("brickWall_Top_BottomRight");
	Sprites[static_cast<size_t>(EBrick_State::Bottom)] = Resource_Manager::Get_Sprite("brickWall_Bottom");
	Sprites[static_cast<size_t>(EBrick_State::Top_Left_Bottom)] = Resource_Manager::Get_Sprite("brickWall_TopLeft_Bottom");
	Sprites[static_cast<size_t>(EBrick_State::Top_Right_Bottom)] = Resource_Manager::Get_Sprite("brickWall_TopRight_Bottom");
	Sprites[static_cast<size_t>(EBrick_State::Destroyed)] = Resource_Manager::Get_Sprite("brickWall_All");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Brick_Wall::Render() const
{
	Curr_Sprite->Render(Position, Size, Rotation);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Brick_Wall::Update(const uint64_t delta)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
