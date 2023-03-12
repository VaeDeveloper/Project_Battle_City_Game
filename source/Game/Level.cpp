#include "Level.h"

#include <iostream>

#include "../Resources/Resource_Manager.h"
#include "GameObjects\Brick_Wall.h"

unsigned BLOCK_SIZE = 16;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Game_Object> Create_Game_Obj_From_Discr(const char descr, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	switch (descr)
	{
	case '0':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall_right"), position, size, rotation);
		

	case '1':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall_bottom"), position, size, rotation);
	

	case '2':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall_left"), position, size, rotation);
	

	case '3':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall_top"), position, size, rotation);
	

	case '4':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall"), position, size, rotation);
	

	case 'G':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall_bottom_left"), position, size, rotation);


	case 'H':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall_bottom_right"), position, size, rotation);


	case 'I':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall_top_left"), position, size, rotation);


	case 'J':
		return std::make_shared<Brick_Wall>(Resource_Manager::Get_Sprite("brickWall_top_right"), position, size, rotation);


	case 'D':
		return nullptr;

	default:
		std::cerr << __func__ << __LINE__ << "element empty !!!" << std::endl;;

	}

	return nullptr;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Level::Level(std::vector<std::string> level_discr)
	:Width(0), Heigth(0), Map_Objects{}
{
	if (level_discr.empty())
	{
		std::cerr << __func__ << __LINE__ << "Level is empty error !!!" << std::endl;
		return;
	}

	Width = level_discr[0].length();
	Heigth = level_discr.size();

	Map_Objects.reserve(Width * Heigth);

	unsigned curr_bottom_offset = static_cast<unsigned>(BLOCK_SIZE * (Heigth - 1));

	for (const std::string& curr_row : level_discr)
	{
		unsigned curr_left_offset = 0;
		for (const char curr_element : curr_row)
		{
			Map_Objects.emplace_back(Create_Game_Obj_From_Discr(curr_element, glm::vec2(curr_left_offset, curr_bottom_offset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE),0.f));

			curr_left_offset += BLOCK_SIZE;
			
		}
		curr_bottom_offset -= BLOCK_SIZE;


	}



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
