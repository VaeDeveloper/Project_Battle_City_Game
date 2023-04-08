#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "../../Renderer/Sprite_Animator.h"
#include "../../System/Timer.h"

#include "Game_Object.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Player Tank class
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
class Sprite; /* f.d */
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Player_Tank : public Game_Object
{
  public:
    Player_Tank(const double max_velocity, const glm::vec2 position, const glm::vec2 size, const float layer);

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
    void Update(const double delta_seconds) override;
    /*-------------------------------------------------------*/

    /*-------------------------------------------------------*/
    /* Orientation and move player */
    /* Setter Orientation Player on game view*/
    void Set_Orientation(const EOrientation orientation);


    /* Getter Velocity */
    double Get_Max_Velocity() const { return Max_Velocity; }
    /*-------------------------------------------------------*/

  private:
    bool bIsSpawning;                 /* Spawning ? */
    bool bHasShield;                  /* has Shield ? */
    double Max_Velocity;              /* Speed velocity float */
    EOrientation Orientation;         /* Orientation Enum */

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

    ///* Tank Sprite Spawn and Animatior Spawn Sprite*/
    std::shared_ptr<RenderEngine::Sprite> Tank_Sprite_Spawn;
    RenderEngine::Sprite_Animator Sprite_Animatior_Spawn;
    
    /* Tank Sprite Shiled And Animator Shiled Sprite */
    std::shared_ptr<RenderEngine::Sprite> Tank_Sprite_Shield;
    RenderEngine::Sprite_Animator Sprite_Animatior_Shield;

    /* Timers */
    Timer Respawn_Timer;
    Timer Shield_Timer;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
