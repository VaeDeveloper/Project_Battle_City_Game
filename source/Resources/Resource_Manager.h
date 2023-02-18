#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

namespace Renderer
{
	class Shader_Program;
	class Texture2D;
	class Sprite;
	class Animated_Sprite;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Shader_Program
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Resource_Manager
{
public:
	//================================================================================================================================================================================================================
	// Constructors and Destructors
	~Resource_Manager() = default;

	/*	Use the actual constructor for this class */
	Resource_Manager(const std::string& executable_path);

	/*	It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
	Resource_Manager(const Resource_Manager&) = delete;
	Resource_Manager& operator=(const Resource_Manager&) = delete;
	Resource_Manager& operator=(Resource_Manager&&) = delete;
	Resource_Manager(Resource_Manager&&) = delete;
	//================================================================================================================================================================================================================




	//================================================================================================================================================================================================================
	//	 Public Methods
	/*   Loading shader with resource project path  shader_name - this name shader vertex_path - vertex_shader.txt fragment_path - fragment_path.txt	*/
	std::shared_ptr<Renderer::Shader_Program> Load_Shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);

	/*	Gettter shader with resource project path.	*/
	std::shared_ptr<Renderer::Shader_Program> Get_Shader_Program(const std::string& shader_name);

	/*  Load Texture Method		*/
	std::shared_ptr<Renderer::Texture2D> Load_Texture(const std::string& texture_name, const std::string& texture_path);

	/*	Gettter texture with resource project path.	*/
	std::shared_ptr<Renderer::Texture2D> Get_Texture(const std::string& texture_name);

	/*	Load  sprite with resource project path.	*/
	std::shared_ptr<Renderer::Sprite> Load_Sprite(const std::string& sprite_name, const std::string& texture_name, const std::string& shader_name, const unsigned int sprite_width, const unsigned int sprite_height, const std::string& subtexture_name = "default");

	/*	Gettter texture with resource project path.	*/
	std::shared_ptr<Renderer::Sprite> Get_Sprite(const std::string& sprite_name);

	/*	Load  animated sprite with resource project path.	*/
	std::shared_ptr<Renderer::Animated_Sprite> Load_Animated_Sprite(const std::string& sprite_name, const std::string& texture_name, const std::string& shader_name, const unsigned int sprite_width, const unsigned int sprite_height, const std::string& subtexture_name = "default");

	/*	Gettter animated sprite with resource project path.	*/
	std::shared_ptr<Renderer::Animated_Sprite> Get_Animated_Sprite(const std::string& sprite_name);



	/* Load Texture Atlas for base texture */
	std::shared_ptr<Renderer::Texture2D> Load_Texture_Atlas(const std::string texture_name, const std::string texture_path, std::vector<std::string> sub_texture, const unsigned subtexture_width, const unsigned subtexture_height);

	//================================================================================================================================================================================================================


private:
	//================================================================================================================================================================================================================
	// Private Methods
	std::string Get_File_String(const std::string& relative_file_path) const;



	//================================================================================================================================================================================================================
	// Private Variables
	/* Map For Shaders */
	typedef std::map<const std::string, std::shared_ptr<Renderer::Shader_Program>> Shader_Programs_Map;
	Shader_Programs_Map Shader_Programs;
	
	/* Map For Textures*/
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> Textures_Map;
	Textures_Map Textures;

	/* Map For Sprite */
	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> Sprite_Map;
	Sprite_Map Sprites;

	/* Map For Animated Sprite */
	typedef std::map<const std::string, std::shared_ptr<Renderer::Animated_Sprite>> Animated_Sprite_Map;
	Animated_Sprite_Map Animated_Sprites;

	std::string Path;
	//================================================================================================================================================================================================================

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
