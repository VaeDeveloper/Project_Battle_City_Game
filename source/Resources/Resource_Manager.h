#pragma once


#include <string>
#include <memory>
#include <map>

namespace Renderer
{
	class Shader_Program;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Shader_Program
//---------------------------------------------------------------------------------------------------------------------------------------------
class Resource_Manager
{
public:
	~Resource_Manager() = default;

	/* Use the actual constructor for this class */
	Resource_Manager(const std::string& executable_path);


	/* It is forbidden to use a constructor without parameters and a constructor with a parameter of this class*/
	Resource_Manager(const Resource_Manager&) = delete;
	Resource_Manager& operator=(const Resource_Manager&) = delete;
	Resource_Manager& operator=(Resource_Manager&&) = delete;
	Resource_Manager(Resource_Manager&&) = delete;



	//---Loading shader with resource project path.--------------------------------------------------------//
	//-----------shader_name - this name shader------------------------------------------------------------//
	//-----------vertex_path - vertex_shader.txt-----------------------------------------------------------//
	//-----------fragment_path - fragment_path.txt---------------------------------------------------------//
	std::shared_ptr<Renderer::Shader_Program> Load_Shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);

	//---Gettter shader with resource project path.--------------------------------------------------------//
	std::shared_ptr<Renderer::Shader_Program> Get_Shader_Program(const std::string& shader_name);

private:
	std::string Get_File_String(const std::string& relative_file_path) const;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Shader_Program>> Shader_Programs_Map;
	Shader_Programs_Map Shader_Programs;

	std::string Path;

};
//---------------------------------------------------------------------------------------------------------------------------------------------
