#include "Level.h"

#include <iostream>

#include "GameObjects\Game_Object.h"

unsigned BLOCK_SIZE = 16;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Level::Level(std::vector<std::string> level_discr)
{
	if (level_discr.empty())
	{
		std::cerr << __func__ << __LINE__ << "Level is empty error !!!" << std::endl;
		return;
	}

	Width = level_discr[0].length();
	Heigth = level_discr.size();

	Map_Objects.reserve(static_cast<size_t>(Width) * Heigth);

	unsigned curr_bottom_offset = BLOCK_SIZE * (Heigth - 1);

	for (const std::string& curr_row : level_discr)
	{
		unsigned curr_left_offset = 0;
		for (const char curr_element : curr_row)
		{
			curr_left_offset += BLOCK_SIZE;
			//TODO
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
