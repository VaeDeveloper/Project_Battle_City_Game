#pragma once

#include <glad\glad.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Vertex Buffer Class
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
	class Vertex_Buffer
	{
	public:
		//================================================================================================================================================================
		// Constructors and Destructors
		~Vertex_Buffer();
		/*	Use the actual constructor for this class */
		Vertex_Buffer();
		Vertex_Buffer& operator=(Vertex_Buffer&& vertex_buffer) noexcept;
		Vertex_Buffer(Vertex_Buffer&& vertex_buffer) noexcept;


		/*	It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
		Vertex_Buffer(const Vertex_Buffer&) = delete;
		Vertex_Buffer& operator=(const Vertex_Buffer&) = delete;
		//================================================================================================================================================================

		
		//================================================================================================================================================================
		// Public Method
		void Init(const void* data, const unsigned size);
		void Update(const void* data, const unsigned size) const;
		void Bind() const;
		void Unbind() const;
		//================================================================================================================================================================

	private:

		//================================================================================================================================================================
		// Private Variables
		GLuint ID;
		//================================================================================================================================================================

	};
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
