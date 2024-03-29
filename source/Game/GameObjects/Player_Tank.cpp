#include "../GameObjects/Player_Tank.h"

#include "../../Renderer/Sprite.h"
#include "../../Resources/Resource_Manager.h"

#include "Bullet.h"
#include "../../Physics/Physics_Engine.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Player_Tank::Player_Tank(const double max_velocity, const glm::vec2 position, const glm::vec2 size, const float layer)
: Game_Object(position, size, 0.f, layer), Orientation(EOrientation::Top), Current_Bullet(std::make_shared<Bullet>(0.1, Position + Size / 4.0f,Size / 2.0f ,Layer)),
  Max_Velocity(max_velocity), Tank_Sprite_Top(Resource_Manager::Get_Sprite("Tank_Top_State")), Tank_Sprite_Bottom(Resource_Manager::Get_Sprite("Tank_Bottom_State")),
  Tank_Sprite_Left(Resource_Manager::Get_Sprite("Tank_Left_State")), Tank_Sprite_Right(Resource_Manager::Get_Sprite("Tank_Right_State")), Sprite_Anim_Top(Tank_Sprite_Top),
  Sprite_Anim_Bottom(Tank_Sprite_Bottom), Sprite_Anim_Left(Tank_Sprite_Left), Sprite_Anim_Right(Tank_Sprite_Right),
  Tank_Sprite_Spawn(Resource_Manager::Get_Sprite("respawn")), Sprite_Animatior_Spawn(Tank_Sprite_Spawn), Tank_Sprite_Shield(Resource_Manager::Get_Sprite("shield")),
  Sprite_Animatior_Shield(Tank_Sprite_Shield), bIsSpawning(true), bHasShield(false)
{

    /* Start Respawn Timer Callback */
    Respawn_Timer.Set_Callback(
        [&]()
        {
            bIsSpawning = false;
            bHasShield = true;
            Shield_Timer.Start_Timer(2000);
        });

    /* Start Respawn Timer */
    Respawn_Timer.Start_Timer(1500);


    /* Start Shield Timer Callback */
    Shield_Timer.Set_Callback(
        [&]()
        {
            bHasShield = false;
        });

    Colliders.emplace_back(glm::vec2(0), Size); // !!! 
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Render() const
{
    if (bIsSpawning)
    {
        /* Render Spawn Animation */
        Tank_Sprite_Spawn->Render(Position, Size, Rotation, Layer, Sprite_Animatior_Spawn.Get_Current_Frame());
    }
    else
    {
        /* Render Orientation Tank Player */
        switch (Orientation)
        {
        case Player_Tank::EOrientation::Top:
            Tank_Sprite_Top->Render(Position, Size, Rotation, Layer, Sprite_Anim_Top.Get_Current_Frame());
            break;

        case Player_Tank::EOrientation::Bottom:
            Tank_Sprite_Bottom->Render(Position, Size, Rotation, Layer, Sprite_Anim_Bottom.Get_Current_Frame());
            break;

        case Player_Tank::EOrientation::Left:
            Tank_Sprite_Left->Render(Position, Size, Rotation, Layer, Sprite_Anim_Left.Get_Current_Frame());
            break;

        case Player_Tank::EOrientation::Right:
            Tank_Sprite_Right->Render(Position, Size, Rotation, Layer, Sprite_Anim_Right.Get_Current_Frame());
            break;

        default:
            break;
        }

        if (bHasShield)
        {
            /* Render Shield Animation */
            Tank_Sprite_Shield->Render(Position, Size, Rotation, Layer + 0.1f, Sprite_Animatior_Shield.Get_Current_Frame());
        }
    }

    /* fire bullet render */
    if (Current_Bullet->Is_Active())
    {
        Current_Bullet->Render();
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Set_Orientation(const EOrientation orientation)
{
    if (Orientation == orientation)
        return;

    Orientation = orientation;

    /* Update Orientation for Player Tank */
    switch (Orientation)
    {
    case EOrientation::Top:
        Direction.x = 0.0f;
        Direction.y = 1.0f;
        break;

    case EOrientation::Bottom:
        Direction.x = 0.0f;
        Direction.y = -1.0f;
        break;

    case EOrientation::Left:
        Direction.x = -1.0f;
        Direction.y = 0.0f;
        break;

    case EOrientation::Right:
        Direction.x = 1.0f;
        Direction.y = 0.0f;
        break;

    default:
        break;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Fire() 
{
    //if (!Current_Bullet->Is_Active())
    {
        Current_Bullet->Fire(Position + Size / 4.0f, Direction);
        Physics::PhysicsEngine::Add_Dynamic_Game_Object(Current_Bullet);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Player_Tank::Update(const double delta_seconds)
{
    if (bIsSpawning)
    {
        /* Update Spawn Animation */
        Sprite_Animatior_Spawn.Update(delta_seconds);
        Respawn_Timer.Update(delta_seconds);
    }
    else
    {
        if (bHasShield)
        {
            /* Update Shield Animation */
            Sprite_Animatior_Shield.Update(delta_seconds);
            Shield_Timer.Update(delta_seconds);
        }

        if (Velocity > 0.0)
        {
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
}
void Player_Tank::Set_Velocity(const double velocity)
{
    if (!bIsSpawning)
    {
        Velocity = velocity;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
