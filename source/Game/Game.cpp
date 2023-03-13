#include "Game.h"


#include "..\Renderer\Shader_Program.h"
#include "..\Renderer\Texture2D.h"
#include "..\Resources\Resource_Manager.h"
#include "..\Renderer\Sprite.h"


#include "..\Game\GameObjects\Player_Tank.h"
#include "Level.h"

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
	if (Player_Tank_Actor)
		Player_Tank_Actor->Render();

	if (ALevel)
		ALevel->Render();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Update(const uint64_t delta_time)
{
	if (ALevel)
		ALevel->Update(delta_time);

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


	glm::mat4 projection_matrix = glm::ortho(0.0f, static_cast<float>(Window_Size.x), 0.0f, static_cast<float>(Window_Size.y), -100.0f, 100.0f);

	sprite_shader_program->Use_Shader();
	sprite_shader_program->Set_Int("tex", 0);
	sprite_shader_program->Set_Matrix4("projection_mat", projection_matrix);

	Player_Tank_Actor = std::make_unique<Player_Tank>(Resource_Manager::Get_Sprite("Tank_Top_State"), 
													  Resource_Manager::Get_Sprite("Tank_Bottom_State"),
													  Resource_Manager::Get_Sprite("Tank_Left_State"),
													  Resource_Manager::Get_Sprite("Tank_Right_State"),
													  0.0000001f, glm::vec2(0), glm::vec2(16.f, 16.f));

	ALevel = std::make_unique<Level>(Resource_Manager::Get_Levels()[0]);

	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
