#pragma once


#include <vector>
#include <string>
#include <memory>

#include "glm\vec2.hpp"


class Game_Object;

//-------------------------------------------------------------------------------------------------------------------------------------
// Level
//-------------------------------------------------------------------------------------------------------------------------------------
class Level
{
public:
	Level(std::vector<std::string> level_discr);


	/*-------------------------------------------------------------*/
	void Render() const;
	void Update(const uint64_t delta);
	size_t Get_Level_Width() const;
	size_t Get_Level_Height() const;

	/* Getter Player Respawn */
	const glm::vec2& Get_Player_Respawn_1() const { return Player_Respawn_1; }
	const glm::vec2& Get_Player_Respawn_2() const { return Player_Respawn_2; }

	/* Getter Enemy Respawn */
	const glm::vec2& Get_Enemy_Respawn_1() const { return Enemy_Respawn_1; }
	const glm::vec2& Get_Enemy_Respawn_2() const { return Enemy_Respawn_2; }
	const glm::vec2& Get_Enemy_Respawn_3() const { return Enemy_Respawn_3; }
	/*-------------------------------------------------------------*/

	unsigned BLOCK_SIZE = 16;


private:
	size_t Width;
	size_t Height;

	std::vector<std::shared_ptr<Game_Object>> Map_Objects;

	/* Respawn Point */
	/* Player Respawn Point */
	glm::ivec2 Player_Respawn_1;
	glm::ivec2 Player_Respawn_2;

	/* Enemy Respawn Point */
	glm::ivec2 Enemy_Respawn_1;
	glm::ivec2 Enemy_Respawn_2;
	glm::ivec2 Enemy_Respawn_3;
};
//-------------------------------------------------------------------------------------------------------------------------------------
