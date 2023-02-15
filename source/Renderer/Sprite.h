#pragma once

#include <glad\glad.h>
#include <glm\vec2.hpp>

#include "memory"


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Sprite
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Renderer
{
	class Texture2D;
	class Shader_Program;

	class Sprite
	{
	public:
		//============================================================================================================================================================
		// Constructors and Destructors
		~Sprite();
		
		/*	Use the actual constructor for this class */
		Sprite(const std::shared_ptr<Texture2D> texture,
			   const std::shared_ptr<Shader_Program> shader_program,
			   const glm::vec2& position = glm::vec2(0.0f), 
			   const glm::vec2& size = glm::vec2(1.0f),
			   const float rotation = 0.0f);

		/*	It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		//============================================================================================================================================================
		//	 Public Methods
		/*Render Method*/
		void Render() const;
		
		/* Set Position Sprite Method*/
		void Set_Position(const glm::vec2& position);
		
		/* Set Size Sprite Method*/
		void Set_Size(const glm::vec2& size);

		/*Set Rotation Sprite Method*/
		void Set_Rotation(const float rotation);
		//============================================================================================================================================================

	private:

		//============================================================================================================================================================
		// Private Variables
		float Rotation;
		std::shared_ptr<Texture2D> Texture;
		std::shared_ptr<Shader_Program> Shader;
		glm::vec2 Position;
		glm::vec2 Size;
		GLuint Vertex_Array_Obj;
		GLuint Vertex_Coord_VB0;
		GLuint Texture_Coord_VB0;

		//============================================================================================================================================================


	};

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
