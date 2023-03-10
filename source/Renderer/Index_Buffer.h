#pragma once

#include <glad\glad.h>



//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
	class Index_Buffer
	{
	public:
		//================================================================================================================================================================
		~Index_Buffer();
		/*	Use the actual constructor for this class */
		Index_Buffer();
		Index_Buffer& operator=(Index_Buffer&& index_buffer) noexcept;
		Index_Buffer(Index_Buffer&& index_buffer) noexcept;


		/*	It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
		Index_Buffer(const Index_Buffer&) = delete;
		Index_Buffer& operator=(const Index_Buffer&) = delete;
		//================================================================================================================================================================


		//================================================================================================================================================================
		void Init(const void* data, const unsigned count);
		void Bind() const;
		void Unbind() const;
		unsigned Get_Count() const { return Count; }
		//================================================================================================================================================================


	private:
		//================================================================================================================================================================
		GLuint ID;
		unsigned Count;
		//================================================================================================================================================================

	};
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
