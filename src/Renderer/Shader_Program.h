#pragma once 

#include <glad\glad.h>
#include <string>


//----------------------------------------------------------------------------------------------------------
//  Renderer::Shader_Program
//----------------------------------------------------------------------------------------------------------
namespace Renderer
{
	class Shader_Program
	{
	public:
		~Shader_Program();

		/* It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
		Shader_Program() = delete;
		Shader_Program(Shader_Program&) = delete;
		Shader_Program& operator=(const Shader_Program&) = delete;

		/* Use the actual constructor for this class */
		Shader_Program(const std::string& vertex_shader, const std::string& fragment_shader);
		Shader_Program& operator=(Shader_Program&& shader_program) noexcept;
		Shader_Program(Shader_Program&& shader_program) noexcept;
	
		bool Is_Compiled() const { return bIs_Compiled; }
		void Use_Shader() const;

	
	private:
		bool Create_Shader(const std::string& source, const GLenum shader_type, GLuint& shader_id);

		bool bIs_Compiled;
		GLuint ID;
	};
}
//----------------------------------------------------------------------------------------------------------
