#include "Level.h"

#include <algorithm>
#include <iostream>

#include "GameObjects\Beton_Wall.h"
#include "GameObjects\Border.h"
#include "GameObjects\Brick_Wall.h"
#include "GameObjects\Eagle.h"
#include "GameObjects\Ice.h"
#include "GameObjects\Trees.h"
#include "GameObjects\Water.h"

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
        std::cerr << " " << __func__ << " " << __LINE__ << " element empty !!!" << std::endl;
        ;
    }

    return nullptr;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Level::Level(std::vector<std::string> level_discr) : Width_Block(0), Height_Block(0), Width_Pixels(0), Height_Pixels(0), Map_Objects{}, Player_Respawn_1(0), Player_Respawn_2(0), Enemy_Respawn_1(0), Enemy_Respawn_2(0), Enemy_Respawn_3(0)
{
    if (level_discr.empty())
    {
        std::cerr << __func__ << __LINE__ << "Level is empty error !!!" << std::endl;
        return;
    }

    Width_Block = level_discr[0].length();
    Height_Block = level_discr.size();
    Width_Pixels = static_cast<unsigned>(Width_Block * BLOCK_SIZE);
    Height_Pixels = static_cast<unsigned>(Height_Block * BLOCK_SIZE);

    /* curr Player 1 and Player 2 position */
    Player_Respawn_1 = {BLOCK_SIZE * (Width_Block / 2 - 1), BLOCK_SIZE / 2};
    Player_Respawn_2 = {BLOCK_SIZE * (Width_Block / 2 + 3), BLOCK_SIZE / 2};

    /* curr Enemy 1, 2 ,3 position */
    Enemy_Respawn_1 = {BLOCK_SIZE, BLOCK_SIZE * Height_Block - BLOCK_SIZE / 2};
    Enemy_Respawn_2 = {BLOCK_SIZE * (Width_Block / 2 + 1), BLOCK_SIZE * Height_Block - BLOCK_SIZE / 2};
    Enemy_Respawn_3 = {BLOCK_SIZE * Width_Block, BLOCK_SIZE * Height_Block - BLOCK_SIZE / 2};

    Map_Objects.reserve(Width_Block * Height_Block + 4);

    unsigned curr_bottom_offset = static_cast<unsigned>(BLOCK_SIZE * (Height_Block - 1) + BLOCK_SIZE / 2.0f);

    for (const std::string& curr_row : level_discr)
    {
        unsigned curr_left_offset = BLOCK_SIZE;

        for (const char curr_element : curr_row)
        {
            switch (curr_element)
            {
            case 'K':
                Player_Respawn_1 = {curr_left_offset, curr_bottom_offset};
                Map_Objects.emplace_back(nullptr);
                break;

            case 'L':
                Player_Respawn_2 = {curr_left_offset, curr_bottom_offset};
                Map_Objects.emplace_back(nullptr);
                break;

            case 'M':
                Enemy_Respawn_1 = {curr_left_offset, curr_bottom_offset};
                Map_Objects.emplace_back(nullptr);
                break;

            case 'N':
                Enemy_Respawn_2 = {curr_left_offset, curr_bottom_offset};
                Map_Objects.emplace_back(nullptr);
                break;

            case 'O':
                Enemy_Respawn_3 = {curr_left_offset, curr_bottom_offset};
                Map_Objects.emplace_back(nullptr);
                break;

            default:
                Map_Objects.emplace_back(Create_Game_Obj_From_Discr(curr_element, glm::vec2(curr_left_offset, curr_bottom_offset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
                break;
            }

            curr_left_offset += BLOCK_SIZE;
        }

        curr_bottom_offset -= BLOCK_SIZE;
    }

    /* Bottom Border */
    Map_Objects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0.0f), glm::vec2(Width_Block * BLOCK_SIZE, BLOCK_SIZE / 2.0f), 0.0f, 0.0f));

    /* Top Border */
    Map_Objects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, Height_Block * BLOCK_SIZE + BLOCK_SIZE / 2), glm::vec2(Width_Block * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0.0f, 0.f));

    /* Left Border */
    Map_Objects.emplace_back(std::make_shared<Border>(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE, (Height_Block + 1) * BLOCK_SIZE), 0.0f, 0.0f));

    /* Right Border */
    Map_Objects.emplace_back(std::make_shared<Border>(glm::vec2((Width_Block + 1) * BLOCK_SIZE, 0.0f), glm::vec2(BLOCK_SIZE * 2.0f, (Height_Block + 1) * BLOCK_SIZE), 0.0f, 0.f));
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
void Level::Update(const double delta)
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
    return (Width_Block + 3) * BLOCK_SIZE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
size_t Level::Get_Level_Height() const
{
    return (Height_Block + 1) * BLOCK_SIZE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<Game_Object>> Level::Get_Object_InArea(const glm::vec2& bottom_left, const glm::vec2& top_right)
{
    std::vector<std::shared_ptr<Game_Object>> output;
    output.reserve(9);

    glm::vec2 bottom_left_conv(std::clamp(bottom_left.x - BLOCK_SIZE, 0.f, static_cast<float>(Width_Pixels)), std::clamp(Height_Pixels - bottom_left.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(Height_Pixels)));

    glm::vec2 top_right_conv(std::clamp(top_right.x - BLOCK_SIZE, 0.f, static_cast<float>(Width_Pixels)), std::clamp(Height_Pixels - top_right.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(Height_Pixels)));

    size_t start_x = static_cast<size_t>(floor(bottom_left_conv.x / BLOCK_SIZE));
    size_t end_x = static_cast<size_t>(ceil(top_right_conv.x / BLOCK_SIZE));

    size_t start_y = static_cast<size_t>(floor(top_right_conv.y / BLOCK_SIZE));
    size_t end_y = static_cast<size_t>(ceil(bottom_left_conv.y / BLOCK_SIZE));

    for (size_t curr_column = start_x; curr_column < end_x; ++curr_column)
    {
        for (size_t curr_row = start_y; curr_row < end_y; ++curr_row)
        {
            auto& curr_object = Map_Objects[curr_row * Width_Block + curr_column];
            if (curr_object)
            {
                output.push_back(curr_object);
            }
        }
    }

    if (end_x >= Width_Block)
        output.push_back(Map_Objects[Map_Objects.size() - 1]);

    if (start_x <= 1)
        output.push_back(Map_Objects[Map_Objects.size() - 2]);

    if (start_y <= 1)
        output.push_back(Map_Objects[Map_Objects.size() - 3]);

    if (end_y >= Height_Block)
        output.push_back(Map_Objects[Map_Objects.size() - 4]);

    return output;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
