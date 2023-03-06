#pragma once 

#include <glad\glad.h>

#include <vector>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Vertex Buffer Layout Class
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{

	//====================================================================================================================================================================
	/* Vertex Buffer Element Structure */
	struct Vertex_Buffer_Layout_Element
	{
		GLuint count;
		GLenum type;
		GLboolean normalized;
		unsigned int size;
	};
	//====================================================================================================================================================================


	class Vertex_Buffer_Layout
	{
	public:
		//================================================================================================================================================================
		// Constructors and Destructors
		/* */
		Vertex_Buffer_Layout();
		//================================================================================================================================================================

		//================================================================================================================================================================
		// Public Method
		/* */
		void ReserveElement(const size_t count);

		/* Getter Stride */
		unsigned Get_Stride() const { return Stride; }

		/* Getter Layout Element */
		const std::vector<Vertex_Buffer_Layout_Element>& Get_Layout_Elements() const { return Layout_Elements; }
		/* */
		void Add_Element_Layout_Float(const unsigned count, const bool normalized);
		//================================================================================================================================================================

	private:

		//================================================================================================================================================================
		// Private Variables
		/* */
		std::vector<Vertex_Buffer_Layout_Element> Layout_Elements;

		/* Stride */
		unsigned Stride;
		//================================================================================================================================================================

	};
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------