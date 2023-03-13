#include "Sprite_Animator.h"
#include "Sprite.h"

using namespace RenderEngine;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Sprite_Animator::Sprite_Animator(std::shared_ptr<Sprite> sprite)
: ASprite(sprite), Current_Frame(0), Current_Frame_Duration(ASprite->Get_Frame_Duration(0)), Current_Animation_Time(0)
{

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Sprite_Animator::Update(const uint64_t delta)
{
	Current_Animation_Time += delta;

	while (Current_Animation_Time >= Current_Frame_Duration)
	{
		Current_Animation_Time -= Current_Frame_Duration;

		++Current_Frame;

		if (Current_Frame == ASprite->Get_Frames_Count())
		{
			Current_Frame = 0;
		}

		Current_Frame_Duration = ASprite->Get_Frame_Duration(Current_Frame);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
