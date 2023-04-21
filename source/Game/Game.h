#pragma once

#include <array>
#include <glm/vec2.hpp>

#include <memory>

class Player_Tank;
class Level;

//-------------------------------------------------------------------------------------------------------------------------------------
//  Game class
//-------------------------------------------------------------------------------------------------------------------------------------
enum class EGame_State : uint8_t
{
    Active, // Active Game
    Pause   // Pause Game
};
//-------------------------------------------------------------------------------------------------------------------------------------
class Game
{
#pragma region Init_
  public:
    ~Game();
    Game(const glm::ivec2 window_size); /* constr	   */

    /* Initilize */
    bool Init(); 
#pragma endregion Init_

#pragma region Games_
    /*-------------------------------------------------------------*/
    void Render();                                 /* Game Render           */
    void Update(const double delta_time);          /* Update Game           */
    void Set_Key(const int key, const int action); /* Keybinding            */
    size_t Get_Curr_Level_Width() const;           /* Current Level Width   */
    size_t Get_Curr_Level_Height() const;          /* Current Level Height  */
                                                   /*-------------------------------------------------------------*/

  private:
    /*----------------------------------------------------------------------------------*/
    std::array<bool, 349> Keys;                     /* Array Key bind                   */
    glm::ivec2 Window_Size;                         /* Window Size                      */
    EGame_State Current_Game_States;                /* Game State enum class (uns char) */
    std::shared_ptr<Player_Tank> Player_Tank_Actor; /* Player Actor                     */
    std::shared_ptr<Level> ALevel;                  /* Level pointer                    */
#pragma endregion Games_
};
//-------------------------------------------------------------------------------------------------------------------------------------
