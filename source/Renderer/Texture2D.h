#pragma once 

#include "glad/glad.h"
#include "glm\vec2.hpp"

#include <string>
#include <map>

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Texture2D
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Renderer
{
	class Texture2D
	{
	public:
		// Struct SubTexure2D for texture 2D sprite 
		struct SubTexture2D
		{
			glm::vec2 Left_Bottom_UV;
			glm::vec2 Right_Top_UV;

			SubTexture2D() : Left_Bottom_UV(0.0f), Right_Top_UV(1.0f) { }
			SubTexture2D(const glm::vec2& left_bottom_uv, const glm::vec2& right_top_uv) : Left_Bottom_UV(left_bottom_uv), Right_Top_UV(right_top_uv) { }
	
		};
		
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

		/* Add SubTexture for Base Texture */
		void Add_SubTexture(std::string texture_name, const glm::vec2& left_bottom_uv, const glm::vec2& right_top_uv);

		const SubTexture2D& Get_SubTexture(const std::string& name) const;

		unsigned Get_Width() const { return Width; }

		unsigned Get_Height() const { return Height; }
		//========================================================================================================================================================

	private:

		//========================================================================================================================================================
		// Private Variables
		GLuint ID;
		GLenum Mode;
		unsigned int Width, Height;

		std::map<std::string, SubTexture2D> SubTexture_Map;
	};
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
