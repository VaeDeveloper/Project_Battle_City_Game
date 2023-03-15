#include "Level.h"

#include <iostream>


#include "GameObjects\Brick_Wall.h"
#include "GameObjects\Beton_Wall.h"
#include "GameObjects\Trees.h"
#include "GameObjects\Ice.h"
#include "GameObjects\Water.h"
#include "GameObjects\Eagle.h"
#include "GameObjects\Border.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Game_Object> Create_Game_Obj_From_Discr(const char descr, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	switch (descr)
	{
	case '0':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Right, position, size, rotation, 0.f);
		
	case '1':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Bottom, position, size, rotation, 0.f);
	
	case '2':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Left, position, size, rotation, 0.f);
	
	case '3':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Top, position, size, rotation, 0.f);
	
	case '4':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::All, position, size, rotation, 0.f);
	
	case 'G':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Bottom_Left, position, size, rotation, 0.f);

	case 'H':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Bottom_Right, position, size, rotation, 0.f);

	case 'I':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Top_Left, position, size, rotation, 0.f);

	case 'J':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Top_Right, position, size, rotation, 0.f);

	case '5':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::Right, position, size, rotation, 0.f);

	case '6':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::Bottom, position, size, rotation, 0.f);

	case '7':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::Left, position, size, rotation, 0.f);

	case '8':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::Top, position, size, rotation, 0.f);

	case '9':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::All, position, size, rotation, 0.f);

	case 'A':
		return std::make_shared<Water>(position, size, rotation, 0.f);

	case 'B':
		return std::make_shared<Trees>(position, size, rotation, 1.f);

	case 'C':
		return std::make_shared<Ice>(position, size, rotation, -1.f);

	case 'E':
		return std::make_shared<Eagle>(position, size, rotation, 1.f);

	case 'D':
		return nullptr;

	default:
		std::cerr << " " <<  __func__ << " " << __LINE__ << " element empty !!!" << std::endl;;

	}

	return nullptr;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Level::Level(std::vector<std::string> level_discr)
:Width(0), Height(0), Map_Objects{}
{
	if (level_discr.empty())
	{
		std::cerr << __func__ << __LINE__ << "Level is empty error !!!" << std::endl;
		return;
	}

	Width = level_discr[0].length();
	Height = level_discr.size();

	/* curr Player 1 and Player 2 position */
	Player_Respawn_1 = { BLOCK_SIZE * (Width / 2 - 1), BLOCK_SIZE / 2 };
	Player_Respawn_2 = { BLOCK_SIZE * (Width / 2 + 3), BLOCK_SIZE / 2 };

	/* curr Enemy 1, 2 ,3 position */
	Enemy_Respawn_1 = { BLOCK_SIZE					  , BLOCK_SIZE * Height - BLOCK_SIZE / 2 };
	Enemy_Respawn_2 = { BLOCK_SIZE * (Width / 2 + 1)  , BLOCK_SIZE * Height - BLOCK_SIZE / 2 };
	Enemy_Respawn_3 = { BLOCK_SIZE * Width            , BLOCK_SIZE * Height - BLOCK_SIZE / 2 };

	Map_Objects.reserve(Width * Height + 4);

	unsigned curr_bottom_offset = static_cast<unsigned>(BLOCK_SIZE * (Height - 1) + BLOCK_SIZE / 2.0f);

	for (const std::string& curr_row : level_discr)
	{
		unsigned curr_left_offset = 0;

		for (const char curr_element : curr_row)
		{
			switch (curr_element)
			{
			case 'K':
				Player_Respawn_1 = { curr_left_offset, curr_bottom_offset };
				break;

			case 'L':
				Player_Respawn_2 = { curr_left_offset, curr_bottom_offset };
				break;

			case 'M':
				Enemy_Respawn_1 = { curr_left_offset, curr_bottom_offset };
				break;

			case 'N':
				Enemy_Respawn_2 = { curr_left_offset, curr_bottom_offset };
				break;

			case 'O':
				Enemy_Respawn_3 = { curr_left_offset, curr_bottom_offset };
				break;

			default:
				Map_Objects.emplace_back(Create_Game_Obj_From_Discr(curr_element, glm::vec2(curr_left_offset, curr_bottom_offset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				break;
			}

			curr_left_offset += BLOCK_SIZE;
		}
		
		curr_bottom_offset -= BLOCK_SIZE;
	}



	int top_height = Height * BLOCK_SIZE + BLOCK_SIZE / 2;

	/* Bottom Border */
	Map_Objects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0.0f), glm::vec2(Width * BLOCK_SIZE, BLOCK_SIZE / 2.0f), 0.0f, 0.0f));

	/* Top Border */
	Map_Objects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, top_height), glm::vec2(Width * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0.0f, 0.f));

	/* Left Border */
	Map_Objects.emplace_back(std::make_shared<Border>(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE, (Height * BLOCK_SIZE) * BLOCK_SIZE), 0.0f, 0.0f));

	/* Right Border */
	Map_Objects.emplace_back(std::make_shared<Border>(glm::vec2((Width + 1) * BLOCK_SIZE, 0.0f), glm::vec2(BLOCK_SIZE * 2.0f, (Height * BLOCK_SIZE) * BLOCK_SIZE), 0.0f, 0.f));

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Level::Render() const
{
	for (const auto& curr_map_object : Map_Objects)
	{
		if (curr_map_object)
		{
			curr_map_object->Render();
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Level::Update(const uint64_t delta)
{
	for (const auto& curr_map_object : Map_Objects)
	{
		if (curr_map_object)
		{
			curr_map_object->Update(delta);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
size_t Level::Get_Level_Width() const
{
	return (Width + 3) * BLOCK_SIZE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
size_t Level::Get_Level_Height() const
{
	return (Height + 1) * BLOCK_SIZE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
