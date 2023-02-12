#include "Shader_Program.h"

#include <iostream>

using namespace Renderer;

//----------------------------------------------------------------------------------------------------------
//  Renderer::Shader_Program
//----------------------------------------------------------------------------------------------------------
Renderer::Shader_Program::~Shader_Program()
{
}
//----------------------------------------------------------------------------------------------------------
Shader_Program::Shader_Program(const std::string& vertex_shader, const std::string& fragment_shader)
:bIs_Compiled(false), ID(0)
{
	GLuint vertex_shader_id;
	if (Create_Shader(vertex_shader, GL_VERTEX_SHADER, vertex_shader_id))
	{
		std::cerr << "VERTEX SHADER COMPILE TIME ERROR! \n" << std::endl;
		return;
	}

	GLuint fragment_shader_id;
	if (Create_Shader(fragment_shader, GL_VERTEX_SHADER, fragment_shader_id))
	{
		std::cerr << "FRAGMENT SHADER COMPILE TIME ERROR! \n" << std::endl;
		return;
	}

}
//----------------------------------------------------------------------------------------------------------
bool Shader_Program::Create_Shader(const std::string& source, const GLenum shader_type, GLuint& shader_id)
{
	GLint success;

	shader_id = glCreateShader(shader_type);
	const char* code = source.c_str();
	glShaderSource(shader_id, 1, &code, nullptr);
	glCompileShader(shader_id);

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar info_log[1024];
		glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);
		std::cerr << "ERROR SHADER COMPILE TIME ERROR\n" << info_log << std::endl;
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------------------------------------
