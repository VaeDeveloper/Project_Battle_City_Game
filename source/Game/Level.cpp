#include "Level.h"

#include <iostream>


#include "GameObjects\Brick_Wall.h"
#include "GameObjects\Beton_Wall.h"
#include "GameObjects\Trees.h"
#include "GameObjects\Ice.h"
#include "GameObjects\Water.h"

unsigned BLOCK_SIZE = 16;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Game_Object> Create_Game_Obj_From_Discr(const char descr, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	switch (descr)
	{
	case '0':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Right, position, size, rotation);
		
	case '1':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Bottom, position, size, rotation);
	
	case '2':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Left, position, size, rotation);
	
	case '3':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Top, position, size, rotation);
	
	case '4':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::All, position, size, rotation);
	
	case 'G':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Bottom_Left, position, size, rotation);

	case 'H':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Bottom_Right, position, size, rotation);

	case 'I':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Top_Left, position, size, rotation);

	case 'J':
		return std::make_shared<Brick_Wall>(Brick_Wall::EBrick_Wall_Type::Top_Right, position, size, rotation);

	case '5':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::Right, position, size, rotation);

	case '6':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::Bottom, position, size, rotation);

	case '7':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::Left, position, size, rotation);

	case '8':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::Top, position, size, rotation);

	case '9':
		return std::make_shared<Beton_Wall>(Beton_Wall::EBeton_Wall_Type::All, position, size, rotation);

	case 'A':
		return std::make_shared<Water>(position, size, rotation);

	case 'B':
		return std::make_shared<Trees>(position, size, rotation);

	case 'C':
		return std::make_shared<Ice>(position, size, rotation);


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
