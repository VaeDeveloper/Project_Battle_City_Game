#pragma once

#include <memory>
#include <unordered_set>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  PhysicsEngine
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Game_Object;
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

  private:
    /* All Dynamic Objects who used Physics */
    static std::unordered_set<std::shared_ptr<Game_Object>> Dynamic_Objects;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
