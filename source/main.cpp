#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Renderer\Shader_Program.h"
#include "Renderer\Texture2D.h"
#include "Resources\Resource_Manager.h"

GLfloat point[] =
{
	 0.0f,   50.0f, 0.0f,
	 50.0f, -50.0f, 0.0f,
	-50.0f, -50.0f, 0.0f
};

GLfloat colors[] =
{
	 1.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 0.0f,
	 0.0f, 0.0f, 1.0f
};

GLfloat tex_coord[] =
{
	0.5f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f
};

/* GLSL Shaders 1*/
const char* vertex_shader =
"#version 460\n"
"layout (location = 0) in vec3 vertex_position;"
"layout (location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position  = vec4(vertex_position, 1.0);"
"}";

/* GLSL Shaders 2*/
const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

glm::ivec2 window_size(640, 480);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void GLFW_Window_Size_Callback(GLFWwindow* window, int width, int height)
{
	window_size.x = width;
	window_size.y = height;
	glViewport(0, 0, window_size.x, window_size.y);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void GLFW_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
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
	std::cout << "Renderer:- " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version:- " << glGetString(GL_VERSION) << std::endl;


	/* background colors */
	glClearColor(1, 0, 0, 1);


	{
		Resource_Manager resource_manager(argv[0]);
		auto Default_Shader_Program = resource_manager.Load_Shaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");

		if (!Default_Shader_Program)
		{
			std::cerr << "Can't create shader program" << std::endl;
			return -1;
		}

		auto tex = resource_manager.Load_Texture("Default_Texture", "res/textures/map_16x16.png");

		// generating Point VBO
		GLuint point_vbo = 0;
		glGenBuffers(1, &point_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

		// generating  Colors VBO
		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		/* load generating texture VBO */ 
		GLuint tex_coord_vbo = 0;
		glGenBuffers(1, &tex_coord_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coord), tex_coord, GL_STATIC_DRAW);


		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);


		/*load points attribute buffer* */ 
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


		/*load colors attribute buffet*/ 
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


		/*load texture coordinate attribute buffet*/
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_vbo);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		Default_Shader_Program->Use_Shader();
		Default_Shader_Program->Set_Int("tex", 0);

		glm::mat4 model_matrix_1 = glm::mat4(1.0f);
		model_matrix_1 = glm::translate(model_matrix_1, glm::vec3(100.f, 200.0f, 0.0f));

		glm::mat4 model_matrix_2 = glm::mat4(1.0f);
		model_matrix_2 = glm::translate(model_matrix_2, glm::vec3(590.0f, 200.0f, 0.0f));

		glm::mat4 projection_matrix = glm::ortho(0.0f, static_cast<float>(window_size.x), 0.0f, static_cast<float>(window_size.y), -100.0f, 100.0f);

		Default_Shader_Program->Set_Matrix4("projection_mat", projection_matrix);

		/* Render LOOP */
		while (!glfwWindowShouldClose(main_window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);	

			Default_Shader_Program->Use_Shader();
			glBindVertexArray(vao);
			tex->Bind_Texture();
			
			Default_Shader_Program->Set_Matrix4("model_mat", model_matrix_1);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			Default_Shader_Program->Set_Matrix4("model_mat", model_matrix_2);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			/* Swap front and back buffers */
			glfwSwapBuffers(main_window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();

	return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
