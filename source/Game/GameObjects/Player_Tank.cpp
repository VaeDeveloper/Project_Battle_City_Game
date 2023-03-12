#include "../GameObjects/Player_Tank.h"
#include "../../Renderer/Animated_Sprite.h"


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Player_Tank::Player_Tank(std::shared_ptr<RenderEngine::Animated_Sprite> sprite, const float velocity, const glm::vec2 position, const glm::vec2 size)
:Game_Object(position,size, 0.f),Orientation(EOrientation::Top), Move(false),Velocity(velocity), Move_Offset(glm::vec2(0.0f, 1.0f)),Tank_Sprite(std::move(sprite))
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Render() const
{
	Tank_Sprite->Render(Position, Size, Rotation);
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
		Tank_Sprite->Set_State("Tank_Top_State");
		Move_Offset.x = 0.0f;
		Move_Offset.y = 1.0f;
		break;
	case EOrientation::Bottom:
		Tank_Sprite->Set_State("Tank_Bottom_State");
		Move_Offset.x = 0.0f;
		Move_Offset.y = -1.0f; 
		break;

	case EOrientation::Left:
		Tank_Sprite->Set_State("Tank_Left_State");
		Move_Offset.x = -1.0f;
		Move_Offset.y = 0.0f; 
		break;

	case EOrientation::Right:
		Tank_Sprite->Set_State("Tank_Right_State");
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
		Tank_Sprite->Update(delta_seconds);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
