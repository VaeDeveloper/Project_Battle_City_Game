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
		struct Frame_Discription 
		{
			Frame_Discription(const glm::vec2 left_bottom_uv, const glm::vec2 right_top_uv, const uint64_t duration)
			: Left_Bottom_UV(left_bottom_uv), Right_Top_UV(right_top_uv), Duration(duration) {}

			glm::vec2 Left_Bottom_UV;
			glm::vec2 Right_Top_UV;
			uint64_t Duration;
		};
		//============================================================================================================================================================


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
		void Render(const glm::vec2& position, const glm::vec2& size, const float rotation,const float layer = 0, const size_t frame_id = 0) const;	/* Render */
		uint64_t Get_Frame_Duration(const size_t frame_id) const;																/* Getter Frame Duration */
		size_t Get_Frames_Count() const;
		void Insert_Frame(std::vector<Frame_Discription> frames_discriptions);
		
		//============================================================================================================================================================

	protected:
		//============================================================================================================================================================
		std::shared_ptr<Texture2D> Texture;
		std::shared_ptr<Shader_Program> Shader;

		Vertex_Array Vertex_Array_Obj;
		Vertex_Buffer Vertex_Coord_Buffer;
		Vertex_Buffer Texture_Coord_Buffer;
		Index_Buffer Index_Pixel_Buffer;

		std::vector<Frame_Discription> Frame_Discriptions;
		mutable size_t Last_Frame_ID;
		//============================================================================================================================================================
	};
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
