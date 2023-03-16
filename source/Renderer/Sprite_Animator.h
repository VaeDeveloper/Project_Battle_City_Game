#pragma once 


#include <memory>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Spite Animator 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
	class Sprite;

	class Sprite_Animator
	{
	public:
		Sprite_Animator(std::shared_ptr<Sprite> sprite);

		/* Update Delta Time */
		void Update(const double delta);

		/* Getter Current Frame */
		size_t Get_Current_Frame() const { return Current_Frame; }


	private:
		std::shared_ptr<Sprite> ASprite;
		size_t Current_Frame;
		double Current_Frame_Duration;
		double Current_Animation_Time;
	};

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
