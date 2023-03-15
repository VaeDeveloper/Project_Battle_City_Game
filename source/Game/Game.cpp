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

	/* Loading number levels: Get_Levels()[number_level] */
	ALevel = std::make_unique<Level>(Resource_Manager::Get_Levels()[1]);

	/* Camera Projection */
	Window_Size.x = static_cast<int>(ALevel->Get_Level_Width());
	Window_Size.y = static_cast<int>(ALevel->Get_Level_Height());

	glm::mat4 projection_matrix = glm::ortho(0.0f, static_cast<float>(Window_Size.x), 0.0f, static_cast<float>(Window_Size.y), -100.0f, 100.0f);

	
	sprite_shader_program->Use_Shader();
	sprite_shader_program->Set_Int("tex", 0);
	sprite_shader_program->Set_Matrix4("projection_mat", projection_matrix);


	/* Loding Player in level */
	Player_Tank_Actor = std::make_unique<Player_Tank>(0.0000001f, ALevel->Get_Player_Respawn_1(), glm::vec2(Level::Block_Size, Level::Block_Size), 0.f);



	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
size_t Game::Get_Curr_Level_Width() const
{
	return ALevel->Get_Level_Width();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
size_t Game::Get_Curr_Level_Height() const
{
	return ALevel->Get_Level_Height();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
