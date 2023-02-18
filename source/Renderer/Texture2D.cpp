#include "Texture2D.h"

using namespace Renderer;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Texture2D
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char* data, const unsigned int channels, const GLenum filter, const GLenum wrap_mode)
: Width(width), Height(height)
{
	switch (channels)
	{
	case 3:
		Mode = GL_RGB;
		break;
	case 4:
		Mode = GL_RGBA;
		break;

	default: 
		Mode = GL_RGBA;
		break;
	}

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, Mode, Width, Height, 0, Mode, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
Texture2D& Texture2D::operator=(Texture2D&& texture2d) noexcept
{
	glDeleteTextures(1, &ID);

	ID = texture2d.ID;
	texture2d.ID = 0;
	Mode = texture2d.Mode;
	Width = texture2d.Width;
	Height = texture2d.Height;

	return *this;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
Texture2D::Texture2D(Texture2D&& texture2d) noexcept
{
	ID = texture2d.ID;
	texture2d.ID = 0;
	Mode = texture2d.Mode;
	Width = texture2d.Width;
	Height = texture2d.Height;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void Texture2D::Bind_Texture() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void Texture2D::Add_SubTexture(std::string texture_name,const glm::vec2& left_bottom_uv, const glm::vec2& right_top_uv)
{
	SubTexture_Map.emplace(std::move(texture_name), SubTexture2D(left_bottom_uv, right_top_uv));
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
const Texture2D::SubTexture2D& Texture2D::Get_SubTexture(const std::string& name) const
{
	const static SubTexture2D default_subtexture;
	
	auto it = SubTexture_Map.find(name);
	
	if (it != SubTexture_Map.end())
		return it->second;

	return default_subtexture;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
