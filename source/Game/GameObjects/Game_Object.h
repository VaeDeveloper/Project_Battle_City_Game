#pragma once

#include <glm/vec2.hpp>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Game_Object
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Game_Object
{
  public:
    virtual ~Game_Object();
    Game_Object(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

    virtual void Render() const = 0;
    virtual void Update(const double delta){};


    virtual double Get_Current_Velocity() { return Velocity; }
    virtual glm::vec2& Get_Current_Position() { return Position; }
    virtual glm::vec2& Get_Current_Direction() { return Direction; }
    virtual void Set_Velocity(const double velocity);

  protected:
    float Layer;
    float Rotation;

    /* Speed */
    double Velocity;

    glm::vec2 Size;
    glm::vec2 Position;
    glm::vec2 Direction;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
