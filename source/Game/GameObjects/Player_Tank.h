#pragma once



#include <memory>
#include <glm/vec2.hpp>


#include "Game_Object.h"
#include "../../Renderer/Sprite_Animator.h"


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Player Tank class
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
	class Sprite;											/* f.d */
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Player_Tank : public Game_Object
{
public:
	Player_Tank(const float velocity,const glm::vec2 position,const glm::vec2 size);

	/*-------------------------------------------------------*/
	/* Orientation Movement Enum */
	enum class EOrientation : uint8_t
	{
		Top,
		Bottom,
		Left,
		Right
	};
	/*-------------------------------------------------------*/


	/*	OVERRIDE  */
	/*-------------------------------------------------------*/
	/* Render Player Tank */
	void Render() const override;

	/* Update Animation Player Sprite */
	void Update(const uint64_t delta_seconds) override;
	/*-------------------------------------------------------*/



	/*-------------------------------------------------------*/
	/* Orientation and move player */
	/* Setter Orientation Player on game view*/
	void Set_Orientation(const EOrientation orientation); 	

	/* Move Player Method*/
	void Move_Player(const bool move);							
	/*-------------------------------------------------------*/

private:
	bool Move;													/* Moving Boolean */
	float Velocity;												/* Speed velocity float */
	glm::vec2 Move_Offset;										/* Vector Movement offset */
	EOrientation Orientation;									/* Orientation Enum */
	
	/* Sprte pointer*/
	std::shared_ptr<RenderEngine::Sprite> Tank_Sprite_Top;		
	std::shared_ptr<RenderEngine::Sprite> Tank_Sprite_Bottom;
	std::shared_ptr<RenderEngine::Sprite> Tank_Sprite_Left;
	std::shared_ptr<RenderEngine::Sprite> Tank_Sprite_Right;

	/* Sprte Animation */
	RenderEngine::Sprite_Animator Sprite_Anim_Top; 
	RenderEngine::Sprite_Animator Sprite_Anim_Bottom;
	RenderEngine::Sprite_Animator Sprite_Anim_Left;
	RenderEngine::Sprite_Animator Sprite_Anim_Right;
	//================================================================================================================================================================


};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
