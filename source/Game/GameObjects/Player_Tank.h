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
	//================================================================================================================================================================
	Player_Tank(const float velocity,const glm::vec2 position,const glm::vec2 size);
	//================================================================================================================================================================

	enum class EOrientation : unsigned char					/* Orientation Movement Enum */
	{
		Top,
		Bottom,
		Left,
		Right
	};

	//============================================================================================================================================================
	/* override */
	void Render() const override;								/* Render Player Tank */
	void Update(const uint64_t delta_seconds) override;			/* Update Animation Player Sprite */

	/* orientation and move player */
	void Set_Orientation(const EOrientation orientation); 		/* Setter Orientation Player on game view*/
	void Move_Player(const bool move);							/* Move Player Method*/
	//============================================================================================================================================================

private:
	//================================================================================================================================================================
	bool Move;													/* */
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
