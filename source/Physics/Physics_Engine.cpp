#include "Physics_Engine.h"

#include "../Game/GameObjects/Game_Object.h"
#include "../Game/Level.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Physics
{
std::unordered_set<std::shared_ptr<Game_Object>> PhysicsEngine::Dynamic_Objects;
std::shared_ptr<Level> PhysicsEngine::Current_Level;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhysicsEngine::Init() {}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhysicsEngine::Destroy()
{
    Dynamic_Objects.clear();
    Current_Level.reset();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhysicsEngine::Update(const double delta_time)
{
    for (auto& curr_object : Dynamic_Objects)
    {
        if (curr_object->Get_Current_Velocity() > 0.0)
        {
            if (curr_object->Get_Current_Direction().x != 0.0f)
            {
                curr_object->Get_Current_Position() = glm::vec2(curr_object->Get_Current_Position().x,
                                          static_cast<unsigned>(curr_object->Get_Current_Position().y / 4.0f + 0.5f) * 4.0f);
            }
            else if (curr_object->Get_Current_Direction().y != 0.0f)
            {
                curr_object->Get_Current_Position() = glm::vec2(static_cast<unsigned>(curr_object->Get_Current_Position().x / 4.0f + 0.5f) * 4.0f,
                                                                                      curr_object->Get_Current_Position().y);
            }


            const auto new_position = curr_object->Get_Current_Position()
                                    + curr_object->Get_Current_Direction()
                                    * static_cast<float>(curr_object->Get_Current_Velocity()
                                    * delta_time);

            /* Get Collision info */
            const auto& colliders = curr_object->Get_Colliders();
            std::vector<std::shared_ptr<Game_Object>> object_toCheck = Current_Level->Get_Object_InArea(new_position, new_position + curr_object->Get_Size());

            bool has_collision = false;

            for (const auto& curr_object_toCheck : object_toCheck)
            {
                const auto& colliders_toCheck = curr_object_toCheck->Get_Colliders();

                if (!colliders_toCheck.empty())
                {
                    if (Has_Intersection(colliders, new_position, colliders_toCheck, curr_object_toCheck->Get_Current_Position()))
                    {
                        has_collision = true;
                        break;
                    }
                }
            }

            /* */
            if (!has_collision)
            {
                curr_object->Get_Current_Position() = new_position;
            }
            else
            {
                if (curr_object->Get_Current_Direction().x != 0.0f)
                {
                    curr_object->Get_Current_Position() = glm::vec2(static_cast<unsigned>(curr_object->Get_Current_Position().x / 8.0f + 0.5f) * 8.0f, curr_object->Get_Current_Position().y);
                }
                else if (curr_object->Get_Current_Direction().y != 0.0f)
                {
                    curr_object->Get_Current_Position() = glm::vec2(curr_object->Get_Current_Position().x, static_cast<unsigned>(curr_object->Get_Current_Position().y / 8.0f + 0.5f) * 8.0f);
                }
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhysicsEngine::Add_Dynamic_Game_Object(std::shared_ptr<Game_Object> game_object)
{
    Dynamic_Objects.insert(std::move(game_object));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhysicsEngine::Set_Current_Level(std::shared_ptr<Level> level)
{
    Current_Level.swap(level);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool PhysicsEngine::Has_Intersection(const std::vector<AABB>& col_1, const glm::vec2& pos_1, const std::vector<AABB>& col_2, const glm::vec2& pos_2)
{
    for (const auto& curr_coll_1 : col_1)
    {
        const glm::vec2 curr_colliders1_bot_left_world = curr_coll_1.Bottom_Left + pos_1;
        const glm::vec2 curr_colliders1_top_right_world = curr_coll_1.Top_Right + pos_1;

        for (const auto& curr_coll_2 : col_2)
        {
            const glm::vec2 curr_colliders2_bot_left_world = curr_coll_2.Bottom_Left + pos_2;
            const glm::vec2 curr_colliders2_top_right_world = curr_coll_2.Top_Right + pos_2;

            if (curr_colliders1_bot_left_world.x >= curr_colliders2_top_right_world.x)
            {
                return false;
            }

            if (curr_colliders1_top_right_world.x <= curr_colliders2_bot_left_world.x)
            {
                return false;
            }

            if (curr_colliders1_bot_left_world.y >= curr_colliders2_top_right_world.y)
            {
                return false;
            }

            if (curr_colliders1_top_right_world.y <= curr_colliders2_bot_left_world.y)
            {
                return false;
            }
        }
    }
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
} // namespace Physics