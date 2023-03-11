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

	/* shader program */
	auto sprite_shader_program = Resource_Manager::Get_Shader_Program("SpriteShader");

	if (!sprite_shader_program)
	{
		std::cerr << __func__ << __LINE__ << "Can't find shader program: " << "sprite_shader" << std::endl;
		return false;
	}

	/* object texture atlas */
	auto texture_atlas = Resource_Manager::Get_Texture("Default_Texture_Atlas");

	if (!texture_atlas)
	{
		std::cerr << __func__ << __LINE__ << "Can't find texture atlas: " << "Default_Texture_Atlas" << std::endl;
		return false;
	}

	auto tanks_texture_atlas = Resource_Manager::Get_Texture("Tanks_Texture_Atlas");

	/* tank texture atlas */
	if (!tanks_texture_atlas)
	{
		std::cerr << __func__ << __LINE__ << "Can't find tank texture atlas:" << "Tanks_Texture_Atlas" << std::endl;
		return false;
	}


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


	glm::mat4 model_matrix_1 = glm::mat4(1.0f);
	model_matrix_1 = glm::translate(model_matrix_1, glm::vec3(100.f, 200.0f, 0.0f));

	glm::mat4 model_matrix_2 = glm::mat4(1.0f);
	model_matrix_2 = glm::translate(model_matrix_2, glm::vec3(590.0f, 200.0f, 0.0f));

	glm::mat4 projection_matrix = glm::ortho(0.0f, static_cast<float>(Window_Size.x), 0.0f, static_cast<float>(Window_Size.y), -100.0f, 100.0f);

	sprite_shader_program->Use_Shader();
	sprite_shader_program->Set_Int("tex", 0);
	sprite_shader_program->Set_Matrix4("projection_mat", projection_matrix);


	//Initial Tank_Sprite 

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
