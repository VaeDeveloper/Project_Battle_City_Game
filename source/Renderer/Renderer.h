#pragma once

#include "Vertex_Array.h"
#include "Index_Buffer.h"
#include "Shader_Program.h"

#include <string>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Renderer Class
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
	class Renderer
	{
	public:
		//============================================================================================================================================================
		static void Draw(const Vertex_Array& vertex_array, const Index_Buffer& index_buffer, const Shader_Program& shader);
		static void Set_Clear_Color(float r, float g, float b, float alpha);
		static void Set_Depth_Test(const bool enable);
		static void Clear();
		static void Set_Viewport(unsigned width, unsigned height, unsigned left_offset = 0, unsigned right_offset = 0);

		static std::string Get_Renderer_Str();		/* return renderer */
		static std::string Get_Version_Str();		/* return version openGL */
		//============================================================================================================================================================
	};
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

