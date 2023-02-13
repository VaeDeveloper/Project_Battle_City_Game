#pragma once 

#include "glad/glad.h"
#include <string>

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Texture2D
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Renderer
{
	class Texture2D
	{
	public:
		//========================================================================================================================================================
		// Constructors and Destructors
		~Texture2D();

		/*	Use the actual constructor for this class */
		Texture2D(const GLuint width, const GLuint height,
				  const unsigned char* data, 
				  const unsigned int channels = 4,
				  const GLenum filter = GL_LINEAR,
				  const GLenum wrap_mode = GL_CLAMP_TO_EDGE);

		Texture2D& operator=(Texture2D&& texture2d) noexcept;
		Texture2D(Texture2D&& texture2d) noexcept;

		/*	It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		//========================================================================================================================================================

		//========================================================================================================================================================
		// Public Methods
		void Bind_Texture() const;

	private:

		//========================================================================================================================================================
		// Private Variables
		GLuint ID;
		GLenum Mode;
		unsigned int Width, Height;


	};
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
