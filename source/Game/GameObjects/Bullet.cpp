#include "Bullet.h"

#include "../../Resources/Resource_Manager.h"
#include "../../Renderer/Sprite.h"


/* For Debug */
#include <iostream>


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Bullet::Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer) 
: Game_Object(position, size, 0.0f, layer), 
Sprite_Top(Resource_Manager::Get_Sprite("bullet_Top")), Sprite_Bottom(Resource_Manager::Get_Sprite("bullet_Bottom")), 
Sprite_Right(Resource_Manager::Get_Sprite("bullet_Right")), Sprite_Left(Resource_Manager::Get_Sprite("bullet_Left")), 
bIs_Active(false) ,Orientation(EOrientation::Top)
{
    Set_Velocity(velocity);

    /* Init Collider for Bullet Sprite */
    Colliders.emplace_back(glm::vec2(0), Size);

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Bullet::Render() const
{
    switch (Orientation)
    {
    case Bullet::EOrientation::Top:
        Sprite_Top->Render(Position, Size, Rotation, Layer);
        break;

    case Bullet::EOrientation::Bottom:
        Sprite_Bottom->Render(Position, Size, Rotation, Layer);
        break;

    case Bullet::EOrientation::Right:
        Sprite_Right->Render(Position, Size, Rotation, Layer);
        break;

    case Bullet::EOrientation::Left:
        Sprite_Left->Render(Position, Size, Rotation, Layer);
        break;

    default:
        throw 666;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Bullet::Fire(const glm::vec2& position, const glm::vec2& direction)
{
    /* Debug !!! */
    std::cout << "Fire" << std::endl;

    Position = position;
    Direction = direction;

    if (Direction.x == 0.0f)
    {
        Orientation = (Direction.y < 0) ? EOrientation::Bottom : EOrientation::Top;
    }
    else
    {
        Orientation = (Direction.x < 0) ? EOrientation::Left : EOrientation::Right;
    }

    bIs_Active = true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
