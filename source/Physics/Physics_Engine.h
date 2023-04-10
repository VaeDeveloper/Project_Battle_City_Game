#pragma once

#include <memory>
#include <unordered_set>

#include "glm/vec2.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  PhysicsEngine
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Game_Object;
class Level;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Physics
{
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct AABB
{
    glm::vec2 Bottom_Left;
    glm::vec2 Top_Right;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class PhysicsEngine
{
  public:
    ~PhysicsEngine() = delete;
    PhysicsEngine() = delete;
    PhysicsEngine(const PhysicsEngine&) = delete;
    PhysicsEngine& operator=(const PhysicsEngine&) = delete;
    PhysicsEngine& operator=(PhysicsEngine&&) = delete;
    PhysicsEngine(PhysicsEngine&&) = delete;

    /* Initialization */
    static void Init();

    /* Destroy Physics */
    static void Destroy();

    /* Update */
    static void Update(const double delta_time);

    /* Add Game Object */
    static void Add_Dynamic_Game_Object(std::shared_ptr<Game_Object> game_object);

    /* Setter Current Level  */
    static void Set_Current_Level(std::shared_ptr<Level> level);

  private:
    /* All Dynamic Objects who used Physics */
    static std::unordered_set<std::shared_ptr<Game_Object>> Dynamic_Objects;

    /* Pointer Curr Level */
    static std::shared_ptr<Level> Current_Level;
};

} // namespace PhysicsEngine
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
