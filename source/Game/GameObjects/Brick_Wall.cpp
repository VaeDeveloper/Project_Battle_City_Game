#include "Brick_Wall.h"

#include "../../Renderer/Sprite.h"
#include "../../Resources/Resource_Manager.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Brick_Wall::Brick_Wall(const EBrick_Wall_Type brick_wall_type, const glm::vec2& position, const glm::vec2& size, const float rotation)
: Game_Object(position, size, rotation), Curr_Brick_State{ EBrick_State::Destroyed,EBrick_State::Destroyed,EBrick_State::Destroyed,EBrick_State::Destroyed }
{
	Sprites[static_cast<size_t>(EBrick_State::All)]					       = Resource_Manager::Get_Sprite("brickWall_All");
	Sprites[static_cast<size_t>(EBrick_State::Top_Left)]			       = Resource_Manager::Get_Sprite("brickWall_TopLeft");
	Sprites[static_cast<size_t>(EBrick_State::Top_Right)]			       = Resource_Manager::Get_Sprite("brickWall_TopRight");
	Sprites[static_cast<size_t>(EBrick_State::Top)]					       = Resource_Manager::Get_Sprite("brickWall_Top");
	Sprites[static_cast<size_t>(EBrick_State::Bottom_Left)]			       = Resource_Manager::Get_Sprite("brickWall_BottomLeft");
	Sprites[static_cast<size_t>(EBrick_State::Left)]				       = Resource_Manager::Get_Sprite("brickWall_Left");
	Sprites[static_cast<size_t>(EBrick_State::Top_Right_Bottom_Left)]      = Resource_Manager::Get_Sprite("brickWall_TopRight_BottomLeft");
	Sprites[static_cast<size_t>(EBrick_State::Top_Bottom_Left)]		       = Resource_Manager::Get_Sprite("brickWall_Top_BottomLeft");
	Sprites[static_cast<size_t>(EBrick_State::Bottom_Right)]		       = Resource_Manager::Get_Sprite("brickWall_BottomRight");
	Sprites[static_cast<size_t>(EBrick_State::Top_Left_Bottom_Right)]      = Resource_Manager::Get_Sprite("brickWall_TopLeft_BottomRight");
	Sprites[static_cast<size_t>(EBrick_State::Right)]				       = Resource_Manager::Get_Sprite("brickWall_Right");
	Sprites[static_cast<size_t>(EBrick_State::Top_Bottom_Right)]	       = Resource_Manager::Get_Sprite("brickWall_Top_BottomRight");
	Sprites[static_cast<size_t>(EBrick_State::Bottom)]				       = Resource_Manager::Get_Sprite("brickWall_Bottom");
	Sprites[static_cast<size_t>(EBrick_State::Top_Left_Bottom)]		       = Resource_Manager::Get_Sprite("brickWall_TopLeft_Bottom");
	Sprites[static_cast<size_t>(EBrick_State::Top_Right_Bottom)]	       = Resource_Manager::Get_Sprite("brickWall_TopRight_Bottom");

	switch (brick_wall_type)
	{
	case EBrick_Wall_Type::All:
		Curr_Brick_State.fill(EBrick_State::All);
		break;
	case EBrick_Wall_Type::Top:
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Top_Left)] = EBrick_State::All;
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Top_Right)] = EBrick_State::All;
		break;
	case EBrick_Wall_Type::Bottom:
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Bottom_Left)] = EBrick_State::All;
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Bottom_Right)] = EBrick_State::All;
		break;
	case EBrick_Wall_Type::Left:
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Top_Left)] = EBrick_State::All;
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Bottom_Left)] = EBrick_State::All;
		break;
	case EBrick_Wall_Type::Right:
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Top_Right)] = EBrick_State::All;
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Bottom_Right)] = EBrick_State::All;
		break;
	case EBrick_Wall_Type::Top_Left:
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Top_Left)] = EBrick_State::All;
		break;
	case EBrick_Wall_Type::Top_Right:
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Top_Right)] = EBrick_State::All;
		break;
	case EBrick_Wall_Type::Bottom_Left:
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Bottom_Left)] = EBrick_State::All;
		break;
	case EBrick_Wall_Type::Bottom_Right:
		Curr_Brick_State[static_cast<size_t>(EBrick_Location::Bottom_Right)] = EBrick_State::All;
		break;
	}



}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Brick_Wall::Render() const
{
	Render_Brick(EBrick_Location::Top_Left);
	Render_Brick(EBrick_Location::Top_Right);
	Render_Brick(EBrick_Location::Bottom_Left);
	Render_Brick(EBrick_Location::Bottom_Right);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Brick_Wall::Update(const uint64_t delta)
{
}
void Brick_Wall::Render_Brick(const EBrick_Location brick_location) const
{
	static const std::array<glm::vec2, 4> offsets =
	{
		glm::vec2(0, Size.y / 2.f),
		glm::vec2(Size.x / 2.f, Size.y / 2.f),
		glm::vec2(0, 0),
		glm::vec2(Size.x / 2.f, 0)
	};

	const EBrick_State state = Curr_Brick_State[static_cast<size_t>(brick_location)];

	if (state != EBrick_State::Destroyed)
	{
		Sprites[static_cast<size_t>(state)]->Render(Position + offsets[static_cast<size_t>(brick_location)], Size / 2.f, Rotation);
	}

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
