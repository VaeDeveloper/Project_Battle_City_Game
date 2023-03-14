#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Shader_Program
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace RenderEngine
{
	class Shader_Program;
	class Texture2D;
	class Sprite;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Resource_Manager
{
public: 
	/* No default constructor !!!
	It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
	~Resource_Manager() = delete;
	Resource_Manager() = delete;
	Resource_Manager(const Resource_Manager&) = delete;
	Resource_Manager& operator=(const Resource_Manager&) = delete;
	Resource_Manager& operator=(Resource_Manager&&) = delete;
	Resource_Manager(Resource_Manager&&) = delete;
	/*----------------------------------------------------------------------------------------------------------*/



	/* Functionality */
	/*----------------------------------------------------------------------------------------------------------*/
	/* Set Path resource */
	static void Set_Executable_Path(const std::string& executable_path);
	static void Unload_All_Resources();

	/*   Loading shader with resource project path  shader_name - this name shader vertex_path - vertex_shader.txt fragment_path - fragment_path.txt	*/
	static std::shared_ptr<RenderEngine::Shader_Program> Load_Shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);

	/*	Gettter shader with resource project path.	*/
	static std::shared_ptr<RenderEngine::Shader_Program> Get_Shader_Program(const std::string& shader_name);

	/*  Load Texture 		*/
	static std::shared_ptr<RenderEngine::Texture2D> Load_Texture(const std::string& texture_name, const std::string& texture_path);

	/*	Gettter texture with resource project path.	*/
	static std::shared_ptr<RenderEngine::Texture2D> Get_Texture(const std::string& texture_name);

	/*	Load  sprite with resource project path.	*/
	static std::shared_ptr<RenderEngine::Sprite> Load_Sprite(const std::string& sprite_name, const std::string& texture_name, const std::string& shader_name, const std::string& subtexture_name = "default");

	/*	Gettter texture with resource project path.	*/
	static std::shared_ptr<RenderEngine::Sprite> Get_Sprite(const std::string& sprite_name);

	/* Load Texture Atlas for base texture */
	static std::shared_ptr<RenderEngine::Texture2D> Load_Texture_Atlas(const std::string texture_name, const std::string texture_path, std::vector<std::string> sub_texture, const unsigned subtexture_width, const unsigned subtexture_height);

	/* Load JSON File */
	static bool Load_JSON_Resources(const std::string& json_path);

	/* Getter Levels */
	static const std::vector<std::vector<std::string>> Get_Levels() { return Levels; }
	/*----------------------------------------------------------------------------------------------------------*/


private:
	/* Get String in file */
	static std::string Get_File_String(const std::string& relative_file_path);

	/* Map For Shaders */
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Shader_Program>> Shader_Programs_Map;
	static Shader_Programs_Map Shader_Programs;
	
	/* Map For Textures */
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> Textures_Map;
	static Textures_Map Textures;

	/* Map For Sprite */
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> Sprite_Map;						
	static Sprite_Map Sprites;

	/* Levels Vector str object */
	static std::vector<std::vector<std::string>> Levels;

	/* Path str object */
	static std::string Path;

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
