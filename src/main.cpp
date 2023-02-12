#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>

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

    glClearColor(0, 1, 0, 1);

    /* Render LOOP */
    while (!glfwWindowShouldClose(main_window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(main_window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}