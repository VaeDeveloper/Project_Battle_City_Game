#include "Resource_Manager.h"
#include "../Renderer/Shader_Program.h"

#include <sstream>
#include <fstream>
#include <iostream>

//---------------------------------------------------------------------------------------------------------------------------------------------
//  Renderer::Shader_Program
//---------------------------------------------------------------------------------------------------------------------------------------------
Resource_Manager::Resource_Manager(const std::string& executable_path)
:Shader_Programs{}, Path{}
{
	size_t found = executable_path.find_last_of("/\\");
	Path = executable_path.substr(0, found);
}
//---------------------------------------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<Renderer::Shader_Program> Resource_Manager::Get_Shader_Program(const std::string& shader_name)
{
	Shader_Programs_Map::const_iterator	it = Shader_Programs.find(shader_name);
	if (it != Shader_Programs.end())
		return it->second;

	std::cerr << "Can't find shader: " << shader_name << std::endl;
	
	return nullptr;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------------------------------------
