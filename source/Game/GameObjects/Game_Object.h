#pragma once

#include <glm/vec2.hpp>
#include <vector>


#include "../../Physics/Physics_Engine.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Game_Object
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Game_Object
{
#pragma region EObjectType_
  public:
    enum class EObjectType
    {
        EOT_BetonWall,
        EOT_Border,
        EOT_BrickWall,
        EOT_Bullet,
        EOT_Eagle,
        EOT_Ice,
        EOT_Tank,
        EOT_Trees,
        Water,

        EOT_UNKNOWN
    };

  protected:
    EObjectType ObjectType;

  public:
    EObjectType Get_Object_Type() const { return ObjectType; }
    virtual bool Collides(const EObjectType objtype) { return true; }
    virtual void On_Collision(){};

#pragma endregion EObjectType_

#pragma region Game_Object_

  public:
    virtual ~Game_Object();
    Game_Object(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

    virtual void Render() const = 0;
    virtual void Update(const double delta){};

    virtual double Get_Current_Velocity() { return Velocity; }
    virtual glm::vec2& Get_Current_Position() { return Position; }
    virtual glm::vec2& Get_Current_Direction() { return Direction; }
    virtual void Set_Velocity(const double velocity);

    /* Getter vector Colliders */
    const std::vector<Physics::AABB>& Get_Colliders() const { return Colliders; }

    const glm::vec2& Get_Size() const { return Size; }

  protected:
    float Layer;
    float Rotation;

    /* Speed */
    double Velocity;

    glm::vec2 Size;
    glm::vec2 Position;
    glm::vec2 Direction;

    /* Collision Colliders */
    std::vector<Physics::AABB> Colliders;
#pragma endregion Game_Object_
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
