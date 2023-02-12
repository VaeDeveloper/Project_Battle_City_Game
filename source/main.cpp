#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>

#include "Renderer\Shader_Program.h"

GLfloat point[] =
{
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char* vertex_shader =
"#version 460\n"
"layout (location = 0) in vec3 vertex_position;"
"layout (location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position  = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

static int g_window_width = 640;
static int g_window_height = 480;

void GLFW_Window_Size_Callback(GLFWwindow* window, int width, int height)
{
    g_window_width = width;
    g_window_height = height;
    glViewport(0, 0, g_window_width, g_window_height);
}

void GLFW_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Error glfwInit failed" << std::endl;
        return -1;
    }


    /* curr version openGL 4.6 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* main_window = glfwCreateWindow(g_window_width, g_window_height, "BATTLE CITY", nullptr, nullptr);
    if (!main_window)
    {
        std::cout << "glfwCreateWindow is failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(main_window, GLFW_Window_Size_Callback);
    glfwSetKeyCallback(main_window, GLFW_Key_Callback);
    /* Make the window's context current */
    glfwMakeContextCurrent(main_window);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD !" << std::endl;
        return -1;
    }

    std::cout << "Renderer:- " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version:- " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 0, 0, 1);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    std::string s_vertex_shader(vertex_shader);
    std::string s_fragment_shader(fragment_shader);
    Renderer::Shader_Program shader_program(s_vertex_shader, s_fragment_shader);

    if (!shader_program.Is_Compiled())
    {
        std::cerr << "ERROR : Can't create shader program\n" << std::endl;
        return -1;
    }

    GLuint point_vbo = 0;
    glGenBuffers(1, &point_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);



    /* Render LOOP */
    while (!glfwWindowShouldClose(main_window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

    
        shader_program.Use_Shader();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(main_window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}