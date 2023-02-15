#include "Resource_Manager.h"
#include "../Renderer/Shader_Program.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Shader_Program
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Resource_Manager::Resource_Manager(const std::string& executable_path)
:Shader_Programs{}, Path{}
{
	size_t found = executable_path.find_last_of("/\\");
	Path = executable_path.substr(0, found);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Renderer::Shader_Program> Resource_Manager::Load_Shaders(const std::string& shader_name,const std::string& vertex_path, const std::string& fragment_path)
{
	std::string vertex_string = Get_File_String(vertex_path);
	std::string fragment_string = Get_File_String(fragment_path);

	if (vertex_string.empty())
	{
		std::cerr << "No Vertex shader!" << std::endl;
		return nullptr;
	}

	if (fragment_string.empty())
	{
		std::cerr << "No Fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::Shader_Program>& new_shader = Shader_Programs.emplace(shader_name, std::make_shared<Renderer::Shader_Program>(vertex_string, fragment_string)).first->second;

	if (new_shader->Is_Compiled())
		return new_shader;
	
	std::cerr << "Can't load shader program!!!\n" 
		<< "Vertex:" << vertex_path << "\n"
		<< "Fragment:" << fragment_path << "\n"
		<< std::endl;

	return nullptr;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Renderer::Shader_Program> Resource_Manager::Get_Shader_Program(const std::string& shader_name)
{
	Shader_Programs_Map::const_iterator	it = Shader_Programs.find(shader_name);
	if (it != Shader_Programs.end())
		return it->second;

	std::cerr << "Can't find shader: " << shader_name << std::endl;
	
	return nullptr;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Renderer::Texture2D> Resource_Manager::Load_Texture(const std::string& texture_name, const std::string& texture_path)
{
	int channels = 0;
	int width = 0, height = 0;

	/* Method loads image data from bottom to top */
	stbi_set_flip_vertically_on_load(true);

	unsigned char* pixels = stbi_load(std::string(Path + "/" + texture_path).c_str(), &width, &height, &channels, 0);

	if (!pixels)
	{
		std::cerr << "Can't load texture image file ! " << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::Texture2D> new_texture = Textures.emplace(texture_name, std::make_shared<Renderer::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);

	return new_texture;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Renderer::Texture2D> Resource_Manager::Get_Texture(const std::string& texture_name)
{
	Textures_Map::const_iterator it = Textures.find(texture_name);

	if (it != Textures.end())
		return it->second;

	std::cerr << "Can't find texture: " << texture_name << std::endl;

	return nullptr;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Renderer::Sprite> Resource_Manager::Load_Sprite(const std::string& sprite_name, const std::string& texture_name, const std::string& shader_name, const unsigned int sprite_width, const unsigned int sprite_height)
{
	auto Texture = Get_Texture(texture_name);
	if (!Texture)
	{
		std::cerr << "Can't find the texture: " << texture_name << " for the sprite!" << std::endl;
	}

	auto Shader = Get_Shader_Program(shader_name);
	if (!Shader)
	{
		std::cerr << "Can't find the shader: " << shader_name << " for the sprite!" << std::endl;
	}

	std::shared_ptr<Renderer::Sprite> new_sprite = Sprites.emplace(shader_name, std::make_shared<Renderer::Sprite>(Texture, Shader,glm::vec2(0.0f, 0.0f), glm::vec2(sprite_width, sprite_height))).first->second;

	return new_sprite;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Renderer::Sprite> Resource_Manager::Get_Sprite(const std::string& sprite_name)
{
	Sprite_Map::const_iterator it = Sprites.find(sprite_name);

	if (it != Sprites.end())
		return it->second;

	std::cerr << "Can't find sprites: " << sprite_name << std::endl;

	return nullptr;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::string Resource_Manager::Get_File_String(const std::string& relative_file_path) const
{
	std::ifstream f;
	std::stringstream buffer;

	f.open(Path + "/" + relative_file_path.c_str(), std::ios::in | std::ios::binary);
	
	if (!f.is_open())
	{
		std::cerr << "Failed to open file" << relative_file_path << std::endl;	
		return std::string{};
	}
	buffer << f.rdbuf();
	
	return buffer.str();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

