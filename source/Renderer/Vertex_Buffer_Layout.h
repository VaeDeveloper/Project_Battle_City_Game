#pragma once

#include <glad\glad.h>

#include <vector>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Vertex Buffer Layout Class
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{

/* Vertex Buffer Element Structure */
struct Vertex_Buffer_Layout_Element
{
    GLuint count;
    GLenum type;
    GLboolean normalized;
    unsigned int size;
};

class Vertex_Buffer_Layout
{
  public:
    Vertex_Buffer_Layout();

    void ReserveElement(const size_t count);       /* */
    unsigned Get_Stride() const { return Stride; } /* Getter Stride */

    const std::vector<Vertex_Buffer_Layout_Element>& Get_Layout_Elements() const /* Getter Layout Element */ { return Layout_Elements; }

    void Add_Element_Layout_Float(const unsigned count, const bool normalized); /* */
                                                                                //================================================================================================================================================================

  private:
    std::vector<Vertex_Buffer_Layout_Element> Layout_Elements; /* */
    unsigned Stride;                                           /* Stride */
};
} // namespace RenderEngine
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
