#include "Game_Object.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Game Object
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Game_Object::~Game_Object()
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Game_Object::Game_Object(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
: Position(position), Size(size), Rotation(rotation), Layer(layer), Direction(0.0, 1.0f), Velocity(0.0)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game_Object::Set_Velocity(const double velocity) 
{
    Velocity = velocity;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
