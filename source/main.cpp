#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>


#include <iostream>
#include <chrono>

#include "Game\Game.h"
#include "Resources\Resource_Manager.h"
#include "Renderer\Renderer.h"

glm::ivec2 window_size(640, 480);
Game game(window_size);





//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void GLFW_Window_Size_Callback(GLFWwindow* window, int width, int height)
{
	window_size.x = width;
	window_size.y = height;
	RenderEngine::Renderer::Set_Viewport(window_size.x, window_size.y);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void GLFW_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	game.Set_Key(key, action);	

}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "Error glfwInit failed" << std::endl;
		return -1;
	}

	/* current version openGL 4.6 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* main_window = glfwCreateWindow(window_size.x, window_size.y, "BATTLE CITY", nullptr, nullptr);
	if (!main_window)
	{
		std::cout << "glfwCreateWindow is failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* window size callback */
	glfwSetWindowSizeCallback(main_window, GLFW_Window_Size_Callback);
	/* keybind callback */
	glfwSetKeyCallback(main_window, GLFW_Key_Callback);
	/* Make the window's context current */
	glfwMakeContextCurrent(main_window);

	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD !" << std::endl;
		return -1;
	}

	/* render and openGL version info */
	std::cout << "Renderer:- " << RenderEngine::Renderer::Get_Renderer_Str() << std::endl;
	std::cout << "OpenGL version:- " << RenderEngine::Renderer::Get_Version_Str() << std::endl;


	/* background colors */	
	RenderEngine::Renderer::Set_Clear_Color(0, 0, 0, 1);

	{
		Resource_Manager::Set_Executable_Path(argv[0]);
		game.Init();

		auto last_time = std::chrono::high_resolution_clock::now();

		/* Render LOOP */
		while (!glfwWindowShouldClose(main_window))
		{

			/* Poll for and process events */
			glfwPollEvents();

			auto current_time = std::chrono::high_resolution_clock::now();
			uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - last_time).count();
			last_time = current_time;

			/* Update duration */
			game.Update(duration);

			/* Clear */
			RenderEngine::Renderer::Clear();

			/* Render Engine */
			game.Render();

			/* Swap front and back buffers */
			glfwSwapBuffers(main_window);

		}
		Resource_Manager::Unload_All_Resources();
	}

	glfwTerminate();

	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
