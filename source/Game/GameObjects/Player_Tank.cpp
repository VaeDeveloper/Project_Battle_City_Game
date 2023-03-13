#include "../GameObjects/Player_Tank.h"

#include "../../Renderer/Sprite.h"
#include "../../Resources/Resource_Manager.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Player_Tank::Player_Tank( const float velocity, const glm::vec2 position, const glm::vec2 size)
: Game_Object(position,size, 0.f),Orientation(EOrientation::Top), Move(false),Velocity(velocity), Move_Offset(glm::vec2(0.0f, 1.0f)),
  Tank_Sprite_Top(Resource_Manager::Get_Sprite("Tank_Top_State")), Tank_Sprite_Bottom(Resource_Manager::Get_Sprite("Tank_Bottom_State")),
  Tank_Sprite_Left(Resource_Manager::Get_Sprite("Tank_Left_State")), Tank_Sprite_Right(Resource_Manager::Get_Sprite("Tank_Right_State")),
  Sprite_Anim_Top(Tank_Sprite_Top),Sprite_Anim_Bottom(Tank_Sprite_Bottom),Sprite_Anim_Left(Tank_Sprite_Left),Sprite_Anim_Right(Tank_Sprite_Right)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Render() const
{
	switch (Orientation)
	{
	case Player_Tank::EOrientation::Top:
		Tank_Sprite_Top->Render(Position, Size, Rotation, Sprite_Anim_Top.Get_Current_Frame());
		break;

	case Player_Tank::EOrientation::Bottom:
		Tank_Sprite_Bottom->Render(Position, Size, Rotation, Sprite_Anim_Bottom.Get_Current_Frame());
		break;

	case Player_Tank::EOrientation::Left:
		Tank_Sprite_Left->Render(Position, Size, Rotation, Sprite_Anim_Left.Get_Current_Frame());
		break;

	case Player_Tank::EOrientation::Right:
		Tank_Sprite_Right->Render(Position, Size, Rotation, Sprite_Anim_Right.Get_Current_Frame());
		break;

	default:
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Set_Orientation(const EOrientation orientation)
{
	if (Orientation == orientation)
		return;

	Orientation = orientation;

	switch (Orientation)
	{
	case EOrientation::Top:
		Move_Offset.x = 0.0f;
		Move_Offset.y = 1.0f;
		break;

	case EOrientation::Bottom:
		Move_Offset.x = 0.0f;
		Move_Offset.y = -1.0f; 
		break;

	case EOrientation::Left:
		Move_Offset.x = -1.0f;
		Move_Offset.y = 0.0f; 
		break;

	case EOrientation::Right:
		Move_Offset.x = 1.0f;
		Move_Offset.y = 0.0f; 
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Move_Player(const bool move)
{
	Move = move;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Update(const uint64_t delta_seconds)
{
	if (Move)
	{
		Position += delta_seconds * Velocity * Move_Offset;
		
		switch (Orientation)
		{
		case Player_Tank::EOrientation::Top:
			Sprite_Anim_Top.Update(delta_seconds);
			break;

		case Player_Tank::EOrientation::Bottom:
			Sprite_Anim_Bottom.Update(delta_seconds);
			break;

		case Player_Tank::EOrientation::Left:
			Sprite_Anim_Left.Update(delta_seconds);
			break;

		case Player_Tank::EOrientation::Right:
			Sprite_Anim_Right.Update(delta_seconds);
			break;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
