#include "Game.h"


#include "..\Renderer\Shader_Program.h"
#include "..\Renderer\Texture2D.h"
#include "..\Resources\Resource_Manager.h"
#include "..\Renderer\Sprite.h"
#include "..\Renderer\Animated_Sprite.h"
#include "..\Game\Player_Tank.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include "GLFW\glfw3.h"

#include <iostream>
#include <cassert>

//#define NDEBUG

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game(const glm::ivec2 window_size)
	:Current_Game_States(EGame_State::Pause), Window_Size(window_size)
{
	Keys.fill(false);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Render()
{
	//Resource_Manager::Get_Animated_Sprite("NewAnimSprite")->Render();
	if (Player_Tank_Actor)
		Player_Tank_Actor->Render();

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Update(const uint64_t delta_time)
{
	//Resource_Manager::Get_Animated_Sprite("NewAnimSprite")->Update(delta_time);
	if (Player_Tank_Actor)
	{
		if (Keys[GLFW_KEY_W])
		{
			Player_Tank_Actor->Set_Orientation(Player_Tank::EOrientation::Top);
			Player_Tank_Actor->Move_Player(true);
		}
		else if (Keys[GLFW_KEY_A])
		{
			Player_Tank_Actor->Set_Orientation(Player_Tank::EOrientation::Left);
			Player_Tank_Actor->Move_Player(true);
		}
		else if (Keys[GLFW_KEY_D])
		{
			Player_Tank_Actor->Set_Orientation(Player_Tank::EOrientation::Right);
			Player_Tank_Actor->Move_Player(true);
		}
		else if (Keys[GLFW_KEY_S])
		{
			Player_Tank_Actor->Set_Orientation(Player_Tank::EOrientation::Bottom);
			Player_Tank_Actor->Move_Player(true);
		}
		else
		{
			Player_Tank_Actor->Move_Player(false);
		}

		Player_Tank_Actor->Update(delta_time);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Set_Key(const int key, const int action)
{
	Keys[key] = action;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Game::Init()
{
	Resource_Manager::Load_JSON_Resources("res/resourses.json");

	auto Default_Shader_Program = Resource_Manager::Load_Shaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");

	if (!Default_Shader_Program)
	{
		assert(!Default_Shader_Program);

#ifndef NDEBUG
		std::cerr << __func__ << "\t " << __LINE__ << "Can't create default shader program in Game::INIT()" << std::endl;
#endif // !NDEBUG


	}

	auto Sprite_Shader_Program = Resource_Manager::Load_Shaders("SpriteShader", "res/shaders/Shader_Vertex.txt", "res/shaders/Sprite_Fragment.txt");

	if (!Sprite_Shader_Program)
	{
		assert(!Sprite_Shader_Program);

#ifndef NDEBUG
		std::cerr << __func__ << "\t " << __LINE__ << "Can't create sprite shader program in Game::INIT()"  << std::endl;
#endif // !NDEBUG

	}


	auto tex = Resource_Manager::Load_Texture("Default_Texture", "res/textures/map_16x16.png");


	std::vector<std::string> sub_textures_names = {
		"block",
		"top_block",
		"bottom_block",
		"left_block",
		"right_block",
		"top_left_block",
		"top_right_block",
		"bottom_left_block",
		"bottom_right_block",
		"beton",
		"top_beton",
		"bottom_beton",
		"left_beton",
		"right_beton",
		"top_left_beton",
		"top_right_beton",
		"bottom_left_beton",
		"bottom_right_beton",
		"water1",
		"water2",
		"water3",
		"trees",
		"ice",
		"wall",
		"eagle",
		"dead_eagle",
		"respawn1",
		"respawn2",
		"respawn3",
		"respawn4"
	};

	auto texture_atlas = Resource_Manager::Load_Texture_Atlas("Default_Texture_Atlas", "res/textures/map_16x16.png", std::move(sub_textures_names), 16, 16);


	auto anim_sprite = Resource_Manager::Load_Animated_Sprite("NewAnimSprite", "Default_Texture_Atlas", "SpriteShader", 100, 100, "water1");
	anim_sprite->Set_Position(glm::vec2(300, 300));

	std::vector<std::pair<std::string, uint64_t>> water_state;
	water_state.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
	water_state.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
	water_state.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

	std::vector<std::pair<std::string, uint64_t>> eagle_state;
	eagle_state.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));
	eagle_state.emplace_back(std::make_pair<std::string, uint64_t>("dead_eagle", 1000000000));

	anim_sprite->Insert_State("water_state", std::move(water_state));
	anim_sprite->Insert_State("eagle_state", std::move(eagle_state));

	anim_sprite->Set_State("water_state");


	Default_Shader_Program->Use_Shader();
	Default_Shader_Program->Set_Int("tex", 0);

	glm::mat4 model_matrix_1 = glm::mat4(1.0f);
	model_matrix_1 = glm::translate(model_matrix_1, glm::vec3(100.f, 200.0f, 0.0f));

	glm::mat4 model_matrix_2 = glm::mat4(1.0f);
	model_matrix_2 = glm::translate(model_matrix_2, glm::vec3(590.0f, 200.0f, 0.0f));

	glm::mat4 projection_matrix = glm::ortho(0.0f, static_cast<float>(Window_Size.x), 0.0f, static_cast<float>(Window_Size.y), -100.0f, 100.0f);

	Default_Shader_Program->Set_Matrix4("projection_mat", projection_matrix);


	Sprite_Shader_Program->Use_Shader();
	Sprite_Shader_Program->Set_Int("tex", 0);
	Sprite_Shader_Program->Set_Matrix4("projection_mat", projection_matrix);


	//Initial Tank_Sprite 

	std::vector<std::string> tanks_sub_textures_names =
	{
		"tank_top_1",
		"tank_top_2",
		"tank_left_1",
		"tank_left_2",
		"tank_bottom_1",
		"tank_bottom_2",
		"tank_right_1",
		"tank_right_2"
	};

	auto tanks_texture_atlas = Resource_Manager::Load_Texture_Atlas("Tanks_Texture_Atlas", "res/textures/tanks.png", std::move(tanks_sub_textures_names), 16, 16);
	auto tanks_anim_sprite = Resource_Manager::Load_Animated_Sprite("Tanks_Animate_Sprite", "Tanks_Texture_Atlas", "SpriteShader", 100, 100, "tank_top_1");

	std::vector<std::pair<std::string, uint64_t>> tank_top_state;
	tank_top_state.emplace_back(std::make_pair<std::string, uint64_t>("tank_top_1", 500000000));
	tank_top_state.emplace_back(std::make_pair<std::string, uint64_t>("tank_top_2", 500000000));

	std::vector<std::pair<std::string, uint64_t>> tank_bottom_state;
	tank_bottom_state.emplace_back(std::make_pair<std::string, uint64_t>("tank_bottom_1", 500000000));
	tank_bottom_state.emplace_back(std::make_pair<std::string, uint64_t>("tank_bottom_2", 500000000));

	std::vector<std::pair<std::string, uint64_t>> tank_right_state;
	tank_right_state.emplace_back(std::make_pair<std::string, uint64_t>("tank_right_1", 500000000));
	tank_right_state.emplace_back(std::make_pair<std::string, uint64_t>("tank_right_2", 500000000));

	std::vector<std::pair<std::string, uint64_t>> tank_left_state;
	tank_left_state.emplace_back(std::make_pair<std::string, uint64_t>("tank_left_1", 500000000));
	tank_left_state.emplace_back(std::make_pair<std::string, uint64_t>("tank_left_2", 500000000));

	tanks_anim_sprite->Insert_State("Tank_Top_State", std::move(tank_top_state));
	tanks_anim_sprite->Insert_State("Tank_Bottom_State", std::move(tank_bottom_state));
	tanks_anim_sprite->Insert_State("Tank_Left_State", std::move(tank_left_state));
	tanks_anim_sprite->Insert_State("Tank_Right_State", std::move(tank_right_state));

	tanks_anim_sprite->Set_State("Tank_Top_State");

	Player_Tank_Actor = std::make_unique<Player_Tank>(tanks_anim_sprite, 0.0000001, glm::vec2(100.0f, 100.0f));

	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
