#include "Shader_Program.h"

#include <iostream>

using namespace Renderer;

//----------------------------------------------------------------------------------------------------------
//  Renderer::Shader_Program
//----------------------------------------------------------------------------------------------------------
Shader_Program::~Shader_Program()
{
	glDeleteProgram(ID);
}
//----------------------------------------------------------------------------------------------------------
Shader_Program::Shader_Program(const std::string& vertex_shader, const std::string& fragment_shader)
:bIs_Compiled(false), ID(0)
{
	GLint success;
	GLuint vertex_shader_id;

	if (!Create_Shader(vertex_shader, GL_VERTEX_SHADER, vertex_shader_id))
	{
		std::cerr << "VERTEX SHADER COMPILE TIME ERROR! \n" << std::endl;
		return;
	}

	GLuint fragment_shader_id;
	if (!Create_Shader(fragment_shader, GL_FRAGMENT_SHADER, fragment_shader_id))
	{
		std::cerr << "FRAGMENT SHADER COMPILE TIME ERROR! \n" << std::endl;
		glDeleteShader(vertex_shader_id);
		return;
	}

	ID = glCreateProgram();
	glAttachShader(ID,vertex_shader_id);
	glAttachShader(ID, fragment_shader_id);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLchar info_log[1024];
		glGetShaderInfoLog(ID, 1024, nullptr, info_log);
		std::cerr << "ERROR SHADER LINK TIME ERROR" << std::endl;
	}
	else
	{
		bIs_Compiled = true;
	}

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}
//----------------------------------------------------------------------------------------------------------
Shader_Program& Shader_Program::operator=(Shader_Program&& shader_program) noexcept
{
	glDeleteProgram(ID);
	ID = shader_program.ID;
	bIs_Compiled = shader_program.bIs_Compiled;

	shader_program.ID = 0;
	shader_program.bIs_Compiled = false;
	return *this;
}
//----------------------------------------------------------------------------------------------------------
Shader_Program::Shader_Program(Shader_Program&& shader_program) noexcept
{
	ID = shader_program.ID;
	bIs_Compiled = shader_program.bIs_Compiled;

	shader_program.ID = 0;
	shader_program.bIs_Compiled = false;
}
//----------------------------------------------------------------------------------------------------------
void Shader_Program::Use_Shader() const
{
	glUseProgram(ID);
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
