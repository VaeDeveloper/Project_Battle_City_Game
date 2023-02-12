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
		Shader_Program(const std::string& vertex_shader, const std::string& fragment_shader);
	
		bool Is_Compiled() const { return bIs_Compiled; }
		bool Use_Shader() const;

	private:
		bool Create_Shader(const std::string& source, const GLenum shader_type, GLuint& shader_id);

		bool bIs_Compiled;
		GLuint ID;
	

	};
}
//----------------------------------------------------------------------------------------------------------
