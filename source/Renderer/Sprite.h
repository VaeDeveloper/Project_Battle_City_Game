#pragma once

#include "Vertex_Buffer.h"
#include "Index_Buffer.h"
#include "Vertex_Array.h"

#include <glad\glad.h>
#include <glm\vec2.hpp>

#include <memory>
#include <string>


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Sprite
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
	class Texture2D;
	class Shader_Program;

	class Sprite
	{
	public:
		//============================================================================================================================================================
		~Sprite();
		
		/*	Use the actual constructor for this class */
		Sprite(const std::shared_ptr<Texture2D> texture,
			const std::string initial_subtexture,
			const std::shared_ptr<Shader_Program> shader_program);
		

		//============================================================================================================================================================
		/*	It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
		//============================================================================================================================================================
		
		
		//============================================================================================================================================================
		virtual void Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const;		/* Render */
		//============================================================================================================================================================

	protected:
		//============================================================================================================================================================
		std::shared_ptr<Texture2D> Texture;
		std::shared_ptr<Shader_Program> Shader;

		Vertex_Array Vertex_Array_Obj;
		Vertex_Buffer Vertex_Coord_Buffer;
		Vertex_Buffer Texture_Coord_Buffer;
		Index_Buffer Index_Pixel_Buffer;
		//============================================================================================================================================================
	};
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
